using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Drawing;
using System.Windows.Forms;
// Модуль для синтеза геометрических моделей, полученных симуляция кинематики процессов резания

namespace RustedNail
{
    class CutSim: ChildMDIForm 
    {
        private TabControl tabControl;
        private TabPage tabPage1;
        private PictureBox pictureBox;


        private void CutSimTabs()
        {
            this.tabControl = new TabControl();
            this.tabPage1 = new TabPage();           

            this.tabControl.Multiline = true;
            this.tabControl.Controls.AddRange(new Control[] {this.tabPage1});
            this.tabControl.Size = new Size(450, 0);


            this.tabPage1.Text = "Парметры";            
            this.Controls.AddRange(new Control[] {this.tabControl});
            this.tabControl.Dock = DockStyle.Right;


            this.pictureBox = new PictureBox();
            this.pictureBox.Parent = this.tabPage1;
            this.pictureBox.Dock = DockStyle.Top;
            this.pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
            this.pictureBox.ClientSize = new Size(450, 250);
            this.pictureBox.Image = Image.FromFile(@"..\..\RustedNail\Modules\CutSim\Исходный контур.png");
        }
        public CutSim()
        {
            Text = "CutSim";

            CutSimTabs();

        }
    }
}
