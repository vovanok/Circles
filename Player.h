#pragma once
#include <iostream>
#include <ctime>
#include <functional>
#include "Enemy.h"
#include "Config.h"

class GameEnviroment;

class Player : public Enemy {
public:
	std::function<void()> OnDie;
	std::function<void()> OnAbsorbEnemy;

	Player()
		: Enemy() { }
	Player(float x, float y, float radius, Color color,
		float velocityX, float velocityY, GameEnviroment* gameEnviroment)
		: Enemy(x, y, radius, color, velocityX, velocityY, gameEnviroment) { }
	virtual ~Player();

	virtual void Impact(char keyCode, int button, int state, int x, int y);
	virtual void Update(float deltaTime);

	virtual void Absorb(Enemy& enemy);
	virtual void UpdateColor() { }

protected:
	clock_t beginStressTime;
	clock_t endStressTime;

	void Impulse(float stressTime, float stressX, float stressY);
};