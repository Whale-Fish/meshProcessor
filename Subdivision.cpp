#include "Subdivision.h"


#define PI 3.1415926

bool Subdivision::subSqrt2(PolygonMesh* src, PolygonMesh& dest)
{
	dest.clear();
	int facesNum = src->n_faces();
	int verticesNum = src->n_vertices();

	std::vector<PolygonMesh::VertexHandle>old_vertices(verticesNum);
	std::vector<PolygonMesh::VertexHandle>new_face_vertices(facesNum);
	PolygonMesh::VertexHandle tmpAddVh;
	std::vector<PolygonMesh::VertexHandle>facesHandle;

	for (auto v_it = src->vertices_begin(); v_it != src->vertices_end(); v_it++)
	{
		POINT3D tmpPoint;
		tmpPoint = src->point(v_it);

		//updata v
		int deg = 0;
		POINT3D surroundSum(0, 0, 0);
		for (PolygonMesh::VertexVertexIter vv_it = src->vv_iter(v_it); vv_it.is_valid(); vv_it++) {
			deg++;
			surroundSum += src->point(vv_it);
		}
		POINT3D newp;
		double alpha = (1 - cos(2 * PI / deg)) / 2;
		newp = (1 - alpha)*tmpPoint + alpha / deg * surroundSum;

		tmpAddVh = dest.add_vertex(PolygonMesh::Point(newp[0], newp[1], newp[2]));
		old_vertices[(*v_it).idx()] = tmpAddVh;
	}


	//cac_new_face_points
	for (auto f_it = src->faces_begin(); f_it != src->faces_end(); ++f_it) {
		std::vector<POINT3D>facePoints;
		for (auto fv_it = src->fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			POINT3D tmpPoint, tmpNor;
			tmpPoint = src->point(fv_it);
			facePoints.push_back(tmpPoint);
		}

		POINT3D newp = (facePoints[0] + facePoints[1] + facePoints[2] + facePoints[3]) / 4;
		tmpAddVh = dest.add_vertex(PolygonMesh::Point(newp[0], newp[1], newp[2]));
		new_face_vertices[(*f_it).idx()] = tmpAddVh;
	}

	PolygonMesh::HalfedgeHandle tmpHeh;
	PolygonMesh::VertexHandle tmpVh;
	PolygonMesh::FaceHandle tmpFh;
	for (auto e_it = src->edges_begin(); e_it != src->edges_end(); ++e_it)
	{
		tmpHeh = src->halfedge_handle(e_it, 0);
		tmpVh = src->from_vertex_handle(tmpHeh);
		tmpFh = src->opposite_face_handle(tmpHeh);

		facesHandle.push_back(old_vertices[tmpVh.idx()]);
		facesHandle.push_back(new_face_vertices[tmpFh.idx()]);

		tmpHeh = src->halfedge_handle(e_it, 1);
		tmpVh = src->from_vertex_handle(tmpHeh);
		tmpFh = src->opposite_face_handle(tmpHeh);

		facesHandle.push_back(old_vertices[tmpVh.idx()]);
		facesHandle.push_back(new_face_vertices[tmpFh.idx()]);

		dest.add_face(facesHandle);
		facesHandle.clear();
	}

	return true;
}