#include "MeshProcessor.h"


MeshProcessor::MeshProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	vWidget = new ViewWidget(this);

	createMenu();
	createActions();
	this->setCentralWidget(vWidget);
}

MeshProcessor::~MeshProcessor()
{

}

void MeshProcessor::createMenu() 
{
	file = menuBar()->addMenu(QStringLiteral("File"));


}

void MeshProcessor::createActions() 
{
	openFile = new QAction(QStringLiteral("file open"), this);
	file->addAction(openFile);  //file 可以试下模板写一下mesh输入


}

void MeshProcessor::signalsConnetSlots() 
{

}