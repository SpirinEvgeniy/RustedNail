using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RustedNail
{
    public class ProgramModule
    {
        public ToolStrip toolStrip;
        public ParentMDIForm parentForm;
        public List<Form> formCollection = new List<Form>();

        public void InitialiseToolStrip(ParentMDIForm parentMDIForm)
        {
            toolStrip = new ToolStrip();
            parentMDIForm.Controls.Add(toolStrip);
            toolStrip.BackColor = System.Drawing.Color.FromArgb(213, 213, 213);
            //toolStrip.Dock = DockStyle.None;
            parentMDIForm.toolStripPanel1.Controls.Add(toolStrip);
            //toolStrip.Anchor = AnchorStyles.None;
            toolStrip.AutoSize = true;
            toolStrip.Show();

            ToolStripItem toolStripItemCloseButton = new ToolStripMenuItem();
            toolStripItemCloseButton.Name = "CloseButton";
            toolStripItemCloseButton.Click += toolStripItemCloseButton_Click;
            toolStripItemCloseButton.Image = Image.FromFile(@"..\..\RustedNail\Res\CloseIcon.png");
            toolStripItemCloseButton.ToolTipText = "Close";
            toolStripItemCloseButton.Alignment = ToolStripItemAlignment.Right;
            toolStrip.Items.Add(toolStripItemCloseButton);
        }

        public void toolStripItemCloseButton_Click(object sender, EventArgs e)
        {
            parentForm.toolStripPanel1.Controls.Remove(toolStrip);

            foreach (Form form in formCollection)
            {
                form.Close();
            }
        }
    }
}
