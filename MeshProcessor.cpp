#include "MeshProcessor.h"

//PolygonMesh gMesh;

MeshProcessor::MeshProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	vWidget = new ViewWidget(this);
	mesh = new PolygonMesh();

	createMenu();
	createActions();
	signalsConnetSlots();
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
	openFileAction = new QAction(QStringLiteral("file open"), this);
	file->addAction(openFileAction);  //file 可以试下模板写一下mesh输入


}

void MeshProcessor::signalsConnetSlots() 
{
	connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
}


void  MeshProcessor::setCurFileName(std::string path)
{
	int strSize = path.size();

	if (strSize == 0)
	{
		printf("Don't choose file!\n");
		return;
	}

	std::stack<char>stk;
	std::string tmpStr;
	
	// get the last letter between .obj, 5 can be substituted by file extension's length, if we have other type input.
	char c = path[strSize - 5]; 
	while (c != '/')
	{
		stk.push(c);
		strSize--;
		c = path[strSize - 5];
	}

	while (!stk.empty())
	{
		char c1 = stk.top();
		curFileName += c1;
		stk.pop();
	}
}

void MeshProcessor::openFile()
{
	OpenMesh::IO::Options opt = OpenMesh::IO::Options::VertexNormal;

	QString qPath = QFileDialog::getOpenFileName(this, QStringLiteral("open"), "./tri_mesh/cube_nor.obj", QStringLiteral("file type (*.obj);;file type (*.off)"));
	std::string path = qPath.toStdString();

	setCurFileName(path);

	mesh->request_vertex_normals();
	if (!OpenMesh::IO::read_mesh(*mesh, path, opt))
	{
		printf("mesh file open error!");
	}

	vWidget->setMesh(mesh);
}

