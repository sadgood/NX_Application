#pragma once
#include <NXOpen/CurveDumbRule.hxx>
#include <NXOpen/DatumCollection.hxx>
#include <NXOpen/DatumPlane.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_GeomcopyBuilder.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Plane.hxx>
#include <NXOpen/PlaneCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/ScCollectorCollection.hxx>
#include <NXOpen/ScRuleFactory.hxx>
using namespace NXOpen;

extern Features::Feature* CopyInstance(Features::Feature* Feature_init);