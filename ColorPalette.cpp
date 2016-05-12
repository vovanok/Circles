#include "ColorPalette.h"

ColorPalette::ColorPalette(Color beginColor, Color endColor, float beginValue, float endValue) {
	minValue = 0;
	maxValue = 100;
	controlColors[minValue] = beginColor;
	controlColors[maxValue] = endColor;

	this->beginValue = beginValue;
	this->endValue = endValue;
}

void ColorPalette::AddUpdControlColor(size_t value, Color color) {
	controlColors[value] = color;
}

Color ColorPalette::GetColor(float value) {
	int persent = (int)((maxValue - minValue) * (value - beginValue) / (endValue - beginValue));
	if (persent < 0)
		persent = 0;
	return GetColor((size_t)persent);
}

Color ColorPalette::GetColor(size_t value) {
	if (value < minValue) value = minValue;
	if (value > maxValue) value = maxValue;

	std::pair<size_t, Color> minLimit;
	std::pair<size_t, Color> maxLimit;
	Color maxOfLess = controlColors[0];
	Color minOfLarge = controlColors[100];

	for (std::map<size_t, Color>::iterator cur = controlColors.begin(); cur != controlColors.end(); cur++) {
		if (cur->first < value) {
			minLimit = *cur;
		}
		else {
			maxLimit = *cur;
			break;
		}
	}

	if (maxLimit.first == minLimit.first)
		return maxLimit.second;

	float factor = ((float)value - (float)minLimit.first) / ((float)maxLimit.first - (float)minLimit.first);
	return Color(
		minLimit.second.r + (maxLimit.second.r - minLimit.second.r) * factor,
		minLimit.second.g + (maxLimit.second.g - minLimit.second.g) * factor,
		minLimit.second.b + (maxLimit.second.b - minLimit.second.b) * factor,
		minLimit.second.a + (maxLimit.second.a - minLimit.second.a) * factor);
}

ColorPalette::~ColorPalette() {
	controlColors.clear();
}