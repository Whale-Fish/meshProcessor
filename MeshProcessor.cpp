#include "MeshProcessor.h"

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
	if (vWidget)
	{
		delete vWidget;
		vWidget = nullptr;
	}

	if (mesh)
	{
		delete mesh;
		mesh = nullptr;
	}
}

void MeshProcessor::createMenu() 
{
	file = menuBar()->addMenu(QStringLiteral("File"));
	render = menuBar()->addMenu(QStringLiteral("Render"));

}

void MeshProcessor::createActions() 
{
	openFileAction = new QAction(QStringLiteral("file open"), this);
	file->addAction(openFileAction);  //file 可以试下模板写一下mesh输入

	pointMode = new QAction(QStringLiteral("point cloud"), this);
	render->addAction(pointMode);

	wireFrameMode = new QAction(QStringLiteral("wire frame"), this);
	render->addAction(wireFrameMode);
}

void MeshProcessor::signalsConnetSlots() 
{
	connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

	connect(pointMode, SIGNAL(triggered()), this, SLOT(showPoints()));
	connect(wireFrameMode, SIGNAL(triggered()), this, SLOT(showWireFrame()));
}

Render* MeshProcessor::getRenderer()
{
	SceneView* sv;
	Render* r;

	vWidget->getSceneViewer(sv);
	sv->getRender(r);

	return r;
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

void MeshProcessor::showPoints()
{
	getRenderer()->setRenderMode(0x0001);
	vWidget->update();
}

void MeshProcessor::showWireFrame()
{
	getRenderer()->setRenderMode(0x0002);
	vWidget->update();
}


