/*****************************************************************************
**
** kf_ufun_function_check_lib.cpp
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
#include <set>
#include <string>
#include <uf.h>
#include <uf_ui.h>
#include <uf_exit.h>
#include <uf_kf.h>
#include <uf_group.h>
#include <uf_obj.h>
#include <assert.h>
#include <uf_assem.h>
#include <uf_modl.h>
#include <uf_facet.h>

#define UF_CALL(X) (report_error( __FILE__, __LINE__, #X, (X)))

static int report_error( char *file, int line, char *call, int irc)
{
    if (irc)
    {
        char err[133] = "";
        char msg[133] = "";

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


/*****************************************************************************
**  Activation Methods
*****************************************************************************/
/*  Unigraphics Startup
**      This entry point activates the application at Unigraphics startup */
extern DllExport void ufsta( char *param, int *returnCode, int rlen )
{
    /* Initialize the API environment */
    if( UF_CALL(UF_initialize()) ) 
    {
        /* Failed to initialize */
        return;
    }
    
    /* TODO: Add your application code here */

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
    return( UF_UNLOAD_UG_TERMINATE );
}

extern "C" DllExport void MISC_AskObjectPointsAverageDistance(
    UF_KF_value_t *data,    /*<I>*/
    int num,                /*<I>*/
    UF_KF_value_t *rv       /*<O>*/
    )
{
    int errorCode = 0;
    errorCode = UF_CALL( UF_initialize() );

    assert( num == 2 );

    tag_t sourceObject = NULL_TAG;
    UF_KF_ask_tag( data[0], &sourceObject );

    if( sourceObject == NULL_TAG )
    {
        UF_KF_make_number( -1.0, rv );
        UF_terminate();
        return;
    }

    char *groupNameStr = NULL;
    UF_KF_ask_string( data[1], &groupNameStr ); // don't free groupNameStr

    if( strlen(groupNameStr) == 0 )
    {
        UF_KF_make_number( -1.0, rv );
        UF_terminate();
        return;
    }

    tag_t groupTag = NULL;

    UF_OBJ_cycle_by_name_and_type(
        UF_ASSEM_ask_work_part(),
        groupNameStr,
        UF_group_type,
        false,
        &groupTag );

    int numObjects = 0;
    tag_t *objects = NULL;
    UF_GROUP_ask_group_data( groupTag, &objects, &numObjects );

    int numPoints = 0;
    double totalDist =0.0;
    for( int i = 0; i < numObjects; i++ )
    {
        int type = 0;
        int subtype = 0;

        UF_OBJ_ask_type_and_subtype( objects[i], &type, &subtype );

        if( type != UF_point_type )
            continue;

        numPoints++;

        double guess1[ 3 ] = { 0.0, 0.0, 0.0 };
        double guess2[ 3 ] = { 0.0, 0.0, 0.0 };
        double minDist = 0.0;
        double ptOnObj1[ 3 ] = { 0.0, 0.0, 0.0 };
        double ptOnObj2[ 3 ] = { 0.0, 0.0, 0.0 };

        errorCode = UF_MODL_ask_minimum_dist (
            sourceObject, 
            objects[i], 
            FALSE, 
            guess1, 
            FALSE, 
            guess2, 
            &minDist, 
            ptOnObj1, 
            ptOnObj2 );

        if( errorCode != 0 )
        {
            UF_free( objects );
            UF_KF_make_number( -1.0, rv );
            UF_terminate();
            return;
        }

        totalDist = totalDist + minDist;
    }

    UF_free( objects );

    double averageDist = 0.0;
    
    if( numPoints == 0 )
    {
        averageDist = -1.0;
    }
    else
    {
        averageDist = totalDist / numPoints;
    }

    UF_KF_make_number( averageDist, rv );

    UF_terminate();
}

