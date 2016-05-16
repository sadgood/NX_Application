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
//              Date: 05-05-2016  (Format: mm-dd-yyyy)
//              Time: 16:40 (Format: hh-mm)
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
		UF_CALL(UF_initialize());
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

		vector<Features::PointFeature*> temp;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				temp.push_back(NULL);
			}
			pointFeature.push_back(temp);
			temp.clear();
		}

		vector<coord> temp1;
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				coord temp = { 0.0,0.0,0.0 };
				temp1.push_back(temp);
			}
			pt_coods.push_back(temp1);
			temp1.clear();
		}

		vector<Features::StudioSpline*> temp2;
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				temp2.push_back(NULL);
			}
			studioSpline.push_back(temp2);
			temp2.clear();
		}

		baseMesh = NULL;
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
		UF_CALL(UF_terminate());
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
        tabControl = dynamic_cast<NXOpen::BlockStyler::TabControl*>(theDialog->TopBlock()->FindBlock("tabControl"));
        tabPage = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("tabPage"));
        group = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group"));
        group5 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group5"));
        selection0 = dynamic_cast<NXOpen::BlockStyler::SelectObject*>(theDialog->TopBlock()->FindBlock("selection0"));
        group6 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group6"));
        point0 = dynamic_cast<NXOpen::BlockStyler::SpecifyPoint*>(theDialog->TopBlock()->FindBlock("point0"));
        point01 = dynamic_cast<NXOpen::BlockStyler::SpecifyPoint*>(theDialog->TopBlock()->FindBlock("point01"));
        button0 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button0"));
        group1 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group1"));
        enum0 = dynamic_cast<NXOpen::BlockStyler::Enumeration*>(theDialog->TopBlock()->FindBlock("enum0"));
        enum01 = dynamic_cast<NXOpen::BlockStyler::Enumeration*>(theDialog->TopBlock()->FindBlock("enum01"));
        button01 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button01"));
        group2 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group2"));
        button02 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button02"));
        group3 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group3"));
        button03 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button03"));
        tabPage1 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("tabPage1"));
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
        else if(block == button0)
        {
        //---------Enter your code here-----------
			coord pt_coods_selected[4] = { 0 };
			pt_coods_selected[0].base_pt[0] = point0->Point().X;
			pt_coods_selected[0].base_pt[1] = point0->Point().Y;
			pt_coods_selected[0].base_pt[2] = point0->Point().Z;

			pt_coods_selected[1].base_pt[0] = point01->Point().X;
			pt_coods_selected[1].base_pt[1] = point01->Point().Y;
			pt_coods_selected[1].base_pt[2] = point01->Point().Z;  //选定点的坐标

			pt_coods_selected[2].base_pt[0] = point01->Point().X;
			pt_coods_selected[2].base_pt[1] = -1 * (point01->Point().Y);
			pt_coods_selected[2].base_pt[2] = point01->Point().Z;

			pt_coods_selected[3].base_pt[0] = point0->Point().X;
			pt_coods_selected[3].base_pt[1] = -1 * (point0->Point().Y);
			pt_coods_selected[3].base_pt[2] = point0->Point().Z; //根据选定点关于y轴对称的坐标

			std::vector<NXOpen::TaggedObject*> selectedObjects;
			selectedObjects = selection0->GetSelectedObjects(); 

			tag_t facetBody = NULL_TAG;
			if (!selectedObjects.empty())
			{
				TaggedObject *obj = NULL;
				obj = selectedObjects.at(0);
				facetBody = obj->GetTag();    //获取facetbody的tag值
				GetPointsCoord(pt_coods_selected, facetBody, pt_coods);  //根据选定点和镜像点的坐标计算剩余5点坐标

				for (int i = 0; i < 2; ++i)
					for (int j = 0; j < 3; ++j)
					{
						string temp;
						pointFeature[i][j] = CreatePointFeature(pt_coods[i][j].base_pt, "Point", temp);
					}
				pointFeature[2][0] = (Features::PointFeature*)CopyInstance(pointFeature[0][0]);
				pointFeature[2][1] = (Features::PointFeature*)CopyInstance(pointFeature[0][1]);
				pointFeature[2][2] = (Features::PointFeature*)CopyInstance(pointFeature[0][2]);

				for (int i = 0; i < 3; ++i)
					studioSpline[0][i] = CreateLine(pointFeature[i][0], pointFeature[i][1], pointFeature[i][2]);  //U方向三条线
				for (int i = 0; i < 3; ++i)
					studioSpline[1][i] = CreateLine(pointFeature[0][i], pointFeature[1][i], pointFeature[2][i]);  //V方向三条线

				baseMesh = CreateThroughCurveMesh(studioSpline);  //根据曲线网格生成曲面
				group1->SetEnable(true);
			}
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
			string Direction_U = enum0->ValueAsString().GetText();
			string Direction_V = enum01->ValueAsString().GetText();
			int direction_U = Direction_U[0] - '0';
			int direction_V = Direction_V[0] - '0';   //获取UV方向控制线数量

			vector<Features::AssociativeLine*> temp;
			vector<Features::PointFeature*> temp_point;
			for (int i = 0; i < direction_U; ++i)
			{
				for (int j = 0; j < direction_V; ++j)
				{
					temp.push_back(NULL); 
					temp_point.push_back(NULL);
				}
				optimizationPointFeature.push_back(temp_point);
				associativeLine.push_back(temp);
				temp.clear();
				temp_point.clear();
			}//根据控制线数量初始化UV方向上优化点和即将生成的点-法线直线

			int percent = 100 / (direction_U - 2 + 1);
			for (int i = 0; i < direction_U - 2; ++i)
			{
				UControlPoint.push_back(CreatePointInCurves((Features::Feature*)studioSpline[0][1], percent * (i + 1)));
				IsoParametricCurves.push_back(IsoparametricCurvesOnFace(baseMesh, UControlPoint[i]));
			}
			
			if (direction_V == 3)
			{
				optimizationPointFeature[0][0] = pointFeature[0][0];
				optimizationPointFeature[direction_U - 1][0] = pointFeature[0][2];
				optimizationPointFeature[0][1] = CreatePointInCurves(studioSpline[1][0], 50);
				for (int i = 0; i < direction_U - 2; ++i)
				{
					optimizationPointFeature[i + 1][0] = CreatePointInCurves((Features::Feature*)IsoParametricCurves[i], 0);
					optimizationPointFeature[i + 1][1] = CreatePointInCurves((Features::Feature*)IsoParametricCurves[i], 50);
				}
				optimizationPointFeature[direction_U - 1][1] = CreatePointInCurves(studioSpline[1][2], 50);

				for (int i = 0; i < direction_U; ++i)
				{
					for (int j = 0; j < 2; ++j)
					{
						associativeLine[i][j] = CreateAssociativeLine(optimizationPointFeature[i][j], baseMesh);
					}
				}
				for (int i = 0; i < direction_U; ++i)
				{
					associativeLine[i][2] = (Features::AssociativeLine*)CopyInstance((Features::Feature*)associativeLine[i][0]);
				}
			}
			/*else if(direction_V == 5)
			{
				CreatePointInCurves(studioSpline[1][0], 50);
				for (int i = 0; i < direction_U - 2; ++i)
				{
					CreatePointInCurves((Features::Feature*)aoocsbuilder[i], 50);
				}
				CreatePointInCurves(studioSpline[1][2], 50);
			}*/

			group2->SetEnable(true);
		}
        else if(block == button02)
        {
        //---------Enter your code here-----------
			group3->SetEnable(true);
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
