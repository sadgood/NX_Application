#include "uf.h"
#include "uf_evalsf.h"
#include "uf_modl.h"
#include "uf_vec.h"
#include "uf_curve.h"

#include <time.h>
#include <vector>
#include <assert.h>

using namespace std;

struct coord_s
{
	double pos[3];
	double vec1[3];
};

// if run error return error code
// if run well return 0
extern int CalcFaceFacetDistance(tag_t object_face,	tag_t object_facet, double &averageDist,int point_num_along_U, int point_num_along_V)
{
	assert(object_face != NULL_TAG);
	assert(object_facet != NULL_TAG);
	
	vector<coord_s> point_vector;  //定义点坐标容器
	double dist_sqrt = 0.0;         //最小二乘距离
	double vec2[3] = { 0.0,0.0,0.0 };

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

			UF_EVALSF_evaluate(evaluator, UF_MODL_EVAL_DERIV1, uv_pair, &surf_eval); //获取曲面信息

			PosTemp.vec1[0] = surf_eval.srf_normal[0];
			PosTemp.vec1[1] = surf_eval.srf_normal[1];
			PosTemp.vec1[2] = surf_eval.srf_normal[2];

			PosTemp.pos[0] = surf_eval.srf_pos[0];
			PosTemp.pos[1] = surf_eval.srf_pos[1];
			PosTemp.pos[2] = surf_eval.srf_pos[2];

			point_vector.push_back(PosTemp);

			PosTemp.pos[0] = 0.0;
			PosTemp.pos[1] = 0.0;
			PosTemp.pos[2] = 0.0;
			PosTemp.vec1[0] = 0.0;
			PosTemp.vec1[1] = 0.0;
			PosTemp.vec1[2] = 0.0;
		}
	}

	double guess1[3] = { 0.0,0.0,0.0 };
	double guess2[3] = { 0.0,0.0,0.0 };
	double min_dist = 0.0;
	double pt_on_obj1[3] = { 0.0,0.0,0.0 };
	double pt_on_obj2[3] = { 0.0,0.0,0.0 };

	int count = 0;

	for (int kLoop = 0; kLoop < point_vector.size(); ++kLoop)
	{
		int is_parallel = 0;

		guess1[0] = point_vector[kLoop].pos[0];
		guess1[1] = point_vector[kLoop].pos[1];
		guess1[2] = point_vector[kLoop].pos[2];

		//UF_CURVE_create_point(point_vector[kLoop].pos, &ads[kLoop]);
		
		UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, guess1, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2);

		UF_CURVE_line_t line_coords;
		tag_t line;

		line_coords.start_point[0] = guess1[0];
		line_coords.start_point[1] = guess1[1];
		line_coords.start_point[2] = guess1[2];
		line_coords.end_point[0] = pt_on_obj2[0];
		line_coords.end_point[1] = pt_on_obj2[1];
		line_coords.end_point[2] = pt_on_obj2[2];

		UF_CURVE_create_line(&line_coords, &line);

		vec2[0] = pt_on_obj2[0] - pt_on_obj1[0];
		vec2[1] = pt_on_obj2[1] - pt_on_obj1[1];
		vec2[2] = pt_on_obj2[2] - pt_on_obj1[2];

		UF_VEC3_is_parallel(point_vector[kLoop].vec1, vec2, 1e-8, &is_parallel);
		if(is_parallel == 1)
		{
			dist_sqrt += min_dist * min_dist;
			count++;
		}
	}
	
	dist_sqrt = dist_sqrt / count;
	averageDist = sqrt(dist_sqrt);
	
	UF_EVALSF_free(&evaluator);

	int error_code = 0;
	return error_code;
}