#include "MeshProcessor.h"


MeshProcessor::MeshProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	vWidget = new ViewWidget(this);

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
	openFile = new QAction(QStringLiteral("File"), this);
	file->addAction(openFile);  //file ��������ģ��дһ��mesh����


}