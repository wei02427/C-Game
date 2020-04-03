#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <stack>
#include <array>
#include "CMap.h"
#include "aStar.h"
namespace game_framework {
	bool Cordinate::isValid(int x, int y, CGameMap & map)
	{
		int value = map.IsEmpty(x * 30, y * 30);
		if (value == 0 || value == 3 || value == 4) {
			if (x < 0 || y < 0 || x >= (X_MAX / X_STEP) || y >= (Y_MAX / Y_STEP)) {
				return false;
			}
			return true;
		}
		return false;
	}
	bool Cordinate::isDestination(int x, int y, Node dest)
	{
		if (x == dest.x && y == dest.y) {
			return true;
		}
		return false;
	}
	double Cordinate::calculateH(int x, int y, Node dest)
	{
		double H = (sqrt((x - dest.x)*(x - dest.x)
			+ (y - dest.y)*(y - dest.y)));
		return H;
	}
	vector<Node> Cordinate::makePath(array<array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest)
	{
		try {
			int x = dest.x;
			int y = dest.y;
			stack<Node> path;
			vector<Node> usablePath;

			while (!(map[x][y].parentX == x && map[x][y].parentY == y)
				&& map[x][y].x != -1 && map[x][y].y != -1)
			{
				path.push(map[x][y]);
				int tempX = map[x][y].parentX;
				int tempY = map[x][y].parentY;
				x = tempX;
				y = tempY;

			}
			path.push(map[x][y]);

			while (!path.empty()) {
				Node top = path.top();
				path.pop();
				//cout << top.x << " " << top.y << endl;
				usablePath.emplace_back(top);
			}
			//TRACE("Found a path \n");
			return usablePath;
		}
		catch (const exception& e) {
			//TRACE( e.what() );
		}
	}
	vector<Node> Cordinate::aStar(Node player, Node dest, CGameMap & map)
	{
		vector<Node> empty;
		if (isValid(dest.x, dest.y, map) == false) {
			//TRACE("Destination is an obstacle\n");
			return empty;
			//終點是障礙物
		}
		if (!(isValid(dest.x - 1, dest.y, map) || isValid(dest.x + 1, dest.y, map) ||
			isValid(dest.x, dest.y + 1, map) || isValid(dest.x, dest.y - 1, map))) {
			//TRACE("Plaler is in obstacle\n");
			return empty;
			//終點被包住
		}
		if (isDestination(player.x, player.y, dest)) {
			//TRACE("You are the destination\n");
			//dest.x += 1;
			return empty;
			//終點是自己
		}
		bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];	//初始化關閉列表

		//初始化整張地圖
		array<array < Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap;
		for (int x = 0; x < (X_MAX / X_STEP); x++) {
			for (int y = 0; y < (Y_MAX / Y_STEP); y++) {
				allMap[x][y].fCost = FLT_MAX;
				allMap[x][y].gCost = FLT_MAX;
				allMap[x][y].hCost = FLT_MAX;
				allMap[x][y].parentX = -1;
				allMap[x][y].parentY = -1;
				allMap[x][y].x = x;
				allMap[x][y].y = y;

				closedList[x][y] = false;
			}
		}
		//------------1.把起始格加入「開啟列表」----------------
		//設定起點
		int x = player.x;
		int y = player.y;
		allMap[x][y].fCost = 0.0;
		allMap[x][y].gCost = 0.0;
		allMap[x][y].hCost = 0.0;
		allMap[x][y].parentX = x;
		allMap[x][y].parentY = y;

		vector<Node> openList;
		openList.emplace_back(allMap[x][y]);
		bool destinationFound = false;
		bool isNULL = true;
		//------------2.重複如下的工作----------------
		while (!openList.empty() && openList.size() < (X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
			Node node;
			do {
				//尋找開啟列表中F值最低的格子。我們稱它為「當前格」。
				float temp = FLT_MAX;
				vector<Node>::iterator itNode;
				isNULL = true;
				for (vector<Node>::iterator it = openList.begin();
					it != openList.end(); it = next(it)) {
					Node n = *it;
					if (n.fCost < temp) {
						temp = n.fCost;
						itNode = it;
						//GAME_ASSERT(false, "fkkk");
						isNULL = false;
					}
				}

				if (!isNULL) {
					node = *itNode;
					openList.erase(itNode);
				}

			} while (!isNULL && isValid(node.x, node.y, map) == false);

			x = node.x;
			y = node.y;
			closedList[x][y] = true; //把它(當前格)存入「關閉列表」。

			//對相鄰的8格中的每一格：
			bool vaildX = true, vaildY = true, vaild = true;
			for (int newX = -1; newX <= 1; newX++) {
				for (int newY = -1; newY <= 1; newY++) {
					float gNew, hNew, fNew;
					if (isValid(x + newX, y + newY, map)) {
						if (abs(newX) - abs(newY) == 0)
						{
							if (newX == -1)
								vaildX = isValid(x + newX + 1, y + newY, map);
							else if (newX == 1)
								vaildX = isValid(x + newX - 1, y + newY, map);
							if (newY == -1)
								vaildY = isValid(x + newX, y + newY + 1, map);
							else if (newY == 1)
								vaildY = isValid(x + newX, y + newY - 1, map);
							vaild = vaildX && vaildY;
						}
						else {
							/*if (!isValid(x + newX + 2, y + newY, map) || !isValid(x + newX, y + newY + 1, map))
								vaild = false;
							else*/
							vaild = true;
						}
					}
					if (vaild && isValid(x + newX, y + newY, map)) {				//如果它可通過
						if (isDestination(x + newX, y + newY, dest))	//找到終點，執行makePath
						{
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							destinationFound = true;
							return makePath(allMap, dest);
						}
						else if (closedList[x + newX][y + newY] == false)	//如果它不在關閉列表中
						{
							//把當前格作為這一格的父節點。記錄這一格的F, G和H值。
							gNew = (float)node.gCost + 1;
							hNew = (float)calculateH(x + newX, y + newY, dest);
							fNew = gNew + hNew;
							// 如果它不在開啟列表中或是新的路徑是否更好
							if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
								allMap[x + newX][y + newY].fCost > fNew)
							{
								//就把這一格的父節點改成當前格，並更新F, G和H值。
								allMap[x + newX][y + newY].fCost = fNew;
								allMap[x + newX][y + newY].gCost = gNew;
								allMap[x + newX][y + newY].hCost = hNew;
								allMap[x + newX][y + newY].parentX = x;
								allMap[x + newX][y + newY].parentY = y;
								openList.emplace_back(allMap[x + newX][y + newY]);
								//添加到開啟列表
							}
						}
					}
				}
			}
		}
		if (destinationFound == false) {
			//TRACE("Destination not found\n");
			return empty;
		}
	}
}