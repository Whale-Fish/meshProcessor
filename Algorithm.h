#pragma once
#include "Subdivision.h"

class Algorithm
{
public:
	int subCnt = 0;
public:
	bool meshSubdivision(PolygonMesh* src, PolygonMesh& dest, Subdivision::SubType type);

private:
	Subdivision sub;

};