extern "C" DllExport void MISC_AskGroupPoints(
    UF_KF_value_t *data,    /*<I>*/
    int num,                /*<I>*/
    UF_KF_value_t *rv       /*<O>*/
)
{
    int errorCode = 0;
    errorCode = UF_CALL( UF_initialize() );

    assert( num == 1 );

    char *groupNameStr = NULL;
    UF_KF_ask_string( data[0], &groupNameStr ); // don't free groupNameStr

    if( strlen(groupNameStr) == 0 )
    {
        UF_KF_make_list( NULL, rv );
        UF_terminate();
        return;
    }

    tag_t groupTag = NULL;

    UF_OBJ_cycle_by_name_and_type(
        UF_ASSEM_ask_work_part(),
        groupNameStr,
        UF_group_type,
        false,
        &groupTag );

    int numObjects = 0;
    tag_t *objects = NULL;
    UF_GROUP_ask_group_data( groupTag, &objects, &numObjects );

    UF_KF_list_p_t listData = NULL;

    for( int i = 0; i < numObjects; i++ )
    {
        int type = 0;
        int subtype = 0;

        UF_OBJ_ask_type_and_subtype( objects[i], &type, &subtype );

        if( type != UF_point_type )
            continue;

        UF_KF_value_p_t tmpValue = NULL;

        UF_KF_make_tag( objects[i], &tmpValue );
        UF_KF_list_push( listData, tmpValue, &listData );
    }

    UF_free( objects );
    UF_KF_make_list( listData, rv );
    UF_terminate();
}

extern "C" DllExport void MISC_AskObjectPointsMaxDistance(
    UF_KF_value_t *data,    /*<I>*/
    int num,                /*<I>*/
    UF_KF_value_t *rv       /*<O>*/
    )
{
    int errorCode = 0;
    errorCode = UF_CALL( UF_initialize() );

    assert( num == 2 );

    tag_t sourceObject = NULL_TAG;
    UF_KF_ask_tag( data[0], &sourceObject );

    if( sourceObject == NULL_TAG )
    {
        UF_KF_make_list( NULL, rv );
        UF_terminate();
        return;
    }

    char *groupNameStr = NULL;
    UF_KF_ask_string( data[1], &groupNameStr ); // don't free groupNameStr

    if( strlen(groupNameStr) == 0 )
    {
        UF_KF_make_list( NULL, rv );
        UF_terminate();
        return;
    }

    tag_t groupTag = NULL;

    UF_OBJ_cycle_by_name_and_type(
        UF_ASSEM_ask_work_part(),
        groupNameStr,
        UF_group_type,
        false,
        &groupTag );

    int numObjects = 0;
    tag_t *objects = NULL;
    UF_GROUP_ask_group_data( groupTag, &objects, &numObjects );

    double maxDist =-1.0;
    tag_t maxPointTag = NULL_TAG;

    for( int i = 0; i < numObjects; i++ )
    {
        int type = 0;
        int subtype = 0;

        UF_OBJ_ask_type_and_subtype( objects[i], &type, &subtype );

        if( type != UF_point_type )
            continue;

        double guess1[ 3 ] = { 0.0, 0.0, 0.0 };
        double guess2[ 3 ] = { 0.0, 0.0, 0.0 };
        double minDist = 0.0;
        double ptOnObj1[ 3 ] = { 0.0, 0.0, 0.0 };
        double ptOnObj2[ 3 ] = { 0.0, 0.0, 0.0 };

        errorCode = UF_MODL_ask_minimum_dist (
            sourceObject, 
            objects[i], 
            FALSE, 
            guess1, 
            FALSE, 
            guess2, 
            &minDist, 
            ptOnObj1, 
            ptOnObj2 );

        if( errorCode != 0 )
        {
            UF_free( objects );
            UF_KF_make_list( NULL, rv );
            UF_terminate();
            return;
        }

        if( minDist > maxDist )
        {
            maxDist = minDist;
            maxPointTag = objects[i];
        }
    }

    UF_free( objects );

    double averageDist = 0.0;

    UF_KF_list_p_t listData = NULL;

    UF_KF_value_p_t valueData = NULL;
    UF_KF_make_tag( maxPointTag, &valueData );
    UF_KF_list_push( listData, valueData, &listData );

    valueData = NULL;
    UF_KF_make_number( maxDist, &valueData );
    UF_KF_list_push( listData, valueData, &listData );

    UF_KF_make_list( listData, rv );

    UF_terminate();
}

