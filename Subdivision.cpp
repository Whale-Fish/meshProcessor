#include "Subdivision.h"


#define PI 3.1415926

bool Subdivision::subSqrt2(PolygonMesh* src, PolygonMesh& dest)
{
	curType = SQRT2;

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

bool Subdivision::subSqrt3(TriMesh* src, TriMesh& dest)
{
	curType = SQRT3;

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

	return true;
}

bool Subdivision::subISqrt2(PolygonMesh* src, PolygonMesh& dest)
{
	curType = ISQRT2;

	auto hasIregularPointsQuad = [](PolygonMesh::FaceHandle fh, PolygonMesh *mesh){
		int deg = 0;
		for (auto vh = mesh->fv_iter(fh); vh.is_valid(); vh++) {
			for (auto it = mesh->vv_iter(vh); it.is_valid(); it++) {
				deg++;
			}
			if (deg != 4) return true;
			deg = 0;
		}
		return false;
	};

	dest.clear();
	int faces_num = src->n_faces();
	int vertices_num = src->n_vertices();

	std::vector<PolygonMesh::VertexHandle>old_vertices(vertices_num);
	std::vector<PolygonMesh::VertexHandle>new_face_vertices(faces_num);
	PolygonMesh::VertexHandle tmp_add_vh;
	std::vector<PolygonMesh::VertexHandle>faces_handle;

	for (auto v_it = src->vertices_begin(); v_it != src->vertices_end(); v_it++)
	{
		POINT3D tmp_point, tmp_norr;
		tmp_point = src->point(v_it);

		tmp_add_vh = dest.add_vertex(PolygonMesh::Point(tmp_point[0], tmp_point[1], tmp_point[2]));
		old_vertices[(*v_it).idx()] = tmp_add_vh;
	}

	//cac_new_face_points
	for (auto f_it = src->faces_begin(); f_it != src->faces_end(); ++f_it) {
		std::vector<POINT3D>face_points;
		std::vector<POINT3D>face_nors;
		std::vector<POINT3D>originFacePoints;
		for (auto fv_it = src->fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
			POINT3D tmp_p;
			tmp_p = src->point(fv_it);
			originFacePoints.push_back(tmp_p);
		}

		int test_n = 0;
		if (hasIregularPointsQuad(*f_it, src)) {
			POINT3D new_p(0, 0, 0), new_nor;
			for (auto fv_it = src->fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
				POINT3D quadV;
				quadV = src->point(fv_it);
				new_p += 0.5 * quadV;

				int quadVecIndex = 0;
				for (int i = 0; i < 4; ++i) {
					if (quadV == originFacePoints[i]) {
						quadVecIndex = i;
						break;
					}
				}
				POINT3D quadVNext = originFacePoints[(quadVecIndex + 1) % 4]; //获得1邻域内的起始第一个顶点

				for (auto fvv_it = src->vv_iter(fv_it); fvv_it.is_valid(); ++fvv_it) {
					POINT3D tmpP;
					tmpP = src->point(fvv_it);
					face_points.push_back(tmpP);
				}

				int firstIndex = 0;
				for (int i = 0; i < face_points.size(); ++i) {
					if (face_points[i] == quadVNext) {
						firstIndex = i;
						break;
					}
				}

				int n = face_points.size();
				for (int i = 0; i < n; ++i) {
					float alpha = 1.0 / 2 / n * (1 + cos(2 * i*PI / n) + cos(2 * (i - 1)*PI / n) - sin(2 * i*PI / n) - sin(2 * (i - 1)*PI / n));
					new_p += alpha * face_points[(firstIndex - i + n) % n]; //逆时针
				}

				test_n++;
				face_points.clear();
			}

			new_p /= 4.0;
			tmp_add_vh = dest.add_vertex(PolygonMesh::Point(new_p[0], new_p[1], new_p[2]));
			new_face_vertices[(*f_it).idx()] = tmp_add_vh;
		}
		else
		{
			for (auto fv_it = src->fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
			{
				POINT3D tmp_point, tmp_norr;
				tmp_point = src->point(fv_it);
				face_points.push_back(tmp_point);
				tmp_norr = src->normal(fv_it);
				face_nors.push_back(tmp_norr);
			}

			for (auto fh_it = src->fh_iter(*f_it); fh_it.is_valid(); ++fh_it) {
				auto ofh_it = src->opposite_halfedge_handle(fh_it);
				auto nextOfh_it = src->next_halfedge_handle(ofh_it);
				auto nNextOfh_it = src->next_halfedge_handle(nextOfh_it);
				POINT3D t1, t2;
				t1 = src->point(src->from_vertex_handle(nNextOfh_it));
				t2 = src->point(src->to_vertex_handle(nNextOfh_it));
				face_points.push_back(t1);
				face_points.push_back(t2);
			}

			POINT3D new_p(0, 0, 0);
			for (int i = 0; i < 12; ++i) {
				if (i < 4) {
					new_p += 5.0 / 16 * face_points[i];
				}
				else
				{
					new_p -= 1.0 / 32 * face_points[i];
				}
			}

			tmp_add_vh = dest.add_vertex(PolygonMesh::Point(new_p[0], new_p[1], new_p[2]));
			new_face_vertices[(*f_it).idx()] = tmp_add_vh;
		}
	}

	PolygonMesh::HalfedgeHandle tmp_heh;
	PolygonMesh::VertexHandle tmp_vh;
	PolygonMesh::FaceHandle tmp_fh;
	for (auto e_it = src->edges_begin(); e_it != src->edges_end(); ++e_it)
	{
		tmp_heh = src->halfedge_handle(e_it, 0);
		tmp_vh = src->from_vertex_handle(tmp_heh);
		tmp_fh = src->opposite_face_handle(tmp_heh);

		faces_handle.push_back(old_vertices[tmp_vh.idx()]);
		faces_handle.push_back(new_face_vertices[tmp_fh.idx()]);

		tmp_heh = src->halfedge_handle(e_it, 1);
		tmp_vh = src->from_vertex_handle(tmp_heh);
		tmp_fh = src->opposite_face_handle(tmp_heh);

		faces_handle.push_back(old_vertices[tmp_vh.idx()]);
		faces_handle.push_back(new_face_vertices[tmp_fh.idx()]);

		dest.add_face(faces_handle);
		faces_handle.clear();
	}

	return true;
}

bool Subdivision::subISqrt3(TriMesh* src, TriMesh& dest)
{
	curType = ISQRT3;

	dest.clear();

	int faces_num = src->n_faces();
	int vertices_num = src->n_vertices();

	std::vector<PolygonMesh::VertexHandle> face_vhandles;
	PolygonMesh::VertexHandle tmp_vhandle;

	dest.request_vertex_normals();
	dest.update_normals();

	std::vector<PolygonMesh::VertexHandle> midpoint_vec;
	std::vector<PolygonMesh::VertexHandle> origin_points_vec;
	std::vector<std::vector<int>> origin_face_points_id(faces_num);

	for (PolygonMesh::VertexIter v_it = src->vertices_begin(); v_it != src->vertices_end(); v_it++)
	{
		POINT3D tmp_element;
		tmp_element = src->point(v_it);
		tmp_vhandle = dest.add_vertex(PolygonMesh::Point(tmp_element[0], tmp_element[1], tmp_element[2]));
		origin_points_vec.push_back(tmp_vhandle);
	}

	int ind = 0;
	for (PolygonMesh::FaceIter f_it = src->faces_begin(); f_it != src->faces_end(); ++f_it)
	{
		POINT3D newp(0, 0, 0);
		POINT3D point3AreaSum(0, 0, 0);
		POINT3D pointsOnTriangleSum(0, 0, 0);
		POINT3D pointsBoundaryMidSum(0, 0, 0);
		for (auto fh_it = src->fh_iter(*f_it); fh_it.is_valid(); ++fh_it) {
			auto opHalfEdge = src->opposite_halfedge_handle(fh_it);
			auto boundaryMidVhandle = src->opposite_he_opposite_vh(opHalfEdge);
			
			POINT3D edgeMidPoint;
			edgeMidPoint = src->point(boundaryMidVhandle);
			pointsBoundaryMidSum += edgeMidPoint;
		}

		for (PolygonMesh::FaceVertexIter fv_it = src->fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			pointsOnTriangleSum += src->point(fv_it);
			for (auto fvv_it = src->vv_iter(*fv_it); fvv_it.is_valid(); ++fvv_it) 
			{
				point3AreaSum += src->point(fvv_it);
			}
			origin_face_points_id[ind].push_back((*fv_it).idx());
		}

		newp = -2.0 / 81 * (point3AreaSum - 2 * pointsBoundaryMidSum - 2 * pointsOnTriangleSum) + 32.0 / 81 * pointsOnTriangleSum - 1.0 / 81 * pointsBoundaryMidSum;
		tmp_vhandle = dest.add_vertex(PolygonMesh::Point(newp[0], newp[1], newp[2]));

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
			id_from = (dest.from_vertex_handle(src->halfedge_handle(e_it, 0))).idx();
			id_to = (dest.to_vertex_handle(src->halfedge_handle(e_it, 0))).idx();
			if (id_from < vertices_num && id_to < vertices_num)
			{
				dest.flip(*e_it);
			}
		}
	}

	return true;
}