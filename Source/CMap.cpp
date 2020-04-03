#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CMap.h"
#include <fstream>
#include <string>
namespace game_framework {
	
	CGameMap::CGameMap()
		: sx(0), sy(0), MW(1200), MH(900)
	{
		Initialize();
	}
	void CGameMap::LoadBitMap()
	{
		map.LoadBitmap(IDB_MAP);
	}
	void CGameMap::OnShow()
	{
		map.SetTopLeft(-sx, -sy);
		map.ShowBitmap();		
	}
	void CGameMap::OnMove()
	{
		if (isLeft && sx>0)
			sx -= 5;
		if (isRight && sx<175)
			sx += 5;
		if (isDown && sy < 130)
			sy += 5;
		if (isUp && sy > 0)
			sy -= 5;

	}
	int CGameMap::ScreenX(int x)
	{
		return (x - sx);
	}
	int CGameMap::ScreenY(int y)
	{
		return (y - sy);
	}
	void CGameMap::SetIsleft(bool flag)
	{
		isLeft = flag;
	}
	void CGameMap::SetIsRight(bool flag)
	{
		isRight = flag;
	}
	void CGameMap::SetIsDown(bool flag)
	{
		isDown = flag;
	}
	void CGameMap::SetIsUp(bool flag)
	{
		isUp = flag;
	}
	void CGameMap::SetValue(int x, int y, char value)
	{
		unsigned int sx = (int)(x / 30);
		unsigned int sy = (int)(y / 30);
		if (sy < data.size() && sx < data[0].size())
			data[sy][sx] = value;
	}
	void CGameMap::Initialize()
	{
		fstream file;
		string value;
		file.open("bmp/map/map.txt");
		GAME_ASSERT(file.is_open(), "failed to open txt");
		if (file)
		{
			while (getline(file, value))
			{
				vector<char>line(value.begin(), value.end());
				data.push_back(line);
			}

		}
		file.close();
	}
	int CGameMap::IsEmpty(int x, int y)
	{
		unsigned int sx = x / 30;
		unsigned int sy = y / 30;
		if (sy < data.size() && sx < data[0].size())
			return data[sy][sx] - '0';
		else
			return 1;
	}
}