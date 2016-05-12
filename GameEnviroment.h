#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iomanip>
#include "IPresentable.h"
#include "Player.h"
#include "GraphicUtils.h"
#include "Config.h"

class Enemy;

class GameEnviroment : public IPresentable {
public:
	Color MinEnemyColor, MaxEnemyColor;

	GameEnviroment()
		: _width(0.0f), _height(0.0f), player(nullptr),
			borderColor(Color(1.0f, 1.0f, 1.0f, 1.0f)),
			backgroundColor(Color(0.0f, 0.0f, 0.0f, 1.0f)),
			isGameWin(false), isGameFail(false) { }

	GameEnviroment(float fieldWidth, float fieldHeight)
		: _width(fieldWidth), _height(fieldHeight), player(nullptr),
			borderColor(Color(1.0f, 1.0f, 1.0f, 1.0f)),
			backgroundColor(Color(0.0f, 0.0f, 0.0f, 1.0f)),
			isGameWin(false), isGameFail(false) { }

	GameEnviroment(float fieldWidth, float fieldHeight, Color borderColor, Color backgroundColor)
		: _width(fieldWidth), _height(fieldHeight), player(nullptr),
			borderColor(borderColor), backgroundColor(backgroundColor),
			isGameWin(false), isGameFail(false) { }

	~GameEnviroment();

	float width() const { return _width; }
	float height() const { return _height; }

	void AddEnemy(Enemy* enemy);
	void SetPlayer(Player* player);
	Player* GetPlayer();
	void Erase();

	virtual void Draw(float deltaTime);
	virtual void Impact(char keyCode, int button, int state, int x, int y);

	void GameFail();
	ColorPalette GetCurrentPalette();

private:
	std::vector<Enemy*> enemies;
	Player* player;
	Color borderColor, backgroundColor;
	
	float _width, _height;

	bool isGameWin;
	bool isGameFail;

	void Update(float deltaTime);
	void CheckEndGame();
	void EnemyAbsorbsDetect();
	void UpdateEnemiesColors();
};