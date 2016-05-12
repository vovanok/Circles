#pragma once

class IPresentable {
public:
	virtual void Draw(float deltaTime) = 0;
	virtual void Impact(char keyCode, int button, int state, int x, int y) = 0;
};