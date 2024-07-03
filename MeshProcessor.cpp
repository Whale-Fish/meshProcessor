#include "MeshProcessor.h"

MeshProcessor::MeshProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	vWidget = new ViewWidget(this);
	mesh.triMesh = new TriMesh();
	isTri = true;

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

	if (mesh.quadMesh)
	{
		delete mesh.quadMesh;
		mesh.quadMesh = nullptr;
	}

	if (mesh.triMesh)
	{
		mesh.triMesh;
		mesh.triMesh = nullptr;
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
	openQuadFile = new QAction(QStringLiteral("quadMesh"), this);
	file->addAction(openQuadFile);  //file 可以试下模板写一下mesh输入
	QIcon icon0;
	icon0.addFile(QString::fromUtf8("Icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
	openQuadFile->setIcon(icon0);

	openTriFile = new QAction(QStringLiteral("triMesh"), this);
	file->addAction(openTriFile);  //file 可以试下模板写一下mesh输入
	QIcon icon1;
	icon1.addFile(QString::fromUtf8("Icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
	openTriFile->setIcon(icon1);

	pointMode = new QAction(QStringLiteral("point cloud"), this);
	render->addAction(pointMode);
	QIcon icon2;
	icon2.addFile(QString::fromUtf8("Icons/points.png"), QSize(), QIcon::Normal, QIcon::Off);
	pointMode->setIcon(icon2);

	wireFrameMode = new QAction(QStringLiteral("wire frame"), this);
	render->addAction(wireFrameMode);
	QIcon icon3;
	icon3.addFile(QString::fromUtf8("Icons/wire.png"), QSize(), QIcon::Normal, QIcon::Off);
	wireFrameMode->setIcon(icon3);

	hiddenWireMode = new QAction(QStringLiteral("hidden wire"), this);
	render->addAction(hiddenWireMode);
	QIcon icon4;
	icon4.addFile(QString::fromUtf8("Icons/backlines.png"), QSize(), QIcon::Normal, QIcon::Off);
	hiddenWireMode->setIcon(icon4);

	flatMode = new QAction(QStringLiteral("flat face"), this);
	render->addAction(flatMode);
	QIcon icon5;
	icon5.addFile(QString::fromUtf8("Icons/flat.png"), QSize(), QIcon::Normal, QIcon::Off);
	flatMode->setIcon(icon5);

	smoothMode = new QAction(QStringLiteral("smooth face"), this);
	render->addAction(smoothMode);
	QIcon icon6;
	icon6.addFile(QString::fromUtf8("Icons/smooth.png"), QSize(), QIcon::Normal, QIcon::Off);
	smoothMode->setIcon(icon6);

	wireFlatMode = new QAction(QStringLiteral("wire flat"), this);
	render->addAction(wireFlatMode);
	QIcon icon7;
	icon7.addFile(QString::fromUtf8("Icons/flatlines.png"), QSize(), QIcon::Normal, QIcon::Off);
	wireFlatMode->setIcon(icon7);

	subSqrt2 = new QAction(QStringLiteral("sqrt2"), this);
	subdivsion->addAction(subSqrt2);
}

void MeshProcessor::updateActionsEnabledStatus()
{
	if (isTri)
	{
		subSqrt2->setEnabled(false);
	}
	else
	{
		subSqrt2->setEnabled(true);
	}
}

void MeshProcessor::signalsConnetSlots() 
{
	connect(openQuadFile, SIGNAL(triggered()), this, SLOT(openQuadFileAction()));
	connect(openTriFile, SIGNAL(triggered()), this, SLOT(openTriFileAction()));

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

void MeshProcessor::openTriFileAction()
{
	delete mesh.quadMesh;
	mesh.quadMesh = nullptr;
	mesh.triMesh = new TriMesh();
	isTri = true;
	updateActionsEnabledStatus();

	OpenMesh::IO::Options opt = OpenMesh::IO::Options::VertexNormal;

	QString qPath = QFileDialog::getOpenFileName(this, QStringLiteral("open"), "./tri_mesh/cube_nor.obj", QStringLiteral("file type (*.obj);;file type (*.off)"));
	std::string path = qPath.toStdString();

	setCurFileName(path);

	mesh.triMesh->request_vertex_normals();
	if (!OpenMesh::IO::read_mesh(*mesh.triMesh, path, opt))
	{
		printf("mesh file open error!");
	}

	vWidget->setMesh(mesh.triMesh);
	alg.subCnt = 0;
}

void MeshProcessor::openQuadFileAction()
{
	delete mesh.triMesh;
	mesh.triMesh = nullptr;
	mesh.quadMesh = new PolygonMesh();
	isTri = false;
	updateActionsEnabledStatus();

	OpenMesh::IO::Options opt = OpenMesh::IO::Options::VertexNormal;

	QString qPath = QFileDialog::getOpenFileName(this, QStringLiteral("open"), "./quad_mesh/cube_nor.obj", QStringLiteral("file type (*.obj);;file type (*.off)"));
	std::string path = qPath.toStdString();

	setCurFileName(path);

	mesh.quadMesh->request_vertex_normals();
	if (!OpenMesh::IO::read_mesh(*mesh.quadMesh, path, opt))
	{
		printf("mesh file open error!");
	}

	vWidget->setMesh(mesh.quadMesh);
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
	PolygonMesh newMesh(*mesh.quadMesh);

	long t1, t2;
	t1 = GetTickCount();
	alg.meshSubdivision(&newMesh, *mesh.quadMesh, Subdivision::SQRT2);
	vWidget->update();
	t2 = GetTickCount();

	alg.subCnt++;
	printf("%d th sqrt2 subdivsion cost time: %d\n", alg.subCnt, t2 - t1);
}


