#pragma once
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_AssociativeLine.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/Features_StudioSpline.hxx>
#include <NXOpen/Features_StudioSplineBuilderEx.hxx>
#include <NXOpen/Line.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Scalar.hxx>
#include <NXOpen/ScalarCollection.hxx>

using namespace NXOpen;

extern Features::StudioSpline* CreateStudioSplineByPoints(Features::PointFeature *pointFeature1, Features::PointFeature *pointFeature2, Features::PointFeature *pointFeature3);

extern Features::StudioSpline* CreateStudioSplineByLine(Features::AssociativeLine* associativeLine1, Features::AssociativeLine* associativeLine2, Features::AssociativeLine* associativeLine3);