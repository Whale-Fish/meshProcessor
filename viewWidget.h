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

	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void wheelEvent(QWheelEvent *wle);

	void setMesh(PolygonMesh* &mesh);
	void setMesh(TriMesh* &mesh);
	void setCurAction(const std::string& action);
	void setCurFile(const std::string& fileName);
	void getSceneViewer(SceneView* &sceneViewer);

	SceneView* sceneViewer;

private:
	std::string curAtion = "";
	std::string curFile = "";
	QPoint lastPos;

private:
	float elevation = 3.0;
	float azimuth = 0.0;
	float dist = 3.0;
};

