#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MeshProcessor.h"
#include "viewWidget.h"

class MeshProcessor : public QMainWindow
{
    Q_OBJECT

public:
    MeshProcessor(QWidget *parent = nullptr);
    ~MeshProcessor();

private:
    Ui::MeshProcessorClass ui;

	ViewWidget *vWidget;

	QMenu *file;

	QAction *openFile;

private:
	void createMenu();
	void createActions();

};
