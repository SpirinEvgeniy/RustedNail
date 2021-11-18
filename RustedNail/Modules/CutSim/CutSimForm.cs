using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;



namespace RustedNail.Modules.CutSim
{
    public partial class CutSimForm : RustedNail.ChildMDIForm // наследовать от Forn  для работы через конструктор интерфейса и от RustedNail.ChildMDIForm для работы модуля
    {
        public double m = 0.0;
        public int z = 0;

        public CutSimForm()
        {
            InitializeComponent();


            this.pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            this.pictureBox1.ClientSize = new Size(450, 250);
            this.pictureBox1.Image = Image.FromFile(@"..\..\RustedNail\Modules\CutSim\Исходный контур.png");


        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            double.TryParse(textBox1.Text, out m);
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox2.Text, out z);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            View.CreateGearRack();            
        }

        private void CutSimForm_Paint(object sender, PaintEventArgs e)
        {           
            myOCCTProxy.RedrawView();
            myOCCTProxy.UpdateView();
        }

        private void CutSimForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Shift)
                myCurrentPressedKey = CurrentPressedKey.CurPressedKey_Shift;
            else if (e.Control)
                myCurrentPressedKey = CurrentPressedKey.CurPressedKey_Ctrl;
        }

        private void CutSimForm_KeyUp(object sender, KeyEventArgs e)
        {
            myCurrentPressedKey = CurrentPressedKey.CurPressedKey_Nothing;
        }

        private void CutSimForm_MouseDown(object sender, MouseEventArgs e)
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
                            case CurrentAction3d.CurAction3d_WindowZooming:
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

        private void CutSimForm_MouseMove(object sender, MouseEventArgs e)
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

        private void CutSimForm_MouseUp(object sender, MouseEventArgs e)
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

        private void CutSimForm_SizeChanged(object sender, EventArgs e)
        {
            myOCCTProxy.UpdateView();
        }
    }
}
