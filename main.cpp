#include <iostream>
#include "GameEnviroment.h"
#include "GraphicMgr.h"
#include "Config.h"

const float SCENE_WIDTH = 200.0f;
const float SCENE_HEIGHT = 100.0f;
const float SCENE_DEADZONE_FOR_START = 5.0f;
const float MIN_START_ENEMY_RADIUS = 1.0f;
const float MAX_START_ENEMY_RADIUS = 6.0f;
const float VELOCITY_MIN = -2.0f;
const float VELOCITY_MAX = 2.0f;

GameEnviroment gameEnviroment;

void StartPause();
void CloseApplication();
void PreDrawHandler(float deltaTime);
float RandomFloatInRange(float rangeBegin, float rangeEnd);
void RestartGame();

int main(int argc, char** argv) {
	RestartGame();

	GraphicMgr::CreateWindow(argc, argv, "SQ_cpp_test", 200, 100, 1000, 500);
	GraphicMgr::SetVisibilityArea(-110, 110, 55, -55);
	GraphicMgr::AddPresentObj(dynamic_cast<IPresentable *>(&gameEnviroment));

	GraphicMgr::AddUpdateKeyboardHandler('0', CloseApplication);
	std::cout	<< "0 - close application" << std::endl;

	GraphicMgr::AddUpdateKeyboardHandler("RrÊê", RestartGame);
	std::cout	<< "R - restart game" << std::endl;

	GraphicMgr::AddUpdateKeyboardHandler("PpÇç", StartPause);
	std::cout	<< "P - start / pause" << std::endl;
	
	GraphicMgr::Run();
}

void StartPause() {
	GraphicMgr::StartStopAnimation();
}

void CloseApplication() {
	GraphicMgr::DestroyWindow();
	exit(0);
}

void RestartGame() {
	gameEnviroment.Erase();
	gameEnviroment = GameEnviroment(
		SCENE_WIDTH, SCENE_HEIGHT, Color(1.0f, 1.0f, 1.0f, 1.0f), Color(0.2f, 0.32f, 0.46f, 1.0f));

	for (size_t i = 0; i < Config::EnemyCount(); i++) {
		float radius = RandomFloatInRange(MIN_START_ENEMY_RADIUS, MAX_START_ENEMY_RADIUS);

		float x = RandomFloatInRange(-SCENE_WIDTH / 2.0f + SCENE_DEADZONE_FOR_START + radius,
																	SCENE_WIDTH / 2.0f - SCENE_DEADZONE_FOR_START - radius);
		float y = RandomFloatInRange(-SCENE_HEIGHT / 2.0f + SCENE_DEADZONE_FOR_START + radius,
																	SCENE_HEIGHT / 2.0f - SCENE_DEADZONE_FOR_START - radius);

		float velocityX = RandomFloatInRange(VELOCITY_MIN, VELOCITY_MAX);
		float velocityY = RandomFloatInRange(VELOCITY_MIN, VELOCITY_MAX);

		gameEnviroment.AddEnemy(new Enemy(x, y, radius, Color(1.0f, 0.0f, 0.0f, 1.0f), velocityX, velocityY, &gameEnviroment));
	}

	gameEnviroment.SetPlayer(new Player(0.0f, 0.0f, Config::PlayerStartRadius(), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0.0f, &gameEnviroment));
}

float RandomFloatInRange(float rangeBegin, float rangeEnd) {
	return rangeBegin + float(rand()) / float(RAND_MAX / (rangeEnd - rangeBegin));
}