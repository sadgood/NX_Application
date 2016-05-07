#include "CreateAssociativeLine.h"

extern Features::AssociativeLine* CreateAssociativeLine(Features::PointFeature *pointFeature1, Features::ThroughCurveMesh *throughCurveMesh1)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	Features::AssociativeLine *nullFeatures_AssociativeLine(NULL);

	Features::AssociativeLineBuilder *associativeLineBuilder1;
	associativeLineBuilder1 = workPart->BaseFeatures()->CreateAssociativeLineBuilder(nullFeatures_AssociativeLine);

	Point3d origin1(0.0, 0.0, 0.0);
	Vector3d normal1(0.0, 0.0, 1.0);
	Plane *plane1;
	plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);

	associativeLineBuilder1->SetStartPointOptions(Features::AssociativeLineBuilder::StartOptionPoint);

	associativeLineBuilder1->Limits()->StartLimit()->SetLimitOption(GeometricUtilities::CurveExtendData::LimitOptionsAtPoint);

	associativeLineBuilder1->Limits()->EndLimit()->SetLimitOption(GeometricUtilities::CurveExtendData::LimitOptionsAtPoint);

	associativeLineBuilder1->SetStartPointOptions(Features::AssociativeLineBuilder::StartOptionInferred);

	associativeLineBuilder1->SetStartPointOptions(Features::AssociativeLineBuilder::StartOptionPoint);

	associativeLineBuilder1->Limits()->SetFullCircle(false);

	Point *point1(dynamic_cast<Point *>(pointFeature1->FindObject("POINT 1")));
	Xform *nullXform(NULL);
	Point *point2;
	point2 = workPart->Points()->CreatePoint(point1, nullXform, SmartObject::UpdateOptionWithinModeling);

	associativeLineBuilder1->StartPoint()->SetValue(point2);

	associativeLineBuilder1->SetEndPointOptions(Features::AssociativeLineBuilder::EndOptionNormal);

	associativeLineBuilder1->Limits()->SetFullCircle(false);

	Face *face1(dynamic_cast<Face *>(throughCurveMesh1->FindObject("FACE 10001 {(-31.0323630064268,26.0427359073581,0) THRU_CURVE_MESH(15)}")));
	associativeLineBuilder1->EndNormal()->SetValue(face1);

	associativeLineBuilder1->Limits()->EndLimit()->SetLimitOption(GeometricUtilities::CurveExtendData::LimitOptionsValue);

	associativeLineBuilder1->Limits()->EndLimit()->Distance()->SetRightHandSide("100");

	View *nullView(NULL);
	Point3d point3(0.0, 0.0, 0.0);
	associativeLineBuilder1->EndNormal()->SetValue(face1, nullView, point3);

	associativeLineBuilder1->SetAssociative(true);

	NXObject *nXObject1;
	nXObject1 = associativeLineBuilder1->Commit();

	associativeLineBuilder1->Destroy();

	plane1->DestroyPlane();

	return (Features::AssociativeLine*)nXObject1;
}
