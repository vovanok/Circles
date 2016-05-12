#pragma once
#include <map>

struct Color {
	float r, g, b, a;
	Color()
		: r(0.0f), g(0.0f), b(0.0f), a(0.0f) { }
	Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a) { }
};

class ColorPalette {
public:
	ColorPalette(Color beginColor, Color endColor, float beginValue, float endValue);
	void AddUpdControlColor(size_t value, Color color);
	Color GetColor(float value);
	Color GetColor(size_t value);
	~ColorPalette();

private:
	std::map<size_t, Color> controlColors;
	size_t minValue, maxValue;
	float beginValue, endValue;
};