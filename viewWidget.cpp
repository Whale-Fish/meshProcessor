#include "ViewWidget.h"


ViewWidget::ViewWidget(QWidget *parent)
{

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