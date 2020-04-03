#pragma once
namespace game_framework {
	class CDifferentTime {
	public:
		bool Delay(int ms);
	private:
		time_t tstart = 0, tend = 0;
	};

}