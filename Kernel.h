#pragma once

#include <vector>

#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <OpenMesh/Core/io/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
typedef OpenMesh::PolyMesh_ArrayKernelT<>  PolygonMesh;
typedef OpenMesh::TriMesh_ArrayKernelT<>  TriMesh;
typedef OpenMesh::Vec3d POINT3D;


class Kernel
{

};

template<typename T>
class Mesh {
public:
	void drawing();


};

