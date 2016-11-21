#pragma once
#include "IPresentable.h"
#include "ColorPalette.h"

class GameEnviroment;

class Enemy : public IPresentable {
public:
	float Radius;
	Color BodyColor;

	Enemy()
		: x(0.0f), y(0.0f), Radius(0.0f), BodyColor(Color(1.0f, 1.0f, 1.0f, 1.0f)),
			velocityX(0.0f), velocityY(0.0f), gameEnv(nullptr) { }
	
	Enemy(float x, float y, float radius, Color color,
				float velocityX, float velocityY, GameEnviroment* gameEnviroment)
		: x(x), y(y), Radius(radius), BodyColor(color),
			velocityX(velocityX), velocityY(velocityY), gameEnv(gameEnviroment) { }

	virtual ~Enemy() { }

	virtual void Update(float deltaTime);

	virtual void Draw(float deltaTime);
	virtual void Impact(char keyCode, int button, int state, int x, int y);

	float CentersDistance(const Enemy& enemy);
	bool IsCollide(const Enemy& enemy);
	virtual void Absorb(Enemy& enemy);
	virtual void UpdateColor();

protected:
	float x, y;
	float velocityX, velocityY;
	
	GameEnviroment* gameEnv;
};