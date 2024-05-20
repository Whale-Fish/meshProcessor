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

	void setMesh(PolygonMesh *mesh);

private:
	SceneView sceneViewer;
	PolygonMesh *mesh;
};

