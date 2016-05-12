#include "GameEnviroment.h"
#include "Enemy.h"

GameEnviroment::~GameEnviroment() {
	Erase();
}

void GameEnviroment::Update(float deltaTime) {
	EnemyAbsorbsDetect();
	
	for (auto enemy : enemies) {
		if (enemy != nullptr) {
			enemy->Update(deltaTime);
		}
	}

	CheckEndGame();
}

void GameEnviroment::Draw(float deltaTime) {
	Update(deltaTime);

	//Walls
	GraphicUtils::DrawFillRectangle(-width() / 2.0f, -height() / 2.0f, width(), height(), borderColor, backgroundColor);

	//Enemies
	for (auto enemy : enemies) {
		if (enemy != nullptr) {
			enemy->Draw(deltaTime);	
		}
	}

	if (isGameWin) {
		GraphicUtils::DrawText(-40.0f, 0.0f, 0.1f, 0.1f, "You Win!");
		GraphicUtils::DrawText(-40.0f, -10.0f, 0.05f, 0.05f, "R to restart, 0 to exit");
	} else if (isGameFail) {
		GraphicUtils::DrawText(-40.0f, 0.0f, 0.1f, 0.1f, "You Fail!");
		GraphicUtils::DrawText(-40.0f, -10.0f, 0.05f, 0.05f, "R to restart, 0 to exit");
	}

	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) <<	(1.0f / deltaTime) << " fps";
	GraphicUtils::DrawText(-109.0f, 51.0f, 0.025f, 0.025f, ss.str());

	GraphicUtils::DrawText(-90.0f, 51.0f, 0.025f, 0.025f, "P - pause/start; R - restart game; 0 - exit");
}

void GameEnviroment::Impact(char keyCode, int button, int state, int x, int y) {
	for (auto enemy : enemies) {
		if (enemy != nullptr) {
			enemy->Impact(keyCode, button, state, x, y);
		}
	}
}

void GameEnviroment::CheckEndGame() {
	isGameWin = true;
	isGameFail = true;

	for(Enemy* enemy : enemies) {
		if (player == enemy)
			continue;

		if (enemy->Radius >= player->Radius) {
			isGameWin = false;
		} else {
			isGameFail = false;
		}
	}
}

void GameEnviroment::EnemyAbsorbsDetect() {
	std::vector<size_t> enemiesDelInds;
	for (size_t i = 0; i < enemies.size(); i++) {
		for (size_t j = 0; j < i; j++) {
			if ((std::find(enemiesDelInds.begin(), enemiesDelInds.end(), i) != enemiesDelInds.end()) ||
					(std::find(enemiesDelInds.begin(), enemiesDelInds.end(), j) != enemiesDelInds.end()) ||
					(!enemies[i]->IsCollide(*enemies[j])))
				continue;

			if (enemies[i]->Radius <= enemies[j]->Radius) {
				enemiesDelInds.push_back(i);
				enemies[j]->Absorb(*enemies[i]);
			} else {
				enemiesDelInds.push_back(j);
				enemies[i]->Absorb(*enemies[j]);
			}
		}
	}
	
	std::sort(enemiesDelInds.begin(), enemiesDelInds.end(), std::greater<int>());
	for (int ind : enemiesDelInds) {
		delete enemies[ind];
		enemies.erase(enemies.begin() + ind);
	}
}

void GameEnviroment::AddEnemy(Enemy* enemy) {
	enemies.push_back(enemy);
}

void GameEnviroment::SetPlayer(Player* player) {
	enemies.push_back(player);
	this->player = player;
	player->OnDie = std::bind(std::mem_fun(&GameEnviroment::GameFail), this);
	player->OnAbsorbEnemy = std::bind(std::mem_fun(&GameEnviroment::UpdateEnemiesColors), this);

	UpdateEnemiesColors();
}

void GameEnviroment::Erase() {
	for (Enemy* enemy : enemies) {
		delete enemy;
	}

	enemies.clear();
}

ColorPalette GameEnviroment::GetCurrentPalette() {
	Color beginColor;
	Color endColor;
	float beginValue;
	float endValue;

	if (player == nullptr) {
		beginColor = endColor = Config::EndEnemyColor();
		beginValue = endValue = 0.0f;
	} else {
		beginColor = Config::BeginEnemyColor();
		endColor = Config::EndEnemyColor();
		beginValue = player->Radius - 5.0f;
		endValue = player->Radius + 5.0f;
	}

	return ColorPalette(beginColor, endColor, beginValue, endValue);
}

void GameEnviroment::GameFail() {
	isGameWin = false;
	isGameFail = true;
}

void GameEnviroment::UpdateEnemiesColors() {
	for (auto enemy : enemies) {
		if (enemy != nullptr) {
			enemy->UpdateColor();
		}
	}
}