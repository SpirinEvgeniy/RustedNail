using System;
using System.Collections.Generic;
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
        }
    }
}
