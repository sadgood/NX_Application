/*****************************************************************************
**
** OutputWireFrame.cpp
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
#include <map>
#include <vector>
#include <uf.h>
#include <uf_ui.h>
#include <uf_exit.h>
#include <uf_curve.h>
#include <uf_obj.h>

#define UF_CALL(X) (report_error( __FILE__, __LINE__, #X, (X)))

static int report_error( char *file, int line, char *call, int irc)
{
    if (irc)
    {
        char err[133],
             msg[133];

        sprintf_s(msg, 133, "*** ERROR code %d at line %d in %s:\n+++ ",
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


static int set_select_filter( UF_UI_selection_p_t select, void* user_data)
{
    int num_triples = 1;
    UF_UI_mask_t mask_triples[] = { { UF_spline_type, 0, 0 } };

    if((UF_UI_set_sel_mask(
        select, 
        UF_UI_SEL_MASK_CLEAR_AND_ENABLE_SPECIFIC,
        num_triples, 
        mask_triples)) 
        == 0
        )
    {
        return (UF_UI_SEL_SUCCESS);
    }
    else
    {
        return (UF_UI_SEL_FAILURE);
    }
}

/*****************************************************************************
**  Activation Methods
*****************************************************************************/
/*  Explicit Activation
**      This entry point is used to activate the application explicitly, as in
**      "File->Execute UG/Open->User Function..." */
extern DllExport void ufusr( char *parm, int *returnCode, int rlen )
{
    /* Initialize the API environment */
    if( UF_CALL(UF_initialize()) ) 
    {
        /* Failed to initialize */
        return;
    }
    
    /* TODO: Add your application code here */

    UF_UI_open_listing_window();

    int error_code = 0;
    int response = 0; 
    int count = 0;
    tag_p_t objects = NULL;

    error_code = UF_UI_select_with_class_dialog (
        "select curves", 
        "select Curves", 
        UF_UI_SEL_SCOPE_WORK_PART, 
        set_select_filter, 
        NULL, 
        &response, 
        &count, 
        &objects );

    std::map < int, std::vector<std::string> > idTextLinesMap;

    for( int i = 0; i < count; i++ )
    {
        UF_DISP_set_highlight( objects[i], FALSE );

        int errorCode = 0;
        UF_CURVE_spline_t splineData = { 0, 0, 0, NULL, NULL, 0.0, 0.0 };
        errorCode = UF_CURVE_ask_spline_data( objects[i], &splineData );

        if( errorCode != 0 )    // failed to get spline data
            continue;

        if( splineData.num_poles != 4 )
        {
            UF_free( splineData.poles);
            UF_free( splineData.knots);
            continue;
        }

        if( splineData.order != 4 )
        {
            UF_free( splineData.poles);
            UF_free( splineData.knots);
            continue;
        }

        char objectName[UF_OBJ_NAME_LEN+1] = "";
        UF_OBJ_ask_name( objects[i], objectName );

        if( strlen( objectName ) == 0 )
        {
            UF_free( splineData.poles);
            UF_free( splineData.knots);
            continue;
        }

        char idString[UF_OBJ_NAME_LEN+1] = "";
        sscanf_s( objectName, "T%[0-9a-z]", idString, UF_OBJ_NAME_LEN+1 );

        if( strlen( idString) == 0 )
        {
            UF_free( splineData.poles);
            UF_free( splineData.knots);
            continue;
        }

        int curveIndex = 0;
        curveIndex = atoi( idString );
        char textLine1[1024] = "";
        sprintf_s(textLine1, 1024, 
            "BEZIER  *%8d%12d%16f%16f%16f T%-6d\n",
            curveIndex, 0, splineData.poles[0][0], splineData.poles[0][1], splineData.poles[0][2], curveIndex);

        char textLine2[1024] = "";
        sprintf_s(textLine2, 1024,
            "*T%-6d%16f%16f%16f\n",
            curveIndex,splineData.poles[1][0], splineData.poles[1][1], splineData.poles[1][2]);

        char textLine3[1024] = "";
        sprintf_s(textLine3, 1024,
            "*T%-6d%16f%16f%16f\n",
            curveIndex,splineData.poles[2][0], splineData.poles[2][1], splineData.poles[2][2]);

        char textLine4[1024] = "";
        sprintf_s(textLine4, 1024,
            "*T%-6d%16f%16f%16f\n",
            curveIndex,splineData.poles[3][0], splineData.poles[3][1], splineData.poles[3][2]);

        std::vector<std::string> textLines;
        textLines.push_back( textLine1 );
        textLines.push_back( textLine2 );
        textLines.push_back( textLine3 );
        textLines.push_back( textLine4 );

        idTextLinesMap.insert(std::map< int , std::vector<std::string> >::value_type( curveIndex , textLines ) );

        UF_free( splineData.poles);
        UF_free( splineData.knots);
    }

    for( std::map< int , std::vector<std::string> >::iterator itr = idTextLinesMap.begin(); itr != idTextLinesMap.end(); itr++ )
    {
        UF_UI_write_listing_window( itr->second.at(0).c_str() );
        UF_UI_write_listing_window( itr->second.at(1).c_str() );
        UF_UI_write_listing_window( itr->second.at(2).c_str() );
        UF_UI_write_listing_window( itr->second.at(3).c_str() ); 
    }

    UF_free( objects );

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
extern int ufusr_ask_unload( void )
{
    return( UF_UNLOAD_IMMEDIATELY );
}

