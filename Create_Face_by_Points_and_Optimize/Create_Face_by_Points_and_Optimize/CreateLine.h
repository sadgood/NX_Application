#pragma once
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/Features_StudioSplineBuilderEx.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Features_StudioSpline.hxx>

using namespace NXOpen;

extern Features::StudioSpline* CreateLine(Features::PointFeature *pointFeature1, Features::PointFeature *pointFeature2, Features::PointFeature *pointFeature3);