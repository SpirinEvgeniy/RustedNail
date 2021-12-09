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
#include<StdSelect_ShapeTypeFilter.hxx>
#include<StdSelect_FaceFilter.hxx>
#include<StdSelect_EdgeFilter.hxx>


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



// вспомогательные построения
void ClearScene(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	// очистка сцены
	AIS_ListOfInteractive aList;

	myAISContext->DisplayedObjects(aList);
	AIS_ListIteratorOfListOfInteractive aListIterator;
	for (aListIterator.Initialize(aList); aListIterator.More(); aListIterator.Next()) {
		myAISContext->Remove(aListIterator.Value(), Standard_False);
	}
	// конец очистки
}

TopoDS_Vertex DisplayVertex(Handle(AIS_InteractiveContext) myAISContext,
	const gp_Pnt& thePoint,
	const char* theText,
	Standard_Boolean theToUpdateViewer,
	Standard_Real theXoffset,
	Standard_Real theYoffset,
	Standard_Real theZoffset)
{
	
	TopoDS_Vertex V1 = BRepBuilderAPI_MakeVertex(thePoint);
	Handle(AIS_Shape) aShape = new AIS_Shape(V1);


	Quantity_Color color(Quantity_NOC_RED);
	Handle_Prs3d_PointAspect myPointAspect = new Prs3d_PointAspect(Aspect_TOM_O, color, 2);
	aShape->Attributes()->SetPointAspect(myPointAspect);
	myAISContext->Display(aShape, theToUpdateViewer);

	Handle(AIS_TextLabel) aLabel = new AIS_TextLabel();
	aLabel->SetText(theText);
	aLabel->SetPosition(gp_Pnt(thePoint.X() + theXoffset, thePoint.Y() + theYoffset, thePoint.Z() + theZoffset));
	
	
	myAISContext->Display(aLabel, theToUpdateViewer);
	return  V1;
}

void DisplayEdgeByVertex(Handle(AIS_InteractiveContext) myAISContext,
	const TopoDS_Vertex& V1, 
	const TopoDS_Vertex& V2,	
	Standard_Boolean theToUpdateViewer,
	const Aspect_TypeOfLine theType,
	Standard_Real width)
{
	

	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(V1, V2);
	

	Handle(AIS_Shape) aShape = new AIS_Shape(E);


	Quantity_Color color(Quantity_NOC_GREEN);	
	Handle(Prs3d_LineAspect) myLineAspect = new Prs3d_LineAspect(color, theType, width);
	aShape->Attributes()->SetWireAspect(myLineAspect);
	myAISContext->Display(aShape, theToUpdateViewer);

}

void DisplayEdgeByCircle(Handle(AIS_InteractiveContext) myAISContext,
	const gp_Circ& L,	
	Standard_Boolean theToUpdateViewer,
	const Aspect_TypeOfLine theType,
	Standard_Real width)
{


	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(L, 0.0, 2*M_PI);

	Handle(AIS_Shape) aShape = new AIS_Shape(E);
	Quantity_Color color(Quantity_NOC_GREEN);
	Handle(Prs3d_LineAspect) myLineAspect = new Prs3d_LineAspect(color, theType, width);
	aShape->Attributes()->SetWireAspect(myLineAspect);
	myAISContext->Display(aShape, theToUpdateViewer);

}

// Примеры ...

void SimpleBody(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);


	Standard_Real sphere_radius = 1.0;
	Standard_Real sphere_angle = atan(0.5);

	gp_Ax2 sphere_origin = gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	TopoDS_Shape sphere = BRepPrimAPI_MakeSphere(sphere_origin, sphere_radius, -sphere_angle, sphere_angle).Shape();
	////
	Standard_Real feature_diameter = 0.8;
	gp_Ax1 feature_origin = gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

	BRepFeat_MakeCylindricalHole feature_maker;
	feature_maker.Init(sphere, feature_origin);
	feature_maker.Perform(feature_diameter / 2.0);
	////
	Standard_Real cylinder_radius = 0.25;
	Standard_Real cylinder_height = 2.0;
	gp_Ax2 cylinder_origin(gp_Pnt(0.0, 0.0, -cylinder_height / 2.0),
		gp_Dir(0.0, 0.0, 1.0));
	BRepPrimAPI_MakeCylinder cylinder(cylinder_origin,
		cylinder_radius,
		cylinder_height);


	gp_Trsf move = gp_Trsf();
	TopoDS_Shape boolean_result = feature_maker.Shape();
	TopoDS_Shape moved_cylinder;
	Standard_Real clone_radius = 1.0;

	for (int clone = 0; clone <= 7; ++clone)
	{
		double angle = clone * M_PI / 4.0;


		move.SetTranslation(gp_Vec(cos(angle) * clone_radius,
			sin(angle) * clone_radius,
			0.0));
		moved_cylinder =
			BRepBuilderAPI_Transform(cylinder.Shape(), move, true).Shape();


		boolean_result =
			BRepAlgoAPI_Cut(boolean_result, moved_cylinder).Shape();
	}

	////
	Standard_Real ring_radius = 0.25;
	Standard_Real torus_radius = 1.0 - ring_radius;
	BRepPrimAPI_MakeTorus torus(torus_radius, ring_radius);
	TopoDS_Shape res = BRepAlgoAPI_Fuse(boolean_result, torus.Shape());

	////
	TColgp_Array1OfPnt FacePoints(1, 7);
	Standard_Real face_inner_radius = 0.6;

	FacePoints(1) = gp_Pnt(face_inner_radius - 0.05, 0.0, -0.05);
	FacePoints(2) = gp_Pnt(face_inner_radius - 0.10, 0.0, -0.025);
	FacePoints(3) = gp_Pnt(face_inner_radius - 0.10, 0.0, 0.025);
	FacePoints(4) = gp_Pnt(face_inner_radius + 0.10, 0.0, 0.025);
	FacePoints(5) = gp_Pnt(face_inner_radius + 0.10, 0.0, -0.025);
	FacePoints(6) = gp_Pnt(face_inner_radius + 0.05, 0.0, -0.05);
	FacePoints(7) = gp_Pnt(face_inner_radius - 0.05, 0.0, -0.05);


	BRepBuilderAPI_MakeWire hexwire;

	for (Standard_Integer i = 1; i < 7; i++)
	{
		BRepBuilderAPI_MakeEdge hexedge(FacePoints(i), FacePoints(i + 1));
		hexwire.Add(hexedge);
	}


	TopoDS_Face hexface = BRepBuilderAPI_MakeFace(hexwire.Wire());


	gp_Ax1 revolve_axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	TopoDS_Shape revolved_shape =
		BRepPrimAPI_MakeRevol(hexface, revolve_axis).Shape();


	gp_Trsf move0 = gp_Trsf();
	move0.SetTranslation(gp_Pnt(0, 0, 0), gp_Pnt(0, 0, sin(0.5)));
	TopoDS_Shape moved_shape =
		BRepBuilderAPI_Transform(revolved_shape, move0, false);


	res = BRepAlgoAPI_Cut(res, moved_shape).Shape();

	
	Handle(AIS_Shape) aSphere = new AIS_Shape(res);
	myAISContext->SetMaterial(aSphere, Graphic3d_NOM_PLASTIC, Standard_True);
	myAISContext->SetColor(aSphere, Quantity_NOC_GREEN, Standard_True);
	myAISContext->Display(aSphere, Standard_True);
	

	//Handle(StdSelect_ShapeTypeFilter) solidFilter = new StdSelect_ShapeTypeFilter(TopAbs_SOLID);
	//Handle(StdSelect_FaceFilter) faceFilter = new StdSelect_FaceFilter(StdSelect_AnyFace);
	//Handle(StdSelect_EdgeFilter) edgeFilter = new StdSelect_EdgeFilter(StdSelect_AnyEdge);
	//myAISContext->AddFilter(solidFilter);
	//myAISContext->AddFilter(faceFilter);
	//myAISContext->AddFilter(edgeFilter);

	myAISContext->Deactivate();
	myAISContext->Activate(aSphere, AIS_Shape::SelectionMode(TopAbs_FACE));
	myAISContext->Activate(aSphere, AIS_Shape::SelectionMode(TopAbs_EDGE));
	myAISContext->Activate(aSphere, AIS_Shape::SelectionMode(TopAbs_VERTEX));

	myView->FitAll();

}

void RotatingRings(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);


	// Задаем параметры
	double m_side = 0.1;       // Длина стороны квадрата кольца
	double m_radius = 1.;      // Радиус внешнего кольца
	double m_time = 0;         // Текущее время
	double m_timeStep = 0.1;   // Шаг по времени
	double m_omega = 1.;       // Угловая скорость

	myView->SetSize(5.);// Размер вида
	int m_pointCount = 0;   // Число положений точки
 //
 // Оси координат
	Handle(AIS_Trihedron) aisTrihedron;
	Handle(Geom_Axis2Placement) axis = new Geom_Axis2Placement(gp::XOY());
	aisTrihedron = new AIS_Trihedron(axis);
	aisTrihedron->SetSize(1.);
	myAISContext->Display(aisTrihedron, Standard_True);

	myView->FitAll();
}

