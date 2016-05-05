#pragma once

#include <NXOpen/NXException.hxx>
#include <NXOpen/CurveFeatureTangentRule.hxx>
#include <NXOpen/DisplayManager.hxx>
#include <NXOpen/Face.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_StudioSpline.hxx>
#include <NXOpen/Features_ThroughCurveMesh.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/Preferences_SessionModeling.hxx>
#include <NXOpen/Preferences_SessionPreferences.hxx>
#include <NXOpen/ScRuleFactory.hxx>
#include <NXOpen/SectionCollection.hxx>
#include <NXOpen/SectionList.hxx>
#include <NXOpen/Spline.hxx>
#include <vector>
using namespace NXOpen;
using namespace std;

extern Features::ThroughCurveMesh* CreateThroughCurveMesh(vector<vector<Features::StudioSpline*> > studioSpline);