#pragma once
#include "ColorPalette.h"

namespace Config {
	Color PlayerColor();
	Color BeginEnemyColor();
	Color EndEnemyColor();
	size_t EnemyCount();
	float StressTimeFactor();
	float EnviromentDecelerationPerSec();
	float PlayerStartRadius();
};