// NX 8.5.3.3
// Journal created by zhaoz on Thu Mar 10 17:08:41 2016 中国标准时间
//
#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_DatumCsys.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/UnitCollection.hxx>
#include <NXOpen/Xform.hxx>
#include <NXOpen/XformCollection.hxx>
using namespace NXOpen;

extern "C" DllExport int ufusr_ask_unload()
{
    return (int)Session::LibraryUnloadOptionImmediately;
}

extern "C" DllExport void ufusr(char *param, int *retCode, int paramLen)
{
    Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Part *displayPart(theSession->Parts()->Display());
    Unit *unit1(dynamic_cast<Unit *>(workPart->UnitCollection()->FindObject("MilliMeter")));
    Expression *expression1;
    expression1 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);
    
    Features::DatumCsys *datumCsys1(dynamic_cast<Features::DatumCsys *>(workPart->Features()->FindObject("DATUM_CSYS(0)")));
    Point *point1(dynamic_cast<Point *>(datumCsys1->FindObject("HANDLE R-709")));
    Xform *nullXform(NULL);
    Point *point2;
    point2 = workPart->Points()->CreatePoint(point1, nullXform, SmartObject::UpdateOptionWithinModeling);
    
    NXObject *nXObject1;
    Xform *xform1;
    xform1 = workPart->Xforms()->CreateExtractXform(point1, SmartObject::UpdateOptionWithinModeling, false, &nXObject1);
    
    Point *point3(dynamic_cast<Point *>(nXObject1));
    Point *point4;
    point4 = workPart->Points()->CreatePoint(point3, nullXform, SmartObject::UpdateOptionWithinModeling);
    
    Expression *expression2;
    expression2 = workPart->Expressions()->CreateSystemExpressionWithUnits("0", unit1);
    
    // ----------------------------------------------
    //   Menu: Tools->Journal->Stop Recording
    // ----------------------------------------------
}
