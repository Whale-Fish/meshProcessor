#pragma once
#include "ViewWidget.h"
#include <QPainter>
#include <iostream>

ViewWidget::ViewWidget(QWidget *parent)
{
	sceneViewer = new SceneView();
}

ViewWidget::~ViewWidget() 
{
	if (sceneViewer)
	{
		delete sceneViewer;
		sceneViewer = nullptr;
	}
}

void ViewWidget::initializeGL() 
{
	sceneViewer->initialize();
}

void ViewWidget::resizeGL(int w, int h)
{
	sceneViewer->resize(w, h);
}

void ViewWidget::paintGL()
{
	sceneViewer->sceneView();

	//other things in painting
	QPainter painter(this);
	
	painter.setPen(Qt::black);
	painter.setFont(QFont("Arial", 10));

	int padding = 8;
	if (curAtion.size()) 
	{
		QString textAction = QString::fromStdString(curAtion);
		int x = width() - painter.fontMetrics().width(textAction) - padding;
		int y = height() - padding;
		painter.drawText(x, y, textAction);
	}

	if (curFile.size())
	{
		QString textName = QString::fromStdString(curFile);
		int x = padding;
		int y = height() - padding;
		painter.drawText(x, y, textName);
	}
}

void ViewWidget::mouseMoveEvent(QMouseEvent *e)
{
	float dx = e->x() - lastPos.x();
	float dy = e->y() - lastPos.y();

	if (e->buttons()&Qt::LeftButton)
	{
		azimuth += 180 * dx / 800;
		elevation += 180 * dy / 600;
		sceneViewer->setCameraParams(elevation, azimuth, dist);
		update();
	}
	lastPos = e->pos();
}

void ViewWidget::mousePressEvent(QMouseEvent *e)
{
	lastPos = e->pos();
}

void ViewWidget::wheelEvent(QWheelEvent *wle)
{
	if (wle->delta() > 0)
	{
		dist += 0.1;
	}
	else if (wle->delta())
	{
		dist -= 0.1;
	}
	sceneViewer->setCameraParams(elevation, azimuth, dist);
	update();
}


void  ViewWidget::setMesh(PolygonMesh* &mesh)
{
	Render *r;
	sceneViewer->getRender(r);
	r->setRenderMesh(mesh);
}

void ViewWidget::setMesh(TriMesh* &mesh)
{
	Render *r;
	sceneViewer->getRender(r);
	r->setRenderMesh(mesh);
}

void ViewWidget::setCurAction(const std::string& action)
{
	this->curAtion = action;
}

void ViewWidget::setCurFile(const std::string& fileName)
{
	this->curFile = fileName;
}

void ViewWidget::getSceneViewer(SceneView* &sceneViewer)
{
	sceneViewer = this->sceneViewer;
}