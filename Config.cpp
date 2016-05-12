#include "Config.h"

Color Config::PlayerColor() {
	return Color(0.5f, 0.5f, 0.5f, 1.0f);
}

Color Config::BeginEnemyColor() {
	return Color(0.4f, 0.4f, 1.0f, 1.0f);
}

Color Config::EndEnemyColor() {
	return Color(1.0f, 0.4f, 0.4f, 1.0f);
}

size_t Config::EnemyCount() {
	return 50;
}

float Config::StressTimeFactor() {
	return 0.8f;
}

float Config::EnviromentDecelerationPerSec() {
	return 0.7f;
}

float Config::PlayerStartRadius() {
	return 4.3f;
}