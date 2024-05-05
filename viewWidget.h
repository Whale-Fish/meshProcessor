#pragma once

#include "SceneView.h"


class ViewWidget :public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	ViewWidget(QWidget *parent);
	~ViewWidget();

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void setBackgroundColor();



private:
	SceneView sceneViewer;
};

