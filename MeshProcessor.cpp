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
	subdivsion = menuBar()->addMenu(QStringLiteral("Subdivsion"));
}

void MeshProcessor::createActions() 
{
	openFileAction = new QAction(QStringLiteral("file open"), this);
	file->addAction(openFileAction);  //file 可以试下模板写一下mesh输入

	pointMode = new QAction(QStringLiteral("point cloud"), this);
	render->addAction(pointMode);

	wireFrameMode = new QAction(QStringLiteral("wire frame"), this);
	render->addAction(wireFrameMode);

	hiddenWireMode = new QAction(QStringLiteral("hidden wire"), this);
	render->addAction(hiddenWireMode);

	flatMode = new QAction(QStringLiteral("flat face"), this);
	render->addAction(flatMode);

	smoothMode = new QAction(QStringLiteral("smooth face"), this);
	render->addAction(smoothMode);

	wireFlatMode = new QAction(QStringLiteral("wire flat"), this);
	render->addAction(wireFlatMode);

	subSqrt2 = new QAction(QStringLiteral("sqrt2"), this);
	subdivsion->addAction(subSqrt2);
}

void MeshProcessor::signalsConnetSlots() 
{
	connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

	connect(pointMode, SIGNAL(triggered()), this, SLOT(showPoints()));
	connect(wireFrameMode, SIGNAL(triggered()), this, SLOT(showWireFrame()));
	connect(hiddenWireMode, SIGNAL(triggered()), this, SLOT(showHiddenWire()));
	connect(flatMode, SIGNAL(triggered()), this, SLOT(showFlat()));
	connect(smoothMode, SIGNAL(triggered()), this, SLOT(showSmooth()));
	connect(wireFlatMode, SIGNAL(triggered()), this, SLOT(showWireFlat()));

	connect(subSqrt2, SIGNAL(triggered()), this, SLOT(subMeshSqrt2()));
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
	alg.subCnt = 0;
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

void MeshProcessor::showHiddenWire()
{
	getRenderer()->setRenderMode(0x0004);
	vWidget->update();
}

void MeshProcessor::showFlat()
{
	getRenderer()->setRenderMode(0x0008);
	vWidget->update();
}
void MeshProcessor::showWireFlat()
{
	getRenderer()->setRenderMode(0x0010);
	vWidget->update();
}

void MeshProcessor::showSmooth()
{
	getRenderer()->setRenderMode(0x0020);
	vWidget->update();
}

void MeshProcessor::subMeshSqrt2()
{
	PolygonMesh newMesh(*mesh);

	long t1, t2;
	t1 = GetTickCount();
	alg.meshSubdivision(&newMesh, *mesh, Subdivision::SQRT2);
	vWidget->update();
	t2 = GetTickCount();

	alg.subCnt++;
	printf("%d th sqrt2 subdivsion cost time: %d\n", alg.subCnt, t2 - t1);
}


