#include "uf.h"
#include "uf_evalsf.h"
#include "uf_modl.h"
#include "uf_vec.h"
#include "uf_curve.h"
#include "uf_facet.h"
#include "uf_csys.h"
#include "uf_mtx.h"

#include <vector>
#include <assert.h>

using namespace std;

struct coord_s
{
	double pos[3];
	double vec1[3];
};

bool AskFacetIsInPoint(tag_t object_facet, coord_s pt, double du[3], double dv[3], bool &FacetIsInFace);
bool pointInPolygon(int polySides, double polyX[], double polyY[], double x, double y);

// if run error return error code
// if run well return 0
extern int CalcFaceFacetDistance(tag_t object_face, tag_t object_facet, double &averageDist, int point_num_along_U, int point_num_along_V)
{
	assert(object_face != NULL_TAG);
	assert(object_facet != NULL_TAG);
	
	int error_code = 0;

	vector<coord_s> point_vector;  //定义点坐标容器（只记录有效点）
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
			AskFacetIsInPoint(object_facet, PosTemp, surf_eval.srf_du, surf_eval.srf_dv, FacetIsInFace);  //判断点法线方向上是否有小平面体
			if (FacetIsInFace == true)  //如果有效则记录
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

	return error_code;
}

bool AskFacetIsInPoint(tag_t object_facet, coord_s pt, double du[3], double dv[3], bool &FacetIsInFace)
{
	FacetIsInFace = false;

	tag_t csys_id = 0;  //坐标系ID
	double matrix_values[9] = { 0 }; //坐标系矩阵
	tag_t matrix_id = 0;  //矩阵ID

	double x_vec[3] = { du[0],du[1],du[2] };//X方向矢量
	double y_vec[3] = { dv[0],dv[1],dv[2] };//Y方向矢量

	UF_MTX3_initialize(x_vec, y_vec, matrix_values);
	UF_CSYS_create_matrix(matrix_values, &matrix_id);
	UF_CSYS_create_temp_csys(pt.pos, matrix_id, &csys_id);
	UF_CSYS_set_wcs(csys_id);
	
	int numFacets = 0;  //记录小平面体个数
	UF_FACET_ask_n_facets_in_model(object_facet, &numFacets);  //获取小平面体的个数
	for (int iLoop = 0; iLoop < numFacets; ++iLoop)
	//for (int iLoop = 0; iLoop < 1; ++iLoop)  //调试用
	{
		int numVertices = 0;  //小平面体顶点数，也是多边形边数
		double vertices[6][3] = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } }; //facet body顶点坐标

		UF_FACET_ask_vertices_of_facet(object_facet, iLoop, &numVertices, vertices);
		double map_vertices[6][3] = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };//映射后顶点坐标

		double polyX[6] = { 0 }; //记录多边形顶点x坐标
		double polyY[6] = { 0 }; //记录多边形顶点y坐标
		
		for (int jLoop = 0; jLoop < numVertices; ++jLoop)
		{
			UF_CSYS_map_point(UF_CSYS_ROOT_COORDS, vertices[jLoop], UF_CSYS_ROOT_WCS_COORDS, map_vertices[jLoop]);  //映射到相对坐标系
			polyX[jLoop] = map_vertices[jLoop][0];
			polyY[jLoop] = map_vertices[jLoop][1];
		}

		FacetIsInFace = pointInPolygon(numVertices, polyX, polyY, 0.0, 0.0);  //测试点即原点(0,0)
		if (FacetIsInFace == true)
		{
			break;   //如果点法线上方有小平面体，则停止循环，返回true
		}
	}
	return FacetIsInFace;
}

bool pointInPolygon(int polySides, double polyX[], double polyY[], double x, double y)
{
	int   i, j = polySides - 1;
	bool  oddNodes = false;

	for (i = 0; i < polySides; i++)
	{
		if ((polyY[i] < y && polyY[j] >= y || polyY[j] < y && polyY[i] >= y) && (polyX[i] <= x || polyX[j] <= x))
		{
			oddNodes ^= (polyX[i] + (y - polyY[i]) / (polyY[j] - polyY[i])*(polyX[j] - polyX[i]) < x);
		}
		j = i;
	}

	return oddNodes;
}  //判断点是否在多边形内