#pragma once
#include "kernel.h"
#include<vector>

class Subdivision
{
public:
	enum SubType {
		SQRT3 = 0,
		SQRT2

	};

	bool subSqrt2(PolygonMesh* src, PolygonMesh& dest);


private:
	SubType curType;
};

