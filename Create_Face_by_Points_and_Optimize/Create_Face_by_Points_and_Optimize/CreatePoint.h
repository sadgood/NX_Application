#pragma once

#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Features_PointFeature.hxx>

#include <vector>

#include "uf_defs.h"
#include "uf_modl.h"
#include "uf_curve.h"

using namespace std;
using namespace NXOpen;

struct coord
{
	double base_pt[3];
};

extern Point* CreatePoint(double coord[3]);
extern int GetPointsCoord(coord *pt_coods_selected, const tag_t &object_facet, vector<vector<coord> > &pt_coods);