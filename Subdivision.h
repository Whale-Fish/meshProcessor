#pragma once
#include "kernel.h"
#include<vector>

class Subdivision
{
public:
	enum SubType {
		SQRT3 = 0,
		SQRT2,
		ISQRT3,
		ISQRT2,

	};

public:
	bool subSqrt2(PolygonMesh* src, PolygonMesh& dest);
	bool subSqrt3(TriMesh* src, TriMesh& dest);
	bool subISqrt2(PolygonMesh* src, PolygonMesh& dest);
	bool subISqrt3(TriMesh* src, TriMesh& dest);

	SubType curType;
};

