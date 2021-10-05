using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RustedNail
{
    public enum CurrentAction3d
    {
        CurAction3d_Nothing,
        CurAction3d_DynamicZooming,
        CurAction3d_WindowZooming,
        CurAction3d_DynamicPanning,
        CurAction3d_GlobalPanning,
        CurAction3d_DynamicRotation
    }
    public enum CurrentPressedKey
    {
        CurPressedKey_Nothing,
        CurPressedKey_Ctrl,
        CurPressedKey_Shift
    }

    public enum ModelFormat
    {
        BREP,
        STEP,
        IGES,
        VRML,
        STL,
        IMAGE
    }

    public partial class ChildMDIForm : Form
    {

        // ПОЛЯ
        private OCCTProxy myOCCTProxy;
        protected CurrentAction3d myCurrentMode;
        protected CurrentPressedKey myCurrentPressedKey;
        protected float myCurZoom;
        protected bool myDegenerateModeIsOn;
        protected int myXmin;
        protected int myYmin;
        protected int myXmax;
        protected int myYmax;
        protected int theButtonDownX;
        protected int theButtonDownY;
        // для очистки рамки
        protected int theRectDownX;
        protected int theRectDownY;
        protected bool IsRectVisible;
        // СВОЙСТВА
        public OCCTProxy View
        {
            get
            {
                return this.myOCCTProxy;
            }
            set
            {
                this.myOCCTProxy = value;
            }
        }
        public CurrentAction3d Mode
        {
            get
            {
                return this.myCurrentMode;
            }
            set
            {
                this.myCurrentMode = value;
            }
        }

        public float Zoom
        {
            set
            {
                this.myCurZoom = value;
            }
        }

        public bool DegenerateMode
        {
            get
            {
                return this.myDegenerateModeIsOn;
            }
            set
            {
                this.myDegenerateModeIsOn = value;
            }
        }
        // МЕТОДЫ

        public ChildMDIForm()
        {
            InitializeComponent();

            myOCCTProxy = new OCCTProxy();
            myCurrentMode = CurrentAction3d.CurAction3d_Nothing;
            myCurrentPressedKey = CurrentPressedKey.CurPressedKey_Nothing;
        }


        public void InitV3D()
        {
            if (!myOCCTProxy.InitViewer(this.Handle))
                MessageBox.Show("Fatal Error during the graphic initialisation", "Error!",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public void InitView()
        {
            this.myOCCTProxy.InitOCCTProxy();
        }

        public void SetContext(OCCTProxy View)
        {
            this.myOCCTProxy.SetAISContext(View);
        }

        private void DrawRectangle(bool draw)
        {
            Graphics gr = Graphics.FromHwnd(this.Handle);
            System.Drawing.Pen p = null;
            if (this.IsRectVisible || (!draw))//erase the rect
            {
                int r = myOCCTProxy.GetBGColR();
                int g = myOCCTProxy.GetBGColG();
                int b = myOCCTProxy.GetBGColB();
                p = new Pen(System.Drawing.Color.FromArgb(r, g, b));
                this.IsRectVisible = false;
                this.myOCCTProxy.UpdateView();
            }
            else if (draw)
            {
                p = new Pen(System.Drawing.Color.White);
                this.IsRectVisible = true;
            }
            if (p == null)
                return;
            int x = Math.Min(this.myXmin, this.myXmax);
            int y = Math.Min(this.myYmin, this.myYmax);
            gr.DrawRectangle(p, x, y, Math.Abs(myXmax - myXmin), Math.Abs(myYmax - myYmin));
            this.theRectDownX = Math.Max(this.myXmin, this.myXmax);
            this.theRectDownY = Math.Max(this.myYmin, this.myYmax);
        }

        protected void MultiMoveEvent(int x, int y)
        {
            myOCCTProxy.MoveTo(x, y);
        }

        protected void MoveEvent(int x, int y)
        {
            myOCCTProxy.MoveTo(x, y);
        }


        protected void MultiInputEvent(int x, int y)
        {
            myOCCTProxy.ShiftSelect();
        }

        protected void InputEvent(int x, int y)
        {
            myOCCTProxy.Select();
        }

        protected void MultiDragEvent(int x, int y, int theState)
        {
            if (theState == -1)
            {
                theButtonDownX = x;
                theButtonDownY = y;
            }
            else if (theState == 1)
                myOCCTProxy.ShiftSelect(Math.Min(theButtonDownX, x), Math.Min(theButtonDownY, y),
                        Math.Max(theButtonDownX, x), Math.Max(theButtonDownY, y));
        }

        protected void DragEvent(int x, int y, int theState)
        {
            if (theState == -1) //mouse is down
            {
                theButtonDownX = x;
                theButtonDownY = y;
            }
            else if (theState == 1) //mouse is up
            {
                myOCCTProxy.Select(Math.Min(theButtonDownX, x), Math.Min(theButtonDownY, y),
                        Math.Max(theButtonDownX, x), Math.Max(theButtonDownY, y));
            }
        }

        protected void Popup(int x, int y)
        {
            //System.Drawing.Point p = new Point(x, y);
            //if (this.myOCCTProxy.IsObjectSelected())
            //    this.myPopupObject.Show(this, p);
            //else
            //    this.myPopup.Show(this, p);
        }

        public void Test()
        {
            myOCCTProxy.Test(); 
        }


        // ОБРАБОТЧИКИ СОБЫТИЙ
        private void ChildMDIForm_SizeChanged(object sender, EventArgs e)
        {
            myOCCTProxy.UpdateView();
        }

        private void ChildMDIForm_Paint(object sender, PaintEventArgs e)
        {
            myOCCTProxy.RedrawView();
            myOCCTProxy.UpdateView();
        }


        private void ChildMDIForm_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left) //left button is pressed
            {
                if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Ctrl)
                {
                    myOCCTProxy.Zoom(myXmax, myYmax, e.X, e.Y);
                    myXmax = e.X; myYmax = e.Y;
                }
                else
                {
                    switch (myCurrentMode)
                    {
                        case CurrentAction3d.CurAction3d_Nothing:
                            DrawRectangle(false);
                            myXmax = e.X; myYmax = e.Y;
                            DrawRectangle(true);
                            break;
                        case CurrentAction3d.CurAction3d_DynamicZooming:
                            myOCCTProxy.Zoom(myXmax, myYmax, e.X, e.Y);
                            myXmax = e.X; myYmax = e.Y;
                            break;
                        case CurrentAction3d.CurAction3d_WindowZooming:
                            DrawRectangle(false);
                            myXmax = e.X; myYmax = e.Y;
                            DrawRectangle(true);//add brush here
                            break;
                        case CurrentAction3d.CurAction3d_DynamicPanning:
                            myOCCTProxy.Pan(e.X - myXmax, myYmax - e.Y);
                            myXmax = e.X; myYmax = e.Y;
                            break;
                        case CurrentAction3d.CurAction3d_GlobalPanning:
                            break;
                        case CurrentAction3d.CurAction3d_DynamicRotation:
                            myOCCTProxy.Rotation(e.X, e.Y);
                            myOCCTProxy.RedrawView();
                            break;
                        default:
                            break;
                    }
                }
            } // e.Button == MouseButtons.Left
            else if (e.Button == MouseButtons.Middle)
            {
                if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Ctrl)
                {
                    myOCCTProxy.Pan(e.X - myXmax, myYmax - e.Y);
                    myXmax = e.X; myYmax = e.Y;
                }
            }//e.Button=MouseButtons.Middle
            else if (e.Button == MouseButtons.Right) //right button is pressed
            {
                if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Ctrl)
                    myOCCTProxy.Rotation(e.X, e.Y);
            }
            else // no buttons are pressed
            {
                myXmax = e.X; myYmax = e.Y;
                if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Shift)
                    MultiMoveEvent(e.X, e.Y);
                else
                    MoveEvent(e.X, e.Y);
            }


        }

        private void ChildMDIForm_MouseUp(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Ctrl)
                        return;
                    switch (myCurrentMode)
                    {
                        case CurrentAction3d.CurAction3d_Nothing:
                            if (e.X == myXmin && e.Y == myYmin)
                            {
                                myXmax = e.X; myYmax = e.Y;
                                if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Shift)
                                    MultiInputEvent(myXmax, myYmax);
                                else
                                    InputEvent(myXmax, myYmax);
                            }
                            else
                            {
                                myXmax = e.X; myYmax = e.Y;
                                DrawRectangle(false);
                                if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Shift)
                                    MultiDragEvent(myXmax, myYmax, 1);
                                else
                                    DragEvent(myXmax, myYmax, 1);
                            }
                            break;
                        case CurrentAction3d.CurAction3d_DynamicZooming:
                            myCurrentMode = CurrentAction3d.CurAction3d_Nothing;
                            break;
                        case CurrentAction3d.CurAction3d_WindowZooming:
                            myXmax = e.X; myYmax = e.Y;
                            DrawRectangle(false);
                            int ValZWMin = 1;
                            if (Math.Abs(myXmax - myXmin) > ValZWMin && Math.Abs(myXmax - myYmax) > ValZWMin)
                                myOCCTProxy.WindowFitAll(myXmin, myYmin, myXmax, myYmax);
                            this.Cursor = System.Windows.Forms.Cursors.Default;
                            RustedNail.ParentMDIForm f = (RustedNail.ParentMDIForm)this.ParentForm;
                            f.SelectionChanged();
                            myCurrentMode = CurrentAction3d.CurAction3d_Nothing;
                            break;
                        case CurrentAction3d.CurAction3d_DynamicPanning:
                            myCurrentMode = CurrentAction3d.CurAction3d_Nothing;
                            break;
                        case CurrentAction3d.CurAction3d_GlobalPanning:
                            myOCCTProxy.Place(e.X, e.Y, myCurZoom);
                            myCurrentMode = CurrentAction3d.CurAction3d_Nothing;
                            break;
                        case CurrentAction3d.CurAction3d_DynamicRotation:
                            myCurrentMode = CurrentAction3d.CurAction3d_Nothing;
                            if (!myDegenerateModeIsOn)
                            {
                                myOCCTProxy.SetDegenerateModeOff();
                                myDegenerateModeIsOn = false;
                            }
                            else
                            {
                                myOCCTProxy.SetDegenerateModeOn();
                                myDegenerateModeIsOn = true;
                            }
                            break;
                        default:
                            break;

                    }
                    break;
                case MouseButtons.Right:
                    if (!myDegenerateModeIsOn)
                    {
                        myOCCTProxy.SetDegenerateModeOff();
                        myDegenerateModeIsOn = false;
                    }
                    else
                    {
                        myOCCTProxy.SetDegenerateModeOn();
                        myDegenerateModeIsOn = true;
                    }
                    break;
                default:
                    break;
            }

            RustedNail.ParentMDIForm parent = (RustedNail.ParentMDIForm)this.ParentForm;
            parent.SelectionChanged();
        }

        private void ChildMDIForm_KeyUp(object sender, KeyEventArgs e)
        {
            myCurrentPressedKey = CurrentPressedKey.CurPressedKey_Nothing;
        }

        private void ChildMDIForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Shift)
                myCurrentPressedKey = CurrentPressedKey.CurPressedKey_Shift;
            else if (e.Control)
                myCurrentPressedKey = CurrentPressedKey.CurPressedKey_Ctrl;
        }

        private void ChildMDIForm_MouseDown(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    myXmin = e.X; myYmin = e.Y;
                    myXmax = e.X; myYmax = e.Y;
                    if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Ctrl)
                        // start the dinamic zooming....
                        myCurrentMode = CurrentAction3d.CurAction3d_DynamicZooming;
                    else
                    {
                        switch (myCurrentMode)
                        {
                            case CurrentAction3d.CurAction3d_Nothing:
                                if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Shift)
                                    MultiDragEvent(myXmax, myYmax, -1);
                                else
                                    DragEvent(myXmax, myYmax, -1);
                                break;
                            case CurrentAction3d.CurAction3d_DynamicRotation:
                                if (!myDegenerateModeIsOn)
                                    myOCCTProxy.SetDegenerateModeOn();
                                //start the rotation
                                myOCCTProxy.StartRotation(e.X, e.Y);
                                break;
                            case RustedNail.CurrentAction3d.CurAction3d_WindowZooming:
                                this.Cursor = System.Windows.Forms.Cursors.Hand;
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case MouseButtons.Right:
                    //MessageBox.Show("right mouse button is down");
                    if (myCurrentPressedKey == CurrentPressedKey.CurPressedKey_Ctrl)
                    {
                        if (!myDegenerateModeIsOn)
                            myOCCTProxy.SetDegenerateModeOn();
                        myOCCTProxy.StartRotation(e.X, e.Y);
                    }
                    else
                         Popup(e.X, e.Y);
                    break;
                default:
                    break;
            }
        }
    }
}
