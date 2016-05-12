#pragma once
#include "ColorPalette.h"
#include <gl/glut.h>
#include <string>

namespace GraphicUtils {
	void DrawFillRectangle(float leftUpAngleX, float leftUpAngleY, float width, float height, Color borderColor, Color fillColor);
	void DrawFillCircle(float centerX, float centerY, float radius, Color borderColor, Color fillColor);
	void DrawText(float x, float y, float scaleX, float scaleY, std::string text);
};