#pragma once
#include"Framework.h"

#include<AIS_Trihedron.hxx>
#include<Geom_Axis2Placement.hxx>
#include<BRepPrimAPI_MakeWedge.hxx>
#include<AIS_Point.hxx>
#include<Geom_CartesianPoint.hxx>
#include<Geom_Axis1Placement.hxx>
#include<AIS_Axis.hxx>
#include<BRepPrimAPI_MakeBox.hxx>
#include<BRepAlgoAPI_Common.hxx>
#include<Geom_BezierCurve.hxx>
#include<gp_Circ.hxx>
#include<BRepBuilderAPI_GTransform.hxx>
#include<BRepPrimAPI_MakeCone.hxx>
#include<BRepBuilderAPI_MakeVertex.hxx>
#include<BRepPrimAPI_MakePrism.hxx>
#include<BRepOffsetAPI_ThruSections.hxx>
#include<BRepBuilderAPI_MakePolygon.hxx>
#include<BRepOffsetAPI_MakeEvolved.hxx>
#include<BRepOffsetAPI_DraftAngle.hxx>
#include<Geom_Plane.hxx>
#include<TopExp_Explorer.hxx>
#include<TopoDS.hxx>
#include<BRepAlgoAPI_Section.hxx>
#include<TopOpeBRepTool_OutCurveType.hxx>
#include<BRepFilletAPI_MakeFillet.hxx>
#include<BRepFilletAPI_MakeChamfer.hxx>
#include<GCE2d_MakeLine.hxx>
#include<BRepLib.hxx>
#include<BRepFeat_MakePrism.hxx>
#include<BRepFeat_MakeRevol.hxx>
#include<BRepFeat_MakePipe.hxx>
#include<BRepFeat_Gluer.hxx>
#include<LocOpe_FindEdges.hxx>
#include<BRepFeat_SplitShape.hxx>
#include<BRepOffsetAPI_MakeThickSolid.hxx>
#include<gp_Elips.hxx>
#include<AIS_ColoredShape.hxx>
#include<AIS_ConnectedInteractive.hxx>
#include<BRepFeat_MakeLinearForm.hxx>
#include<BRepOffsetAPI_MakePipe.hxx>
#include<AIS_TextLabel.hxx>

// для лекции
#include <math_Vector.hxx> 
#include <math_Matrix.hxx>
#include <math_Gauss.hxx>
#include <GccAna_Circ2d2TanRad.hxx>
#include <GccAna_Lin2d2Tan.hxx>
#include <GccEnt.hxx>
#include <GccEnt_QualifiedCirc.hxx>
#include <GccEnt_QualifiedLin.hxx>
#include <gp_Circ2d.hxx>
#include <gce_MakeCirc2d.hxx>

Handle(AIS_Shape) StepImport(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView, Standard_CString filename, double transp)
{
	STEPControl_Reader reader;
	IFSelect_ReturnStatus stat = reader.ReadFile(filename); 
	IFSelect_PrintCount mode = IFSelect_ListByItem;
	reader.PrintCheckLoad(false, mode);

	Standard_Integer NbRoots = reader.NbRootsForTransfer();
	Standard_Integer num = reader.TransferRoots();
	Standard_Integer NbTrans = reader.TransferRoots();

	TopoDS_Shape result = reader.OneShape();
	TopoDS_Shape shape = reader.Shape();

	Handle(AIS_Shape) StepShape = new AIS_Shape(shape);
	

	//Doc->myAISContext->SetColor(StepShape, Quantity_NOC_RED3, Standard_False);
	myAISContext->SetTransparency(StepShape, transp, Standard_False);
	myAISContext->SetMaterial(StepShape, Graphic3d_NOM_GOLD, Standard_False);
	//Doc->myAISContext->SetMaterial(StepShape, Graphic3d_NOM_GLASS, Standard_False);
	//Doc->myAISContext->Display(StepShape, Standard_False);
	const Handle(Prs3d_Drawer) selectionStyle = new Prs3d_Drawer();

	myAISContext->SelectionStyle()->SetColor(Quantity_NOC_BLUE1);

	//myAISContext->Display(StepShape, 1, -1, Standard_False);
	myView->FitAll();
	return StepShape;

}