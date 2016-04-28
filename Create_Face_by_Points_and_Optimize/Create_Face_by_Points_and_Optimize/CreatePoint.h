#pragma once

#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Features_PointFeature.hxx>

using namespace std;
using namespace NXOpen;

Features::PointFeature * CreatePointFeature(double coord[3])
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