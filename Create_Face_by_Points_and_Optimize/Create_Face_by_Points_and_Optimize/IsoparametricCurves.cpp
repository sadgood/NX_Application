#include "IsoparametricCurves.h"

extern void IsoparametricCurvesOnFace(Features::ThroughCurveMesh *throughCurveMesh, Features::PointFeature *pointFeature)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	Features::IsoparametricCurves *nullFeatures_IsoparametricCurves(NULL);

	Features::IsoparametricCurvesBuilder *isoparametricCurvesBuilder1;
	isoparametricCurvesBuilder1 = workPart->Features()->CreateIsoparametricCurvesBuilder(nullFeatures_IsoparametricCurves);

	Face *face1 = NULL;
	vector<Face*> faces;
	faces = throughCurveMesh->GetFaces();
	face1 = faces.at(0);
	Point3d point1(-149.387892284156, 194.491516946575, 668.602055690795);
	isoparametricCurvesBuilder1->SelectObject()->SetValue(face1, workPart->ModelingViews()->WorkView(), point1);

	isoparametricCurvesBuilder1->UpdateIsoparametricCurves();

	isoparametricCurvesBuilder1->SetDirection(Features::IsoparametricCurvesBuilder::DirectionTypesIsoU);

	isoparametricCurvesBuilder1->SetPlacement(Features::IsoparametricCurvesBuilder::PlacementTypesThroughPoints);

	isoparametricCurvesBuilder1->UpdateIsoparametricCurves();

	// ----------------------------------------------
	//   Dialog Begin Point
	// ----------------------------------------------
	Point *point3(dynamic_cast<Point *>(pointFeature->FindObject("POINT 1")));
	Xform *nullXform(NULL);
	Point *point4;
	point4 = workPart->Points()->CreatePoint(point3, nullXform, SmartObject::UpdateOptionWithinModeling);

	Features::GeometricConstraintData *geometricConstraintData1;
	geometricConstraintData1 = isoparametricCurvesBuilder1->ConstraintManager()->CreateGeometricConstraintData();

	geometricConstraintData1->SetPoint(point4);

	isoparametricCurvesBuilder1->ConstraintManager()->Append(geometricConstraintData1);

	/*std::vector<Point *> points1(0);
	Point *nullPoint(NULL);
	isoparametricCurvesBuilder1->SetActivePoints(points1, nullPoint);

	Features::GeometricConstraintData *geometricConstraintData2;
	geometricConstraintData2 = isoparametricCurvesBuilder1->ConstraintManager()->FindItem(0);

	Point *point5;
	point5 = geometricConstraintData2->Point();

	isoparametricCurvesBuilder1->UpdateIsoparametricCurves();

	std::vector<Point *> points2(0);
	isoparametricCurvesBuilder1->SetActivePoints(points2, nullPoint);

	isoparametricCurvesBuilder1->UpdateIsoparametricCurves();*/

	NXObject *nXObject1;
	nXObject1 = isoparametricCurvesBuilder1->Commit();

	isoparametricCurvesBuilder1->Destroy();

	// ----------------------------------------------
	//   Menu: Tools->Journal->Stop Recording
	// ----------------------------------------------
}
