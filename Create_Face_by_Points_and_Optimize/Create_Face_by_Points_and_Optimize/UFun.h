#pragma once

#include <iostream>
#include <set>
#include <string>
#include <uf.h>
#include <uf_ui.h>
#include <uf_exit.h>
#include <uf_kf.h>
#include <uf_group.h>
#include <uf_obj.h>
#include <assert.h>
#include <uf_assem.h>
#include <uf_modl.h>
#include <uf_facet.h>
#include "Create_Face_by_Points_and_Optimize.hpp"

using namespace std;

extern void MISC_AskSheetToFacetAverageDistance(
	tag_t facetBody,    /*<I>*/
	tag_t sheetBody,
	double &result       /*<O>*/
);