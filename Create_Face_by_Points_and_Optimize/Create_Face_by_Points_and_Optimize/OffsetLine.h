#pragma once
#include <NXOpen/CurveFeatureTangentRule.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Face.hxx>
#include <NXOpen/FaceTangentRule.hxx>
#include <NXOpen/Features_AOCSBuilder.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_StudioSpline.hxx>
#include <NXOpen/Features_ThroughCurveMesh.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/ScCollectorCollection.hxx>
#include <NXOpen/ScRuleFactory.hxx>
#include <NXOpen/SectionCollection.hxx>
#include <NXOpen/Spline.hxx>
using namespace NXOpen;

extern Features::AOCSBuilder* OffsetLine(Features::StudioSpline *studioSpline1, Features::ThroughCurveMesh *throughCurveMesh1, double Distance);