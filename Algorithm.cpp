#include "Algorithm.h"

bool Algorithm::QuadMeshSubdivision(PolygonMesh* src, PolygonMesh& dest, Subdivision::SubType type)
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

bool Algorithm::TriMeshSubdivision(TriMesh* src, TriMesh& dest, Subdivision::SubType type)
{
	bool ret = false;
	switch (type)
	{
	case Subdivision::SubType::SQRT3:
		ret = sub.subSqrt3(src, dest);
		break;
	default:
		break;
	}

	return ret;
}