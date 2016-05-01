//==============================================================================
//  WARNING!!  This file is overwritten by the Block UI Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  C:\Users\zhaoz\Documents\GitHubVisualStudio\NX_Application\Create_Face_by_Points_and_Optimize\Create_Face_by_Points_and_Optimize\Create_Face_by_Points_and_Optimize.cpp
//
//        This file was generated by the NX Block UI Styler
//        Created by: zhaoz
//              Version: NX 8.5
//              Date: 04-29-2016  (Format: mm-dd-yyyy)
//              Time: 09:12 (Format: hh-mm)
//
//==============================================================================

//==============================================================================
//  Purpose:  This TEMPLATE file contains C++ source to guide you in the
//  construction of your Block application dialog. The generation of your
//  dialog file (.dlx extension) is the first step towards dialog construction
//  within NX.  You must now create a NX Open application that
//  utilizes this file (.dlx).
//
//  The information in this file provides you with the following:
//
//  1.  Help on how to load and display your Block UI Styler dialog in NX
//      using APIs provided in NXOpen.BlockStyler namespace
//  2.  The empty callback methods (stubs) associated with your dialog items
//      have also been placed in this file. These empty methods have been
//      created simply to start you along with your coding requirements.
//      The method name, argument list and possible return values have already
//      been provided for you.
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "Create_Face_by_Points_and_Optimize.hpp"
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(Create_Face_by_Points_and_Optimize::theSession) = NULL;
UI *(Create_Face_by_Points_and_Optimize::theUI) = NULL;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
Create_Face_by_Points_and_Optimize::Create_Face_by_Points_and_Optimize()
{
    try
    {
        // Initialize the NX Open C++ API environment
        Create_Face_by_Points_and_Optimize::theSession = NXOpen::Session::GetSession();
        Create_Face_by_Points_and_Optimize::theUI = UI::GetUI();
        theDlxFileName = "Create_Face_by_Points_and_Optimize.dlx";
        theDialog = Create_Face_by_Points_and_Optimize::theUI->CreateDialog(theDlxFileName);
        // Registration of callback functions
        theDialog->AddApplyHandler(make_callback(this, &Create_Face_by_Points_and_Optimize::apply_cb));
        theDialog->AddOkHandler(make_callback(this, &Create_Face_by_Points_and_Optimize::ok_cb));
        theDialog->AddUpdateHandler(make_callback(this, &Create_Face_by_Points_and_Optimize::update_cb));
        theDialog->AddFilterHandler(make_callback(this, &Create_Face_by_Points_and_Optimize::filter_cb));
        theDialog->AddInitializeHandler(make_callback(this, &Create_Face_by_Points_and_Optimize::initialize_cb));
        theDialog->AddDialogShownHandler(make_callback(this, &Create_Face_by_Points_and_Optimize::dialogShown_cb));

		for (int i = 0; i < 9; ++i)
			pPointFeature[i] = NULL;
		for (int i = 0; i < 9; ++i)
			pt_coods[i] = { 0 };
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        throw;
    }
}

