#pragma once
#include <NXOpen/NXException.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Face.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_IsoparametricCurvesBuilder.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/Features_ThroughCurveMesh.hxx>
#include <NXOpen/ModelingView.hxx>
#include <NXOpen/ModelingViewCollection.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/ScalarCollection.hxx>
#include <NXOpen/SelectDisplayableObject.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/UnitCollection.hxx>
#include <vector>

using namespace NXOpen;
using namespace std;

extern Features::IsoparametricCurves * IsoparametricCurvesOnFace(Features::ThroughCurveMesh *throughCurveMesh, Features::PointFeature *pointFeature);