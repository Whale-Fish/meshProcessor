#include "ViewWidget.h"


ViewWidget::ViewWidget(QWidget *parent)
{
	mesh = nullptr;
}

ViewWidget::~ViewWidget() 
{

}

void ViewWidget::initializeGL() 
{
	sceneViewer.initialize();
}

void ViewWidget::resizeGL(int w, int h)
{
	sceneViewer.resize(w, h);
}

void ViewWidget::paintGL()
{
	sceneViewer.sceneView();
}

void ViewWidget::setBackgroundColor() {



}

void  ViewWidget::setMesh(PolygonMesh *mesh_)
{
	sceneViewer.getRender().setRenderMesh(mesh_);
}
