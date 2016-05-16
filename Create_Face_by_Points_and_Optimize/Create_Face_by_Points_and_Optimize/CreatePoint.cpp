#include "CreatePoint.h"

extern Features::PointFeature * CreatePointFeature(double coord[3], string pointTag, string &PointName)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	char coord_str1[20] = "";
	char coord_str2[20] = "";
	char coord_str3[20] = "";
	sprintf_s(coord_str1, "%f", coord[0]);
	sprintf_s(coord_str2, "%f", coord[1]);
	sprintf_s(coord_str3, "%f", coord[2]);
	string coord_str[3];
	coord_str[0] = coord_str1;
	coord_str[1] = coord_str2;
	coord_str[2] = coord_str3;

	int timeNow = system("time");
	char temp[20] = "";
	sprintf_s(temp, "%d", timeNow);
	string TimeNow = temp;
	Point *thePoint = NULL;

	Unit *unit1(dynamic_cast<Unit *>(workPart->UnitCollection()->FindObject("MilliMeter")));
	Expression *expression1;
	expression1 = workPart->Expressions()->CreateSystemExpressionWithUnits(pointTag + "_" + TimeNow + "_x=" + coord_str[0], unit1);

	Scalar *scalar1;
	scalar1 = workPart->Scalars()->CreateScalarExpression(expression1, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

	Expression *expression2;
	expression2 = workPart->Expressions()->CreateSystemExpressionWithUnits(pointTag + "_" + TimeNow + "_y=" + coord_str[1], unit1);

	Scalar *scalar2;
	scalar2 = workPart->Scalars()->CreateScalarExpression(expression2, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

	Expression *expression3;
	expression3 = workPart->Expressions()->CreateSystemExpressionWithUnits(pointTag + "_" + TimeNow + "_z=" + coord_str[2], unit1);

	Scalar *scalar3;
	scalar3 = workPart->Scalars()->CreateScalarExpression(expression3, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

	thePoint = workPart->Points()->CreatePoint(scalar1, scalar2, scalar3, SmartObject::UpdateOptionWithinModeling);
	thePoint->SetVisibility(SmartObject::VisibilityOptionVisible);

	Features::Feature *nullFeatures_Feature(NULL);
	Features::PointFeatureBuilder *thePointFeatureBuilder = NULL;
	thePointFeatureBuilder = workPart->BaseFeatures()->CreatePointFeatureBuilder(nullFeatures_Feature);
	thePointFeatureBuilder->SetPoint(thePoint);

	NXObject *theNXObject = NULL;
	theNXObject = thePointFeatureBuilder->Commit();

	thePointFeatureBuilder->Destroy();
	return (Features::PointFeature*)theNXObject;
}

extern int GetPointsCoord(coord *pt_coods_selected, const tag_t &object_facet, vector<vector<coord> > &pt_coods)
{
	coord pt_temp[4] = { 0 };
	pt_temp[0].base_pt[0] = (pt_coods_selected[0].base_pt[0] + pt_coods_selected[1].base_pt[0]) / 2;
	pt_temp[0].base_pt[1] = (pt_coods_selected[0].base_pt[1] + pt_coods_selected[1].base_pt[1]) / 2;
	pt_temp[0].base_pt[2] = (pt_coods_selected[0].base_pt[2] + pt_coods_selected[1].base_pt[2]) / 2;

	pt_temp[1].base_pt[0] = (pt_coods_selected[0].base_pt[0] + pt_coods_selected[3].base_pt[0]) / 2;
	pt_temp[1].base_pt[1] = (pt_coods_selected[0].base_pt[1] + pt_coods_selected[3].base_pt[1]) / 2;
	pt_temp[1].base_pt[2] = (pt_coods_selected[0].base_pt[2] + pt_coods_selected[3].base_pt[2]) / 2;

	pt_temp[3].base_pt[0] = (pt_coods_selected[1].base_pt[0] + pt_coods_selected[2].base_pt[0]) / 2;
	pt_temp[3].base_pt[1] = (pt_coods_selected[1].base_pt[1] + pt_coods_selected[2].base_pt[1]) / 2;
	pt_temp[3].base_pt[2] = (pt_coods_selected[1].base_pt[2] + pt_coods_selected[2].base_pt[2]) / 2;

	pt_temp[2].base_pt[0] = (pt_temp[1].base_pt[0] + pt_temp[3].base_pt[0]) / 2;
	pt_temp[2].base_pt[1] = (pt_temp[1].base_pt[1] + pt_temp[3].base_pt[1]) / 2;
	pt_temp[2].base_pt[2] = (pt_temp[1].base_pt[2] + pt_temp[3].base_pt[2]) / 2;   

	pt_coods[0][0] = pt_coods_selected[0];
	pt_coods[0][2] = pt_coods_selected[1];

	double guess2[3] = { 0.0,0.0,0.0 };
	double min_dist = 0.0;   //×î¶Ì¾àÀë
	double pt_on_obj1[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object1£¨pt_temp£©
	double pt_on_obj2[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object2£¨object_facet£©

	int errorCode = 0;
	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(	NULL_TAG, object_facet, 1, pt_temp[0].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[0][1].base_pt[0] = pt_on_obj2[0];
	pt_coods[0][1].base_pt[1] = pt_on_obj2[1];
	pt_coods[0][1].base_pt[2] = pt_on_obj2[2];

	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[1].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[1][0].base_pt[0] = pt_on_obj2[0];
	pt_coods[1][0].base_pt[1] = pt_on_obj2[1];
	pt_coods[1][0].base_pt[2] = pt_on_obj2[2];

	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[2].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[1][1].base_pt[0] = pt_on_obj2[0];
	pt_coods[1][1].base_pt[1] = pt_on_obj2[1];
	pt_coods[1][1].base_pt[2] = pt_on_obj2[2];

	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[3].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[1][2].base_pt[0] = pt_on_obj2[0];
	pt_coods[1][2].base_pt[1] = pt_on_obj2[1];
	pt_coods[1][2].base_pt[2] = pt_on_obj2[2];

	return 0;
}

extern Features::PointFeature* CreatePointInCurves(Features::Feature *studioSpline1, double ratio)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	Section *section1;
	section1 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	section1->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);

	std::vector<IBaseCurve *> curves1(1);
	Spline *spline1(dynamic_cast<Spline *>(studioSpline1->FindObject("CURVE 1")));
	curves1[0] = spline1;
	CurveDumbRule *curveDumbRule1;
	curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);

	section1->AllowSelfIntersection(false);

	std::vector<SelectionIntentRule *> rules1(1);
	rules1[0] = curveDumbRule1;
	NXObject *nullNXObject(NULL);
	Point3d helpPoint1(1005.13137827263, -251.775740702984, 675.25033335631);
	section1->AddToSection(rules1, spline1, nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);

	Unit *nullUnit(NULL);
	Expression *expression1;
	expression1 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", nullUnit);
	expression1->SetValue(ratio);

	Scalar *scalar1;
	scalar1 = workPart->Scalars()->CreateScalarExpression(expression1, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

	Section *section2;
	section2 = section1->CloneSection();

	Curve *curve1;
	curve1 = workPart->Curves()->CreateSmartCompositeCurve(section2, SmartObject::UpdateOptionWithinModeling, 0.00095);

	Spline *spline2(dynamic_cast<Spline *>(curve1));
	Point *point1;
	point1 = workPart->Points()->CreatePoint(spline2, scalar1, PointCollection::PointOnCurveLocationOptionPercentArcLength, SmartObject::UpdateOptionWithinModeling);

	section1->Clear();

	section1->Destroy();

	point1->SetVisibility(SmartObject::VisibilityOptionVisible);

	Features::Feature *nullFeatures_Feature(NULL);

	Features::PointFeatureBuilder *pointFeatureBuilder1;
	pointFeatureBuilder1 = workPart->BaseFeatures()->CreatePointFeatureBuilder(nullFeatures_Feature);

	pointFeatureBuilder1->SetPoint(point1);

	NXObject *nXObject1;
	nXObject1 = pointFeatureBuilder1->Commit();

	pointFeatureBuilder1->Destroy();

	return (Features::PointFeature*)nXObject1;
}