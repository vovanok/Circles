#include "Player.h"

void Player::Impact(char keyCode, int button, int state, int x, int y) {
	if (state == 0) {
		beginStressTime = clock();
	} else if (state == 1) {
		endStressTime = clock();
		
		float stressTime = float(endStressTime - beginStressTime) / CLOCKS_PER_SEC;
		if (stressTime < 0.0f)
			stressTime = 0.0f;

		Impulse(stressTime, x, y);
	}
}

void Player::Update(float deltaTime) {
	Enemy::Update(deltaTime);
	float decelerationFactor = 1.0f - (1.0f - Config::EnviromentDecelerationPerSec()) * deltaTime;
	velocityX *= decelerationFactor;
	velocityY *= decelerationFactor;
}

void Player::Impulse(float stressTime, float stressX, float stressY) {
	velocityX = (x - stressX) * stressTime * Config::StressTimeFactor();
	velocityY = (y - stressY) * stressTime * Config::StressTimeFactor();
}

Player::~Player() {
	if (OnDie)
		OnDie();
}

void Player::Absorb(Enemy& enemy) {
	Enemy::Absorb(enemy);
	
	if (OnAbsorbEnemy)
		OnAbsorbEnemy();
}