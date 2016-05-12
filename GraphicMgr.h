#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <ctime>
#include "IPresentable.h"
#include <gl/glut.h>

namespace GraphicMgr {
	void ReDisplay();
	void Run();
	void StartStopAnimation();
	bool IsRunAnimation();
	void AddPresentObj(IPresentable *obj);
	void ClearPresentObjs();
	void AddUpdateKeyboardHandler(unsigned char key, std::function<void()> handler);
	void AddUpdateKeyboardHandler(std::string keys, std::function<void()> handler);
	void ClearKeyboardHandler();
	void SetVisibilityArea(float left, float right, float up, float down);
	void CreateWindow(int argc, char **argv, const std::string name, size_t x, size_t y, size_t width, size_t height);
	void DestroyWindow();

	namespace {
		float leftVisibilityBound;
		float rightVisibilityBound;
		float upVisibilityBound;
		float downVisibilityBound;
		
		int wndHdlr;
		float deltaTime;
		float fps;

		bool isRun;

		size_t windowWidth;
		size_t windowHeight;
		
		std::vector<IPresentable*> presentObjs;
		std::map<unsigned char, std::function<void()>> keyboardHandlers;

		void onDisplay();
		void onReshape(int width, int height);
		void onKeyboard(unsigned char key, int x, int y);
		void onMouse(int button, int state, int x, int y);
	}
};