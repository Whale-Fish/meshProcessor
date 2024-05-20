#include "SceneView.h"

void SceneView::initialize() 
{
	this->initializeOpenGLFunctions();

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glDisable(GL_DITHER);
	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	// lighting
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	zNear = 0.1;
	zFar = 1000.0;
	fovy = 45.0f;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void SceneView::resize(int w,int h)
{
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fovy, (GLfloat)w / (GLfloat)h, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SceneView::sceneView()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);

	glLoadIdentity();
	gluLookAt(0, 0, dist, 0, 0, 0, 0, 1, 0);
	glRotatef(elevation, 1, 0, 0);
	glRotatef(azimuth, 0, 1, 0);

	setLights();

	// painting
	renderer.build();
}

void SceneView::setLights()
{
	GLfloat ambient[] = { 0.4, 0.6, 0.2, 1.0 };
	GLfloat position[] = { 1.0, 1.0, 1.0, 1.0 };

	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}

Render SceneView::getRender()
{
	return renderer;
}