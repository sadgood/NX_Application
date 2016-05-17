#include "UFun.h"

extern void MISC_AskSheetToFacetAverageDistance(
	tag_t facetBody,    /*<I>*/
	tag_t sheetBody,
	double &result       /*<O>*/
)
{
	int errorCode = 0;
	errorCode = UF_CALL(UF_initialize());

	if (facetBody == NULL_TAG)
	{
		result = -1.0;
		UF_terminate();
	}
	else
	{
		int type = 0;
		int subtype = 0;

		UF_OBJ_ask_type_and_subtype(facetBody, &type, &subtype);

		if (UF_faceted_model_type != type)
		{
			result = -1.0;
			UF_terminate();
		}
	}

	if (sheetBody == NULL_TAG)
	{
		result = -1.0;
		UF_terminate();
	}
	else
	{
		int bodyType = 0;
		UF_MODL_ask_body_type(sheetBody, &bodyType);

		/*if (UF_MODL_SHEET_BODY != bodyType)
		{
			result = -1.0;
			UF_terminate();
		}*/
	}

	int numFacets = 0;
	UF_FACET_ask_n_facets_in_model(facetBody, &numFacets);

	int step = 0;
	step = ((numFacets / 2000) > 1) ? (numFacets / 2000) : 1;

	int k = 1 / 2;

	std::set<std::string> coordStrings;

	for (int i = 0; i < numFacets; i = i + step)
	{
		int numVertices = 0;
		double vertices[6][3] = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };
		UF_FACET_ask_vertices_of_facet(facetBody, i, &numVertices, vertices);

		for (int j = 0; j < numVertices; j++)
		{
			char msg[1024] = "";
			sprintf_s(msg, 1024, "%16.6f,%16.6f,%16.6f", vertices[j][0] + 0.5e-8, vertices[j][1] + 0.5e-8, vertices[j][2] + 0.5e-8);
			coordStrings.insert(msg);
		}
	}

	if (coordStrings.empty())
	{
		result = -1.0;
		UF_terminate();
	}

	double sumDist = 0.0;

	for (std::set<std::string>::iterator itr = coordStrings.begin(); itr != coordStrings.end(); ++itr)
	{

		char xstr[1024] = "";
		char ystr[1024] = "";
		char zstr[1024] = "";
		sscanf_s(itr->c_str(), "%*[ ]%[^,],%*[ ]%[^,],%*[ ]%[^,]", xstr, sizeof(xstr), ystr, sizeof(ystr), zstr, sizeof(zstr));

		double coord[3] = { 0.0, 0.0, 0.0 };
		coord[0] = atof(xstr);
		coord[1] = atof(ystr);
		coord[2] = atof(zstr);

		double guess2[3] = { 0.0, 0.0, 0.0 };
		double minDist = 0.0;
		double ptOnObj1[3] = { 0.0, 0.0, 0.0 };
		double ptOnObj2[3] = { 0.0, 0.0, 0.0 };

		errorCode = UF_MODL_ask_minimum_dist(
			NULL_TAG,
			sheetBody,
			TRUE,
			coord,
			FALSE,
			guess2,
			&minDist,
			ptOnObj1,
			ptOnObj2);

		sumDist = sumDist + minDist;
	}

	result = sumDist / coordStrings.size();
	UF_terminate();
}