#include "Function_Repos.h"
#include "uf_defs.h"
#include "uf_modl.h"
#include "uf_curve.h"

extern int Create_Point(coord pt_coods[9], tag_t object_facet)
{
	coord pt_temp[5] = { 0 };
	pt_temp[0].base_pt[0] = (pt_coods[0].base_pt[0] + pt_coods[1].base_pt[0]) / 2;
	pt_temp[0].base_pt[1] = (pt_coods[0].base_pt[1] + pt_coods[1].base_pt[1]) / 2;
	pt_temp[0].base_pt[2] = (pt_coods[0].base_pt[2] + pt_coods[1].base_pt[2]) / 2;

	pt_temp[1].base_pt[0] = (pt_coods[1].base_pt[0] + pt_coods[2].base_pt[0]) / 2;
	pt_temp[1].base_pt[1] = (pt_coods[1].base_pt[1] + pt_coods[2].base_pt[1]) / 2;
	pt_temp[1].base_pt[2] = (pt_coods[1].base_pt[2] + pt_coods[2].base_pt[2]) / 2;

	pt_temp[2].base_pt[0] = (pt_coods[2].base_pt[0] + pt_coods[3].base_pt[0]) / 2;
	pt_temp[2].base_pt[1] = (pt_coods[2].base_pt[1] + pt_coods[3].base_pt[1]) / 2;
	pt_temp[2].base_pt[2] = (pt_coods[2].base_pt[2] + pt_coods[3].base_pt[2]) / 2;

	pt_temp[3].base_pt[0] = (pt_coods[3].base_pt[0] + pt_coods[0].base_pt[0]) / 2;
	pt_temp[3].base_pt[1] = (pt_coods[3].base_pt[1] + pt_coods[0].base_pt[1]) / 2;
	pt_temp[3].base_pt[2] = (pt_coods[3].base_pt[2] + pt_coods[0].base_pt[2]) / 2;

	pt_temp[4].base_pt[0] = (pt_temp[0].base_pt[0] + pt_temp[2].base_pt[0]) / 2;
	pt_temp[4].base_pt[1] = (pt_temp[0].base_pt[1] + pt_temp[2].base_pt[1]) / 2;
	pt_temp[4].base_pt[2] = (pt_temp[0].base_pt[2] + pt_temp[2].base_pt[2]) / 2;

	double guess2[3] = { 0.0,0.0,0.0 };
	double min_dist = 0.0;   //最短距离
	double pt_on_obj1[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object1（pt_temp）
	double pt_on_obj2[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object2（object_facet）

	for (int iLoop = 0; iLoop < 5; ++iLoop)
	{
		UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[iLoop].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2);
		pt_coods[iLoop + 4].base_pt[0] = pt_on_obj2[0];
		pt_coods[iLoop + 4].base_pt[1] = pt_on_obj2[1];
		pt_coods[iLoop + 4].base_pt[2] = pt_on_obj2[2];
	}

	return 0;
}

extern int Create_Line(coord pt_coods[9], tag_t spline_tag[6])
{
	int degree = 3;
	int num_points = 3;
	UF_CURVE_pt_slope_crvatr_t point_data[3] = { 0 };
	//double parameters[3] = { NULL };
	int save_def_data = 0;

	int pt_data[6][3] = { {0,4,1},{ 7,8,5 },{ 3,6,2 },{0,7,3},{ 4,8,6 },{1,5,2} };   //记录样条曲线中控制点的信息，共6条样条曲线，每条曲线上共3个控制点

	for (int nLoop = 0; nLoop < 6; ++nLoop)
	{
		for (int iLoop = 0; iLoop < 3; ++iLoop)
		{
			for (int jLoop = 0; jLoop < 3; ++jLoop)
			{
				point_data[iLoop].point[jLoop] = pt_coods[pt_data[nLoop][iLoop]].base_pt[jLoop];
			}
			point_data[iLoop].crvatr_type = UF_CURVE_CRVATR_AUTO_DIR;
			point_data[iLoop].slope_type = UF_CURVE_SLOPE_AUTO;
		}
		UF_CURVE_create_spline_thru_pts(degree, 0, num_points, point_data, NULL, 1, &spline_tag[nLoop]);
	}
	return 0;
}

extern int Create_Face(tag_t line[6])
{
	tag_t line_prim[3] = { 0 };
	tag_t line_cross[3] = { 0 };

	for (int iLoop = 0; iLoop < 3; ++iLoop)
	{
		line_prim[iLoop] = line[iLoop];
		line_cross[iLoop] = line[iLoop + 3];
	}

	int dir[3] = { UF_MODL_CURVE_START_FROM_BEGIN, UF_MODL_CURVE_START_FROM_BEGIN ,UF_MODL_CURVE_START_FROM_BEGIN };
	int string[3] = { 1 };

	UF_STRING_t s_prim;
	UF_MODL_init_string_list(&s_prim);
	UF_MODL_create_string_list(3, 3, &s_prim);
	s_prim.dir = dir;
	s_prim.id = line_prim;
	s_prim.string = string;

	UF_STRING_t s_cross;
	UF_MODL_init_string_list(&s_cross);
	UF_MODL_create_string_list(3, 3, &s_cross);
	s_cross.dir = dir;
	s_cross.id = line_cross;
	s_cross.string = string;

	UF_STRING_t s_spine;
	UF_MODL_init_string_list(&s_spine);
	UF_MODL_create_string_list(3, 3, &s_spine);

	int end_point = 0;
	int emphasis = 3;
	int body_type = 0;
	int spline_pts = 0;
	UF_FEATURE_SIGN boolean = UF_NULLSIGN;
	double tol[3] = { 0 };
	tag_t c_face_id[4] = { 0 };
	int c_flag[4] = { 0 };
	tag_t body_obj_id = 0;

	UF_MODL_create_curve_mesh(&s_prim, &s_cross, &s_spine, &end_point, &emphasis, &body_type, &spline_pts, boolean, tol, c_face_id, c_flag, &body_obj_id);

	return 0;
}