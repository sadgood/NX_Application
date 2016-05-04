#include "CreateLine.h"

extern Features::StudioSpline* CreateLine(Features::PointFeature *pointFeature1, Features::PointFeature *pointFeature2, Features::PointFeature *pointFeature3)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	NXObject *nullNXObject(NULL);

	Features::StudioSplineBuilderEx *studioSplineBuilderEx1;
	studioSplineBuilderEx1 = workPart->Features()->CreateStudioSplineBuilderEx(nullNXObject);

	Point3d origin1(0.0, 0.0, 0.0);
	Vector3d normal1(0.0, 0.0, 1.0);
	/*Plane *plane1;
	plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);
	studioSplineBuilderEx1->SetDrawingPlane(plane1);*/

	// ----------------------------------------------
	//   Dialog Begin Point
	// ----------------------------------------------    
	Point *point1(dynamic_cast<Point *>(pointFeature1->FindObject("POINT 1")));
	Xform *nullXform(NULL);
	Point *point2;
	point2 = workPart->Points()->CreatePoint(point1, nullXform, SmartObject::UpdateOptionWithinModeling);

	Features::GeometricConstraintData *geometricConstraintData1;
	geometricConstraintData1 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();

	geometricConstraintData1->SetPoint(point2);

	studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData1);

	studioSplineBuilderEx1->Evaluate();

	// ----------------------------------------------
	//   Dialog Begin Point
	// ----------------------------------------------
	Point *point3(dynamic_cast<Point *>(pointFeature2->FindObject("POINT 1")));
	Point *point4;
	point4 = workPart->Points()->CreatePoint(point3, nullXform, SmartObject::UpdateOptionWithinModeling);

	Features::GeometricConstraintData *geometricConstraintData2;
	geometricConstraintData2 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();

	geometricConstraintData2->SetPoint(point4);

	studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData2);

	studioSplineBuilderEx1->Evaluate();

	// ----------------------------------------------
	//   Dialog Begin Point
	// ----------------------------------------------
	Point *point5(dynamic_cast<Point *>(pointFeature3->FindObject("POINT 1")));
	Point *point6;
	point6 = workPart->Points()->CreatePoint(point5, nullXform, SmartObject::UpdateOptionWithinModeling);

	Features::GeometricConstraintData *geometricConstraintData3;
	geometricConstraintData3 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();

	geometricConstraintData3->SetPoint(point6);

	studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData3);

	studioSplineBuilderEx1->Evaluate();

	NXObject *nXObject1;
	nXObject1 = studioSplineBuilderEx1->Commit();

	studioSplineBuilderEx1->Destroy();

	return (Features::StudioSpline*)nXObject1;
}
