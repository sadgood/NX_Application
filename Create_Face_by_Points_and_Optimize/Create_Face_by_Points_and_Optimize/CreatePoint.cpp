#include <uf.h>
#include <uf_ui.h>
#include "CreatePoint.h"
#define UF_CALL(X) (report_error( __FILE__, __LINE__, #X, (X)))

static int report_error(char *file, int line, char *call, int irc)
{
	if (irc)
	{
		char err[133],
			msg[133];

		sprintf(msg, "*** ERROR code %d at line %d in %s:\n+++ ",
			irc, line, file);
		UF_get_fail_message(irc, err);

		UF_print_syslog(msg, FALSE);
		UF_print_syslog(err, FALSE);
		UF_print_syslog("\n", FALSE);
		UF_print_syslog(call, FALSE);
		UF_print_syslog(";\n", FALSE);

		if (!UF_UI_open_listing_window())
		{
			UF_UI_write_listing_window(msg);
			UF_UI_write_listing_window(err);
			UF_UI_write_listing_window("\n");
			UF_UI_write_listing_window(call);
			UF_UI_write_listing_window(";\n");
		}
	}

	return(irc);
}

extern Features::PointFeature * CreatePointFeature(double coord[3])
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	Point3d coordinates(coord[0], coord[1], coord[2]);
	Point *thePoint = NULL;
	thePoint = workPart->Points()->CreatePoint(coordinates);
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
	coord pt_temp[5] = { 0 };
	pt_temp[0].base_pt[0] = (pt_coods_selected[0].base_pt[0] + pt_coods_selected[1].base_pt[0]) / 2;
	pt_temp[0].base_pt[1] = (pt_coods_selected[0].base_pt[1] + pt_coods_selected[1].base_pt[1]) / 2;
	pt_temp[0].base_pt[2] = (pt_coods_selected[0].base_pt[2] + pt_coods_selected[1].base_pt[2]) / 2;

	pt_temp[1].base_pt[0] = (pt_coods_selected[1].base_pt[0] + pt_coods_selected[2].base_pt[0]) / 2;
	pt_temp[1].base_pt[1] = (pt_coods_selected[1].base_pt[1] + pt_coods_selected[2].base_pt[1]) / 2;
	pt_temp[1].base_pt[2] = (pt_coods_selected[1].base_pt[2] + pt_coods_selected[2].base_pt[2]) / 2;

	pt_temp[2].base_pt[0] = (pt_coods_selected[2].base_pt[0] + pt_coods_selected[3].base_pt[0]) / 2;
	pt_temp[2].base_pt[1] = (pt_coods_selected[2].base_pt[1] + pt_coods_selected[3].base_pt[1]) / 2;
	pt_temp[2].base_pt[2] = (pt_coods_selected[2].base_pt[2] + pt_coods_selected[3].base_pt[2]) / 2;

	pt_temp[3].base_pt[0] = (pt_coods_selected[3].base_pt[0] + pt_coods_selected[0].base_pt[0]) / 2;
	pt_temp[3].base_pt[1] = (pt_coods_selected[3].base_pt[1] + pt_coods_selected[0].base_pt[1]) / 2;
	pt_temp[3].base_pt[2] = (pt_coods_selected[3].base_pt[2] + pt_coods_selected[0].base_pt[2]) / 2;

	pt_temp[4].base_pt[0] = (pt_coods_selected[0].base_pt[0] + pt_coods_selected[2].base_pt[0]) / 2;
	pt_temp[4].base_pt[1] = (pt_coods_selected[0].base_pt[1] + pt_coods_selected[2].base_pt[1]) / 2;
	pt_temp[4].base_pt[2] = (pt_coods_selected[0].base_pt[2] + pt_coods_selected[2].base_pt[2]) / 2;   //获取选取的四个点的中点坐标，pt_coods[0-3]是手动选取的点的坐标

	pt_coods[0][0] = pt_coods_selected[0];
	pt_coods[0][2] = pt_coods_selected[1];
	pt_coods[2][2] = pt_coods_selected[2];
	pt_coods[2][0] = pt_coods_selected[3];

	double guess2[3] = { 0.0,0.0,0.0 };
	double min_dist = 0.0;   //最短距离
	double pt_on_obj1[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object1（pt_temp）
	double pt_on_obj2[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object2（object_facet）

	int errorCode = 0;
	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(	NULL_TAG, object_facet, 1, pt_temp[0].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[0][1].base_pt[0] = pt_on_obj2[0];
	pt_coods[0][1].base_pt[1] = pt_on_obj2[1];
	pt_coods[0][1].base_pt[2] = pt_on_obj2[2];

	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[1].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[1][2].base_pt[0] = pt_on_obj2[0];
	pt_coods[1][2].base_pt[1] = pt_on_obj2[1];
	pt_coods[1][2].base_pt[2] = pt_on_obj2[2];

	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[2].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[2][1].base_pt[0] = pt_on_obj2[0];
	pt_coods[2][1].base_pt[1] = pt_on_obj2[1];
	pt_coods[2][1].base_pt[2] = pt_on_obj2[2];

	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[3].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[1][0].base_pt[0] = pt_on_obj2[0];
	pt_coods[1][0].base_pt[1] = pt_on_obj2[1];
	pt_coods[1][0].base_pt[2] = pt_on_obj2[2];

	errorCode = UF_CALL(UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[4].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2));
	pt_coods[1][1].base_pt[0] = pt_on_obj2[0];
	pt_coods[1][1].base_pt[1] = pt_on_obj2[1];
	pt_coods[1][1].base_pt[2] = pt_on_obj2[2];

	return 0;
}