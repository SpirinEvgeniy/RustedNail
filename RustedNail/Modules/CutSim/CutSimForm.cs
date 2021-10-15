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
    public partial class CutSimForm : RustedNail.ChildMDIForm
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
    }
}
