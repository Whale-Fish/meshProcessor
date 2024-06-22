#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog.h>
#include <string>
#include <stack>
#include "ui_MeshProcessor.h"
#include "viewWidget.h"

class MeshProcessor : public QMainWindow
{
    Q_OBJECT

public:
    MeshProcessor(QWidget *parent = nullptr);
    ~MeshProcessor();

	Render* getRenderer();

private:
    Ui::MeshProcessorClass ui;

	ViewWidget *vWidget;

	QMenu *file;
	QMenu *render;

	QAction *openFileAction;

	QAction *pointMode;
	QAction *wireFrameMode;

private:
	PolygonMesh *mesh;
	std::string curFileName;

private:
	void createMenu();
	void createActions();
	void signalsConnetSlots();
	void setCurFileName(std::string path);

	// slots func
private slots:
	void openFile();
	void showPoints();
	void showWireFrame();
};
