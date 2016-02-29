// NX 8.5.3.3
// Journal created by Zhao on Mon Feb 29 14:10:55 2016 中国标准时间
//
#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/SmartObject.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/UnitCollection.hxx>
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
    //   Menu: Insert->Datum/Point->Point...
    // ----------------------------------------------
    Session::UndoMarkId markId1;
    markId1 = theSession->SetUndoMark(Session::MarkVisibilityVisible, "Start");
    
    Unit *unit1(dynamic_cast<Unit *>(workPart->UnitCollection()->FindObject("MilliMeter")));
    Expression *expression1;
    expression1 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);
    
    Expression *expression2;
    expression2 = workPart->Expressions()->CreateSystemExpressionWithUnits("p70_x=-1147.42100238800", unit1);
    
    Expression *expression3;
    expression3 = workPart->Expressions()->CreateSystemExpressionWithUnits("p71_y=409.78634357452", unit1);
    
    Expression *expression4;
    expression4 = workPart->Expressions()->CreateSystemExpressionWithUnits("p72_z=166.63490235806", unit1);
    
    Expression *expression5;
    expression5 = workPart->Expressions()->CreateSystemExpressionWithUnits("p73_xdelta=0.00000000000", unit1);
    
    Expression *expression6;
    expression6 = workPart->Expressions()->CreateSystemExpressionWithUnits("p74_ydelta=0.00000000000", unit1);
    
    Expression *expression7;
    expression7 = workPart->Expressions()->CreateSystemExpressionWithUnits("p75_zdelta=0.00000000000", unit1);
    
    Expression *expression8;
    expression8 = workPart->Expressions()->CreateSystemExpressionWithUnits("p76_radius=0.00000000000", unit1);
    
    Unit *unit2(dynamic_cast<Unit *>(workPart->UnitCollection()->FindObject("Degrees")));
    Expression *expression9;
    expression9 = workPart->Expressions()->CreateSystemExpressionWithUnits("p77_angle=0.00000000000", unit2);
    
    Expression *expression10;
    expression10 = workPart->Expressions()->CreateSystemExpressionWithUnits("p78_zdelta=0.00000000000", unit1);
    
    Expression *expression11;
    expression11 = workPart->Expressions()->CreateSystemExpressionWithUnits("p79_radius=0.00000000000", unit1);
    
    Expression *expression12;
    expression12 = workPart->Expressions()->CreateSystemExpressionWithUnits("p80_angle1=0.00000000000", unit2);
    
    Expression *expression13;
    expression13 = workPart->Expressions()->CreateSystemExpressionWithUnits("p81_angle2=0.00000000000", unit2);
    
    Expression *expression14;
    expression14 = workPart->Expressions()->CreateSystemExpressionWithUnits("p82_distance=0", unit1);
    
    Expression *expression15;
    expression15 = workPart->Expressions()->CreateSystemExpressionWithUnits("p83_arclen=0", unit1);
    
    Unit *nullUnit(NULL);
    Expression *expression16;
    expression16 = workPart->Expressions()->CreateSystemExpressionWithUnits("p84_percent=0", nullUnit);
    
    expression2->SetRightHandSide("-1147.421002388");
    
    expression3->SetRightHandSide("409.78634357452");
    
    expression4->SetRightHandSide("166.63490235806");
    
    expression5->SetRightHandSide("0");
    
    expression6->SetRightHandSide("0");
    
    expression7->SetRightHandSide("0");
    
    expression8->SetRightHandSide("0");
    
    expression9->SetRightHandSide("0");
    
    expression10->SetRightHandSide("0");
    
    expression11->SetRightHandSide("0");
    
    expression12->SetRightHandSide("0");
    
    expression13->SetRightHandSide("0");
    
    expression14->SetRightHandSide("0");
    
    expression16->SetRightHandSide("100");
    
    expression15->SetRightHandSide("0");
    
    theSession->SetUndoMarkName(markId1, NXString("Point \345\257\271\350\257\235\346\241\206", NXString::UTF8));
    
    expression3->SetRightHandSide("409.786343574524");
    
    expression4->SetRightHandSide("166.634902358055");
    
    expression2->SetRightHandSide("-1147.42100238800");
    
    expression3->SetRightHandSide("409.78634357452");
    
    expression4->SetRightHandSide("166.63490235806");
    
    expression5->SetRightHandSide("0.00000000000");
    
    expression6->SetRightHandSide("0.00000000000");
    
    expression7->SetRightHandSide("0.00000000000");
    
    expression8->SetRightHandSide("0.00000000000");
    
    expression9->SetRightHandSide("0.00000000000");
    
    expression10->SetRightHandSide("0.00000000000");
    
    expression11->SetRightHandSide("0.00000000000");
    
    expression12->SetRightHandSide("0.00000000000");
    
    expression13->SetRightHandSide("0.00000000000");
    
    expression16->SetRightHandSide("100.00000000000");
    
    Point3d coordinates1(-1080.2093744278, 488.304287195206, 175.066322088242);
    Point *point1;
    point1 = workPart->Points()->CreatePoint(coordinates1);
    
    expression2->SetRightHandSide("-1080.2093744278");
    
    expression3->SetRightHandSide("488.304287195206");
    
    expression4->SetRightHandSide("175.066322088242");
    
    expression2->SetRightHandSide("-1080.20937442780");
    
    expression3->SetRightHandSide("488.30428719521");
    
    expression4->SetRightHandSide("175.06632208824");
    
    Session::UndoMarkId markId2;
    markId2 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Point");
    
    theSession->DeleteUndoMark(markId2, NULL);
    
    Session::UndoMarkId markId3;
    markId3 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Point");
    
    theSession->DeleteUndoMark(markId3, NULL);
    
    theSession->SetUndoMarkName(markId1, "Point");
    
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
        workPart->Expressions()->Delete(expression3);
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
        workPart->Expressions()->Delete(expression5);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression6);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression7);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression8);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression9);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression10);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression11);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression12);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression13);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression14);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression15);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    try
    {
        // 表达式仍然在使用中。
        workPart->Expressions()->Delete(expression16);
    }
    catch (const NXException &ex)
    {
      ex.AssertErrorCode(1050029);
    }
    
    workPart->Expressions()->Delete(expression1);
    
    point1->SetVisibility(SmartObject::VisibilityOptionVisible);
    
    Features::Feature *nullFeatures_Feature(NULL);
    
    if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
    {
        throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
    }
    
    Features::PointFeatureBuilder *pointFeatureBuilder1;
    pointFeatureBuilder1 = workPart->BaseFeatures()->CreatePointFeatureBuilder(nullFeatures_Feature);
    
    pointFeatureBuilder1->SetPoint(point1);
    
    NXObject *nXObject1;
    nXObject1 = pointFeatureBuilder1->Commit();
    
    pointFeatureBuilder1->Destroy();
    
    // ----------------------------------------------
    //   Menu: Tools->Journal->Stop Recording
    // ----------------------------------------------
}
