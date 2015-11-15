/*****************************************************************************
**
** Create_Face_by_Points.cpp
**
** Description:
**     Contains Unigraphics entry points for the application.
**
*****************************************************************************/

/* Include files */
#if ! defined ( __hp9000s800 ) && ! defined ( __sgi ) && ! defined ( __sun )
#   include <strstream>
#   include <iostream>
using std::ostrstream;
using std::endl;
using std::ends;
using std::cerr;
#else
#   include <strstream.h>
#   include <iostream.h>
#endif
#include "uf.h"
#include "uf_ui.h"
#include "uf_exit.h"
#include "uf_ui_types.h"

#include "Function_Repos.h"

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


/*****************************************************************************
**  Activation Methods
*****************************************************************************/
/*  Explicit Activation
**      This entry point is used to activate the application explicitly, as in
**      "File->Execute UG/Open->User Function..." */



extern DllExport void ufusr(char *parm, int *returnCode, int rlen)
{
	/* Initialize the API environment */
	if (UF_CALL(UF_initialize()))
	{
		/* Failed to initialize */
		return;
	}

	/* TODO: Add your application code here */

	char cue_facet[] = "message";
	char title_facet[] = "select facet";
	int response_facet = 0;
	tag_t object_facet = NULL_TAG, view_facet = NULL_TAG;
	double cursor_facet[3] = { 0.0,0.0,0.0 };

	int errorCode_facet = 0;
	errorCode_facet = UF_CALL(UF_UI_select_with_single_dialog(cue_facet, title_facet, UF_UI_SEL_SCOPE_WORK_PART, NULL, NULL, &response_facet, &object_facet, cursor_facet, &view_facet));

	if (object_facet != NULL_TAG)  //??facet body
	{
		UF_DISP_set_highlight(object_facet, 0);

		char *cue = "Point Construct";
		UF_UI_POINT_base_method_t base_method = UF_UI_POINT_ON_SURFACE_PT;
		tag_t point_tag[9] = { 0 };
		coord pt_coods[9] = { 0 };
		int response = 0;
		for (int iLoop = 0; iLoop < 4; ++iLoop)
		{
			UF_UI_point_construct(cue, &base_method, &point_tag[iLoop], pt_coods[iLoop].base_pt, &response);
		} //构建4个控制点

		Create_Point(pt_coods, object_facet);   //建立余下的5个点，9个点均在facet body上

		tag_t line[6] = { 0 };  //定义6条直线

		Create_Line(pt_coods, line);  //构建6条样条曲线

		Create_Face(line); //根据曲线网格生成曲面
	}





	/* Terminate the API environment */
	UF_CALL(UF_terminate());
}

/*****************************************************************************
**  Utilities
*****************************************************************************/

/* Unload Handler
**     This function specifies when to unload your application from Unigraphics.
**     If your application registers a callback (from a MenuScript item or a
**     User Defined Object for example), this function MUST return
**     "UF_UNLOAD_UG_TERMINATE". */
extern int ufusr_ask_unload(void)
{
	return(UF_UNLOAD_IMMEDIATELY);
}

static int SetFaceSelection(UF_UI_selection_p_t select, void* user_data)
{
	int num_triples = 1;
	UF_UI_mask_t mask_triples[] = { UF_solid_type, UF_solid_face_subtype, UF_UI_SEL_FEATURE_ANY_FACE };
	/* enable only lines and edges */
	if ((UF_CALL(UF_UI_set_sel_mask(select, UF_UI_SEL_MASK_CLEAR_AND_ENABLE_SPECIFIC, num_triples, mask_triples))) == 0)
	{
		return (UF_UI_SEL_SUCCESS);
	}
	else
	{
		return (UF_UI_SEL_FAILURE);
	}
}
