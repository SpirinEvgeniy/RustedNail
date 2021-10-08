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
    public partial class ParentMDIForm : Form
    {
        private bool isWindowsTabbed = false;
        private int lastChildFormNumber = 0;
        protected ModelFormat myModelFormat;
        private WindowsTabPanelManager windowsTabPanelManager;

        public ParentMDIForm()
        {
            InitializeComponent();
        }

        private void createToolStripMenuItem_Click(object sender, EventArgs e)
        {
            lastChildFormNumber++;

            ChildMDIForm childMDIForm = new ChildMDIForm();
            childMDIForm.MdiParent = this;
            childMDIForm.Show();
            childMDIForm.InitView();
            childMDIForm.InitV3D();
            childMDIForm.View.SetDisplayMode(1);
            childMDIForm.Test();
        }

        private void cascadeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.Cascade);
        }

        private void horizontalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void verticalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.TileVertical);
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (this.MdiChildren.Count() > 0)
                this.ActiveMdiChild.Close();
        }

        private void closeAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (Form childForm in this.MdiChildren)
                childForm.Close();
        }

        public void SelectionChanged()
        {

        }

        private void toolStripRunButton_Click(object sender, EventArgs e)
        {
            int number;
            ChildMDIForm childMDIForm = (ChildMDIForm)this.ActiveMdiChild;
            if ((childMDIForm != null) && (int.TryParse(toolStripExampleIDTextBox.Text, out number)))
            {
                childMDIForm.View.SetDisplayMode(1);
                switch (number)
                {
                    case 1:
                        childMDIForm.View.Example1();
                        break;
                    case 2:
                        childMDIForm.View.Example2();
                        break;
                    case 3:
                        childMDIForm.View.Example3();
                        break;
                    case 4:
                        childMDIForm.View.Example4();
                        break;
                    case 5:
                        childMDIForm.View.Example5();
                        break;
                    case 6:
                        childMDIForm.View.Example6();
                        break;
                    case 7:
                        childMDIForm.View.Example7();
                        break;
                    case 8:
                        childMDIForm.View.Example8();
                        break;
                    case 9:
                        childMDIForm.View.Example9();
                        break;
                    case 10:
                        childMDIForm.View.Example10();
                        break;
                    case 11:
                        childMDIForm.View.Example11();
                        break;
                    case 12:
                        childMDIForm.View.Example12();
                        break;
                    case 13:
                        childMDIForm.View.Example13();
                        break;
                    case 14:
                        childMDIForm.View.Example14();
                        break;
                    case 15:
                        childMDIForm.View.Example15();
                        break;
                    case 16:
                        childMDIForm.View.Example16();
                        break;
                    case 17:
                        childMDIForm.View.Example17();
                        break;
                    case 18:
                        childMDIForm.View.Example18();
                        break;
                    case 19:
                        childMDIForm.View.Example19();
                        break;
                    case 20:
                        childMDIForm.View.Example20();
                        break;
                    case 21:
                        childMDIForm.View.Example21();
                        break;
                    case 22:
                        childMDIForm.View.Example22();
                        break;
                    case 23:
                        childMDIForm.View.Example23();
                        break;
                    case 24:
                        childMDIForm.View.Example24();
                        break;
                    case 25:
                        childMDIForm.View.Example25();
                        break;
                    case 26:
                        childMDIForm.View.Example26();
                        break;
                    case 27:
                        childMDIForm.View.Example27();
                        break;
                    case 28:
                        childMDIForm.View.Example28();
                        break;
                    case 29:
                        childMDIForm.View.Example29();
                        break;
                    case 30:
                        childMDIForm.View.Example30();
                        break;
                    case 31:
                        childMDIForm.View.Example31();
                        break;
                    case 32:
                        childMDIForm.View.Example32();
                        break;
                    case 33:
                        childMDIForm.View.Example33();
                        break;
                    case 34:
                        childMDIForm.View.Example34();
                        break;
                    case 35:
                        childMDIForm.View.Example35();
                        break;
                    case 36:
                        childMDIForm.View.Example36();
                        break;
                    case 37:
                        childMDIForm.View.Example37();
                        break;
                }
            }
        }

        private void toTabPanelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!isWindowsTabbed) //если сейчас в режиме окон
            {
                windowsTabPanelManager = new WindowsTabPanelManager(this);
                windowsTabPanelManager.MakeActive();
                toTabPanelToolStripMenuItem.Text = "To windows mode";
            }
            else //если сейчас в режиме вкладок
            {
                toTabPanelToolStripMenuItem.Text = "To tabs mode";
                windowsTabPanelManager.MakeInactive();
            }

            isWindowsTabbed = !isWindowsTabbed;
        }
    }
}
