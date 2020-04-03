#ifndef ASTAR_H
#define ASTAR_H
#pragma once
#define X_MAX 1200
#define X_STEP 30
#define Y_MAX 900
#define Y_STEP 30
namespace game_framework {
	struct Node
	{
		int y;
		int x;
		int parentX;
		int parentY;
		float gCost;
		float hCost;
		float fCost;
	};

	inline bool operator < (const Node& lhs, const Node& rhs)
	{//We need to overload "<" to put our struct into a set
		return lhs.fCost < rhs.fCost;
	}

	class CGameMap;
	class Cordinate {
	public:
		static vector<Node> aStar(Node player, Node dest, CGameMap &map); //aStar�t��k
	private:
		static bool isValid(int x, int y, CGameMap &map); //�P�_�`�I�O�_����ê��
		static bool isDestination(int x, int y, Node dest); //�P�_�`�I�O�_�����I
		static double calculateH(int x, int y, Node dest); //�p��h(���~����)��e��ܲ��I�Z��
		static vector<Node> makePath(array<array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest); //��X�̲׸��|
	
	};
}
#endif