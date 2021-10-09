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
        private TabControl tabControl;
        private ParentMDIForm parentMDIForm { get; set; }
        private List<ChildMDIForm> childMDIForms; 

        public WindowsTabPanelManager(ParentMDIForm parentMDI)
        {
            tabControl = new TabControl();
            tabControl.Parent = parentMDI;
            tabControl.Dock = DockStyle.Fill;
            tabControl.Visible = false;
            parentMDIForm = parentMDI;

            childMDIForms = new List<ChildMDIForm>();

            foreach (ChildMDIForm childForm in parentMDI.MdiChildren)
            {
                childMDIForms.Add(childForm);
            }
        }

        public void MakeActive() //Включить режим панели
        {
            int counter = 0;

            tabControl.Visible = true;
            tabControl.BringToFront();

            for (int i = 0; i < parentMDIForm.MdiChildren.Count(); i++)
            {
                tabControl.TabPages.Add($"window{i + 1}");
            }

            foreach (var child in parentMDIForm.MdiChildren)
            {
                child.Parent = tabControl.TabPages[counter];
                child.FormBorderStyle = FormBorderStyle.None;
                child.Dock = DockStyle.Fill;
                counter++;
            }
        }

        public void MakeInactive() //Выключить режим панели (переключиться режим окон)
        {
            foreach (ChildMDIForm childForm in childMDIForms)
            {
                childForm.MdiParent = parentMDIForm;
                childForm.Dock = DockStyle.None;
                childForm.FormBorderStyle = FormBorderStyle.Sizable;
            }
            tabControl.TabPages.Clear();
            tabControl.Visible = false;
            parentMDIForm.LayoutMdi(MdiLayout.TileVertical);
            int c = parentMDIForm.MdiChildren.Count();
        }
    }
}
