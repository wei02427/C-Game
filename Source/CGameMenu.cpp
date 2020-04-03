#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMenu.h"
#include "CDifferentTime.h"
namespace game_framework {
	CGameMenu::CGameMenu():x(0), y(0), timer(new CDifferentTime()),page(0){}
	void CGameMenu::LoadBitMap()
	{ 
		int bitmap[7] = { IDB_MENU,IDB_INTRODUCE,IDB_HOWTOPLAY1,IDB_HOWTOPLAY2 ,IDB_HOWTOPLAY3,IDB_GAMEOVER,IDB_MENU_SUCCESS };
		for (int i = 0; i < 7; i++) {
			menu[i].LoadBitmapA(bitmap[i]);
		}
		select[0].LoadBitmapA(IDB_MENU_SELECT,RGB(255,242,0));
		select[1].LoadBitmapA(IDB_HOW_SELECT, RGB(255, 242, 0));
		select[0].SetTopLeft(786.5, 322);
		select[1].SetTopLeft(19, 678);
	}

	void CGameMenu::OnShow(bool result)
	{
		
		if (page == 5)
			page += result;
		menu[page].SetTopLeft(0, 0);
		menu[page].ShowBitmap();
		static bool flicker = false;
		if (timer->Delay(700))
			flicker = !flicker;
		if (flicker)
			if(page==0)
				select[0].ShowBitmap();
			else
				select[1].ShowBitmap(1.01);
	}

	int CGameMenu::SwitchMenu(UINT nChar)
	{
		if (nChar == KEY_DOWN || nChar == KEY_UP)
		{
			CAudio::Instance()->Play(AUDIO_SELECT, false);
		}
		if (nChar == KEY_SPACE)
		{
			CAudio::Instance()->Play(AUDIO_ENTER, false);
		}
		if (page == 0) {
			static int i = 0;
			
			if (nChar == KEY_DOWN && i+1<=2)
				i++;
			else if (nChar == KEY_UP && i - 1 >= 0)
				i--;
			if (i == 2)
				select[0].SetTopLeft(786.5, 322 + i * 121);
			else
				select[0].SetTopLeft(784, 322 +i*121);

			if (nChar == KEY_SPACE) {
				switch (i)
				{
				case 0:
					select[1].SetTopLeft(768  , 678);
					page = 2;
					break;
				case 1:
					page = 5;
					select[1].SetTopLeft(118 , 660);
					select[0].SetTopLeft(786.5, 322);
					i = 0;
					return true;
				case 2:
					select[1].SetTopLeft(770, 678);
					page = 1;
					break;
				}
			}
		}
		else if (page==5 || page==6){
			static int i = 0;
			if (nChar == KEY_RIGHT && i + 1 <= 1)
				i++;
			else if (nChar == KEY_LEFT && i - 1 >= 0)
				i--;

			select[1].SetTopLeft(118 + i * 592, 660);
			if (nChar == KEY_SPACE) {
				switch (i)
				{
				case 0:
					page = 0;
					return true;
				case 1:
					return false;

				}
			}
		}
		else {
			if (page == 1) {
				select[1].SetTopLeft(770, 678);
				if (nChar == KEY_SPACE)
					page = 0;
			}
			else {
				static int i = 1;
				if (nChar == KEY_RIGHT && i + 1 <= 1)
					i++;
				else if (nChar == KEY_LEFT && i - 1 >= 0)
					i--;

				select[1].SetTopLeft(19 +i*749, 678 );
				if (nChar == KEY_SPACE) {
					switch (i)
					{
					case 0:
						if (page != 2)
							page--;
						else {
							i = 1;
							page = 0;
						}
						break;
					case 1:
						if (page != 4)
							page++;
						else
							//i = 1;
							page = 0;
						break;

					}
				}
			}
		}
		if (page != 5 && page != 6)
			return false;
		else
			return 3;
	}



	CGameMenu::~CGameMenu()
	{
		delete timer;
	}



	

}
