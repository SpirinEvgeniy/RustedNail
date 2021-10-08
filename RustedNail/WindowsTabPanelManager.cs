using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RustedNail
{
    public class WindowsTabPanelManager
    {
        public TabControl tabControl;
        public ParentMDIForm parentMDIForm { get; private set; }

        public WindowsTabPanelManager(ParentMDIForm parentMDI)
        {
            tabControl = new TabControl();
            tabControl.Parent = parentMDI;
            tabControl.Dock = DockStyle.Fill;
            tabControl.Visible = false;
            parentMDIForm = parentMDI;
        }

        public void MakeActive() //Включить режим панели
        {
            tabControl.Visible = true;
            for (int i = 0; i < parentMDIForm.MdiChildren.Count()-1; i++)
            {
                tabControl.TabPages.Add($"window{i + 1}");
            }

            //здесь должен быть код занесения всех форм во вкладки панели
        }

        public void MakeInactive() //Выключить режим панели (переключиться режим окон)
        {
            //здесь должен быть код переключения в режим окон
            tabControl.TabPages.Clear();
            tabControl.Visible = false;
        }
    }
}
