#pragma once

#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Features_PointFeature.hxx>

using namespace std;
using namespace NXOpen;

extern Features::PointFeature * CreatePointFeature(double coord[3]);