//------------------------------------------------------------------------------
// Destructor for NX Styler class
//------------------------------------------------------------------------------
Create_Face_by_Points_and_Optimize::~Create_Face_by_Points_and_Optimize()
{
    if (theDialog != NULL)
    {
        delete theDialog;
        theDialog = NULL;
    }
}
//------------------------------- DIALOG LAUNCHING ---------------------------------
//
//    Before invoking this application one needs to open any part/empty part in NX
//    because of the behavior of the blocks.
//
//    Make sure the dlx file is in one of the following locations:
//        1.) From where NX session is launched
//        2.) $UGII_USER_DIR/application
//        3.) For released applications, using UGII_CUSTOM_DIRECTORY_FILE is highly
//            recommended. This variable is set to a full directory path to a file 
//            containing a list of root directories for all custom applications.
//            e.g., UGII_CUSTOM_DIRECTORY_FILE=$UGII_ROOT_DIR\menus\custom_dirs.dat
//
//    You can create the dialog using one of the following way:
//
//    1. USER EXIT
//
//        1) Create the Shared Library -- Refer "Block UI Styler programmer's guide"
//        2) Invoke the Shared Library through File->Execute->NX Open menu.
//
//------------------------------------------------------------------------------
extern "C" DllExport void  ufusr(char *param, int *retcod, int param_len)
{
    Create_Face_by_Points_and_Optimize *theCreate_Face_by_Points_and_Optimize = NULL;
    try
    {
        theCreate_Face_by_Points_and_Optimize = new Create_Face_by_Points_and_Optimize();
        // The following method shows the dialog immediately
        theCreate_Face_by_Points_and_Optimize->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        Create_Face_by_Points_and_Optimize::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    if(theCreate_Face_by_Points_and_Optimize != NULL)
    {
        delete theCreate_Face_by_Points_and_Optimize;
        theCreate_Face_by_Points_and_Optimize = NULL;
    }
}

//------------------------------------------------------------------------------
// This method specifies how a shared image is unloaded from memory
// within NX. This method gives you the capability to unload an
// internal NX Open application or user  exit from NX. Specify any
// one of the three constants as a return value to determine the type
// of unload to perform:
//
//
//    Immediately : unload the library as soon as the automation program has completed
//    Explicitly  : unload the library from the "Unload Shared Image" dialog
//    AtTermination : unload the library when the NX session terminates
//
//
// NOTE:  A program which associates NX Open applications with the menubar
// MUST NOT use this option since it will UNLOAD your NX Open application image
// from the menubar.
//------------------------------------------------------------------------------
extern "C" DllExport int ufusr_ask_unload()
{
    //return (int)Session::LibraryUnloadOptionExplicitly;
    return (int)Session::LibraryUnloadOptionImmediately;
    //return (int)Session::LibraryUnloadOptionAtTermination;
}

//------------------------------------------------------------------------------
// Following method cleanup any housekeeping chores that may be needed.
// This method is automatically called by NX.
//------------------------------------------------------------------------------
extern "C" DllExport void ufusr_cleanup(void)
{
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        Create_Face_by_Points_and_Optimize::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

int Create_Face_by_Points_and_Optimize::Show()
{
    try
    {
        theDialog->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        Create_Face_by_Points_and_Optimize::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//---------------------Block UI Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void Create_Face_by_Points_and_Optimize::initialize_cb()
{
    try
    {
        group = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group"));
        group5 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group5"));
        selection0 = dynamic_cast<NXOpen::BlockStyler::SelectObject*>(theDialog->TopBlock()->FindBlock("selection0"));
        group6 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group6"));
        point0 = dynamic_cast<NXOpen::BlockStyler::SpecifyPoint*>(theDialog->TopBlock()->FindBlock("point0"));
        point01 = dynamic_cast<NXOpen::BlockStyler::SpecifyPoint*>(theDialog->TopBlock()->FindBlock("point01"));
        point02 = dynamic_cast<NXOpen::BlockStyler::SpecifyPoint*>(theDialog->TopBlock()->FindBlock("point02"));
        point03 = dynamic_cast<NXOpen::BlockStyler::SpecifyPoint*>(theDialog->TopBlock()->FindBlock("point03"));
        button0 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button0"));
        group4 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group4"));
        group1 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group1"));
        enum0 = dynamic_cast<NXOpen::BlockStyler::Enumeration*>(theDialog->TopBlock()->FindBlock("enum0"));
        enum01 = dynamic_cast<NXOpen::BlockStyler::Enumeration*>(theDialog->TopBlock()->FindBlock("enum01"));
        button01 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button01"));
        group2 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group2"));
        button02 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button02"));
        group3 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group3"));
        button03 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button03"));
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        Create_Face_by_Points_and_Optimize::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void Create_Face_by_Points_and_Optimize::dialogShown_cb()
{
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        Create_Face_by_Points_and_Optimize::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int Create_Face_by_Points_and_Optimize::apply_cb()
{
    int errorCode = 0;
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        errorCode = 1;
        Create_Face_by_Points_and_Optimize::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int Create_Face_by_Points_and_Optimize::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
    try
    {
        if(block == selection0)
        {
        //---------Enter your code here-----------
        }
        else if(block == point0)
        {
        //---------Enter your code here-----------
        }
        else if(block == point01)
        {
        //---------Enter your code here-----------
        }
        else if(block == point02)
        {
        //---------Enter your code here-----------
        }
        else if(block == point03)
        {
        //---------Enter your code here-----------
        }
        else if(block == button0)
        {
        //---------Enter your code here-----------

			pt_coods[0] = { point0->Point().X, point0->Point().Y, point0->Point().Z };
			pPointFeature[0] = CreatePointFeature(pt_coods[0].base_pt);
			pt_coods[1] = { point01->Point().X, point01->Point().Y, point01->Point().Z };
			pPointFeature[1] = CreatePointFeature(pt_coods[1].base_pt);
			pt_coods[2] = { point02->Point().X, point02->Point().Y, point02->Point().Z };
			pPointFeature[2] = CreatePointFeature(pt_coods[2].base_pt);
			pt_coods[3] = { point03->Point().X, point03->Point().Y, point03->Point().Z };
			pPointFeature[3] = CreatePointFeature(pt_coods[3].base_pt);

			vector<TaggedObject*> Obj = selection0->GetSelectedObjects();

			tag_t facetBody = Obj.at(0)->GetTag();
			GetPointsCoord(pt_coods, facetBody);
			for (int i = 4; i < 9; ++i)
				pPointFeature[i] = CreatePointFeature(pt_coods[i].base_pt);

        }
        else if(block == enum0)
        {
        //---------Enter your code here-----------
        }
        else if(block == enum01)
        {
        //---------Enter your code here-----------
        }
        else if(block == button01)
        {
        //---------Enter your code here-----------
        }
        else if(block == button02)
        {
        //---------Enter your code here-----------
        }
        else if(block == button03)
        {
        //---------Enter your code here-----------
        }
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        Create_Face_by_Points_and_Optimize::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int Create_Face_by_Points_and_Optimize::ok_cb()
{
    int errorCode = 0;
    try
    {
        errorCode = apply_cb();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        errorCode = 1;
        Create_Face_by_Points_and_Optimize::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int Create_Face_by_Points_and_Optimize::filter_cb(NXOpen::BlockStyler::UIBlock* block, NXOpen::TaggedObject* selectObject)
{
    return(UF_UI_SEL_ACCEPT);
}

//------------------------------------------------------------------------------
//Function Name: GetBlockProperties
//Description: Returns the propertylist of the specified BlockID
//------------------------------------------------------------------------------
PropertyList* Create_Face_by_Points_and_Optimize::GetBlockProperties(const char *blockID)
{
    return theDialog->GetBlockProperties(blockID);
}
