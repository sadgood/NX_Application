// NX 8.5.3.3
// Journal created by zhaoz on Tue May 17 10:25:06 2016 中国标准时间
//
#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/CoordinateSystem.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_AssociativeLine.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_GeometricConstraintData.hxx>
#include <NXOpen/Features_GeometricConstraintDataManager.hxx>
#include <NXOpen/Features_StudioSplineBuilderEx.hxx>
#include <NXOpen/GeometricUtilities_OrientXpressBuilder.hxx>
#include <NXOpen/GeometricUtilities_SplineExtensionBuilder.hxx>
#include <NXOpen/Line.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Plane.hxx>
#include <NXOpen/PlaneCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/Scalar.hxx>
#include <NXOpen/ScalarCollection.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/Spline.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/Xform.hxx>
#include <NXOpen/XformCollection.hxx>
using namespace NXOpen;

extern "C" DllExport int ufusr_ask_unload()
{
    return (int)Session::LibraryUnloadOptionImmediately;
}

extern "C" DllExport void ufusr(char *param, int *retCode, int paramLen)
{
    Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Part *displayPart(theSession->Parts()->Display());
    // ----------------------------------------------
    //   Menu: Insert->Curve->Studio Spline...
    // ----------------------------------------------
    Session::UndoMarkId markId1;
    markId1 = theSession->SetUndoMark(Session::MarkVisibilityVisible, "Start");
    
    NXObject *nullNXObject(NULL);
    
    if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
    {
        throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
    }
    
    Features::StudioSplineBuilderEx *studioSplineBuilderEx1;
    studioSplineBuilderEx1 = workPart->Features()->CreateStudioSplineBuilderEx(nullNXObject);
    
    Point3d origin1(0.0, 0.0, 0.0);
    Vector3d normal1(0.0, 0.0, 1.0);
    Plane *plane1;
    plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);
    
    studioSplineBuilderEx1->SetDrawingPlane(plane1);
    
    Unit *unit1;
    unit1 = studioSplineBuilderEx1->Extender()->EndValue()->Units();
    
    Expression *expression1;
    expression1 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);
    
    Expression *expression2;
    expression2 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);
    
    Point3d origin2(0.0, 0.0, 0.0);
    Vector3d normal2(0.0, 0.0, 1.0);
    Plane *plane2;
    plane2 = workPart->Planes()->CreatePlane(origin2, normal2, SmartObject::UpdateOptionWithinModeling);
    
    studioSplineBuilderEx1->SetMovementPlane(plane2);
    
    Expression *expression3;
    expression3 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);
    
    Expression *expression4;
    expression4 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);
    
    studioSplineBuilderEx1->OrientExpress()->SetReferenceOption(GeometricUtilities::OrientXpressBuilder::ReferenceWcsDisplayPart);
    
    studioSplineBuilderEx1->SetMovementMethod(Features::StudioSplineBuilderEx::MovementMethodTypeView);
    
    studioSplineBuilderEx1->OrientExpress()->SetAxisOption(GeometricUtilities::OrientXpressBuilder::AxisPassive);
    
    studioSplineBuilderEx1->OrientExpress()->SetPlaneOption(GeometricUtilities::OrientXpressBuilder::PlanePassive);
    
    studioSplineBuilderEx1->Extender()->EndValue()->SetRightHandSide("0");
    
    Expression *expression5(dynamic_cast<Expression *>(workPart->Expressions()->FindObject("p71")));
    expression5->SetRightHandSide("0");
    
    studioSplineBuilderEx1->SetInputCurveOption(Features::StudioSplineBuilderEx::InputCurveOptionsHide);
    
    theSession->SetUndoMarkName(markId1, NXString("Studio Spline \345\257\271\350\257\235\346\241\206", NXString::UTF8));
    
    studioSplineBuilderEx1->SetMatchKnotsType(Features::StudioSplineBuilderEx::MatchKnotsTypesNone);
    
    Session::UndoMarkId markId2;
    markId2 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Studio Spline");
    
    theSession->DeleteUndoMark(markId2, NULL);
    
    Session::UndoMarkId markId3;
    markId3 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Studio Spline");
    
    // ----------------------------------------------
    //   Menu: Edit->Snap Point->Existing Point
    // ----------------------------------------------
    Expression *expression6;
    expression6 = workPart->Expressions()->CreateSystemExpression("0.000000");
    
    Scalar *scalar1;
    scalar1 = workPart->Scalars()->CreateScalarExpression(expression6, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Features::AssociativeLine *associativeLine1(dynamic_cast<Features::AssociativeLine *>(workPart->Features()->FindObject("LINE(45)")));
    Line *line1(dynamic_cast<Line *>(associativeLine1->FindObject("CURVE 1")));
    Point *point1;
    point1 = workPart->Points()->CreatePoint(line1, scalar1, SmartObject::UpdateOptionWithinModeling);
    
    NXObject *nXObject1;
    Xform *xform1;
    xform1 = workPart->Xforms()->CreateExtractXform(line1, SmartObject::UpdateOptionWithinModeling, false, &nXObject1);
    
    Features::GeometricConstraintData *geometricConstraintData1;
    geometricConstraintData1 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData1->SetPoint(point1);
    
    studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData1);
    
    theSession->SetUndoMarkName(markId3, NXString("\350\211\272\346\234\257\346\240\267\346\235\241 - \351\200\211\346\213\251", NXString::UTF8));
    
    theSession->SetUndoMarkVisibility(markId3, NULL, Session::MarkVisibilityVisible);
    
    theSession->SetUndoMarkVisibility(markId1, NULL, Session::MarkVisibilityInvisible);
    
    Session::UndoMarkId markId4;
    markId4 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Studio Spline");
    
    Expression *expression7;
    expression7 = workPart->Expressions()->CreateSystemExpression("0.000000");
    
    Scalar *scalar2;
    scalar2 = workPart->Scalars()->CreateScalarExpression(expression7, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Features::Feature *feature1(dynamic_cast<Features::Feature *>(workPart->Features()->FindObject("Geometry Instance(50:1A:1A)")));
    Line *line2(dynamic_cast<Line *>(feature1->FindObject("CURVE 1")));
    Point *point2;
    point2 = workPart->Points()->CreatePoint(line2, scalar2, SmartObject::UpdateOptionWithinModeling);
    
    NXObject *nXObject2;
    Xform *xform2;
    xform2 = workPart->Xforms()->CreateExtractXform(line2, SmartObject::UpdateOptionWithinModeling, false, &nXObject2);
    
    Features::GeometricConstraintData *geometricConstraintData2;
    geometricConstraintData2 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData2->SetPoint(point2);
    
    studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData2);
    
    theSession->SetUndoMarkName(markId4, NXString("\350\211\272\346\234\257\346\240\267\346\235\241 - \351\200\211\346\213\251", NXString::UTF8));
    
    theSession->SetUndoMarkVisibility(markId4, NULL, Session::MarkVisibilityVisible);
    
    theSession->SetUndoMarkVisibility(markId1, NULL, Session::MarkVisibilityInvisible);
    
    Session::UndoMarkId markId5;
    markId5 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Studio Spline");
    
    Expression *expression8;
    expression8 = workPart->Expressions()->CreateSystemExpression("0.000000");
    
    Scalar *scalar3;
    scalar3 = workPart->Scalars()->CreateScalarExpression(expression8, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
    
    Features::AssociativeLine *associativeLine2(dynamic_cast<Features::AssociativeLine *>(workPart->Features()->FindObject("LINE(47)")));
    Line *line3(dynamic_cast<Line *>(associativeLine2->FindObject("CURVE 1")));
    Point *point3;
    point3 = workPart->Points()->CreatePoint(line3, scalar3, SmartObject::UpdateOptionWithinModeling);
    
    NXObject *nXObject3;
    Xform *xform3;
    xform3 = workPart->Xforms()->CreateExtractXform(line3, SmartObject::UpdateOptionWithinModeling, false, &nXObject3);
    
    Features::GeometricConstraintData *geometricConstraintData3;
    geometricConstraintData3 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData3->SetPoint(point3);
    
    studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData3);
    
    theSession->SetUndoMarkName(markId5, NXString("\350\211\272\346\234\257\346\240\267\346\235\241 - \351\200\211\346\213\251", NXString::UTF8));
    
    theSession->SetUndoMarkVisibility(markId5, NULL, Session::MarkVisibilityVisible);
    
    theSession->SetUndoMarkVisibility(markId1, NULL, Session::MarkVisibilityInvisible);
    
    Session::UndoMarkId markId6;
    markId6 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Studio Spline");
    
    Session::UndoMarkId markId7;
    markId7 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Studio Spline");
    
    theSession->DeleteUndoMark(markId7, NULL);
    
    Session::UndoMarkId markId8;
    markId8 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Studio Spline");
    
    NXObject *nXObject4;
    nXObject4 = studioSplineBuilderEx1->Commit();
    
    theSession->DeleteUndoMark(markId8, NULL);
    
    theSession->SetUndoMarkName(markId1, "Studio Spline");
    
    studioSplineBuilderEx1->Destroy();
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression2);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression4);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression1);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression3);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    theSession->SetUndoMarkVisibility(markId1, NULL, Session::MarkVisibilityVisible);
    
    theSession->DeleteUndoMark(markId5, NULL);
    
    theSession->DeleteUndoMark(markId4, NULL);
    
    theSession->DeleteUndoMark(markId3, NULL);
    
    // ----------------------------------------------
    //   Menu: Tools->Journal->Stop Recording
    // ----------------------------------------------
}
