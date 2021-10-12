using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RustedNail.Modules.MatrixSolver
{
    public class MatrixSolver : ProgramModule
    {
        private MainForm_MatrixSolver mainForm;
        public ParentMDIForm parentForm;
        public ToolStrip toolStrip;

        public void Load(ParentMDIForm parentMDIForm)
        {
            //здесь пишите ваш доп. код для подгрузки

            mainForm = new MainForm_MatrixSolver();
            mainForm.MdiParent = parentMDIForm;
            mainForm.Show();
            InitialiseToolStrip(parentMDIForm);
            parentForm = parentMDIForm;
        }

        private void InitialiseToolStrip(ParentMDIForm parentMDIForm)
        {
            toolStrip = new ToolStrip();
            toolStrip.Parent = parentMDIForm;
            toolStrip.Dock = DockStyle.Right;

            //здесь пишите ваш код для настройки ToolStrip
            //ToolStripItem item1 = new ToolStripItem();


            toolStrip.Show();
        }
    }
}
