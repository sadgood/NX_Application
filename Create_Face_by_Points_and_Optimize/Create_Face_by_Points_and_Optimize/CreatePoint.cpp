#include "CreatePoint.h"

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

extern int GetPointsCoord(coord pt_coods[9], tag_t object_facet)
{
	coord pt_temp[5] = { 0 };
	pt_temp[0].base_pt[0] = (pt_coods[0].base_pt[0] + pt_coods[1].base_pt[0]) / 2;
	pt_temp[0].base_pt[1] = (pt_coods[0].base_pt[1] + pt_coods[1].base_pt[1]) / 2;
	pt_temp[0].base_pt[2] = (pt_coods[0].base_pt[2] + pt_coods[1].base_pt[2]) / 2;

	pt_temp[1].base_pt[0] = (pt_coods[1].base_pt[0] + pt_coods[2].base_pt[0]) / 2;
	pt_temp[1].base_pt[1] = (pt_coods[1].base_pt[1] + pt_coods[2].base_pt[1]) / 2;
	pt_temp[1].base_pt[2] = (pt_coods[1].base_pt[2] + pt_coods[2].base_pt[2]) / 2;

	pt_temp[2].base_pt[0] = (pt_coods[2].base_pt[0] + pt_coods[3].base_pt[0]) / 2;
	pt_temp[2].base_pt[1] = (pt_coods[2].base_pt[1] + pt_coods[3].base_pt[1]) / 2;
	pt_temp[2].base_pt[2] = (pt_coods[2].base_pt[2] + pt_coods[3].base_pt[2]) / 2;

	pt_temp[3].base_pt[0] = (pt_coods[3].base_pt[0] + pt_coods[0].base_pt[0]) / 2;
	pt_temp[3].base_pt[1] = (pt_coods[3].base_pt[1] + pt_coods[0].base_pt[1]) / 2;
	pt_temp[3].base_pt[2] = (pt_coods[3].base_pt[2] + pt_coods[0].base_pt[2]) / 2;

	pt_temp[4].base_pt[0] = (pt_temp[0].base_pt[0] + pt_temp[2].base_pt[0]) / 2;
	pt_temp[4].base_pt[1] = (pt_temp[0].base_pt[1] + pt_temp[2].base_pt[1]) / 2;
	pt_temp[4].base_pt[2] = (pt_temp[0].base_pt[2] + pt_temp[2].base_pt[2]) / 2;   //��ȡѡȡ���ĸ�����е����꣬pt_coods[0-3]���ֶ�ѡȡ�ĵ������

	double guess2[3] = { 0.0,0.0,0.0 };
	double min_dist = 0.0;   //��̾���
	double pt_on_obj1[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object1��pt_temp��
	double pt_on_obj2[3] = { 0.0,0.0,0.0 };   //Minimum distance Point on object2��object_facet��

	for (int iLoop = 0; iLoop < 5; ++iLoop)
	{
		UF_MODL_ask_minimum_dist(NULL_TAG, object_facet, 1, pt_temp[iLoop].base_pt, 0, guess2, &min_dist, pt_on_obj1, pt_on_obj2);
		pt_coods[iLoop + 4].base_pt[0] = pt_on_obj2[0];
		pt_coods[iLoop + 4].base_pt[1] = pt_on_obj2[1];
		pt_coods[iLoop + 4].base_pt[2] = pt_on_obj2[2];
	}    //��ȡÿ���ߵ��е����굽�Ƶ�����ĵ������

	return 0;
}