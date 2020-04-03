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
			//���I�O��ê��
		}
		if (!(isValid(dest.x - 1, dest.y, map) || isValid(dest.x + 1, dest.y, map) ||
			isValid(dest.x, dest.y + 1, map) || isValid(dest.x, dest.y - 1, map))) {
			//TRACE("Plaler is in obstacle\n");
			return empty;
			//���I�Q�]��
		}
		if (isDestination(player.x, player.y, dest)) {
			//TRACE("You are the destination\n");
			//dest.x += 1;
			return empty;
			//���I�O�ۤv
		}
		bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];	//��l�������C��

		//��l�ƾ�i�a��
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
		//------------1.��_�l��[�J�u�}�ҦC��v----------------
		//�]�w�_�I
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
		//------------2.���Ʀp�U���u�@----------------
		while (!openList.empty() && openList.size() < (X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
			Node node;
			do {
				//�M��}�ҦC��F�ȳ̧C����l�C�ڭ̺٥����u��e��v�C
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
			closedList[x][y] = true; //�⥦(��e��)�s�J�u�����C��v�C

			//��۾F��8�椤���C�@��G
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
					if (vaild && isValid(x + newX, y + newY, map)) {				//�p�G���i�q�L
						if (isDestination(x + newX, y + newY, dest))	//�����I�A����makePath
						{
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							destinationFound = true;
							return makePath(allMap, dest);
						}
						else if (closedList[x + newX][y + newY] == false)	//�p�G�����b�����C��
						{
							//���e��@���o�@�檺���`�I�C�O���o�@�檺F, G�MH�ȡC
							gNew = (float)node.gCost + 1;
							hNew = (float)calculateH(x + newX, y + newY, dest);
							fNew = gNew + hNew;
							// �p�G�����b�}�ҦC���άO�s�����|�O�_��n
							if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
								allMap[x + newX][y + newY].fCost > fNew)
							{
								//�N��o�@�檺���`�I�令��e��A�ç�sF, G�MH�ȡC
								allMap[x + newX][y + newY].fCost = fNew;
								allMap[x + newX][y + newY].gCost = gNew;
								allMap[x + newX][y + newY].hCost = hNew;
								allMap[x + newX][y + newY].parentX = x;
								allMap[x + newX][y + newY].parentY = y;
								openList.emplace_back(allMap[x + newX][y + newY]);
								//�K�[��}�ҦC��
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