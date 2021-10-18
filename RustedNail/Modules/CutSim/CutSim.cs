using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RustedNail.Modules.CutSim
{
    public class CutSim : ProgramModule
    {
        //здесь создайте поля для ваших форм, с модификатором доступа private
        private CutSim_MainForm mainForm;

        public void Load(ParentMDIForm parentMDIForm)
        {
            parentForm = parentMDIForm;
            //здесь пишите ваш доп. код для подгрузки (инициализация форм, их заголовок и т.п.)
            //Обязательно каждую форму добавьте в коллекцию форм formCollection!
            mainForm = new CutSim_MainForm();
            mainForm.Text = "Cut Sim";
            mainForm.MdiParent = parentForm;
            mainForm.Width = 600;
            mainForm.Height = 400;
            mainForm.Show();

            formCollection.Add(mainForm);
            ChangeToolStripSettings(parentMDIForm);
        }

        private void ChangeToolStripSettings(ParentMDIForm parentMDIForm)
        {
            InitialiseToolStrip(parentMDIForm);

            //здесь пишите ваш код для настройки ToolStrip (добавление кнопок, подгрузка иконок и т.п.)
            //первым ToolStripItem'ом обязательно должен быть Label с названием вашего модуля
            //Каждый созданный item добавьте в toolStip

            ToolStripLabel toolStripItem1Label = new ToolStripLabel();
            toolStripItem1Label.Text = "Cut Sim";

            toolStrip.Items.Add(toolStripItem1Label);
        }
    }
}