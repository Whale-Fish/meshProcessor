#pragma once
#include "Subdivision.h"

class Algorithm
{
public:
	int subCnt = 0;
public:
	bool QuadMeshSubdivision(PolygonMesh* src, PolygonMesh& dest, Subdivision::SubType type);
	bool TriMeshSubdivision(TriMesh* src, TriMesh& dest, Subdivision::SubType type);

private:
	Subdivision sub;

};
