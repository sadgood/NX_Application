#include "uf.h"
#include "uf_evalsf.h"
#include "uf_modl.h"
#include "uf_vec.h"
#include "uf_curve.h"
#include "uf_facet.h"
#include "uf_csys.h"
#include "uf_mtx.h"

#include <time.h>
#include <vector>
#include <assert.h>

using namespace std;

struct coord_s
{
	double pos[3];
	double vec1[3];
};

bool AskFacetIsInPoint(tag_t object_facet, coord_s pt, double du[3], double dv[3], bool &FacetIsInFace);

// if run error return error code
// if run well return 0
extern int CalcFaceFacetDistance(tag_t object_face, tag_t object_facet, double &averageDist, int point_num_along_U, int point_num_along_V)
{
	assert(object_face != NULL_TAG);
	assert(object_facet != NULL_TAG);

	vector<coord_s> point_vector;  //定义点坐标容器
	double dist_sqrt = 0.0;         //最小二乘距离
	double vec2[3] = { 0.0,0.0,0.0 };  //uv生成点与其最近距离facet上点连线的方向向量

	UF_EVALSF_p_t evaluator = NULL;

	UF_EVALSF_initialize(object_face, &evaluator);  //对曲面参数初始化

	double uv_min_max[4] = { 0.0, 0.0, 0.0, 0.0 };

	UF_EVALSF_ask_face_uv_minmax(evaluator, uv_min_max);    //获取曲面的U线、V线参数

	double uv_pair[2] = { 0.0, 0.0 };
	UF_MODL_SRF_VALUE_t surf_eval = { NULL };

	coord_s PosTemp = { 0, 0 ,0 };

	for (int iLoop = 0; iLoop < point_num_along_U; ++iLoop)
	{
		for (int jLoop = 0; jLoop < point_num_along_V; ++jLoop)
		{
			uv_pair[0] = uv_min_max[0] + (uv_min_max[1] - uv_min_max[0]) * iLoop / point_num_along_U;
			uv_pair[1] = uv_min_max[2] + (uv_min_max[3] - uv_min_max[2]) * jLoop / point_num_along_V;

			UF_EVALSF_evaluate(evaluator, UF_MODL_EVAL_DERIV1, uv_pair, &surf_eval); //获取曲面信息（获取曲面上单一点，以及此点初的各种属性，例如方向向量）

			PosTemp.vec1[0] = surf_eval.srf_normal[0];
			PosTemp.vec1[1] = surf_eval.srf_normal[1];
			PosTemp.vec1[2] = surf_eval.srf_normal[2];  //该点处向量

			PosTemp.pos[0] = surf_eval.srf_pos[0];
			PosTemp.pos[1] = surf_eval.srf_pos[1];
			PosTemp.pos[2] = surf_eval.srf_pos[2];   //该点坐标

			bool FacetIsInFace = false;
			AskFacetIsInPoint(object_facet, PosTemp, surf_eval.srf_du, surf_eval.srf_dv, FacetIsInFace);
			if (FacetIsInFace == true)
			{
				point_vector.push_back(PosTemp);   //储存该点信息
			}

			PosTemp.pos[0] = 0.0;
			PosTemp.pos[1] = 0.0;
			PosTemp.pos[2] = 0.0;
			PosTemp.vec1[0] = 0.0;
			PosTemp.vec1[1] = 0.0;
			PosTemp.vec1[2] = 0.0;   //重新置零
		}
	}//在uv方向上截取出point_num_along_U*point_num_along_V个点

	double UV_Point[3] = { 0.0,0.0,0.0 };  //储存中的UV上的点坐标
	double guess2[3] = { 0.0,0.0,0.0 };
	double min_dist = 0.0;   //最短距离
	double pt_on_obj1[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object1（UV_Point）
	double pt_on_obj2[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object2（object_facet）

	for (int kLoop = 0; kLoop < point_vector.size(); ++kLoop)
	{
		UV_Point[0] = point_vector[kLoop].pos[0];
		UV_Point[1] = point_vector[kLoop].pos[1];
		UV_Point[2] = point_vector[kLoop].pos[2];   //储存中的UV上的点坐标
		UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, UV_Point, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2);  //UV_Point点到object_facet的最小距离
		dist_sqrt += min_dist * min_dist;
	}

	dist_sqrt = dist_sqrt / point_vector.size();
	averageDist = sqrt(dist_sqrt);  //计算最小二乘距离

	UF_EVALSF_free(&evaluator);  //清除指针

	int error_code = 0;
	return error_code;
}

bool AskFacetIsInPoint(tag_t object_facet, coord_s pt, double du[3], double dv[3], bool &FacetIsInFace)
{
	tag_t csys_id = 0;
	double matrix_values[9] = { 0 };
	tag_t matrix_id = 0;

	double x_vec[3] = { du[0],du[1],du[2] };//X方向矢量
	double y_vec[3] = { dv[0],dv[1],dv[2] };//Y方向矢量

	UF_MTX3_initialize(x_vec, y_vec, matrix_values);
	UF_CSYS_create_matrix(matrix_values, &matrix_id);
	UF_CSYS_create_csys(pt.pos, matrix_id, &csys_id);
	UF_CSYS_set_wcs(csys_id);
	
	int numFacets = 0;
	UF_FACET_ask_n_facets_in_model(object_facet, &numFacets);  //获取小平面体的个数
	//for (int iLoop = 0; iLoop < numFacets; ++iLoop)
	for (int iLoop = 0; iLoop < 1; ++iLoop)
	{
		int numVertices = 0;
		double vertices[6][3] = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };

		UF_FACET_ask_vertices_of_facet(object_facet, iLoop, &numVertices, vertices);
		double map_vertices[6][3] = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };

		for (int jLoop = 0; jLoop < numVertices; jLoop++)
		{
			UF_CSYS_map_point(UF_CSYS_ROOT_COORDS, vertices[jLoop], UF_CSYS_ROOT_WCS_COORDS, map_vertices[jLoop]);
		}
	}
	FacetIsInFace = true;
	return true;
}