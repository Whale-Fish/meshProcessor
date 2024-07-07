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

	curType = SQRT2;
	return true;
}

bool Subdivision::subSqrt3(TriMesh* src, TriMesh& dest)
{
	dest.clear();

	int faces_num = src->n_faces();
	int vertices_num = src->n_vertices();

	std::vector<PolygonMesh::VertexHandle> face_vhandles;
	PolygonMesh::VertexHandle tmp_vhandle;
	PolygonMesh::Normal tmp_nor;
	std::vector<POINT3D>tmp_face_points_and_nors;

	dest.request_vertex_normals();
	dest.update_normals();

	std::vector<PolygonMesh::VertexHandle> midpoint_vec;
	std::vector<PolygonMesh::VertexHandle> origin_points_vec;
	std::vector<std::vector<int>> origin_face_points_id(faces_num);

	std::vector<POINT3D> my_point_nors_vec;

	// update old vertices
	for (PolygonMesh::VertexIter v_it = src->vertices_begin(); v_it != src->vertices_end(); v_it++)
	{
		POINT3D tmp_element;
		tmp_element = src->point(v_it);
		tmp_face_points_and_nors.push_back(tmp_element);

		//updata v
		int deg = 0;
		POINT3D surround_sum(0, 0, 0);
		for (PolygonMesh::VertexVertexIter vv_it = src->vv_iter(v_it); vv_it.is_valid(); vv_it++) {
			deg++;
			surround_sum += src->point(vv_it);
		}
		POINT3D newp;
		double alpha = (4 - 2 * cos(2 * PI / deg)) / 9;
		newp = (1 - alpha)*tmp_element + alpha / deg * surround_sum;

		tmp_vhandle = dest.add_vertex(PolygonMesh::Point(newp[0], newp[1], newp[2]));
		dest.set_normal(tmp_vhandle, tmp_nor);

		origin_points_vec.push_back(tmp_vhandle);
	}

	// add new face central point
	int ind = 0;
	for (PolygonMesh::FaceIter f_it = src->faces_begin(); f_it != src->faces_end(); ++f_it)
	{
		tmp_face_points_and_nors.clear();
		POINT3D newp(0, 0, 0);
		POINT3D newNor(0, 0, 0);
		POINT3D tmp_element;
		for (PolygonMesh::FaceVertexIter fv_it = src->fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			tmp_element = src->point(fv_it);
			tmp_face_points_and_nors.push_back(tmp_element);

			origin_face_points_id[ind].push_back((*fv_it).idx());
		}

		newp = (tmp_face_points_and_nors[0] + tmp_face_points_and_nors[1] + tmp_face_points_and_nors[2]) / 3.0;
		tmp_nor[0] = newNor[0]; tmp_nor[1] = newNor[1]; tmp_nor[2] = newNor[2];
		tmp_vhandle = dest.add_vertex(PolygonMesh::Point(newp[0], newp[1], newp[2]));
		dest.set_normal(tmp_vhandle, tmp_nor);

		midpoint_vec.push_back(tmp_vhandle);
		ind++;
	}

	//add faces
	for (int i = 0; i < faces_num; ++i)
	{
		face_vhandles.clear();
		face_vhandles.push_back(midpoint_vec[i]);
		face_vhandles.push_back(origin_points_vec[origin_face_points_id[i][0]]);
		face_vhandles.push_back(origin_points_vec[origin_face_points_id[i][1]]);
		dest.add_face(face_vhandles);
		face_vhandles.clear();
		face_vhandles.push_back(midpoint_vec[i]);
		face_vhandles.push_back(origin_points_vec[origin_face_points_id[i][1]]);
		face_vhandles.push_back(origin_points_vec[origin_face_points_id[i][2]]);
		dest.add_face(face_vhandles);
		face_vhandles.clear();
		face_vhandles.push_back(midpoint_vec[i]);
		face_vhandles.push_back(origin_points_vec[origin_face_points_id[i][2]]);
		face_vhandles.push_back(origin_points_vec[origin_face_points_id[i][0]]);
		dest.add_face(face_vhandles);
	}

	for (PolygonMesh::EdgeIter e_it = dest.edges_begin(); e_it != dest.edges_end(); ++e_it)
	{

		if (!dest.is_boundary(*e_it))
		{
			int id_from, id_to;
			id_from = (dest.from_vertex_handle(dest.halfedge_handle(e_it, 0))).idx();
			id_to = (dest.to_vertex_handle(dest.halfedge_handle(e_it, 0))).idx();
			if (id_from < vertices_num && id_to < vertices_num) //边不包括新生成的面中心点
			{
				dest.flip(*e_it);
			}
		}
	}

	curType = SQRT3;
	return true;
}