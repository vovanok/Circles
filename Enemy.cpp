#include "Enemy.h"
#include "GameEnviroment.h"

void Enemy::Update(float deltaTime) {
	if (gameEnv != nullptr) {
		//Check walls collision
		float xMax = gameEnv->width() / 2.0f;
		if (x + Radius >= xMax) {
			x = xMax - Radius;
			velocityX = -velocityX;
		}
		
		float xMin = -gameEnv->width() / 2.0f;
		if (x - Radius <= xMin) {
			x = xMin + Radius;
			velocityX = -velocityX;
		}

		float yMax = gameEnv->height() / 2.0f;
		if (y + Radius >= yMax) {
			y = yMax - Radius;
			velocityY = -velocityY;
		}
		
		float yMin = -gameEnv->height() / 2.0f;
		if (y - Radius <= yMin) {
			y = yMin + Radius;
			velocityY = -velocityY;
		}
	}

	//Update coordinates
	x += velocityX * deltaTime;
	y += velocityY * deltaTime;
}

void Enemy::Draw(float detaTime) {
	Update(detaTime);
	
	GraphicUtils::DrawFillCircle(x, y, Radius, Color(0.8f, 0.8f, 0.8f, 1.0f), BodyColor);
}

void Enemy::Impact(char keyCode, int button, int state, int x, int y) {
}

float Enemy::CentersDistance(const Enemy& enemy) {
	return sqrtf(powf(x - enemy.x, 2.0f) + powf(y - enemy.y, 2.0f));
}

bool Enemy::IsCollide(const Enemy& enemy) {
	return CentersDistance(enemy) <= (Radius + enemy.Radius);
}

void Enemy::Absorb(Enemy& enemy) {
	Radius = sqrtf(powf(Radius, 2.0f) + powf(enemy.Radius, 2.0f));

	if (gameEnv == nullptr)
		return;

	float maxRadius = std::min(gameEnv->width(), gameEnv->height()) / 2.0f;
	Radius = Radius <= maxRadius ? Radius : maxRadius;

	UpdateColor();
}

void Enemy::UpdateColor() {
	if (gameEnv == nullptr)
		return;

	BodyColor = gameEnv->GetCurrentPalette().GetColor(Radius);
}