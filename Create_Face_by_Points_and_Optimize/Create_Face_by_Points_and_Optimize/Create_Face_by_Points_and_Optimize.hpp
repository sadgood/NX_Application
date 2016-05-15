//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  C:\Users\zhaoz\Documents\GitHubVisualStudio\NX_Application\Create_Face_by_Points_and_Optimize\Create_Face_by_Points_and_Optimize\Create_Face_by_Points_and_Optimize.hpp
//
//        This file was generated by the NX Block Styler
//        Created by: zhaoz
//              Version: NX 8.5
//              Date: 05-05-2016  (Format: mm-dd-yyyy)
//              Time: 16:40
//
//==============================================================================

#ifndef CREATE_FACE_BY_POINTS_AND_OPTIMIZE_H_INCLUDED
#define CREATE_FACE_BY_POINTS_AND_OPTIMIZE_H_INCLUDED

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include <uf_defs.h>
#include <uf_ui_types.h>
#include <iostream>
#include <NXOpen/Session.hxx>
#include <NXOpen/UI.hxx>
#include <NXOpen/NXMessageBox.hxx>
#include <NXOpen/Callback.hxx>
#include <NXOpen/NXException.hxx>
#include <NXOpen/BlockStyler_UIBlock.hxx>
#include <NXOpen/BlockStyler_BlockDialog.hxx>
#include <NXOpen/BlockStyler_PropertyList.hxx>
#include <NXOpen/BlockStyler_TabControl.hxx>
#include <NXOpen/BlockStyler_Group.hxx>
#include <NXOpen/BlockStyler_SelectObject.hxx>
#include <NXOpen/BlockStyler_SpecifyPoint.hxx>
#include <NXOpen/BlockStyler_Button.hxx>
#include <NXOpen/BlockStyler_Enumeration.hxx>

#include <uf.h>
#include "CreatePoint.h"
#include "CreateLine.h"
#include "CreateMesh.h"
#include "CopyInstance.h"
#include "CreateAssociativeLine.h"
#include "OffsetLine.h"
#include "IsoparametricCurves.h"

//------------------------------------------------------------------------------
//Bit Option for Property: SnapPointTypesEnabled
//------------------------------------------------------------------------------
#define              SnapPointTypesEnabled_UserDefined (1 << 0);
#define                 SnapPointTypesEnabled_Inferred (1 << 1);
#define           SnapPointTypesEnabled_ScreenPosition (1 << 2);
#define                 SnapPointTypesEnabled_EndPoint (1 << 3);
#define                 SnapPointTypesEnabled_MidPoint (1 << 4);
#define             SnapPointTypesEnabled_ControlPoint (1 << 5);
#define             SnapPointTypesEnabled_Intersection (1 << 6);
#define                SnapPointTypesEnabled_ArcCenter (1 << 7);
#define            SnapPointTypesEnabled_QuadrantPoint (1 << 8);
#define            SnapPointTypesEnabled_ExistingPoint (1 << 9);
#define             SnapPointTypesEnabled_PointonCurve (1 <<10);
#define           SnapPointTypesEnabled_PointonSurface (1 <<11);
#define         SnapPointTypesEnabled_PointConstructor (1 <<12);
#define     SnapPointTypesEnabled_TwocurveIntersection (1 <<13);
#define             SnapPointTypesEnabled_TangentPoint (1 <<14);
#define                    SnapPointTypesEnabled_Poles (1 <<15);
#define         SnapPointTypesEnabled_BoundedGridPoint (1 <<16);
//------------------------------------------------------------------------------
//Bit Option for Property: SnapPointTypesOnByDefault
//------------------------------------------------------------------------------
#define          SnapPointTypesOnByDefault_UserDefined (1 << 0);
#define             SnapPointTypesOnByDefault_Inferred (1 << 1);
#define       SnapPointTypesOnByDefault_ScreenPosition (1 << 2);
#define             SnapPointTypesOnByDefault_EndPoint (1 << 3);
#define             SnapPointTypesOnByDefault_MidPoint (1 << 4);
#define         SnapPointTypesOnByDefault_ControlPoint (1 << 5);
#define         SnapPointTypesOnByDefault_Intersection (1 << 6);
#define            SnapPointTypesOnByDefault_ArcCenter (1 << 7);
#define        SnapPointTypesOnByDefault_QuadrantPoint (1 << 8);
#define        SnapPointTypesOnByDefault_ExistingPoint (1 << 9);
#define         SnapPointTypesOnByDefault_PointonCurve (1 <<10);
#define       SnapPointTypesOnByDefault_PointonSurface (1 <<11);
#define     SnapPointTypesOnByDefault_PointConstructor (1 <<12);
#define SnapPointTypesOnByDefault_TwocurveIntersection (1 <<13);
#define         SnapPointTypesOnByDefault_TangentPoint (1 <<14);
#define                SnapPointTypesOnByDefault_Poles (1 <<15);
#define     SnapPointTypesOnByDefault_BoundedGridPoint (1 <<16);
//------------------------------------------------------------------------------
// Namespaces needed for following template
//------------------------------------------------------------------------------
using namespace std;
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

