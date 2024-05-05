#pragma once

#include "Render.h"

/**
* this class is created for scene operation, such as resize or mouse events
*/
class SceneView: public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	void initialize();
	void resize(int w, int h);
	void sceneView();

protected:
	GLdouble		fovy;
	GLdouble        zNear;
	GLdouble        zFar;

	//GLdouble modelviewMatrix[16];

private:
	int width;
	int height;

	float elevation = 3.0;
	float azimuth = 0.0;
	float dist = 3.0;

private:
	QPoint lastPos;
	Render renderer;
};

