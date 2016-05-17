#include "CreateStudioSpline.h"

extern Features::StudioSpline* CreateStudioSplineByPoints(Features::PointFeature *pointFeature1, Features::PointFeature *pointFeature2, Features::PointFeature *pointFeature3)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	NXObject *nullNXObject(NULL);

	Features::StudioSplineBuilderEx *studioSplineBuilderEx1;
	studioSplineBuilderEx1 = workPart->Features()->CreateStudioSplineBuilderEx(nullNXObject);

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

extern Features::StudioSpline* CreateStudioSplineByLine(Features::AssociativeLine* associativeLine1, Features::AssociativeLine* associativeLine2, Features::AssociativeLine* associativeLine3)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	NXObject *nullNXObject(NULL);

	Features::StudioSplineBuilderEx *studioSplineBuilderEx1;
	studioSplineBuilderEx1 = workPart->Features()->CreateStudioSplineBuilderEx(nullNXObject);

	// ----------------------------------------------
	//   Dialog Begin Point
	// ----------------------------------------------
	Expression *expression1;
	expression1 = workPart->Expressions()->CreateSystemExpression("1.000000");

	Scalar *scalar1;
	scalar1 = workPart->Scalars()->CreateScalarExpression(expression1, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

	Line *line1(dynamic_cast<Line *>(associativeLine1->FindObject("CURVE 1")));
	Point *point1;
	point1 = workPart->Points()->CreatePoint(line1, scalar1, SmartObject::UpdateOptionWithinModeling);

	Features::GeometricConstraintData *geometricConstraintData1;
	geometricConstraintData1 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();

	geometricConstraintData1->SetPoint(point1);

	studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData1);

	studioSplineBuilderEx1->Evaluate();

	// ----------------------------------------------
	//   Dialog Begin Point
	// ----------------------------------------------
	Expression *expression2;
	expression2 = workPart->Expressions()->CreateSystemExpression("1.000000");

	Scalar *scalar2;
	scalar2 = workPart->Scalars()->CreateScalarExpression(expression2, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

	Line *line2(dynamic_cast<Line *>(associativeLine2->FindObject("CURVE 1")));
	Point *point2;
	point2 = workPart->Points()->CreatePoint(line2, scalar2, SmartObject::UpdateOptionWithinModeling);

	Features::GeometricConstraintData *geometricConstraintData2;
	geometricConstraintData2 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();

	geometricConstraintData2->SetPoint(point2);

	studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData2);

	studioSplineBuilderEx1->Evaluate();

	// ----------------------------------------------
	//   Dialog Begin Point
	// ----------------------------------------------
	//Point *point5(dynamic_cast<Point *>(pointFeature3->FindObject("POINT 1")));
	Point *point6;
	//point6 = workPart->Points()->CreatePoint(point5, nullXform, SmartObject::UpdateOptionWithinModeling);

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