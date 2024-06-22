#pragma once

#include "Render.h"
#include <Qt3DInput/QMouseEvent>  

/**
* this class is created for scene operation, such as resize or mouse events
*/
class SceneView: public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	SceneView();
	~SceneView();

	void initialize();
	void resize(int w, int h);
	void sceneView();

	void setBackgroundColor();
	void setCameraParams(float elevation, float azimuth, float dist);
	void setLights();
	void getRender(Render* &renderer);

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
	Render* renderer;
};

class showStatus {
public:
	


private:
	int isShow = 0;
	int hasNors = 0;

};

