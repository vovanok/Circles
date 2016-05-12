#include "GraphicUtils.h"

namespace GraphicUtils {
	namespace {
		const float PI_DIV_180 = 3.14159f / 180.0f;
	}

	void DrawFillRectangle(float leftUpAngleX, float leftUpAngleY, float width, float height, Color borderColor, Color fillColor) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glColor4f(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
		glBegin(GL_POLYGON);
		glVertex2d(leftUpAngleX, leftUpAngleY);
		glVertex2d(leftUpAngleX + width, leftUpAngleY);
		glVertex2d(leftUpAngleX + width, leftUpAngleY + height);
		glVertex2d(leftUpAngleX, leftUpAngleY + height);
		glEnd();

		glColor4f(borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		glBegin(GL_LINE_LOOP);
		glVertex2d(leftUpAngleX, leftUpAngleY);
		glVertex2d(leftUpAngleX + width, leftUpAngleY);
		glVertex2d(leftUpAngleX + width, leftUpAngleY + height);
		glVertex2d(leftUpAngleX, leftUpAngleY + height);
		glEnd();

		glPopMatrix();
	}

	void DrawFillCircle(float centerX, float centerY, float radius, Color borderColor, Color fillColor) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(centerX, centerY, 0.0f);

		glColor4f(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
		glBegin(GL_POLYGON);
   
		for (int grad = 0; grad < 360; grad++) {
			float rad = grad * PI_DIV_180;
			glVertex2f(cos(rad) * radius, sin(rad) * radius);
		}

		glEnd();

		glColor4f(borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		glBegin(GL_LINE_LOOP);
   
		for (int grad = 0; grad < 360; grad++) {
			float rad = grad * PI_DIV_180;
			glVertex2f(cos(rad) * radius, sin(rad) * radius);
		}

		glEnd();

		glPopMatrix();
	}

	void DrawText(float x, float y, float scaleX, float scaleY, std::string text) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(x, y, 0.0f);

		glScalef(scaleX, scaleY, 1.0f);
		for(char ch : text) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ch);
		}

		glPopMatrix();
	}
};
