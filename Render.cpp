#include "Render.h"

Render::Render()
{
	mesh = nullptr;
	mode = 0x0002;
}

Render::~Render() 
{

}

/**
* Set mesh material
*/
void Render::setMaterial(GLfloat mat[17]) 
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &mat[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &mat[4]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &mat[8]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &mat[12]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &mat[16]);
}

void Render::setRenderMode(unsigned int mode) 
{
	this->mode = mode;
	setMaterialByMode(mode);
}

void Render::setMaterialByMode(unsigned int mode) {
	switch (mode) {
	case 0x0001: // vertex mode
		updateRenderingMaterial(RenderingMaterial::matMeshFace);
		setMaterial(matRendering);
		break;
	case 0x0002: // wire frame
		updateRenderingMaterial(RenderingMaterial::matMeshEdge);
		setMaterial(matRendering);
		break;
	case 0x0004: // hidden line
		updateRenderingMaterial(RenderingMaterial::matMeshEdge);
		setMaterial(matRendering);
		break;
	case 0x0008: // solid flat
		updateRenderingMaterial(RenderingMaterial::matMeshFace);
		setMaterial(matRendering);
		break;
	case 0x0010: // wire flat
		updateRenderingMaterial(RenderingMaterial::matMeshFace);
		setMaterial(matRendering);
		break;
	case 0x0020: // smooth
		updateRenderingMaterial(RenderingMaterial::matMeshFace);
		setMaterial(matRendering);
		break;
	default:
		break;
	}
}

void Render::setColoredMaterial(int color)
{
	float red[4] = { 1.0, 0.0, 0.0, 1.0 };
	float blue[4] = { 0.0, 0.0, 0.9, 1.0 };
	float green[4] = { 0.0, 0.8, 0.0, 1.0 };
	float yellow[4] = { 0.8, 0.8, 0.1, 1.0 };
	float white[4] = { 1.0, 1.0, 1.0, 1.0 };
	float c1[4] = { 1.0, 0.0, 0.6, 1.0 };
	float paple[4] = { 0.5, 0.0, 1.0, 1.0 };
	float c3[4] = { 1.0, 0.3, 0.5, 1.0 };
	float c4[4] = { 0.2, 0.3, 0.2, 1.0 };
	float c5[4] = { 0.0, 0.0, 0.0, 1.0 };
	float orange[4] = { 0.9, 0.4, 0.0, 1.0 };
	switch (color)
	{
	case 0:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
		break;

	case 1:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
		break;

	case 2:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
		break;

	case 3:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
		break;

	case 4:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
		break;
	case 5:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c1);
		break;
	case 6:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, paple);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, paple);
		break;
	case 7:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c3);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c3);
		break;
	case 8:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c4);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c4);
		break;
	case 9:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c5);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c5);
		break;
	case 10:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, orange);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, orange);
		break;
	}
}

void Render::setRenderMesh(PolygonMesh* mesh)
{
	this->mesh = mesh;
}

/**
* update the rendering material
**/
void Render::updateRenderingMaterial(float mat[])
{
	for (unsigned int i = 0; i < 17; i++)
	{
		matRendering[i] = mat[i];
	}
}

void Render::build()
{
	switch (mode)
	{
	case 0x0001:
		buildPoints();
		break;
	case 0x0002:
		buildWireFrame();
		break;
	default:
		break;
	}
}

void Render::buildPoints() 
{
	if (!mesh)
	{
		return;
	}

	POINT3D v;

	glShadeModel(GL_SMOOTH);
	setMaterialByMode(mode);
	glPointSize(3.0);
	for (auto it = mesh->vertices_begin(); it != mesh->vertices_end(); ++it)
	{
		glBegin(GL_POINTS);
		v = mesh->point(it);
		glVertex3d(v[0], v[1], v[2]);
		glEnd();
	}
}

void Render::buildWireFrame()
{
	if (!mesh)
	{
		return;
	}

	POINT3D v1, v2;

	glShadeModel(GL_SMOOTH);
	setMaterialByMode(mode);
	glLineWidth(1.2f);
	for (auto it = mesh->edges_begin(); it != mesh->edges_end(); ++it)
	{
		v1 = mesh->point(mesh->from_vertex_handle(mesh->halfedge_handle((*it), 0)));
		v2 = mesh->point(mesh->to_vertex_handle(mesh->halfedge_handle((*it), 0)));

		glBegin(GL_LINES);
		glVertex3d(v1[0], v1[1], v1[2]);
		glVertex3d(v2[0], v2[1], v2[2]);
		glEnd();
	}
}

