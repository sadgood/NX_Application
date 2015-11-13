#include "Function_Repos.h"
#include "uf_defs.h"
#include "uf_modl.h"

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
	double min_dist = 0.0;   //×î¶Ì¾àÀë
	double pt_on_obj1[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object1£¨pt_temp£©
	double pt_on_obj2[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object2£¨object_facet£©

	for (int iLoop = 0; iLoop < 5; ++iLoop)
	{
		UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[iLoop].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2);
		pt_coods[iLoop + 4].base_pt[0] = pt_on_obj2[0];
		pt_coods[iLoop + 4].base_pt[1] = pt_on_obj2[1];
		pt_coods[iLoop + 4].base_pt[2] = pt_on_obj2[2];
	}
	
	return 0;
}

extern int Create_Line(coord pt_coods[9])
{

	return 0;
}

extern int Create_Face(coord pt_coods[9])
{

	return 0;
}