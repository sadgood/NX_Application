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

void adf()
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	// ----------------------------------------------
	//   Menu: Insert->Datum/Point->Point...
	// ----------------------------------------------

	Unit *unit1(dynamic_cast<Unit *>(workPart->UnitCollection()->FindObject("MilliMeter")));
	Expression *expression1;
	expression1 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);

	Expression *expression2;
	expression2 = workPart->Expressions()->CreateSystemExpressionWithUnits("p70_x=-1147.42100238800", unit1);

	Expression *expression3;
	expression3 = workPart->Expressions()->CreateSystemExpressionWithUnits("p71_y=409.78634357452", unit1);

	Expression *expression4;
	expression4 = workPart->Expressions()->CreateSystemExpressionWithUnits("p72_z=166.63490235806", unit1);

	expression2->SetRightHandSide("-1080.20937442780");

	expression3->SetRightHandSide("488.30428719521");

	expression4->SetRightHandSide("175.06632208824");

	Point3d coordinates1(-1080.2093744278, 488.304287195206, 175.066322088242);
	Point *point1;
	point1 = workPart->Points()->CreatePoint(coordinates1);

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

	workPart->Expressions()->Delete(expression1);

	point1->SetVisibility(SmartObject::VisibilityOptionVisible);

	Features::Feature *nullFeatures_Feature(NULL);

	if (!workPart->Preferences()->Modeling()->GetHistoryMode())
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
