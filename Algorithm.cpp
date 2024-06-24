#include "Algorithm.h"

bool Algorithm::meshSubdivision(PolygonMesh* src, PolygonMesh& dest, Subdivision::SubType type)
{
	bool ret = false;
	switch (type)
	{
	case Subdivision::SubType::SQRT2:
		ret = sub.subSqrt2(src, dest);
		break;
	default:
		break;
	}

	return ret;
}