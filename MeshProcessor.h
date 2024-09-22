#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog.h>
#include <string>
#include <stack>
#include "ui_MeshProcessor.h"
#include "viewWidget.h"
#include "Algorithm.h"

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

	QAction *openQuadFile;
	QAction *openTriFile;
	QAction *saveFile;

	QAction *pointMode;
	QAction *wireFrameMode;
	QAction *hiddenWireMode;
	QAction *flatMode;
	QAction *smoothMode;
	QAction *wireFlatMode;

	QAction *subSqrt2;
	QAction *subSqrt3;
	QAction *subISqrt2;
	QAction *subISqrt3;

private:
	PolygonMesh *quadMesh;
	TriMesh *triMesh;

	bool isTri;
	std::string curFileName;
	std::string  curActionName;
	Algorithm alg;

private:
	void createMenu();
	void createActions();
	void updateMenuActions();
	void signalsConnetSlots();
	void setCurFileName(std::string path);

	// slots func
private slots:
	void openTriFileAction();
	void openQuadFileAction();
	void saveFileAction();
	void showPoints();
	void showWireFrame();
	void showHiddenWire();
	void showFlat();
	void showWireFlat();
	void showSmooth();

	void subMeshSqrt2();
	void subMeshSqrt3(); 
	void subMeshISqrt2();
	void subMeshISqrt3();
};
