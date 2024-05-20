#pragma once
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include<GL\GLU.h>
#include <GL\GL.h>
#include "glut.h"
#include "RenderingMaterial.h"
#include "Kernel.h"

enum RenderMode {
	RENDERING_MODE_POINT = 0x0001,
	RENDERING_MODE_WIRE_FRAME = 0x0002,
	RENDERING_MODE_HIDDEN_LINE = 0x0004,
	RENDERING_MODE_FLAT = 0x0008,
	RENDERING_MODE_WIRE_FLAT = 0x0010,
	RENDERING_MODE_SMOOTH = 0x0020,
};

class Render
{
public:
	Render();
	~Render();

	static void setMaterial(GLfloat mat[17]);
	void setMaterialByMode(unsigned int mode);
	void setColoredMaterial(int color);
	void setRenderMesh(PolygonMesh* mesh);
	void setRenderMode(unsigned int mode);
	void updateRenderingMaterial(float mat[]);

	// render mode
	void build();
	void buildPoints();
	void buildWireFrame();
	//void buildHiddenWire();
	//void buildSmooth();
	//void buildFlat();
	//void buildWireFlat();

private:
	PolygonMesh* mesh;

private:
	unsigned int mode;
	GLfloat matRendering[17];
};

