#pragma once
#include "uf_defs.h"
struct coord
{
	double base_pt[3];
};

extern int Create_Point(coord pt_coods[9], tag_t object_facet);

extern int Create_Line(coord pt_coods[9], tag_t spline_tag[6]);

extern int Create_Face(tag_t line[6], tag_t &body_obj_id);