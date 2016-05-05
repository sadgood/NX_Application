// NX 8.5.3.3
// Journal created by zhaoz on Thu May 05 16:19:35 2016 中国标准时间
//
#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/Axis.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/CurveDumbRule.hxx>
#include <NXOpen/DatumCollection.hxx>
#include <NXOpen/DatumPlane.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureBuilder.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_GeomcopyBuilder.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/GeometricUtilities_BetweenLocationsData.hxx>
#include <NXOpen/GeometricUtilities_GeometryLocationData.hxx>
#include <NXOpen/GeometricUtilities_OnPathDimensionBuilder.hxx>
#include <NXOpen/IPlane.hxx>
#include <NXOpen/ModelingView.hxx>
#include <NXOpen/ModelingViewCollection.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Plane.hxx>
#include <NXOpen/PlaneCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/ScCollector.hxx>
#include <NXOpen/ScCollectorCollection.hxx>
#include <NXOpen/ScRuleFactory.hxx>
#include <NXOpen/Section.hxx>
#include <NXOpen/SelectObject.hxx>
#include <NXOpen/SelectObjectList.hxx>
#include <NXOpen/SelectionIntentRule.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/TaggedObject.hxx>
#include <NXOpen/TaggedObjectList.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/View.hxx>
using namespace NXOpen;

extern "C" DllExport void ufusr(char *param, int *retCode, int paramLen)
{
    Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    // ----------------------------------------------
    //   Menu: Insert->Associative Copy->Instance Geometry...
    // ----------------------------------------------
    
    Features::Feature *nullFeatures_Feature(NULL);
    
    Features::GeomcopyBuilder *geomcopyBuilder1;
    geomcopyBuilder1 = workPart->Features()->CreateGeomcopyBuilder(nullFeatures_Feature);
    
    Point3d origin1(0.0, 0.0, 0.0);
    Vector3d normal1(0.0, 0.0, 1.0);
    Plane *plane1;
    plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);
    
    geomcopyBuilder1->SetMirrorPlane(plane1);
    
    geomcopyBuilder1->SetType(Features::GeomcopyBuilder::TransformTypesMirror);
    
    geomcopyBuilder1->TranslateDistance()->SetRightHandSide("10");
    
    geomcopyBuilder1->RotateDistance()->SetRightHandSide("0");
    
    geomcopyBuilder1->OnPathDistance()->Expression()->SetRightHandSide("0");
    
    geomcopyBuilder1->RotateAngle()->SetRightHandSide("45");
    
    geomcopyBuilder1->AlongPathAngle()->SetRightHandSide("0");
    
    geomcopyBuilder1->NumberOfCopies()->SetRightHandSide("1");
    
    geomcopyBuilder1->SetCsysMirrorOption(Features::GeomcopyBuilder::CsysMirrorOptionsMirrorYAndZ);
    
    ScCollector *scCollector1;
    scCollector1 = workPart->ScCollectors()->CreateCollector();
    
    std::vector<Point *> points1(1);
    Features::PointFeature *pointFeature1(dynamic_cast<Features::PointFeature *>(workPart->Features()->FindObject("POINT(1)")));
    Point *point1(dynamic_cast<Point *>(pointFeature1->FindObject("POINT 1")));
    points1[0] = point1;
    CurveDumbRule *curveDumbRule1;
    curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleCurveDumbFromPoints(points1);
    
    std::vector<SelectionIntentRule *> rules1(1);
    rules1[0] = curveDumbRule1;
    scCollector1->ReplaceRules(rules1, false);
    
    bool added1;
    added1 = geomcopyBuilder1->GeometryToInstance()->Add(scCollector1);
    
    std::vector<Point *> points2(2);
    points2[0] = point1;
    Features::PointFeature *pointFeature2(dynamic_cast<Features::PointFeature *>(workPart->Features()->FindObject("POINT(2)")));
    Point *point2(dynamic_cast<Point *>(pointFeature2->FindObject("POINT 1")));
    points2[1] = point2;
    CurveDumbRule *curveDumbRule2;
    curveDumbRule2 = workPart->ScRuleFactory()->CreateRuleCurveDumbFromPoints(points2);
    
    std::vector<SelectionIntentRule *> rules2(1);
    rules2[0] = curveDumbRule2;
    scCollector1->ReplaceRules(rules2, false);
    
    plane1->SetMethod(PlaneTypes::MethodTypeDistance);
    
    std::vector<NXObject *> geom1(1);
    DatumPlane *datumPlane1(dynamic_cast<DatumPlane *>(workPart->Datums()->FindObject("DATUM_CSYS(0) XY plane")));
    geom1[0] = datumPlane1;
    plane1->SetGeometry(geom1);
    
    plane1->SetFlip(false);
    
    plane1->SetReverseSide(false);
    
    Expression *expression3;
    expression3 = plane1->Expression();
    
    expression3->SetRightHandSide("0");
    
    plane1->SetAlternate(PlaneTypes::AlternateTypeOne);
    
    plane1->Evaluate();
    
    plane1->SetMethod(PlaneTypes::MethodTypeDistance);
    
    std::vector<NXObject *> geom2(1);
    geom2[0] = datumPlane1;
    plane1->SetGeometry(geom2);
    
    plane1->SetFlip(false);
    
    plane1->SetReverseSide(false);
    
    Expression *expression4;
    expression4 = plane1->Expression();
    
    expression4->SetRightHandSide("0");
    
    plane1->SetAlternate(PlaneTypes::AlternateTypeOne);
    
    plane1->Evaluate();
    
    Features::Feature *feature1;
    feature1 = geomcopyBuilder1->CommitFeature();
    
    Expression *expression5(geomcopyBuilder1->NumberOfCopies());
    geomcopyBuilder1->Destroy();
    
    Features::GeomcopyBuilder *geomcopyBuilder2;
    geomcopyBuilder2 = workPart->Features()->CreateGeomcopyBuilder(nullFeatures_Feature);
    
    Point3d origin2(0.0, 0.0, 0.0);
    Vector3d normal2(0.0, 0.0, 1.0);
    Plane *plane2;
    plane2 = workPart->Planes()->CreatePlane(origin2, normal2, SmartObject::UpdateOptionWithinModeling);
    
    geomcopyBuilder2->SetMirrorPlane(plane2);
    
    geomcopyBuilder2->SetType(Features::GeomcopyBuilder::TransformTypesMirror);
    
    geomcopyBuilder2->TranslateDistance()->SetRightHandSide("10");
    
    geomcopyBuilder2->RotateDistance()->SetRightHandSide("0");
    
    geomcopyBuilder2->OnPathDistance()->Expression()->SetRightHandSide("0");
    
    geomcopyBuilder2->RotateAngle()->SetRightHandSide("45");
    
    geomcopyBuilder2->AlongPathAngle()->SetRightHandSide("0");
    
    geomcopyBuilder2->NumberOfCopies()->SetRightHandSide("1");
    
    geomcopyBuilder2->SetCsysMirrorOption(Features::GeomcopyBuilder::CsysMirrorOptionsMirrorYAndZ);
    
    // ----------------------------------------------
    //   Dialog Begin Instance Geometry
    // ----------------------------------------------
    // ----------------------------------------------
    //   Menu: Tools->Journal->Stop Recording
    // ----------------------------------------------
}
