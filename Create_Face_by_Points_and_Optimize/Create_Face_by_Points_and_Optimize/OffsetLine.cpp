#include "OffsetLine.h"

extern Features::AOCSBuilder* OffsetLine(Features::StudioSpline *studioSpline1, Features::ThroughCurveMesh *throughCurveMesh1, double Distance)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	Features::Feature *nullFeatures_Feature(NULL);

	Features::AOCSBuilder *aOCSBuilder1;
	aOCSBuilder1 = workPart->Features()->CreateAocsBuilder(nullFeatures_Feature);

	Section *section1;
	section1 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	aOCSBuilder1->SetLawString(section1);

	GeometricUtilities::LawBuilder *lawBuilder1;
	lawBuilder1 = aOCSBuilder1->Law();

	Expression *expression3;
	expression3 = lawBuilder1->Value();

	ScCollector *nullScCollector(NULL);
	aOCSBuilder1->SetFaceCollector(nullScCollector);

	aOCSBuilder1->SetTrimMethod(Features::AOCSBuilder::TrimWithinSection);

	aOCSBuilder1->SetExtendMethod(Features::AOCSBuilder::ExtendWithinSection);

	aOCSBuilder1->SetTrimToFaceEdgesOption(false);

	aOCSBuilder1->SetExtendToFaceOption(Features::AOCSBuilder::ExtendToFaceNone);

	aOCSBuilder1->SetAssociativeOutputOption(true);

	aOCSBuilder1->SetOffsetMode(Features::AOCSBuilder::OffsetTypeChordal);

	aOCSBuilder1->SetDistanceTolerance(0.001);

	aOCSBuilder1->SetOffsetDistType(Features::AOCSBuilder::OffsetDistanceTypeVariable);

	aOCSBuilder1->SetLawStringFlip(false);

	aOCSBuilder1->SetOffsetDirectionOption(Features::AOCSBuilder::OffsetDirectionNormalToCurve);

	aOCSBuilder1->SetFilletOption(Features::AOCSBuilder::FilletOptionsNoFillet);

	aOCSBuilder1->SetRemoveSelfIntersections(true);

	section1->SetDistanceTolerance(0.001);

	section1->SetChainingTolerance(0.00095);

	aOCSBuilder1->Law()->AlongSpineData()->Spine()->SetDistanceTolerance(0.001);

	aOCSBuilder1->Law()->AlongSpineData()->Spine()->SetChainingTolerance(0.00095);

	aOCSBuilder1->Law()->LawCurve()->SetDistanceTolerance(0.001);

	aOCSBuilder1->Law()->LawCurve()->SetChainingTolerance(0.00095);

	section1->PrepareMappingData();

	section1->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);

	std::vector<Features::Feature *> features1(1);
	features1[0] = studioSpline1;
	Spline *spline1(dynamic_cast<Spline *>(studioSpline1->FindObject("CURVE 1")));
	Curve *nullCurve(NULL);
	CurveFeatureTangentRule *curveFeatureTangentRule1;
	curveFeatureTangentRule1 = workPart->ScRuleFactory()->CreateRuleCurveFeatureTangent(features1, spline1, nullCurve, false, 0.00095, 0.05);

	section1->AllowSelfIntersection(false);

	std::vector<SelectionIntentRule *> rules1(1);
	rules1[0] = curveFeatureTangentRule1;
	NXObject *nullNXObject(NULL);
	Point3d helpPoint1(1004.83826617385, -275.016774719709, 672.951093664654);
	section1->AddToSection(rules1, spline1, nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);

	aOCSBuilder1->UpdateCurvesStatus(true);

	ScCollector *scCollector1;
	scCollector1 = workPart->ScCollectors()->CreateCollector();

	Face *face1(dynamic_cast<Face *>(throughCurveMesh1->FindObject("FACE 10001 {(328.4392891977557,-6.1913585369856,720.6039636893484) THRU_CURVE_MESH(36)}")));
	std::vector<Face *> boundaryFaces1(0);
	FaceTangentRule *faceTangentRule1;
	faceTangentRule1 = workPart->ScRuleFactory()->CreateRuleFaceTangent(face1, boundaryFaces1, 0.05);

	std::vector<SelectionIntentRule *> rules2(1);
	rules2[0] = faceTangentRule1;
	scCollector1->ReplaceRules(rules2, false);

	aOCSBuilder1->SetFaceCollector(scCollector1);

	aOCSBuilder1->UpdateFaces();

	aOCSBuilder1->SetLawStringFlip(false);

	expression3->SetValue(Distance);

	aOCSBuilder1->UpdateCurvesStatus(true);

	aOCSBuilder1->SetExtendToFaceOption(Features::AOCSBuilder::ExtendToFaceBoundary);

	Features::Feature *feature1;
	feature1 = aOCSBuilder1->CommitFeature();

	section1->CleanMappingData();

	aOCSBuilder1->Destroy();

	return (Features::AOCSBuilder*)feature1;
}
