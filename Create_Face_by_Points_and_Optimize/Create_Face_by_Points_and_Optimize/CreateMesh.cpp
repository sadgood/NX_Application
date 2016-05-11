#include "CreateMesh.h"

extern Features::ThroughCurveMesh* CreateThroughCurveMesh(vector<vector<Features::studioSpline*> > studioSpline)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	// ----------------------------------------------
	//   Menu: Insert->Mesh Surface->Through Curve Mesh...
	// ----------------------------------------------

	Features::Feature *nullFeatures_Feature(NULL);

	Features::ThroughCurveMeshBuilder *throughCurveMeshBuilder1;
	throughCurveMeshBuilder1 = workPart->Features()->CreateThroughCurveMeshBuilder(nullFeatures_Feature);

	Section *section1;
	section1 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	throughCurveMeshBuilder1->PrimaryCurvesList()->Append(section1);

	section1->SetAllowedEntityTypes(Section::AllowTypesCurvesAndPoints);

	
	std::vector<Features::Feature *> features1(1);
	features1[0] = studioSpline[0][0];
	Spline *spline1(dynamic_cast<Spline *>(studioSpline[0][0]->FindObject("CURVE 1")));
	Curve *nullCurve(NULL);
	CurveFeatureTangentRule *curveFeatureTangentRule1;
	curveFeatureTangentRule1 = workPart->ScRuleFactory()->CreateRuleCurveFeatureTangent(features1, spline1, nullCurve, false, 0.00095, 0.05);

	section1->AllowSelfIntersection(false);

	std::vector<SelectionIntentRule *> rules1(1);
	rules1[0] = curveFeatureTangentRule1;
	NXObject *nullNXObject(NULL);
	Point3d helpPoint1(0.0, 0.0, 0.0);
	section1->AddToSection(rules1, spline1, nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);

	Section *section2;
	section2 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	throughCurveMeshBuilder1->PrimaryCurvesList()->Append(section2);

	section2->SetAllowedEntityTypes(Section::AllowTypesCurvesAndPoints);

	std::vector<Features::Feature *> features2(1);
	features2[0] = studioSpline[0][1];
	Spline *spline2(dynamic_cast<Spline *>(studioSpline[0][1]->FindObject("CURVE 1")));
	CurveFeatureTangentRule *curveFeatureTangentRule2;
	curveFeatureTangentRule2 = workPart->ScRuleFactory()->CreateRuleCurveFeatureTangent(features2, spline2, nullCurve, false, 0.00095, 0.05);

	section2->AllowSelfIntersection(false);

	std::vector<SelectionIntentRule *> rules2(1);
	rules2[0] = curveFeatureTangentRule2;
	Point3d helpPoint2(0.0, 0.0, 0.0);
	section2->AddToSection(rules2, spline2, nullNXObject, nullNXObject, helpPoint2, Section::ModeCreate, false);

	Section *section3;
	section3 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	throughCurveMeshBuilder1->PrimaryCurvesList()->Append(section3);

	section3->SetAllowedEntityTypes(Section::AllowTypesCurvesAndPoints);

	std::vector<Features::Feature *> features3(1);
	features3[0] = studioSpline[0][2];
	Spline *spline3(dynamic_cast<Spline *>(studioSpline[0][2]->FindObject("CURVE 1")));
	CurveFeatureTangentRule *curveFeatureTangentRule3;
	curveFeatureTangentRule3 = workPart->ScRuleFactory()->CreateRuleCurveFeatureTangent(features3, spline3, nullCurve, false, 0.00095, 0.05);

	section3->AllowSelfIntersection(false);

	std::vector<SelectionIntentRule *> rules3(1);
	rules3[0] = curveFeatureTangentRule3;
	Point3d helpPoint3(0.0, 0.0, 0.0);
	section3->AddToSection(rules3, spline3, nullNXObject, nullNXObject, helpPoint3, Section::ModeCreate, false);

	Section *section4;
	section4 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	throughCurveMeshBuilder1->CrossCurvesList()->Append(section4);

	section4->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);

	std::vector<Features::Feature *> features4(1);
	features4[0] = studioSpline[1][0];
	Spline *spline4(dynamic_cast<Spline *>(studioSpline[1][0]->FindObject("CURVE 1")));
	CurveFeatureTangentRule *curveFeatureTangentRule4;
	curveFeatureTangentRule4 = workPart->ScRuleFactory()->CreateRuleCurveFeatureTangent(features4, spline4, nullCurve, false, 0.00095, 0.05);

	section4->AllowSelfIntersection(false);

	std::vector<SelectionIntentRule *> rules4(1);
	rules4[0] = curveFeatureTangentRule4;
	Point3d helpPoint4(0.0, 0.0, 0.0);
	section4->AddToSection(rules4, spline4, nullNXObject, nullNXObject, helpPoint4, Section::ModeCreate, false);

	Section *section5;
	section5 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	throughCurveMeshBuilder1->CrossCurvesList()->Append(section5);

	section5->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);

	std::vector<Features::Feature *> features5(1);
	features5[0] = studioSpline[1][1];
	Spline *spline5(dynamic_cast<Spline *>(studioSpline[1][1]->FindObject("CURVE 1")));
	CurveFeatureTangentRule *curveFeatureTangentRule5;
	curveFeatureTangentRule5 = workPart->ScRuleFactory()->CreateRuleCurveFeatureTangent(features5, spline5, nullCurve, false, 0.00095, 0.05);

	section5->AllowSelfIntersection(false);

	std::vector<SelectionIntentRule *> rules5(1);
	rules5[0] = curveFeatureTangentRule5;
	Point3d helpPoint5(0.0, 0.0, 0.0);
	section5->AddToSection(rules5, spline5, nullNXObject, nullNXObject, helpPoint5, Section::ModeCreate, false);

	Section *section6;
	section6 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	throughCurveMeshBuilder1->CrossCurvesList()->Append(section6);

	section6->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);

	std::vector<Features::Feature *> features6(1);
	features6[0] = studioSpline[1][2];
	Spline *spline6(dynamic_cast<Spline *>(studioSpline[1][2]->FindObject("CURVE 1")));
	CurveFeatureTangentRule *curveFeatureTangentRule6;
	curveFeatureTangentRule6 = workPart->ScRuleFactory()->CreateRuleCurveFeatureTangent(features6, spline6, nullCurve, false, 0.00095, 0.05);

	section6->AllowSelfIntersection(false);

	std::vector<SelectionIntentRule *> rules6(1);
	rules6[0] = curveFeatureTangentRule6;
	Point3d helpPoint6(0.0, 0.0, 0.0);
	section6->AddToSection(rules6, spline6, nullNXObject, nullNXObject, helpPoint6, Section::ModeCreate, false);

	Features::Feature *feature1;
	feature1 = throughCurveMeshBuilder1->CommitFeature();

	throughCurveMeshBuilder1->Destroy();

	return (Features::ThroughCurveMesh*)feature1;
	// ----------------------------------------------
	//   Menu: Tools->Journal->Stop Recording
	// ----------------------------------------------
}
