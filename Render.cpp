#include "Render.h"

Render::Render()
{

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
	case 0x0001:
		updateRenderingMaterial(RenderingMaterial::matMeshFace);
		setMaterial(matRendering);
		break;
	default:
		break;
	}
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