void ExampleOnMirror(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeWedge(60., 100., 80., 20.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	gp_Trsf theTransformation;
	gp_Pnt PntCenterOfTheTransformation(110, 60, 60);
	Handle(AIS_Point) aispnt = new AIS_Point(new Geom_CartesianPoint(PntCenterOfTheTransformation));
	myAISContext->Display(aispnt, Standard_False);
	theTransformation.SetMirror(PntCenterOfTheTransformation);
	BRepBuilderAPI_Transform myBRepTransformation(S, theTransformation);
	TopoDS_Shape S2 = myBRepTransformation.Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_BLUE1, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();

}

void ExampleOnMirroraxis(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeWedge(60., 100., 80., 20.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	gp_Trsf theTransformation;
	gp_Ax1 axe = gp_Ax1(gp_Pnt(110, 60, 60), gp_Dir(0., 1., 0.));
	Handle(Geom_Axis1Placement) Gax1 = new Geom_Axis1Placement(axe);
	Handle(AIS_Axis) ax1 = new AIS_Axis(Gax1);
	myAISContext->Display(ax1, Standard_False);
	theTransformation.SetMirror(axe);
	BRepBuilderAPI_Transform myBRepTransformation(S, theTransformation);
	TopoDS_Shape S2 = myBRepTransformation.Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_BLUE1, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();
}

void ExampleOnCut(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape theBox = BRepPrimAPI_MakeBox(200, 60, 60).Shape();

	Handle(AIS_Shape)	ais1 = new AIS_Shape(theBox);
	myAISContext->SetDisplayMode(ais1, 1, Standard_False);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);

	TopoDS_Shape theSphere = BRepPrimAPI_MakeSphere(gp_Pnt(100, 20, 20), 80).Shape();
	Handle(AIS_Shape)	ais2 = new AIS_Shape(theSphere);
	myAISContext->SetDisplayMode(ais2, 1, Standard_False);
	myAISContext->SetColor(ais2, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO2 = ais2;
	myAISContext->SetSelected(anIO2, Standard_False);

	TopoDS_Shape ShapeCut = BRepAlgoAPI_Cut(theSphere, theBox);

	myAISContext->Erase(ais1, Standard_False);
	myAISContext->Erase(ais2, Standard_False);

	Handle(AIS_Shape)	aSection = new AIS_Shape(ShapeCut);
	myAISContext->SetDisplayMode(aSection, 1, Standard_False);
	myAISContext->SetColor(aSection, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(aSection, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(aSection, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOSection = aSection;
	myAISContext->SetSelected(anIOSection, Standard_False);
	myAISContext->UpdateCurrentViewer();
	myView->FitAll();

}

void ExampleOnCommon(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	gp_Ax2 axe(gp_Pnt(10, 10, 10), gp_Dir(1, 2, 1));
	TopoDS_Shape theBox = BRepPrimAPI_MakeBox(axe, 60, 80, 100).Shape();

	Handle(AIS_Shape) aboxshape = new AIS_Shape(theBox);
	myAISContext->SetColor(aboxshape, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(aboxshape, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetTransparency(aboxshape, 0.2, Standard_False);
	myAISContext->Display(aboxshape, AIS_Shaded, 0, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOBoxShape = aboxshape;
	myAISContext->SetSelected(anIOBoxShape, Standard_False);

	TopoDS_Shape theWedge = BRepPrimAPI_MakeWedge(60., 100., 80., 20.).Shape();

	Handle(AIS_Shape) awedge = new AIS_Shape(theWedge);
	myAISContext->SetColor(awedge, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(awedge, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetTransparency(awedge, 0.0, Standard_False);
	myAISContext->Display(awedge, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOWedge = awedge;
	myAISContext->SetSelected(anIOWedge, Standard_False);
	myAISContext->UpdateCurrentViewer();
	//Sleep(500);

	TopoDS_Shape theCommonSurface = BRepAlgoAPI_Common(theBox, theWedge);

	myAISContext->Erase(aboxshape, false);
	myAISContext->Erase(awedge, false);

	Handle(AIS_Shape) acommon = new AIS_Shape(theCommonSurface);
	myAISContext->SetColor(acommon, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(acommon, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(acommon, AIS_Shaded, 0, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOCommon = acommon;
	myAISContext->SetSelected(anIOCommon, Standard_False);
	myAISContext->UpdateCurrentViewer();
	myView->FitAll();

}

void ExampleOnRotate(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeWedge(60., 100., 80., 20.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	gp_Trsf theTransformation;
	gp_Ax1 axe = gp_Ax1(gp_Pnt(200, 60, 60), gp_Dir(0., 1., 0.));
	Handle(Geom_Axis1Placement) Gax1 = new Geom_Axis1Placement(axe);
	Handle(AIS_Axis) ax1 = new AIS_Axis(Gax1);
	myAISContext->Display(ax1, Standard_False);
	theTransformation.SetRotation(axe, 30 * M_PI / 180);
	BRepBuilderAPI_Transform myBRepTransformation(S, theTransformation);
	TopoDS_Shape S2 = myBRepTransformation.Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_BLUE1, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myAISContext->UpdateCurrentViewer();
	myView->FitAll();


}

void ExampleOnScale(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeWedge(60., 100., 80., 20.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	gp_Trsf theTransformation;
	gp_Pnt theCenterOfScale(200, 60, 60);
	Handle(AIS_Point) aispnt = new AIS_Point(new Geom_CartesianPoint(theCenterOfScale));

	myAISContext->Display(aispnt, Standard_False);
	theTransformation.SetScale(theCenterOfScale, 0.5);
	BRepBuilderAPI_Transform myBRepTransformation(S, theTransformation);
	TopoDS_Shape S2 = myBRepTransformation.Shape();

	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_BLUE1, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myAISContext->UpdateCurrentViewer();
	myView->FitAll();

}

void ExampleOnPipe(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TColgp_Array1OfPnt CurvePoles(1, 4);
	gp_Pnt pt = gp_Pnt(0., 0., 0.);
	CurvePoles(1) = pt;
	pt = gp_Pnt(20., 50., 0.);
	CurvePoles(2) = pt;
	pt = gp_Pnt(60., 100., 0.);
	CurvePoles(3) = pt;
	pt = gp_Pnt(150., 0., 0.);
	CurvePoles(4) = pt;
	Handle(Geom_BezierCurve) curve = new Geom_BezierCurve(CurvePoles);
	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(curve);
	TopoDS_Wire W = BRepBuilderAPI_MakeWire(E);
	Handle(AIS_Shape) ais1 = new AIS_Shape(W);
	myAISContext->Display(ais1, Standard_False);
	//Fit();
//	Sleep(500);
	gp_Circ c = gp_Circ(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 1., 0.)), 10.);
	TopoDS_Edge Ec = BRepBuilderAPI_MakeEdge(c);
	TopoDS_Wire Wc = BRepBuilderAPI_MakeWire(Ec);
	Handle(AIS_Shape) ais3 = new AIS_Shape(Wc);
	myAISContext->Display(ais3, Standard_False);
	TopoDS_Face F = BRepBuilderAPI_MakeFace(gp_Pln(gp::ZOX()), Wc);
	TopoDS_Shape S = BRepOffsetAPI_MakePipe(W, F);
	Handle(AIS_Shape) ais2 = new AIS_Shape(S);
	myAISContext->SetColor(ais2, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myAISContext->UpdateCurrentViewer();
	myView->FitAll();

}

void ExampleOnFuse(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	gp_Pnt P(-5, 5, -5);
	TopoDS_Shape theBox1 = BRepPrimAPI_MakeBox(60, 200, 70).Shape();
	Handle(AIS_Shape)	ais1 = new AIS_Shape(theBox1);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);

	TopoDS_Shape theBox2 = BRepPrimAPI_MakeBox(P, 20, 150, 110).Shape();
	Handle(AIS_Shape)	ais2 = new AIS_Shape(theBox2);
	myAISContext->SetColor(ais2, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO2 = ais2;
	myAISContext->SetSelected(anIO2, Standard_False);

	TopoDS_Shape FusedShape = BRepAlgoAPI_Fuse(theBox1, theBox2);

	myAISContext->Erase(ais1, false);
	myAISContext->Erase(ais2, false);

	Handle(AIS_Shape)	aFusion = new AIS_Shape(FusedShape);
	myAISContext->SetDisplayMode(aFusion, 1, Standard_False);
	myAISContext->SetColor(aFusion, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(aFusion, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(aFusion, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOFusion = aFusion;
	myAISContext->SetSelected(anIOFusion, Standard_False);
	myAISContext->UpdateCurrentViewer();
	myView->FitAll();
}

void ExampleOnDeform(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeWedge(60., 100., 80., 20.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);

	gp_GTrsf theTransformation;
	gp_Mat rot(1, 0, 0, 0, 0.5, 0, 0, 0, 1.5);
	theTransformation.SetVectorialPart(rot);
	theTransformation.SetTranslationPart(gp_XYZ(5, 5, 5));

	BRepBuilderAPI_GTransform myBRepTransformation(S, theTransformation);
	TopoDS_Shape S2 = myBRepTransformation.Shape();

	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_BLUE1, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();
}

void ExampleOnBox(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape B1 = BRepPrimAPI_MakeBox(200., 150., 100.).Shape();
	Handle(AIS_Shape) aBox1 = new AIS_Shape(B1);
	myAISContext->SetMaterial(aBox1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetColor(aBox1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->Display(aBox1, Standard_False);
	TopoDS_Shape B2 = BRepPrimAPI_MakeBox(gp_Ax2(gp_Pnt(-200., -80., -70.),
		gp_Dir(1., 2., 1.)),
		80., 90., 120.).Shape();
	Handle(AIS_Shape) aBox2 = new AIS_Shape(B2);
	myAISContext->SetMaterial(aBox2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetColor(aBox2, Quantity_NOC_RED, Standard_False);
	myAISContext->Display(aBox2, Standard_False);
	myView->FitAll();
}

void ExampleOnCylinder(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape C1 = BRepPrimAPI_MakeCylinder(50., 200.).Shape();
	Handle(AIS_Shape) aCyl1 = new AIS_Shape(C1);
	myAISContext->SetMaterial(aCyl1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetColor(aCyl1, Quantity_NOC_RED, Standard_False);
	myAISContext->Display(aCyl1, Standard_False);
	TopoDS_Shape C2 = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(200., 200., 0.),
		gp_Dir(0., 0., 1.)),
		40., 110., 210. * M_PI / 180).Shape();
	Handle(AIS_Shape) aCyl2 = new AIS_Shape(C2);
	myAISContext->SetMaterial(aCyl2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetColor(aCyl2, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->Display(aCyl2, Standard_False);
	myView->FitAll();
}

void ExampleOnSphere(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape S1 = BRepPrimAPI_MakeSphere(gp_Pnt(-200., -250., 0.), 80.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S1);
	myAISContext->SetColor(ais1, Quantity_NOC_AZURE, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	TopoDS_Shape S2 = BRepPrimAPI_MakeSphere(100., 120. * M_PI / 180).Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	TopoDS_Shape S3 = BRepPrimAPI_MakeSphere(gp_Pnt(200., 250., 0.), 100.,
		-60. * M_PI / 180, 60. * M_PI / 180).Shape();
	Handle(AIS_Shape) ais3 = new AIS_Shape(S3);
	myAISContext->SetColor(ais3, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(ais3, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais3, Standard_False);
	TopoDS_Shape S4 = BRepPrimAPI_MakeSphere(gp_Pnt(0., 0., -300.), 150.,
		-45. * M_PI / 180, 45. * M_PI / 180, 45. * M_PI / 180).Shape();
	Handle(AIS_Shape) ais4 = new AIS_Shape(S4);
	myAISContext->SetColor(ais4, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais4, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais4, Standard_False);
	myView->FitAll();
}

void ExampleOnDisplacement(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeWedge(60., 100., 80., 20.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	gp_Trsf theTransformation;

	gp_Ax3 ax3_1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	gp_Ax3 ax3_2(gp_Pnt(60, 60, 60), gp_Dir(1, 1, 1));

	theTransformation.SetDisplacement(ax3_1, ax3_2);
	BRepBuilderAPI_Transform myBRepTransformation(S, theTransformation);
	TopoDS_Shape TransformedShape = myBRepTransformation.Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(TransformedShape);
	myAISContext->SetColor(ais2, Quantity_NOC_BLUE1, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();

}

void ExampleOnCone(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape C1 = BRepPrimAPI_MakeCone(50., 25., 200.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(C1);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetColor(ais1, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	TopoDS_Shape C2 = BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(100., 100., 0.),
		gp_Dir(0., 0., 1.)),
		60., 0., 150., 210. * M_PI / 180).Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(C2);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetColor(ais2, Quantity_NOC_GREEN, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();
}

void ExampleOnTorus(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape S1 = BRepPrimAPI_MakeTorus(60., 20.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S1);
	myAISContext->SetColor(ais1, Quantity_NOC_AZURE, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	TopoDS_Shape S2 = BRepPrimAPI_MakeTorus(gp_Ax2(gp_Pnt(100., 100., 0.), gp_Dir(1., 1., 1.)),
		50., 20., 210. * M_PI / 180).Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	TopoDS_Shape S3 = BRepPrimAPI_MakeTorus(gp_Ax2(gp_Pnt(-200., -150., -100), gp_Dir(0., 1., 0.)),
		60., 20., -45. * M_PI / 180, 45. * M_PI / 180, 90. * M_PI / 180).Shape();
	Handle(AIS_Shape) ais3 = new AIS_Shape(S3);
	myAISContext->SetColor(ais3, Quantity_NOC_CORAL, Standard_False);
	myAISContext->SetMaterial(ais3, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais3, Standard_False);
	myView->FitAll();
}

void ExampleOnWedge(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape S1 = BRepPrimAPI_MakeWedge(60., 100., 80., 20.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S1);
	myAISContext->SetColor(ais1, Quantity_NOC_AZURE, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	TopoDS_Shape S2 = BRepPrimAPI_MakeWedge(gp_Ax2(gp_Pnt(100., 100., 0.), gp_Dir(0., 0., 1.)),
		60., 50., 80., 25., -10., 40., 70.).Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_CORAL2, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();
}

void ExampleOnPrism(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Vertex V1 = BRepBuilderAPI_MakeVertex(gp_Pnt(-200., -200., 0.));
	Handle(AIS_Shape) ais1 = new AIS_Shape(V1);
	myAISContext->Display(ais1, Standard_False);
	TopoDS_Shape S1 = BRepPrimAPI_MakePrism(V1, gp_Vec(0., 0., 100.));
	Handle(AIS_Shape) ais2 = new AIS_Shape(S1);
	myAISContext->Display(ais2, Standard_False);

	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(gp_Pnt(-150., -150, 0.), gp_Pnt(-50., -50, 0.));
	Handle(AIS_Shape) ais3 = new AIS_Shape(E);
	myAISContext->Display(ais3, Standard_False);
	TopoDS_Shape S2 = BRepPrimAPI_MakePrism(E, gp_Vec(0., 0., 100.));
	Handle(AIS_Shape) ais4 = new AIS_Shape(S2);
	myAISContext->SetColor(ais4, Quantity_NOC_CORAL2, Standard_False);
	myAISContext->SetMaterial(ais4, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais4, Standard_False);

	TopoDS_Edge E1 = BRepBuilderAPI_MakeEdge(gp_Pnt(0., 0., 0.), gp_Pnt(50., 0., 0.));
	TopoDS_Edge E2 = BRepBuilderAPI_MakeEdge(gp_Pnt(50., 0., 0.), gp_Pnt(50., 50., 0.));
	TopoDS_Edge E3 = BRepBuilderAPI_MakeEdge(gp_Pnt(50., 50., 0.), gp_Pnt(0., 0., 0.));
	TopoDS_Wire W = BRepBuilderAPI_MakeWire(E1, E2, E3);
	TopoDS_Shape S3 = BRepPrimAPI_MakePrism(W, gp_Vec(0., 0., 100.));
	Handle(AIS_Shape) ais5 = new AIS_Shape(W);
	myAISContext->Display(ais5, Standard_False);
	Handle(AIS_Shape) ais6 = new AIS_Shape(S3);
	myAISContext->SetColor(ais6, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais6, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais6, Standard_False);

	gp_Circ c = gp_Circ(gp_Ax2(gp_Pnt(200., 200., 0.), gp_Dir(0., 0., 1.)), 80.);
	TopoDS_Edge Ec = BRepBuilderAPI_MakeEdge(c);
	TopoDS_Wire Wc = BRepBuilderAPI_MakeWire(Ec);
	TopoDS_Face F = BRepBuilderAPI_MakeFace(gp_Pln(gp::XOY()), Wc);
	Handle(AIS_Shape) ais7 = new AIS_Shape(F);
	myAISContext->Display(ais7, Standard_False);
	TopoDS_Shape S4 = BRepPrimAPI_MakePrism(F, gp_Vec(0., 0., 100.));
	Handle(AIS_Shape) ais8 = new AIS_Shape(S4);
	myAISContext->SetColor(ais8, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais8, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais8, Standard_False);
	myView->FitAll();
}

void ExampleOnRevol(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Vertex V1 = BRepBuilderAPI_MakeVertex(gp_Pnt(-200., -200., 0.));
	Handle(AIS_Shape) ais1 = new AIS_Shape(V1);
	myAISContext->Display(ais1, Standard_False);
	gp_Ax1 axe = gp_Ax1(gp_Pnt(-170., -170., 0.), gp_Dir(0., 0., 1.));
	Handle(Geom_Axis1Placement) Gax1 = new Geom_Axis1Placement(axe);
	Handle(AIS_Axis) ax1 = new AIS_Axis(Gax1);
	myAISContext->Display(ax1, Standard_False);
	TopoDS_Shape S1 = BRepPrimAPI_MakeRevol(V1, axe);
	Handle(AIS_Shape) ais2 = new AIS_Shape(S1);
	myAISContext->Display(ais2, Standard_False);

	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(gp_Pnt(-120., -120, 0.), gp_Pnt(-120., -120, 100.));
	Handle(AIS_Shape) ais3 = new AIS_Shape(E);
	myAISContext->Display(ais3, Standard_False);
	axe = gp_Ax1(gp_Pnt(-100., -100., 0.), gp_Dir(0., 0., 1.));
	Handle(Geom_Axis1Placement) Gax2 = new Geom_Axis1Placement(axe);
	Handle(AIS_Axis) ax2 = new AIS_Axis(Gax2);
	myAISContext->Display(ax2, Standard_False);
	TopoDS_Shape S2 = BRepPrimAPI_MakeRevol(E, axe);
	Handle(AIS_Shape) ais4 = new AIS_Shape(S2);
	myAISContext->SetColor(ais4, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(ais4, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais4, Standard_False);

	TopoDS_Edge E1 = BRepBuilderAPI_MakeEdge(gp_Pnt(0., 0., 0.), gp_Pnt(50., 0., 0.));
	TopoDS_Edge E2 = BRepBuilderAPI_MakeEdge(gp_Pnt(50., 0., 0.), gp_Pnt(50., 50., 0.));
	TopoDS_Edge E3 = BRepBuilderAPI_MakeEdge(gp_Pnt(50., 50., 0.), gp_Pnt(0., 0., 0.));
	TopoDS_Wire W = BRepBuilderAPI_MakeWire(E1, E2, E3);
	axe = gp_Ax1(gp_Pnt(0., 0., 30.), gp_Dir(0., 1., 0.));
	Handle(Geom_Axis1Placement) Gax3 = new Geom_Axis1Placement(axe);
	Handle(AIS_Axis) ax3 = new AIS_Axis(Gax3);
	myAISContext->Display(ax3, Standard_False);
	TopoDS_Shape S3 = BRepPrimAPI_MakeRevol(W, axe, 210. * M_PI / 180);
	Handle(AIS_Shape) ais5 = new AIS_Shape(W);
	myAISContext->Display(ais5, Standard_False);
	Handle(AIS_Shape) ais6 = new AIS_Shape(S3);
	myAISContext->SetColor(ais6, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais6, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais6, Standard_False);

	gp_Circ c = gp_Circ(gp_Ax2(gp_Pnt(200., 200., 0.), gp_Dir(0., 0., 1.)), 80.);
	TopoDS_Edge Ec = BRepBuilderAPI_MakeEdge(c);
	TopoDS_Wire Wc = BRepBuilderAPI_MakeWire(Ec);
	TopoDS_Face F = BRepBuilderAPI_MakeFace(gp_Pln(gp::XOY()), Wc);
	axe = gp_Ax1(gp_Pnt(290, 290., 0.), gp_Dir(0., 1, 0.));
	Handle(Geom_Axis1Placement) Gax4 = new Geom_Axis1Placement(axe);
	Handle(AIS_Axis) ax4 = new AIS_Axis(Gax4);
	myAISContext->Display(ax4, Standard_False);
	TopoDS_Shape S4 = BRepPrimAPI_MakeRevol(F, axe, 90. * M_PI / 180);
	Handle(AIS_Shape) ais8 = new AIS_Shape(S4);
	myAISContext->SetColor(ais8, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais8, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais8, Standard_False);
	myView->FitAll();
}

void ExampleOnThru(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	gp_Circ c1 = gp_Circ(gp_Ax2(gp_Pnt(-100., 0., -100.), gp_Dir(0., 0., 1.)), 40.);
	TopoDS_Edge E1 = BRepBuilderAPI_MakeEdge(c1);
	TopoDS_Wire W1 = BRepBuilderAPI_MakeWire(E1);
	Handle(AIS_Shape) sec1 = new AIS_Shape(W1);
	myAISContext->Display(sec1, Standard_False);
	gp_Circ c2 = gp_Circ(gp_Ax2(gp_Pnt(-10., 0., -0.), gp_Dir(0., 0., 1.)), 40.);
	TopoDS_Edge E2 = BRepBuilderAPI_MakeEdge(c2);
	TopoDS_Wire W2 = BRepBuilderAPI_MakeWire(E2);
	Handle(AIS_Shape) sec2 = new AIS_Shape(W2);
	myAISContext->Display(sec2, Standard_False);
	gp_Circ c3 = gp_Circ(gp_Ax2(gp_Pnt(-75., 0., 100.), gp_Dir(0., 0., 1.)), 40.);
	TopoDS_Edge E3 = BRepBuilderAPI_MakeEdge(c3);
	TopoDS_Wire W3 = BRepBuilderAPI_MakeWire(E3);
	Handle(AIS_Shape) sec3 = new AIS_Shape(W3);
	myAISContext->Display(sec3, Standard_False);
	gp_Circ c4 = gp_Circ(gp_Ax2(gp_Pnt(0., 0., 200.), gp_Dir(0., 0., 1.)), 40.);
	TopoDS_Edge E4 = BRepBuilderAPI_MakeEdge(c4);
	TopoDS_Wire W4 = BRepBuilderAPI_MakeWire(E4);
	Handle(AIS_Shape) sec4 = new AIS_Shape(W4);
	myAISContext->Display(sec4, Standard_False);
	BRepOffsetAPI_ThruSections generator(Standard_False, Standard_True);
	generator.AddWire(W1);
	generator.AddWire(W2);
	generator.AddWire(W3);
	generator.AddWire(W4);
	generator.Build();
	TopoDS_Shape S1 = generator.Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S1);
	myAISContext->SetColor(ais1, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);

	gp_Circ c1b = gp_Circ(gp_Ax2(gp_Pnt(100., 0., -100.), gp_Dir(0., 0., 1.)), 40.);
	TopoDS_Edge E1b = BRepBuilderAPI_MakeEdge(c1b);
	TopoDS_Wire W1b = BRepBuilderAPI_MakeWire(E1b);
	Handle(AIS_Shape) sec1b = new AIS_Shape(W1b);
	myAISContext->Display(sec1b, Standard_False);
	gp_Circ c2b = gp_Circ(gp_Ax2(gp_Pnt(210., 0., -0.), gp_Dir(0., 0., 1.)), 40.);
	TopoDS_Edge E2b = BRepBuilderAPI_MakeEdge(c2b);
	TopoDS_Wire W2b = BRepBuilderAPI_MakeWire(E2b);
	Handle(AIS_Shape) sec2b = new AIS_Shape(W2b);
	myAISContext->Display(sec2b, Standard_False);
	gp_Circ c3b = gp_Circ(gp_Ax2(gp_Pnt(275., 0., 100.), gp_Dir(0., 0., 1.)), 40.);
	TopoDS_Edge E3b = BRepBuilderAPI_MakeEdge(c3b);
	TopoDS_Wire W3b = BRepBuilderAPI_MakeWire(E3b);
	Handle(AIS_Shape) sec3b = new AIS_Shape(W3b);
	myAISContext->Display(sec3b, Standard_False);
	gp_Circ c4b = gp_Circ(gp_Ax2(gp_Pnt(200., 0., 200.), gp_Dir(0., 0., 1.)), 40.);
	TopoDS_Edge E4b = BRepBuilderAPI_MakeEdge(c4b);
	TopoDS_Wire W4b = BRepBuilderAPI_MakeWire(E4b);
	Handle(AIS_Shape) sec4b = new AIS_Shape(W4b);
	myAISContext->Display(sec4b, Standard_False);
	BRepOffsetAPI_ThruSections generatorb(Standard_True, Standard_False);
	generatorb.AddWire(W1b);
	generatorb.AddWire(W2b);
	generatorb.AddWire(W3b);
	generatorb.AddWire(W4b);
	generatorb.Build();
	TopoDS_Shape S2 = generatorb.Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	myAISContext->SetColor(ais2, Quantity_NOC_ALICEBLUE, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();
}

void ExampleOnEvolved(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	BRepBuilderAPI_MakePolygon P;
	P.Add(gp_Pnt(0., 0., 0.));
	P.Add(gp_Pnt(200., 0., 0.));
	P.Add(gp_Pnt(200., 200., 0.));
	P.Add(gp_Pnt(0., 200., 0.));
	P.Add(gp_Pnt(0., 0., 0.));
	TopoDS_Wire W = P.Wire();

	Handle(AIS_Shape) ais1 = new AIS_Shape(W);
	myAISContext->Display(ais1, Standard_False);

	TopoDS_Wire wprof = BRepBuilderAPI_MakePolygon(gp_Pnt(0., 0., 0.), gp_Pnt(-60., -60., -200.));

	Handle(AIS_Shape) ais3 = new AIS_Shape(wprof);
	myAISContext->Display(ais3, Standard_False);
	//Fit();
	Sleep(500);
	TopoDS_Shape S = BRepOffsetAPI_MakeEvolved(W, wprof, GeomAbs_Arc, Standard_True, Standard_False, Standard_True, 0.0001);

	Handle(AIS_Shape) ais2 = new AIS_Shape(S);
	myAISContext->SetColor(ais2, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();
}

void ExampleOnDraft(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape S = BRepPrimAPI_MakeBox(200., 300., 150.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);

	BRepOffsetAPI_DraftAngle adraft(S);
	TopExp_Explorer Ex;
	for (Ex.Init(S, TopAbs_FACE); Ex.More(); Ex.Next()) {
		TopoDS_Face F = TopoDS::Face(Ex.Current());
		Handle(Geom_Plane) surf = Handle(Geom_Plane)::DownCast(BRep_Tool::Surface(F));
		gp_Pln apln = surf->Pln();
		gp_Dir dirF = apln.Axis().Direction();
		if (dirF.IsNormal(gp_Dir(0., 0., 1.), Precision::Angular()))
			adraft.Add(F, gp_Dir(0., 0., 1.), 15. * M_PI / 180, gp_Pln(gp::XOY()));
	}
	ais1->Set(adraft.Shape());
	myAISContext->Redisplay(ais1, Standard_False);
	myView->FitAll();
}

void ExampleOnSection(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{

	ClearScene(myAISContext, myView);

	TopoDS_Shape atorus = BRepPrimAPI_MakeTorus(120, 20).Shape();

	Handle(AIS_Shape) ashape = new AIS_Shape(atorus);
	myAISContext->SetColor(ashape, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(ashape, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetDisplayMode(ashape, 1, Standard_False);
	myAISContext->SetTransparency(ashape, 0.1, Standard_False);
	myAISContext->Display(ashape, Standard_False);

	gp_Vec V1(1, 1, 1);
	Standard_Real radius = 120;
	Standard_Integer i = -3;

	for (i; i <= 3; i++) {
		TopoDS_Shape asphere = BRepPrimAPI_MakeSphere(gp_Pnt(26 * 3 * i, 0, 0), radius).Shape();

		Handle(AIS_Shape) theShape = new AIS_Shape(asphere);
		myAISContext->SetTransparency(theShape, 0.1, Standard_False);
		myAISContext->SetColor(theShape, Quantity_NOC_WHITE, Standard_False);
		myAISContext->SetDisplayMode(theShape, 1, Standard_False);
		myAISContext->Display(theShape, Standard_False);
		//Fit();

		Standard_Boolean PerformNow = Standard_False;

		BRepAlgoAPI_Section section(atorus, asphere, PerformNow);
		section.ComputePCurveOn1(Standard_True);
		section.Approximation(TopOpeBRepTool_APPROX);
		section.Build();

		Handle(AIS_Shape) asection = new AIS_Shape(section.Shape());
		myAISContext->SetDisplayMode(asection, 0, Standard_False);
		myAISContext->SetColor(asection, Quantity_NOC_WHITE, Standard_False);
		myAISContext->Display(asection, Standard_False);
		if (i < 3) {
			myAISContext->Remove(theShape, Standard_False);
		}
	}
	myAISContext->UpdateCurrentViewer();
	myView->FitAll();
}

void ExampleOnBlend(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape Box = BRepPrimAPI_MakeBox(gp_Pnt(-400, 0, 0), 200, 230, 180).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(Box);
	myAISContext->SetColor(ais1, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);


	BRepFilletAPI_MakeFillet fillet(Box);

	for (TopExp_Explorer ex(Box, TopAbs_EDGE); ex.More(); ex.Next()) {
		TopoDS_Edge Edge = TopoDS::Edge(ex.Current());
		fillet.Add(20, Edge);
	}

	myAISContext->Remove(ais1, Standard_False);

	TopoDS_Shape blendedBox = fillet.Shape();
	Handle(AIS_Shape) aBlendbox = new AIS_Shape(blendedBox);
	myAISContext->SetColor(aBlendbox, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(aBlendbox, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(aBlendbox, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOBlendBox = aBlendbox;
	myAISContext->SetSelected(anIOBlendBox, Standard_False);



	gp_Pnt P1(250, 150, 75);
	TopoDS_Shape S1 = BRepPrimAPI_MakeBox(300, 200, 200).Shape();
	TopoDS_Shape S2 = BRepPrimAPI_MakeBox(P1, 120, 180, 70).Shape();

	TopoDS_Shape fusedShape = BRepAlgoAPI_Fuse(S1, S2);
	Handle(AIS_Shape) ais2 = new AIS_Shape(fusedShape);
	myAISContext->SetColor(ais2, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO2 = ais2;
	myAISContext->SetSelected(anIO2, Standard_False);


	BRepFilletAPI_MakeFillet fill(fusedShape);

	for (TopExp_Explorer ex1(fusedShape, TopAbs_EDGE); ex1.More(); ex1.Next()) {
		TopoDS_Edge E = TopoDS::Edge(ex1.Current());
		fill.Add(E);
	}

	for (Standard_Integer i = 1; i <= fill.NbContours(); i++) {
		Standard_Real longueur(fill.Length(i));
		Standard_Real Rad(0.15 * longueur);
		fill.SetRadius(Rad, i, 1);
	}

	TopoDS_Shape blendedFusedSolids = fill.Shape();

	Handle(AIS_Shape) aBlend = new AIS_Shape(blendedFusedSolids);
	myAISContext->SetColor(aBlend, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(aBlend, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(aBlend, Standard_False);

	myAISContext->Remove(ais2, Standard_False);
	myView->FitAll();
}

void ExampleOnEvolvedblend(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{

	ClearScene(myAISContext, myView);

	TopoDS_Shape theBox = BRepPrimAPI_MakeBox(200, 200, 200).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(theBox);
	myAISContext->SetColor(ais1, Quantity_NOC_BROWN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);


	BRepFilletAPI_MakeFillet Rake(theBox);

	TopExp_Explorer ex(theBox, TopAbs_EDGE);
	ex.Next();
	ex.Next();
	ex.Next();
	ex.Next();
	Rake.Add(8, 50, TopoDS::Edge(ex.Current()));
	Rake.Build();
	if (Rake.IsDone()) {
		TopoDS_Shape evolvedBox = Rake.Shape();
		ais1->Set(evolvedBox);
		myAISContext->Redisplay(ais1, Standard_False);
		myAISContext->SetSelected(anIO1, Standard_False);

	}

	TopoDS_Shape theCylinder = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-300, 0, 0), gp::DZ()), 100, 200).Shape();
	Handle(AIS_Shape) ais3 = new AIS_Shape(theCylinder);
	myAISContext->SetColor(ais3, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais3, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais3, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO3 = ais3;
	myAISContext->SetSelected(anIO3, Standard_False);


	BRepFilletAPI_MakeFillet fillet(theCylinder);

	TColgp_Array1OfPnt2d TabPoint2(1, 20);

	for (Standard_Integer i = 0; i <= 19; i++) {
		gp_Pnt2d Point2d(i * 2 * M_PI / 19, 60 * cos(i * M_PI / 19 - M_PI / 2) + 10);
		TabPoint2.SetValue(i + 1, Point2d);
	}

	TopExp_Explorer exp2(theCylinder, TopAbs_EDGE);
	fillet.Add(TabPoint2, TopoDS::Edge(exp2.Current()));
	fillet.Build();
	if (fillet.IsDone()) {
		TopoDS_Shape LawEvolvedCylinder = fillet.Shape();
		ais3->Set(LawEvolvedCylinder);
		myAISContext->Redisplay(ais3, Standard_False);
		myAISContext->SetSelected(anIO3, Standard_False);

	}

	gp_Pnt P(350, 0, 0);
	TopoDS_Shape theBox2 = BRepPrimAPI_MakeBox(P, 200, 200, 200).Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(theBox2);
	myAISContext->SetColor(ais2, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO2 = ais2;
	myAISContext->SetSelected(anIO2, Standard_False);


	BRepFilletAPI_MakeFillet afillet(theBox2);

	TColgp_Array1OfPnt2d TabPoint(1, 6);

	gp_Pnt2d P1(0., 8.);
	gp_Pnt2d P2(0.2, 16.);
	gp_Pnt2d P3(0.4, 25.);
	gp_Pnt2d P4(0.6, 55.);
	gp_Pnt2d P5(0.8, 28.);
	gp_Pnt2d P6(1., 20.);
	TabPoint.SetValue(1, P1);
	TabPoint.SetValue(2, P2);
	TabPoint.SetValue(3, P3);
	TabPoint.SetValue(4, P4);
	TabPoint.SetValue(5, P5);
	TabPoint.SetValue(6, P6);

	TopExp_Explorer exp(theBox2, TopAbs_EDGE);
	exp.Next();
	exp.Next();
	exp.Next();
	exp.Next();

	afillet.Add(TabPoint, TopoDS::Edge(exp.Current()));

	afillet.Build();
	if (afillet.IsDone()) {
		TopoDS_Shape LawevolvedBox = afillet.Shape();
		ais2->Set(LawevolvedBox);
		myAISContext->Redisplay(ais2, Standard_False);
		myAISContext->SetSelected(anIO2, Standard_False);

	}
	myView->FitAll();
}

void ExampleOnChamf(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape theBox = BRepPrimAPI_MakeBox(60, 200, 70).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(theBox);
	myAISContext->SetColor(ais1, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);


	BRepFilletAPI_MakeChamfer MC(theBox);
	// add all the edges to chamfer
	TopTools_IndexedDataMapOfShapeListOfShape M;
	TopExp::MapShapesAndAncestors(theBox, TopAbs_EDGE, TopAbs_FACE, M);
	for (Standard_Integer i = 1; i <= M.Extent(); i++) {
		TopoDS_Edge E = TopoDS::Edge(M.FindKey(i));
		TopoDS_Face F = TopoDS::Face(M.FindFromIndex(i).First());
		MC.Add(5, 5, E, F);
	}

	TopoDS_Shape ChanfrenedBox = MC.Shape();
	Handle(AIS_Shape) aBlendedBox = new AIS_Shape(ChanfrenedBox);
	myAISContext->SetColor(aBlendedBox, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(aBlendedBox, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(aBlendedBox, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOBlendedBox = aBlendedBox;
	myAISContext->SetSelected(anIOBlendedBox, Standard_False);

	myAISContext->Erase(ais1, Standard_True);
	myView->FitAll();
}

void ExampleOnPrismLocal(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeBox(400., 250., 300.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);

	myAISContext->SetColor(ais1, Quantity_NOC_GREEN, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);


	TopExp_Explorer Ex;
	Ex.Init(S, TopAbs_FACE);
	Ex.Next();
	TopoDS_Face F = TopoDS::Face(Ex.Current());
	Handle(Geom_Surface) surf = BRep_Tool::Surface(F);
	Handle(Geom_Plane) Pl = Handle(Geom_Plane)::DownCast(surf);
	gp_Dir D = Pl->Pln().Axis().Direction();
	// new in 2.0 ..use the trigonometric orientation to make the extrusion.
	D.Reverse();
	gp_Pnt2d p1, p2;
	Handle(Geom2d_Curve) aline;
	BRepBuilderAPI_MakeWire MW;
	p1 = gp_Pnt2d(200., -100.);
	p2 = gp_Pnt2d(100., -100.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(100., -200.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(200., -200.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(200., -100.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	BRepBuilderAPI_MakeFace MKF;
	MKF.Init(surf, Standard_False, Precision::Confusion());
	MKF.Add(MW.Wire());
	TopoDS_Shape FP = MKF.Face();
	BRepLib::BuildCurves3d(FP);
	BRepFeat_MakePrism MKP(S, FP, F, D, 0, Standard_True);
	MKP.Perform(200.);
	TopoDS_Shape res1 = MKP.Shape();
	ais1->Set(res1);

	myAISContext->Redisplay(ais1, Standard_False);
	myAISContext->SetSelected(anIO1, Standard_False);


	Ex.Next();
	TopoDS_Face F2 = TopoDS::Face(Ex.Current());
	surf = BRep_Tool::Surface(F2);
	Pl = Handle(Geom_Plane)::DownCast(surf);
	D = Pl->Pln().Axis().Direction();
	D.Reverse();
	BRepBuilderAPI_MakeWire MW2;
	p1 = gp_Pnt2d(100., 100.);
	p2 = gp_Pnt2d(200., 100.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW2.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(150., 200.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW2.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(100., 100.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW2.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	BRepBuilderAPI_MakeFace MKF2;
	MKF2.Init(surf, Standard_False, Precision::Confusion());
	MKF2.Add(MW2.Wire());
	FP = MKF2.Face();
	BRepLib::BuildCurves3d(FP);
	BRepFeat_MakePrism MKP2(res1, FP, F2, D, 1, Standard_True);
	MKP2.Perform(100.);
	TopoDS_Shape res2 = MKP2.Shape();
	ais1->Set(res2);

	myAISContext->Redisplay(ais1, Standard_False);
	myAISContext->SetSelected(anIO1, Standard_False);

	myView->FitAll();

}

void ExampleOnRevolLocal(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeBox(400., 250., 300.).Shape();

	Handle(AIS_Shape) ais1 = new AIS_Shape(S);

	myAISContext->SetColor(ais1, Quantity_NOC_CORAL, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);
	//Fit();
	Sleep(500);

	TopExp_Explorer Ex;
	Ex.Init(S, TopAbs_FACE);
	Ex.Next();
	Ex.Next();
	TopoDS_Face F1 = TopoDS::Face(Ex.Current());
	Handle(Geom_Surface) surf = BRep_Tool::Surface(F1);
	Handle(Geom_Plane) Pl = Handle(Geom_Plane)::DownCast(surf);
	gp_Ax1 D = gp::OX();
	BRepBuilderAPI_MakeWire MW1;
	gp_Pnt2d p1, p2;
	p1 = gp_Pnt2d(100., 100.);
	p2 = gp_Pnt2d(200., 100.);
	Handle(Geom2d_Line) aline = GCE2d_MakeLine(p1, p2).Value();
	MW1.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(150., 200.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW1.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(100., 100.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW1.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	BRepBuilderAPI_MakeFace MKF1;
	MKF1.Init(surf, Standard_False, Precision::Confusion());
	MKF1.Add(MW1.Wire());
	TopoDS_Face FP = MKF1.Face();
	BRepLib::BuildCurves3d(FP);
	BRepFeat_MakeRevol MKrev(S, FP, F1, D, 1, Standard_True);
	Ex.Next();
	Ex.Next();
	TopoDS_Face F2 = TopoDS::Face(Ex.Current());
	MKrev.Perform(F2);
	TopoDS_Shape res1 = MKrev.Shape();


	myAISContext->Remove(ais1, Standard_False);
	Handle(AIS_Shape) ais2 = new AIS_Shape(res1);
	myAISContext->Display(ais2, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO2 = ais2;
	myAISContext->SetSelected(anIO2, Standard_False);
	myView->FitAll();
}

void ExampleOnPipeLocal(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S = BRepPrimAPI_MakeBox(400., 250., 300.).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);

	myAISContext->SetColor(ais1, Quantity_NOC_CORAL, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);


	TopExp_Explorer Ex;
	Ex.Init(S, TopAbs_FACE);
	Ex.Next();
	Ex.Next();
	TopoDS_Face F1 = TopoDS::Face(Ex.Current());
	Handle(Geom_Surface) surf = BRep_Tool::Surface(F1);
	BRepBuilderAPI_MakeWire MW1;
	gp_Pnt2d p1, p2;
	p1 = gp_Pnt2d(100., 100.);
	p2 = gp_Pnt2d(200., 100.);
	Handle(Geom2d_Line) aline = GCE2d_MakeLine(p1, p2).Value();
	MW1.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(150., 200.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW1.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	p1 = p2;
	p2 = gp_Pnt2d(100., 100.);
	aline = GCE2d_MakeLine(p1, p2).Value();
	MW1.Add(BRepBuilderAPI_MakeEdge(aline, surf, 0., p1.Distance(p2)));
	BRepBuilderAPI_MakeFace MKF1;
	MKF1.Init(surf, Standard_False, Precision::Confusion());
	MKF1.Add(MW1.Wire());
	TopoDS_Face FP = MKF1.Face();
	BRepLib::BuildCurves3d(FP);
	TColgp_Array1OfPnt CurvePoles(1, 3);
	gp_Pnt pt = gp_Pnt(150., 0., 150.);
	CurvePoles(1) = pt;
	pt = gp_Pnt(200., -100., 150.);
	CurvePoles(2) = pt;
	pt = gp_Pnt(150., -200., 150.);
	CurvePoles(3) = pt;
	Handle(Geom_BezierCurve) curve = new Geom_BezierCurve(CurvePoles);
	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(curve);
	TopoDS_Wire W = BRepBuilderAPI_MakeWire(E);
	BRepFeat_MakePipe MKPipe(S, FP, F1, W, 1, Standard_True);
	MKPipe.Perform();
	TopoDS_Shape res1 = MKPipe.Shape();
	ais1->Set(res1);

	myAISContext->Redisplay(ais1, Standard_False);
	myAISContext->SetSelected(anIO1, Standard_False);
	myView->FitAll();
}

void ExampleOnGlueLocal(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	TopoDS_Shape S1 = BRepPrimAPI_MakeBox(gp_Pnt(-500., -500., 0.), gp_Pnt(-100., -250., 300.)).Shape();

	Handle(AIS_Shape) ais1 = new AIS_Shape(S1);
	myAISContext->SetColor(ais1, Quantity_NOC_ORANGE, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);

	TopExp_Explorer Ex1;
	Ex1.Init(S1, TopAbs_FACE);
	Ex1.Next();
	Ex1.Next();
	Ex1.Next();
	Ex1.Next();
	Ex1.Next();
	TopoDS_Face F1 = TopoDS::Face(Ex1.Current());
	TopoDS_Shape S2 = BRepPrimAPI_MakeBox(gp_Pnt(-400., -400., 300.), gp_Pnt(-200., -300., 500.)).Shape();
	Handle(AIS_Shape) ais2 = new AIS_Shape(S2);

	myAISContext->SetColor(ais2, Quantity_NOC_AZURE, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO2 = ais2;
	myAISContext->SetSelected(anIO2, Standard_False);


	TopExp_Explorer Ex2;
	Ex2.Init(S2, TopAbs_FACE);
	Ex2.Next();
	Ex2.Next();
	Ex2.Next();
	Ex2.Next();
	TopoDS_Face F2 = TopoDS::Face(Ex2.Current());
	BRepFeat_Gluer glue(S2, S1);
	glue.Bind(F2, F1);
	TopoDS_Shape res1 = glue.Shape();
	myAISContext->Erase(ais2, Standard_False);

	ais1->Set(res1);

	myAISContext->Redisplay(ais1, Standard_False);
	myAISContext->SetSelected(anIO1, Standard_False);

	TopoDS_Shape S3 = BRepPrimAPI_MakeBox(500., 400., 300.).Shape();

	Handle(AIS_Shape) ais3 = new AIS_Shape(S3);
	myAISContext->SetColor(ais3, Quantity_NOC_ORANGE, Standard_False);
	myAISContext->SetMaterial(ais3, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais3, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO3 = ais3;
	myAISContext->SetSelected(anIO3, Standard_False);


	TopExp_Explorer Ex3;
	Ex3.Init(S3, TopAbs_FACE);
	Ex3.Next();
	Ex3.Next();
	Ex3.Next();
	Ex3.Next();
	Ex3.Next();
	TopoDS_Face F3 = TopoDS::Face(Ex3.Current());
	TopoDS_Shape S4 = BRepPrimAPI_MakeBox(gp_Pnt(0., 0., 300.), gp_Pnt(200., 200., 500.)).Shape();

	Handle(AIS_Shape) ais4 = new AIS_Shape(S4);
	myAISContext->SetColor(ais4, Quantity_NOC_AZURE, Standard_False);
	myAISContext->SetMaterial(ais4, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais4, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO4 = ais4;
	myAISContext->SetSelected(anIO4, Standard_False);


	TopExp_Explorer Ex4;
	Ex4.Init(S4, TopAbs_FACE);
	Ex4.Next();
	Ex4.Next();
	Ex4.Next();
	Ex4.Next();
	TopoDS_Face F4 = TopoDS::Face(Ex4.Current());
	BRepFeat_Gluer glue2(S4, S3);
	glue2.Bind(F4, F3);
	LocOpe_FindEdges CommonEdges(F4, F3);
	for (CommonEdges.InitIterator(); CommonEdges.More(); CommonEdges.Next())
		glue2.Bind(CommonEdges.EdgeFrom(), CommonEdges.EdgeTo());
	TopoDS_Shape res2 = glue2.Shape();
	myAISContext->Erase(ais3, Standard_False);

	ais4->Set(res2);

	myAISContext->Redisplay(ais4, Standard_False);
	myAISContext->SetSelected(anIO4, Standard_False);
	myView->FitAll();
}

void ExampleOnSplitLocal(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape S = BRepPrimAPI_MakeBox(gp_Pnt(-100, -60, -80), 150, 200, 170).Shape();

	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);

	BRepAlgoAPI_Section asect(S, gp_Pln(1, 2, 1, -15), Standard_False);
	asect.ComputePCurveOn1(Standard_True);
	asect.Approximation(Standard_True);
	asect.Build();
	TopoDS_Shape R = asect.Shape();

	BRepFeat_SplitShape asplit(S);

	for (TopExp_Explorer Ex(R, TopAbs_EDGE); Ex.More(); Ex.Next()) {
		TopoDS_Shape anEdge = Ex.Current();
		TopoDS_Shape aFace;
		if (asect.HasAncestorFaceOn1(anEdge, aFace)) {
			TopoDS_Face F = TopoDS::Face(aFace);
			TopoDS_Edge E = TopoDS::Edge(anEdge);
			asplit.Add(E, F);
		}
	}

	asplit.Build();


	myAISContext->Erase(ais1, Standard_False);


	TopoDS_Shape Result = asplit.Shape();

	Handle(AIS_Shape) ais2 = new AIS_Shape(Result);

	myAISContext->SetColor(ais2, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->SetDisplayMode(ais2, 1, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO2 = ais2;
	myAISContext->SetSelected(anIO2, Standard_False);
	myView->FitAll();
}

void ExampleOnThickLocal(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape S1 = BRepPrimAPI_MakeBox(150, 200, 110).Shape();

	Handle(AIS_Shape) abox1 = new AIS_Shape(S1);
	myAISContext->SetColor(abox1, Quantity_NOC_WHITE, Standard_False);
	myAISContext->SetMaterial(abox1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(abox1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIOBox1 = abox1;
	myAISContext->SetSelected(anIOBox1, Standard_False);


	TopTools_ListOfShape aList;
	TopExp_Explorer Ex(S1, TopAbs_FACE);
	Ex.Next();	//this is the front face
	TopoDS_Shape aFace = Ex.Current();
	aList.Append(aFace);

	BRepOffsetAPI_MakeThickSolid aSolidMaker;
	aSolidMaker.MakeThickSolidByJoin(S1, aList, 10, 0.01);
	TopoDS_Shape aThickSolid = aSolidMaker.Shape();

	Handle(AIS_Shape) ais1 = new AIS_Shape(aThickSolid);
	myAISContext->SetColor(ais1, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);


	myAISContext->Erase(abox1, Standard_True);
	myView->FitAll();

}

void ExampleOnOffsetLocal(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Shape S1 = BRepPrimAPI_MakeBox(150, 200, 110).Shape();

	Handle(AIS_Shape) aisBox1 = new AIS_Shape(S1);
	myAISContext->SetColor(aisBox1, Quantity_NOC_BROWN, Standard_False);
	myAISContext->SetMaterial(aisBox1, Graphic3d_NOM_GOLD, Standard_False);
	myAISContext->Display(aisBox1, Standard_False);

	BRepOffsetAPI_MakeOffsetShape aShapeMaker1;
	aShapeMaker1.PerformByJoin(S1, 60, 0.01);
	TopoDS_Shape anOffsetShape1 = aShapeMaker1.Shape();

	Handle(AIS_Shape) ais1 = new AIS_Shape(anOffsetShape1);
	myAISContext->SetColor(ais1, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_GOLD, Standard_False);
	myAISContext->SetTransparency(ais1, 0.5, Standard_False);
	myAISContext->Display(ais1, Standard_False);


	TopoDS_Shape S2 = BRepPrimAPI_MakeBox(gp_Pnt(500, 0, 0), 220, 140, 180).Shape();

	Handle(AIS_Shape) aisBox2 = new AIS_Shape(S2);
	myAISContext->SetColor(aisBox2, Quantity_NOC_WHITE, Standard_False);
	myAISContext->SetMaterial(aisBox2, Graphic3d_NOM_GOLD, Standard_False);
	myAISContext->SetTransparency(aisBox2, 0.5, Standard_False);
	myAISContext->Display(aisBox2, Standard_False);


	BRepOffsetAPI_MakeOffsetShape aShapeMaker2;
	aShapeMaker2.PerformByJoin(S2, -40, 0.01,
		BRepOffset_Skin, Standard_False, Standard_False, GeomAbs_Arc);
	TopoDS_Shape anOffsetShape2 = aShapeMaker2.Shape();

	Handle(AIS_Shape) ais2 = new AIS_Shape(anOffsetShape2);
	myAISContext->SetColor(ais2, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_GOLD, Standard_False);
	myAISContext->Display(ais2, Standard_False);
	myView->FitAll();
}

void ExampleOnVertex(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Vertex V1, V2, V3;

	V1 = BRepBuilderAPI_MakeVertex(gp_Pnt(0, 0, 0));
	V2 = BRepBuilderAPI_MakeVertex(gp_Pnt(10, 7, 25));

	gp_Pnt P(-12, 8, -4);
	BRepBuilderAPI_MakeVertex MV(P);
	V3 = MV.Vertex();

	Handle(AIS_Shape) Point1 = new AIS_Shape(V1);
	myAISContext->Display(Point1, Standard_False);
	Handle(AIS_Shape) Point2 = new AIS_Shape(V2);
	myAISContext->Display(Point2, Standard_False);
	Handle(AIS_Shape) Point3 = new AIS_Shape(V3);
	myAISContext->Display(Point3, Standard_False);
	myView->FitAll();
}

void ExampleOnEdge(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{

	ClearScene(myAISContext, myView);


	TopoDS_Edge BlueEdge, YellowEdge, WhiteEdge, RedEdge, GreenEdge;
	TopoDS_Vertex V1, V2, V3, V4;

	/////////////The blue edge

	BlueEdge = BRepBuilderAPI_MakeEdge(gp_Pnt(-80, -50, -20), gp_Pnt(-30, -60, -60));

	/////////////The yellow edge

	V1 = BRepBuilderAPI_MakeVertex(gp_Pnt(-20, 10, -30));
	V2 = BRepBuilderAPI_MakeVertex(gp_Pnt(10, 7, -25));
	YellowEdge = BRepBuilderAPI_MakeEdge(V1, V2);

	/////////////The white edge

	gp_Lin line(gp_Ax1(gp_Pnt(10, 10, 10), gp_Dir(1, 0, 0)));
	WhiteEdge = BRepBuilderAPI_MakeEdge(line, -20, 10);

	//////////////The red edge

	gp_Elips Elips(gp_Ax2(gp_Pnt(10, 0, 0), gp_Dir(1, 1, 1)), 60, 30);
	RedEdge = BRepBuilderAPI_MakeEdge(Elips, 0, M_PI / 2);

	/////////////The green edge and the both extreme vertex

	gp_Pnt P1(-15, 200, 10);
	gp_Pnt P2(5, 204, 0);
	gp_Pnt P3(15, 200, 0);
	gp_Pnt P4(-15, 20, 15);
	gp_Pnt P5(-5, 20, 0);
	gp_Pnt P6(15, 20, 0);
	gp_Pnt P7(24, 120, 0);
	gp_Pnt P8(-24, 120, 12.5);
	TColgp_Array1OfPnt array(1, 8);
	array.SetValue(1, P1);
	array.SetValue(2, P2);
	array.SetValue(3, P3);
	array.SetValue(4, P4);
	array.SetValue(5, P5);
	array.SetValue(6, P6);
	array.SetValue(7, P7);
	array.SetValue(8, P8);
	Handle(Geom_BezierCurve) curve = new Geom_BezierCurve(array);

	BRepBuilderAPI_MakeEdge ME(curve);
	GreenEdge = ME;
	V3 = ME.Vertex1();
	V4 = ME.Vertex2();

	//////////////Display
	Handle(AIS_Shape) blue = new AIS_Shape(BlueEdge);
	myAISContext->SetColor(blue, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->Display(blue, Standard_False);

	Handle(AIS_Shape) yellow = new AIS_Shape(YellowEdge);
	myAISContext->SetColor(yellow, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->Display(yellow, Standard_False);

	Handle(AIS_Shape) white = new AIS_Shape(WhiteEdge);
	myAISContext->SetColor(white, Quantity_NOC_WHITE, Standard_False);
	myAISContext->Display(white, Standard_False);

	Handle(AIS_Shape) red = new AIS_Shape(RedEdge);
	myAISContext->SetColor(red, Quantity_NOC_RED, Standard_False);
	myAISContext->Display(red, Standard_False);

	Handle(AIS_Shape) green = new AIS_Shape(GreenEdge);
	myAISContext->SetColor(green, Quantity_NOC_GREEN, Standard_False);
	myAISContext->Display(green, Standard_False);

	Handle(AIS_Shape) Point1 = new AIS_Shape(V3);
	myAISContext->Display(Point1, Standard_False);
	Handle(AIS_Shape) Point2 = new AIS_Shape(V4);
	myAISContext->Display(Point2, Standard_False);
	myView->FitAll();
}

void ExampleOnWire(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);

	TopoDS_Wire RedWire, YellowWire, WhiteWire,
		ExistingWire, ExistingWire2;

	TopoDS_Edge Edge1, Edge2, Edge3, Edge4, Edge5, Edge6, Edge7, LastEdge;
	TopoDS_Vertex LastVertex;

	////////////The red wire is build from a single edge

	gp_Elips Elips(gp_Ax2(gp_Pnt(250, 0, 0), gp_Dir(1, 1, 1)), 160, 90);
	Edge1 = BRepBuilderAPI_MakeEdge(Elips, 0, M_PI / 2);

	RedWire = BRepBuilderAPI_MakeWire(Edge1);

	///////////the yellow wire is build from an existing wire and an edge

	gp_Circ circle(gp_Ax2(gp_Pnt(-300, 0, 0), gp_Dir(1, 0, 0)), 80);
	Edge2 = BRepBuilderAPI_MakeEdge(circle, 0, M_PI);

	ExistingWire = BRepBuilderAPI_MakeWire(Edge2);

	Edge3 = BRepBuilderAPI_MakeEdge(gp_Pnt(-300, 0, -80), gp_Pnt(-90, 20, -30));

	BRepBuilderAPI_MakeWire MW1(ExistingWire, Edge3);
	if (MW1.IsDone()) {
		YellowWire = MW1;
	}


	//////////the white wire is built with an existing wire and 3 edges.
	//////////we use the methods Add, Edge and Vertex from BRepBuilderAPI_MakeWire.

	gp_Circ circle2(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)), 200);
	Edge4 = BRepBuilderAPI_MakeEdge(circle2, 0, M_PI);

	ExistingWire2 = BRepBuilderAPI_MakeWire(Edge4);

	gp_Pnt P1(0, 0, -200);
	gp_Pnt P2(5, 204, 0);
	Edge5 = BRepBuilderAPI_MakeEdge(P1, P2);

	gp_Pnt P3(-15, 20, 15);
	Edge6 = BRepBuilderAPI_MakeEdge(P2, P3);
	gp_Pnt P4(15, 20, 0);
	Edge7 = BRepBuilderAPI_MakeEdge(P3, P4);

	BRepBuilderAPI_MakeWire MW;
	MW.Add(ExistingWire2);
	MW.Add(Edge5);
	MW.Add(Edge6);
	MW.Add(Edge7);

	if (MW.IsDone()) {
		WhiteWire = MW.Wire();
		LastEdge = MW.Edge();
		LastVertex = MW.Vertex();
	}


	Handle(AIS_Shape) red = new AIS_Shape(RedWire);
	myAISContext->SetColor(red, Quantity_NOC_RED, Standard_False);
	myAISContext->Display(red, Standard_False);

	Handle(AIS_Shape) yellow = new AIS_Shape(YellowWire);
	myAISContext->SetColor(yellow, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->Display(yellow, Standard_False);

	Handle(AIS_Shape) white = new AIS_Shape(WhiteWire);
	myAISContext->SetColor(white, Quantity_NOC_WHITE, Standard_False);
	myAISContext->Display(white, Standard_False);

	Handle(AIS_Shape) lastE = new AIS_Shape(LastEdge);
	myAISContext->SetWidth(lastE, 3, Standard_False);
	myAISContext->SetColor(lastE, Quantity_NOC_RED, Standard_False);
	myAISContext->Display(lastE, Standard_False);

	Handle(AIS_Shape) lastV = new AIS_Shape(LastVertex);
	myAISContext->Display(lastV, Standard_False);
	myView->FitAll();
}

void ExampleOnExplorer(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	myAISContext->RemoveAll(false);

	TopoDS_Shape aBox = BRepPrimAPI_MakeBox(100, 100, 100).Shape();
	Standard_Integer j(8);
	Handle(AIS_ColoredShape) theBox = new AIS_ColoredShape(aBox);
	myAISContext->SetColor(theBox, Quantity_NOC_RED, Standard_False);
	myAISContext->SetMaterial(theBox, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(theBox, AIS_Shaded, 0, Standard_False);


	for (TopExp_Explorer exp(aBox, TopAbs_FACE); exp.More(); exp.Next())
	{
		TopoDS_Face aCurrentFace = TopoDS::Face(exp.Current());
		{
			Handle(AIS_ColoredDrawer) aSubFaceAspects = theBox->CustomAspects(aCurrentFace);
			aSubFaceAspects->SetShadingAspect(new Prs3d_ShadingAspect());
			*aSubFaceAspects->ShadingAspect()->Aspect() = *theBox->Attributes()->ShadingAspect()->Aspect();
			aSubFaceAspects->ShadingAspect()->Aspect()->ChangeFrontMaterial().SetTransparency(0.8f);
			myAISContext->Redisplay(theBox, false);
		}

		//test the orientation of the current face
		TopAbs_Orientation orient = aCurrentFace.Orientation();

		//Recover the geometric plane
		TopLoc_Location location;
		Handle(Geom_Surface) aGeometricSurface = BRep_Tool::Surface(aCurrentFace, location);

		Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aGeometricSurface);

		//Build an AIS_Shape with a new color
		Handle(AIS_Shape) theMovingFace = new AIS_Shape(aCurrentFace);
		Quantity_NameOfColor aCurrentColor = (Quantity_NameOfColor)j;
		myAISContext->SetColor(theMovingFace, aCurrentColor, Standard_False);
		myAISContext->SetMaterial(theMovingFace, Graphic3d_NOM_PLASTIC, Standard_False);
		//Find the normal vector of each face
		gp_Pln agpPlane = aPlane->Pln();
		gp_Ax1 norm = agpPlane.Axis();
		gp_Dir dir = norm.Direction();
		gp_Vec move(dir);

		TopLoc_Location aLocation;
		Handle(AIS_ConnectedInteractive) theTransformedDisplay = new AIS_ConnectedInteractive();
		theTransformedDisplay->Connect(theMovingFace, aLocation);

		Handle(Geom_Transformation) theMove = new Geom_Transformation(aLocation.Transformation());
		myAISContext->Display(theTransformedDisplay, Standard_False);
		myAISContext->UpdateCurrentViewer();


		for (Standard_Integer i = 1; i <= 30; i++)
		{
			theMove->SetTranslation(move * i);
			if (orient == TopAbs_FORWARD)  myAISContext->SetLocation(theTransformedDisplay, TopLoc_Location(theMove->Trsf()));
			else  myAISContext->SetLocation(theTransformedDisplay, TopLoc_Location(theMove->Inverted()->Trsf()));

			myAISContext->Redisplay(theTransformedDisplay, true);
		}
		j += 15;
	}

	myAISContext->UpdateCurrentViewer();
	myView->FitAll();
}

void ExampleOnLinearLocal(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	BRepBuilderAPI_MakeWire mkw;
	gp_Pnt p1 = gp_Pnt(0., 0., 0.);
	gp_Pnt p2 = gp_Pnt(200., 0., 0.);
	mkw.Add(BRepBuilderAPI_MakeEdge(p1, p2));
	p1 = p2;
	p2 = gp_Pnt(200., 0., 50.);
	mkw.Add(BRepBuilderAPI_MakeEdge(p1, p2));
	p1 = p2;
	p2 = gp_Pnt(50., 0., 50.);
	mkw.Add(BRepBuilderAPI_MakeEdge(p1, p2));
	p1 = p2;
	p2 = gp_Pnt(50., 0., 200.);
	mkw.Add(BRepBuilderAPI_MakeEdge(p1, p2));
	p1 = p2;
	p2 = gp_Pnt(0., 0., 200.);
	mkw.Add(BRepBuilderAPI_MakeEdge(p1, p2));
	p1 = p2;
	mkw.Add(BRepBuilderAPI_MakeEdge(p2, gp_Pnt(0., 0., 0.)));

	TopoDS_Shape S = BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(mkw.Wire()),
		gp_Vec(gp_Pnt(0., 0., 0.), gp_Pnt(0., 100., 0.)));

	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_CYAN2, Standard_False);
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(ais1, Standard_False);
	const Handle(AIS_InteractiveObject)& anIO1 = ais1;
	myAISContext->SetSelected(anIO1, Standard_False);


	TopoDS_Wire W = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(gp_Pnt(50., 45., 100.),
		gp_Pnt(100., 45., 50.)));
	Handle(Geom_Plane) aplane = new Geom_Plane(0., 1., 0., -45.);
	BRepFeat_MakeLinearForm aform(S, W, aplane, gp_Vec(0., 10., 0.), gp_Vec(0., 0., 0.),
		1, Standard_True);
	aform.Perform(/*10.*/); // new in 2.0

	TopoDS_Shape res = aform.Shape();
	ais1->Set(res);
	myAISContext->Redisplay(ais1, Standard_False);
	myAISContext->SetSelected(anIO1, Standard_False);
	myView->FitAll();

}

void ExampleOnNut(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	/// лекция 

	Handle(Geom_Line) aLine;
	Handle(Geom_Curve) aCurve;


	Handle(Geom_Point) aPnt1;

	Handle(Geom_CartesianPoint) aPnt2, aPnt3;
	aPnt2 = new Geom_CartesianPoint(0.0, 0.0, 0.0);
	aPnt1 = aPnt2;
	aPnt3 = Handle(Geom_CartesianPoint)::DownCast(aPnt1);

	// пример решение СЛАУ
	math_Matrix a(1, 3, 1, 3);
	math_Vector b1(1, 3), b2(1, 3);
	math_Vector x1(1, 3), x2(1, 3);


	math_Gauss aSol(a);
	if (aSol.IsDone())
	{
		aSol.Solve(b1, x1);
		aSol.Solve(b2, x2);
	}


	//if (dynamic_cast<Geom_Line>(aCurve.get()) != 0)
	//if (aCurve->IsKind(STANDARD_TYPE(Geom_Line)))





	///конец лекция

	// очистка сцены
	ClearScene(myAISContext, myView);
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

	TopoDS_Face face = BRepBuilderAPI_MakeFace(W);




	TopoDS_Shape S = BRepPrimAPI_MakeRevol(face, axe, 2 * M_PI).Shape();
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
	//myAISContext->SetColor(aBlendedBox, Quantity_NOC_YELLOW, Standard_False);
	//myAISContext->SetMaterial(aBlendedBox, Graphic3d_NOM_PLASTIC, Standard_False);
	//myAISContext->Display(aBlendedBox, Standard_False);
	//const Handle(AIS_InteractiveObject)& anIOBlendedBox = aBlendedBox;
	//myAISContext->SetSelected(anIOBlendedBox, Standard_False);
	// 
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
		TopoDS_Edge E = BRepBuilderAPI_MakeEdge(gp_Pnt(-b / 2, x0, y0), gp_Pnt(-b / 2, x, y));
		MW.Add(E);
		x0 = x;
		y0 = y;
	}

	DSW = MW.Wire();

	Handle(AIS_Shape) aisW2 = new AIS_Shape(DSW);
	myAISContext->Display(aisW2, Standard_False);

	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(DSW);
	gp_Vec aPrismVec(b, 0, 0);

	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);
	Handle(AIS_Shape) aismS = new AIS_Shape(myBody);

	TopoDS_Shape theCommonSurface1 = BRepAlgoAPI_Common(myBody, ChanfrenedBox);

	Handle(AIS_Shape) acommon1 = new AIS_Shape(theCommonSurface1);

	myAISContext->SetColor(aBlendedBox, Quantity_NOC_YELLOW, Standard_False);
	myAISContext->SetMaterial(aBlendedBox, Graphic3d_NOM_PLASTIC, Standard_False);
	myAISContext->Display(acommon1, Standard_False);


	myView->FitAll();
}

void ExampleOnConstraints(Handle(AIS_InteractiveContext) myAISContext, Handle(V3d_View) myView)
{
	ClearScene(myAISContext, myView);
	
	//gp_XYZ O(0, 0, 0);
	//gp_XYZ A(1, 2, 3);
	//gp_XYZ B(2, 2, 2);
	//gp_XYZ C(3, 2, 3);
	
	//Standard_Real result = A.DotCross(B, C);
	//TopoDS_Vertex V1 = DisplayVertex(myAISContext, A, "A", false, 0.1, 0.1, 0.1);
	//TopoDS_Vertex V2 = DisplayVertex(myAISContext, B, "B", false, 0.1, 0.1, 0.1);
	//TopoDS_Vertex V3 = DisplayVertex(myAISContext, C, "C", false, 0.1, 0.1, 0.1);
	//TopoDS_Vertex V0 = DisplayVertex(myAISContext, O, "0", false, 0.1, 0.1, 0.1);

	//DisplayEdgeByVertex(myAISContext, V0, V1, false, Aspect_TOL_DASH, 1.0);
	//DisplayEdgeByVertex(myAISContext, V0, V2, false, Aspect_TOL_DASH, 1.0);
	//DisplayEdgeByVertex(myAISContext, V0, V3, false, Aspect_TOL_DASH, 1.0);


	
  //==============================================================

	gp_Pnt2d P1(2, 3);
	gp_Pnt2d P2(4, 4);
	gp_Pnt2d P3(6, 7);
	gp_Pnt2d P4(10, 10);
	gp_Circ2d C2 = gce_MakeCirc2d(P1, P2, P3);
	GccEnt_QualifiedCirc QC = GccEnt::Outside(C2);
	//GccAna_Lin2d2Tan LT (QC, P4, Precision::Confusion());
	
	GccAna_Lin2d2Tan* LT = new GccAna_Lin2d2Tan(QC, P4, Precision::Confusion());
	if (LT->IsDone())
	{
		Standard_Integer NbSol = LT->NbSolutions();
		for (Standard_Integer k = 1; k <= NbSol; k++)
		{
			gp_Lin2d L = LT->ThisSolution(k);
			
		}
	}
	
	//==============================================================
	
	

	myView->FitAll();
}