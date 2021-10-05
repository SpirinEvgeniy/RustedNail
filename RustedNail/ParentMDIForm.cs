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
        protected RustedNail.ModelFormat myModelFormat;

        int _lastChildFormNumber = 0;

        public ParentMDIForm()
        {
            InitializeComponent();
        }

        private void createToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _lastChildFormNumber++;
      

            ChildMDIForm childMDIForm = new ChildMDIForm();
            childMDIForm.MdiParent = this;            
            childMDIForm.Show();
            childMDIForm.InitView();
            childMDIForm.InitV3D();
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
    }
}
