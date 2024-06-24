#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog.h>
#include <string>
#include <stack>
#include "ui_MeshProcessor.h"
#include "viewWidget.h"
#include "Algorithm/Algorithm.h"

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
	QMenu* subdivsion;

	QAction *openFileAction;

	QAction *pointMode;
	QAction *wireFrameMode;
	QAction *hiddenWireMode;
	QAction *flatMode;
	QAction *smoothMode;
	QAction *wireFlatMode;

	QAction *subSqrt2;

private:
	PolygonMesh *mesh;
	std::string curFileName;
	Algorithm alg;

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
	void showHiddenWire();
	void showFlat();
	void showWireFlat();
	void showSmooth();
	void subMeshSqrt2();
};
