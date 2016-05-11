#pragma once
#include <NXOpen/Face.hxx>
#include <NXOpen/Features_AssociativeLineBuilder.hxx>
#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/Features_ThroughCurveMesh.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Plane.hxx>
#include <NXOpen/PlaneCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/SelectDisplayableObject.hxx>
#include <NXOpen/SelectPoint.hxx>
#include <vector>
using namespace NXOpen;
using namespace std;

extern Features::AssociativeLine* CreateAssociativeLine(Features::PointFeature *pointFeature1, Features::ThroughCurveMesh *throughCurveMesh1);