extern "C" DllExport void MISC_AskFirstFacetBodyByName(
    UF_KF_value_t *data,    /*<I>*/
    int num,                /*<I>*/
    UF_KF_value_t *rv       /*<O>*/
    )
{
    int errorCode = 0;
    errorCode = UF_CALL( UF_initialize() );

    assert( num == 1 );

    char *nameStr = NULL;
    UF_KF_ask_string( data[0], &nameStr ); // don't free groupNameStr

    if( strlen(nameStr) == 0 )
    {
        UF_KF_make_tag( NULL_TAG, rv );
        UF_terminate();
        return;
    }

    tag_t currentObject = NULL_TAG;

    do 
    {
        UF_OBJ_cycle_by_name( nameStr, &currentObject );

        if( currentObject != NULL_TAG )
        {
            int type = UF_point_type;
            int subtype = 0;

            UF_OBJ_ask_type_and_subtype( currentObject, &type, &subtype);
            
            if( type == UF_faceted_model_type )
            {
                break;
            }
        }
    } while ( currentObject != NULL_TAG );

    UF_KF_make_tag( currentObject, rv );
    UF_terminate();
}

extern "C" DllExport void MISC_AskSheetToFacetAverageDistance(
    UF_KF_value_t *data,    /*<I>*/
    int num,                /*<I>*/
    UF_KF_value_t *rv       /*<O>*/
)
{
    int errorCode = 0;
    errorCode = UF_CALL( UF_initialize() );

    assert( num == 2 );

    tag_t facetBody = NULL_TAG;
    UF_KF_ask_tag( data[0], &facetBody );

    if( facetBody == NULL_TAG )
    {
        UF_KF_make_number( -1.0, rv );
        UF_terminate();
    }
    else
    {
        int type = 0;
        int subtype = 0;

        UF_OBJ_ask_type_and_subtype( facetBody, &type, &subtype );

        if( UF_faceted_model_type!= type )
        {
            UF_KF_make_number( -1.0, rv );
            UF_terminate();
        }
    }

    tag_t sheetBody = NULL_TAG;
    UF_KF_ask_tag( data[1], &sheetBody );

    if( sheetBody == NULL_TAG )
    {
        UF_KF_make_number( -1.0, rv );
        UF_terminate();
    }
    else
    {
        int bodyType = 0;
        UF_MODL_ask_body_type( sheetBody, &bodyType );

        if( UF_MODL_SHEET_BODY != bodyType )
        {
            UF_KF_make_number( -1.0, rv );
            UF_terminate();
        }
    }

    int numFacets = 0;
    UF_FACET_ask_n_facets_in_model( facetBody, &numFacets );

    int step = 0;
    step = ( ( numFacets / 2000 ) > 1 )? ( numFacets/ 2000 ):1; 

    int k = 1/2;

    std::set<std::string> coordStrings;

    for( int i = 0; i < numFacets; i=i+step )
    {
        int numVertices = 0;
        double vertices[6][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } };
        UF_FACET_ask_vertices_of_facet( facetBody, i, &numVertices, vertices );

        for ( int j = 0; j < numVertices; j++ )
        {
            char msg[1024] = "";
            sprintf_s( msg, 1024, "%16.6f,%16.6f,%16.6f", vertices[j][0]+0.5e-8,vertices[j][1]+0.5e-8,vertices[j][2]+0.5e-8 );
            coordStrings.insert( msg );
        }
    }

    if( coordStrings.empty() )
    {
        UF_KF_make_number( -1.0, rv );
        UF_terminate();
    }

    double sumDist = 0.0;

    for( std::set<std::string>::iterator itr = coordStrings.begin(); itr != coordStrings.end(); ++itr )
    {

        char xstr[1024] = "";
        char ystr[1024] = "";
        char zstr[1024] = "";
        sscanf_s( itr->c_str(), "%*[ ]%[^,],%*[ ]%[^,],%*[ ]%[^,]", xstr, sizeof( xstr), ystr,sizeof( ystr), zstr, sizeof( zstr) );

        double coord[3] = { 0.0, 0.0, 0.0 };
        coord[0] = atof( xstr );
        coord[1] = atof( ystr );
        coord[2] = atof( zstr );

        double guess2[ 3 ] = { 0.0, 0.0, 0.0 };
        double minDist = 0.0;
        double ptOnObj1[ 3 ] = { 0.0, 0.0, 0.0 };
        double ptOnObj2[ 3 ] = { 0.0, 0.0, 0.0 };

        errorCode = UF_MODL_ask_minimum_dist (
            NULL_TAG,
            sheetBody, 
            TRUE, 
            coord, 
            FALSE, 
            guess2, 
            &minDist, 
            ptOnObj1, 
            ptOnObj2 );

        sumDist = sumDist + minDist;
    }

    UF_KF_make_number( sumDist/ coordStrings.size(), rv );
    UF_terminate();
}