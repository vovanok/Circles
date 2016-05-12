#include "GraphicMgr.h"

namespace GraphicMgr {
	void ReDisplay() {
		glutPostRedisplay();
	}

	void Run() {
		isRun = true;
		glutMainLoop();
	}

	void StartStopAnimation() {
		if (!isRun) {
			isRun = true;
			ReDisplay();
		} else {
			isRun = false;
		}
	}

	bool IsRunAnimation() {
		return isRun;
	}

	void AddPresentObj(IPresentable *obj) {
		presentObjs.push_back(obj);
	}

	void ClearPresentObjs() {
		presentObjs.clear();
	}

	void AddUpdateKeyboardHandler(unsigned char key, std::function<void()> handler) {
		keyboardHandlers[key] = handler;
	}

	void AddUpdateKeyboardHandler(std::string keys, std::function<void()> handler) {
		for(char key : keys)
			AddUpdateKeyboardHandler(key, handler);
	}

	void ClearKeyboardHandler() {
		keyboardHandlers.clear();
	}

	void SetVisibilityArea(float left, float right, float up, float down) {
		leftVisibilityBound = left;
		rightVisibilityBound = right;
		upVisibilityBound = up;
		downVisibilityBound = down;
	}


	void CreateWindow(int argc, char **argv, const std::string name, size_t x, size_t y, size_t width, size_t height) {
		glutInit (&argc, argv);
		glutInitWindowPosition (x, y);
		glutInitWindowSize(width, height);
		windowWidth = width;
		windowHeight = height;

		glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE);
		wndHdlr = glutCreateWindow(name.c_str());
	
		isRun = false;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glutDisplayFunc(onDisplay);
		glutReshapeFunc(onReshape);
		glutKeyboardFunc(onKeyboard);
		glutMouseFunc(onMouse);
	}

	void DestroyWindow() {
		glutDestroyWindow(wndHdlr);
	}

	namespace {
		void onDisplay() {
			clock_t startTime = clock();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			for(size_t i = 0; i < presentObjs.size(); i++)
				presentObjs[i]->Draw(deltaTime);
	
			glFlush();

			clock_t stopTime;
	
			do {
				stopTime = clock();
				deltaTime = float(stopTime - startTime) / CLOCKS_PER_SEC;
				fps = 1.0f / deltaTime;
			} while(fps > 60.0f);

			if (isRun)
				glutPostRedisplay();
		}

		void onReshape(int width, int height) {
			windowWidth = width;
			windowHeight = height;
			glViewport(0, 0, (GLsizei)width, (GLsizei)height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glOrtho(leftVisibilityBound, rightVisibilityBound,
				downVisibilityBound, upVisibilityBound, 0, 200);

			glMatrixMode(GL_MODELVIEW);
		}

		void onKeyboard(unsigned char key, int x, int y) {
			keyboardHandlers[key]();

			for(size_t i = 0; i < presentObjs.size(); i++)
				presentObjs[i]->Impact(key, 0, 0, x, y);

			ReDisplay();
		}

		void onMouse(int button, int state, int x, int y) {
			float sceneX = float(x) - float(windowWidth) / 2.0f;	
			float sceneY = -float(y) + float(windowHeight) / 2.0f;	

			for(size_t i = 0; i < presentObjs.size(); i++)
				presentObjs[i]->Impact('\0', button, state, sceneX, sceneY);
		}
	}
};