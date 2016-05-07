#include "CopyInstance.h"

extern Features::Feature* CopyInstance(Features::Feature* Feature_init)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	Features::Feature *nullFeatures_Feature(NULL);

	Features::GeomcopyBuilder *geomcopyBuilder1;
	geomcopyBuilder1 = workPart->Features()->CreateGeomcopyBuilder(nullFeatures_Feature);

	Point3d origin1(0.0, 0.0, 0.0);
	Vector3d normal1(0.0, 0.0, 1.0);
	Plane *plane1;
	plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);

	geomcopyBuilder1->SetMirrorPlane(plane1);

	geomcopyBuilder1->SetType(Features::GeomcopyBuilder::TransformTypesMirror);

	ScCollector *scCollector1;
	scCollector1 = workPart->ScCollectors()->CreateCollector();

	std::vector<Features::Feature *> features1(1);
	features1[0] = Feature_init;
	CurveFeatureRule *curveFeatureRule1;
	curveFeatureRule1 = workPart->ScRuleFactory()->CreateRuleCurveFeature(features1);

	std::vector<SelectionIntentRule *> rules1(1);
	rules1[0] = (SelectionIntentRule *)curveFeatureRule1;
	scCollector1->ReplaceRules(rules1, false);

	bool added1;
	added1 = geomcopyBuilder1->GeometryToInstance()->Add(scCollector1);

	plane1->SetMethod(PlaneTypes::MethodTypeDistance);

	std::vector<NXObject *> geom1(1);
	DatumPlane *datumPlane1(dynamic_cast<DatumPlane *>(workPart->Datums()->FindObject("DATUM_CSYS(0) XY plane")));
	geom1[0] = datumPlane1;
	plane1->SetGeometry(geom1);

	plane1->SetFlip(false);
	plane1->SetReverseSide(false);
	plane1->SetAlternate(PlaneTypes::AlternateTypeOne);
	plane1->Evaluate();

	Features::Feature *feature1;
	feature1 = geomcopyBuilder1->CommitFeature();

	geomcopyBuilder1->Destroy();

	return feature1;
}