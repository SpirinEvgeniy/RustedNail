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

void GearRack(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	// очистка сцены
	AIS_ListOfInteractive aList;

	myAISContext->DisplayedObjects(aList);
	AIS_ListIteratorOfListOfInteractive aListIterator;
	for (aListIterator.Initialize(aList); aListIterator.More(); aListIterator.Next()) {
		myAISContext->Remove(aListIterator.Value(), Standard_False);
	}
	// конец очистки

	// создаем эскиз "профиль"
	Standard_Real D = 40.;
	Standard_Real d = 15;
	Standard_Real b = 16;

	TopoDS_Edge E1 = BRepBuilderAPI_MakeEdge(gp_Pnt(b / 2, 0.5 * d, 0.), gp_Pnt(b / 2, 0.5 * D, 0.));
	TopoDS_Edge E2 = BRepBuilderAPI_MakeEdge(gp_Pnt(b / 2, 0.5 * D, 0.), gp_Pnt(-b / 2, 0.5 * D, 0.));
	TopoDS_Edge E3 = BRepBuilderAPI_MakeEdge(gp_Pnt(-b / 2, 0.5 * D, 0.), gp_Pnt(-b / 2, 0.5 * d, 0.));
	TopoDS_Edge E4 = BRepBuilderAPI_MakeEdge(gp_Pnt(-b / 2, 0.5 * d, 0.), gp_Pnt(b / 2, 0.5 * d, 0.));

	TopoDS_Wire W = BRepBuilderAPI_MakeWire(E1, E2, E3, E4);

	gp_Ax1 axe = gp_Ax1(gp_Pnt(0., 0., 0.), gp_Dir(1., 0., 0.));

	Handle(Geom_Axis1Placement) Gax = new Geom_Axis1Placement(axe);
	Handle(AIS_Axis) ax = new AIS_Axis(Gax);
	Handle(AIS_Shape) aisW = new AIS_Shape(W);

	//myAISContext->Display(ax, Standard_False);
	myAISContext->Display(aisW, Standard_False);
	// конец создаем эскиз "профиль"



	// вращаем тело
	TopoDS_Shape S = BRepPrimAPI_MakeRevol(W, axe, 2 * M_PI);
	Handle(AIS_Shape) aisS = new AIS_Shape(S);
	//myAISContext->SetColor(aisS, Quantity_NOC_GREEN, Standard_False);
	//myAISContext->SetMaterial(aisS, Graphic3d_NOM_PLASTIC, Standard_False);
	//myAISContext->Display(aisS, Standard_False);
	// конец вращаем тело

	// фаски
	BRepFilletAPI_MakeChamfer MC(S);

	TopTools_IndexedDataMapOfShapeListOfShape M;
	TopExp::MapShapesAndAncestors(S, TopAbs_EDGE, TopAbs_FACE, M);

	TopoDS_Edge E = TopoDS::Edge(M.FindKey(2));
	TopoDS_Face F = TopoDS::Face(M.FindFromIndex(2).First());
	MC.Add(3, 3, E, F);

	E = TopoDS::Edge(M.FindKey(3));
	F = TopoDS::Face(M.FindFromIndex(3).First());
	MC.Add(3, 3, E, F);


	//for (Standard_Integer i = 1; i <= M.Extent(); i++) {
	//	TopoDS_Edge E = TopoDS::Edge(M.FindKey(i));
	//	TopoDS_Face F = TopoDS::Face(M.FindFromIndex(i).First());
	//	MC.Add(3, 3, E, F);
	//}

	TopoDS_Shape ChanfrenedBox = MC.Shape();
	Handle(AIS_Shape) aBlendedBox = new AIS_Shape(ChanfrenedBox);
	myAISContext->SetColor(aBlendedBox, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(aBlendedBox, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(aBlendedBox, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOBlendedBox = aBlendedBox;
	myAISContext->SetSelected(anIOBlendedBox, Standard_False);

	// конец фаски

	// вырез
	Standard_Real fi = 0;
	Standard_Real dfi = 2 * M_PI / 6;
	Standard_Real x, y, x0, y0;
	x0 = 0.5 * D * cos(0.0);
	y0 = 0.5 * D * sin(0.0);
	BRepBuilderAPI_MakeWire MW;
	TopoDS_Wire DSW;
	for (Standard_Integer i = 0; i <= 6; i++) {
		fi += dfi;
		x = 0.5 * D * cos(fi);
		y = 0.5 * D * sin(fi);
		TopoDS_Edge E = BRepBuilderAPI_MakeEdge(gp_Pnt(0, x0, y0), gp_Pnt(0, x, y));
		MW.Add(E);
		x0 = x;
		y0 = y;
	}
	DSW = MW.Wire();
	Handle(AIS_Shape) aisW2 = new AIS_Shape(DSW);
	myAISContext->Display(aisW2, Standard_False);



	myView->FitAll();
}