#pragma once

#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <vector>

#include "uf_defs.h"
#include "uf_modl.h"
#include "uf_curve.h"
#include <uf.h>
#include <uf_ui.h>

#define UF_CALL(X) (report_error( __FILE__, __LINE__, #X, (X)))

using namespace std;
using namespace NXOpen;

struct coord
{
	double base_pt[3];
};

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

extern Features::PointFeature * CreatePointFeature(double coord[3]);
extern int GetPointsCoord(coord *pt_coods_selected, const tag_t &object_facet, vector<vector<coord> > &pt_coods);