// NX 8.5.3.3
// Journal created by Zhao on Tue May 03 12:20:02 2016 中国标准时间
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
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_GeometricConstraintData.hxx>
#include <NXOpen/Features_GeometricConstraintDataManager.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/Features_StudioSplineBuilderEx.hxx>
#include <NXOpen/GeometricUtilities_OrientXpressBuilder.hxx>
#include <NXOpen/GeometricUtilities_SplineExtensionBuilder.hxx>
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
#include <NXOpen/UnitCollection.hxx>
using namespace NXOpen;

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
    
    // ----------------------------------------------
    //   Dialog Begin Point
    // ----------------------------------------------    
    Features::PointFeature *pointFeature1(dynamic_cast<Features::PointFeature *>(workPart->Features()->FindObject("POINT(1)")));
    Point *point2(dynamic_cast<Point *>(pointFeature1->FindObject("POINT 1")));
    Xform *nullXform(NULL);
    Point *point3;
    point3 = workPart->Points()->CreatePoint(point2, nullXform, SmartObject::UpdateOptionWithinModeling);
    
    
    Features::GeometricConstraintData *geometricConstraintData1;
    geometricConstraintData1 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData1->SetPoint(point3);
    
    studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData1);
    
    studioSplineBuilderEx1->Evaluate();
    
    // ----------------------------------------------
    //   Dialog Begin Point
    // ----------------------------------------------
    Features::PointFeature *pointFeature2(dynamic_cast<Features::PointFeature *>(workPart->Features()->FindObject("POINT(2)")));
    Point *point5(dynamic_cast<Point *>(pointFeature2->FindObject("POINT 1")));
    Point *point6;
    point6 = workPart->Points()->CreatePoint(point5, nullXform, SmartObject::UpdateOptionWithinModeling);
    
    Features::GeometricConstraintData *geometricConstraintData2;
    geometricConstraintData2 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData2->SetPoint(point6);
    
    studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData2);
    
    studioSplineBuilderEx1->Evaluate();
    
    // ----------------------------------------------
    //   Dialog Begin Point
    // ----------------------------------------------
    Features::PointFeature *pointFeature3(dynamic_cast<Features::PointFeature *>(workPart->Features()->FindObject("POINT(3)")));
    Point *point8(dynamic_cast<Point *>(pointFeature3->FindObject("POINT 1")));
    Point *point9;
    point9 = workPart->Points()->CreatePoint(point8, nullXform, SmartObject::UpdateOptionWithinModeling);
    
    Features::GeometricConstraintData *geometricConstraintData3;
    geometricConstraintData3 = studioSplineBuilderEx1->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData3->SetPoint(point9);
    
    studioSplineBuilderEx1->ConstraintManager()->Append(geometricConstraintData3);
    
    studioSplineBuilderEx1->Evaluate();
    
    NXObject *nXObject1;
    nXObject1 = studioSplineBuilderEx1->Commit();
    
    theSession->SetUndoMarkName(markId1, "Studio Spline");
    
    studioSplineBuilderEx1->Destroy();
    
    // ----------------------------------------------
    //   Menu: Tools->Journal->Stop Recording
    // ----------------------------------------------
}
