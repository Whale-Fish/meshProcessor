#include "RenderingMaterial.h"

float RenderingMaterial::matMeshFace[17] =
{ 1.0f, 1.0f, 1.0f, 1.0f,
0.9f, 0.4f, 0.0f, 0.5f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

// material for mesh entity edge
float RenderingMaterial::matMeshEdge[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
0.9f, 0.4f, 0.0f, 0.5f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

// material for mesh entity vertex
float RenderingMaterial::matMeshVertex[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
0.9f, 0.4f, 0.0f, 0.5f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

float RenderingMaterial::matRedColor[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
1.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

float RenderingMaterial::matBlueColor[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
0.0f, 0.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

float RenderingMaterial::matGreenColor[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
0.0f, 1.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

float RenderingMaterial::matGrayColor[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
0.8f, 0.8f, 0.6f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

float RenderingMaterial::matYellowColor[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
1.0f, 1.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

float RenderingMaterial::matPurpleColor[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
1.0f, 0.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };

float RenderingMaterial::matBlackColor[17] =
{ 0.2f, 0.2f, 0.2f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f,
50.0f };