class DllExport Create_Face_by_Points_and_Optimize
{
    // class members
public:
    static Session *theSession;
    static UI *theUI;
    Create_Face_by_Points_and_Optimize();
    ~Create_Face_by_Points_and_Optimize();
    int Show();
    
    //----------------------- BlockStyler Callback Prototypes ---------------------
    // The following member function prototypes define the callbacks 
    // specified in your BlockStyler dialog.  The empty implementation
    // of these prototypes is provided in the Create_Face_by_Points_and_Optimize.cpp file. 
    // You are REQUIRED to write the implementation for these functions.
    //------------------------------------------------------------------------------
    void initialize_cb();
    void dialogShown_cb();
    int apply_cb();
    int ok_cb();
    int update_cb(NXOpen::BlockStyler::UIBlock* block);
    int filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject);
    PropertyList* GetBlockProperties(const char *blockID);
    
private:
    const char* theDlxFileName;
    NXOpen::BlockStyler::BlockDialog* theDialog;
    NXOpen::BlockStyler::TabControl* tabControl;// Block type: Tabs Page
    NXOpen::BlockStyler::Group* tabPage;// Block type: Group
    NXOpen::BlockStyler::Group* group;// Block type: Group
    NXOpen::BlockStyler::Group* group5;// Block type: Group
    NXOpen::BlockStyler::SelectObject* selection0;// Block type: Selection
    NXOpen::BlockStyler::Group* group6;// Block type: Group
    NXOpen::BlockStyler::SpecifyPoint* point0;// Block type: Specify Point
    NXOpen::BlockStyler::SpecifyPoint* point01;// Block type: Specify Point
    NXOpen::BlockStyler::Button* button0;// Block type: Button
    NXOpen::BlockStyler::Group* group1;// Block type: Group
    NXOpen::BlockStyler::Enumeration* enum0;// Block type: Enumeration
    NXOpen::BlockStyler::Enumeration* enum01;// Block type: Enumeration
    NXOpen::BlockStyler::Button* button01;// Block type: Button
    NXOpen::BlockStyler::Group* group2;// Block type: Group
    NXOpen::BlockStyler::Button* button02;// Block type: Button
    NXOpen::BlockStyler::Group* group3;// Block type: Group
    NXOpen::BlockStyler::Button* button03;// Block type: Button
    NXOpen::BlockStyler::Group* tabPage1;// Block type: Group
    
private:
	vector<vector<Features::PointFeature*> > pointFeature; //记录生成的点特征（包括手动点上的两个点以及计算出的中点和镜像后的点）
	vector<vector<coord> > pt_coods;//记录生成的点坐标（包括手动点上的两个点以及计算出的中点）
	vector<vector<Features::StudioSpline*> > studioSpline;//记录根据点特征生成的样条曲线
	Features::ThroughCurveMesh* baseMesh;//记录根据样条曲线生成的曲面
	vector<Features::AOCSBuilder*> aoocsbuilder; //U方向生成的偏置曲线
	vector<vector<Features::PointFeature*> > optimizationPointFeature;//根据uv方向设定的点数量，生成优化时使用的点特征
	vector<Features::PointFeature*> UControlPoint;//U方向控制点，控制U方向上等参曲线的位置
	vector<vector<Features::AssociativeLine*> > associativeLine;//根据优化时使用的点特征生成的点-法线直线
	
};
#endif //CREATE_FACE_BY_POINTS_AND_OPTIMIZE_H_INCLUDED
