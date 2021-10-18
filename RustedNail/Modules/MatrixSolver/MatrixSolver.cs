using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RustedNail.Modules.MatrixSolver
{
    public class MatrixSolver : ProgramModule
    {
        //здесь создайте поля для ваших форм, с модификатором доступа private
        private MainForm_MatrixSolver mainForm;

        public void Load(ParentMDIForm parentMDIForm)
        {
            //здесь пишите ваш доп. код для подгрузки (инициализация форм, их заголовок и т.п.)
            //Обязательно каждую форму добавьте в коллекцию форм formCollection!

            parentForm = parentMDIForm;
            mainForm = new MainForm_MatrixSolver();
            mainForm.MdiParent = parentMDIForm;
            mainForm.Text = "Matrix Solver";
            mainForm.Show();


            formCollection.Add(mainForm);
            ChangeToolStripSettings(parentMDIForm);
        }

        private void ChangeToolStripSettings(ParentMDIForm parentMDIForm)
        {
            InitialiseToolStrip(parentMDIForm);

            //здесь пишите ваш код для настройки ToolStrip (добавление кнопок и т.п.)
            //первым ToolStripItem'ом должен быть Label с названием вашего модуля
            ToolStripLabel toolStripItem1Label = new ToolStripLabel();
            toolStripItem1Label.Text = "Matrix Solver";

            ToolStripItem toolStripItem2PlayButton = new ToolStripMenuItem();
            toolStripItem2PlayButton.Name = "PlayButton";
            toolStripItem2PlayButton.Click += toolStripItem2PlayButton_Click; 
            toolStripItem2PlayButton.Image = Image.FromFile(@"..\..\RustedNail\Modules\MatrixSolver\Icons\Play.png");
            toolStripItem2PlayButton.ToolTipText = "Play";

            ToolStripItem toolStripItem3StopButton = new ToolStripMenuItem();
            toolStripItem3StopButton.Name = "StopButton";
            toolStripItem3StopButton.Click += toolStripItem3StopButton_Click;
            toolStripItem3StopButton.Image = Image.FromFile(@"..\..\RustedNail\Modules\MatrixSolver\Icons\Stop.png");
            toolStripItem3StopButton.ToolTipText = "Stop";

            ToolStripItem toolStripItem4PasteButton = new ToolStripMenuItem();
            toolStripItem4PasteButton.Name = "PasteButton";
            toolStripItem4PasteButton.Click += toolStripItem4PasteButton_Click;
            toolStripItem4PasteButton.Image = Image.FromFile(@"..\..\RustedNail\Modules\MatrixSolver\Icons\Paste.png");
            toolStripItem4PasteButton.ToolTipText = "Paste";

            ToolStripItem toolStripItem5ExportButton = new ToolStripMenuItem();
            toolStripItem5ExportButton.Name = "ExportButton";
            toolStripItem5ExportButton.Click += toolStripItem5ExportButton_Click;
            toolStripItem5ExportButton.Image = Image.FromFile(@"..\..\RustedNail\Modules\MatrixSolver\Icons\Export.png");
            toolStripItem5ExportButton.ToolTipText = "Export";

            toolStrip.Items.Add(toolStripItem1Label);
            toolStrip.Items.Add(toolStripItem2PlayButton);
            toolStrip.Items.Add(toolStripItem3StopButton);
            toolStrip.Items.Add(toolStripItem4PasteButton);
            toolStrip.Items.Add(toolStripItem5ExportButton);
        }

        private void toolStripItem3StopButton_Click(object sender, EventArgs e)
        {
            
        }

        private void toolStripItem5ExportButton_Click(object sender, EventArgs e)
        {
            
        }

        private void toolStripItem4PasteButton_Click(object sender, EventArgs e)
        {
            
        }

        private void toolStripItem2PlayButton_Click(object sender, EventArgs e)
        {
            
        }

    }
}
