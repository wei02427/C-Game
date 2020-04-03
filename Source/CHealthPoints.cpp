#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHealthPoints.h"


namespace game_framework {
	CHealthPoints::CHealthPoints(int width,int height,int frameColor,int bkColor,int bloodColor):bar_width(width),bar_height(height),frame(frameColor),background(bkColor),blood(bloodColor)
	{
	}
	void CHealthPoints::ShowHP(int x, int y, int percent)
	{
		const int x1 = x;
		const int x2 = x1 + bar_width;
		const int y1 = y;
		const int y2 = y1 + bar_height;
		const int pen_width = bar_height / 8;
		const int progress_x1 = x1 + pen_width;
		const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / 100;
		const int progress_x2_end = x2 - pen_width;
		const int progress_y1 = y1 + pen_width;
		const int progress_y2 = y2 - pen_width;
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 

		CBrush *pb, b(frame);				// 畫 progress框
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(x1, y1, x2, y2);
		CBrush b1(background);				// 畫 progrss中心
		pDC->SelectObject(&b1);
		pDC->Rectangle(progress_x1, progress_y1, progress_x2_end, progress_y2);

		CBrush b2(blood);					// 畫 progrss進度
		pDC->SelectObject(&b2);
		pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);

		pDC->SelectObject(pb);						// 釋放 brush
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		
	}


}

