
namespace RustedNail
{
    partial class ParentMDIForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ParentMDIForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.createToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cascadeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.horizontalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.verticalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.modulesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.matrixSolverToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cutSimToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip_OCCT_examples = new System.Windows.Forms.ToolStrip();
            this.toolStripRunButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripExampleIDTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripPanel1 = new System.Windows.Forms.ToolStripPanel();
            this.toolStripPanel4 = new System.Windows.Forms.ToolStripPanel();
            this.roMonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.toolStrip_OCCT_examples.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.AllowMerge = false;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.windowsToolStripMenuItem,
            this.modulesToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1184, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.createToolStripMenuItem,
            this.openToolStripMenuItem,
            this.closeToolStripMenuItem,
            this.closeAllToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(37, 20);
            this.toolStripMenuItem1.Text = "File";
            // 
            // createToolStripMenuItem
            // 
            this.createToolStripMenuItem.Name = "createToolStripMenuItem";
            this.createToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.createToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.createToolStripMenuItem.Text = "Create";
            this.createToolStripMenuItem.Click += new System.EventHandler(this.createToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.openToolStripMenuItem.Text = "Open";
            // 
            // closeToolStripMenuItem
            // 
            this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
            this.closeToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.closeToolStripMenuItem.Text = "Close";
            this.closeToolStripMenuItem.Click += new System.EventHandler(this.closeToolStripMenuItem_Click);
            // 
            // closeAllToolStripMenuItem
            // 
            this.closeAllToolStripMenuItem.Name = "closeAllToolStripMenuItem";
            this.closeAllToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.closeAllToolStripMenuItem.Text = "Close All";
            this.closeAllToolStripMenuItem.Click += new System.EventHandler(this.closeAllToolStripMenuItem_Click);
            // 
            // windowsToolStripMenuItem
            // 
            this.windowsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cascadeToolStripMenuItem,
            this.horizontalToolStripMenuItem,
            this.verticalToolStripMenuItem});
            this.windowsToolStripMenuItem.Name = "windowsToolStripMenuItem";
            this.windowsToolStripMenuItem.Size = new System.Drawing.Size(68, 20);
            this.windowsToolStripMenuItem.Text = "Windows";
            // 
            // cascadeToolStripMenuItem
            // 
            this.cascadeToolStripMenuItem.Name = "cascadeToolStripMenuItem";
            this.cascadeToolStripMenuItem.Size = new System.Drawing.Size(129, 22);
            this.cascadeToolStripMenuItem.Text = "Cascade";
            this.cascadeToolStripMenuItem.Click += new System.EventHandler(this.cascadeToolStripMenuItem_Click);
            // 
            // horizontalToolStripMenuItem
            // 
            this.horizontalToolStripMenuItem.Name = "horizontalToolStripMenuItem";
            this.horizontalToolStripMenuItem.Size = new System.Drawing.Size(129, 22);
            this.horizontalToolStripMenuItem.Text = "Horizontal";
            this.horizontalToolStripMenuItem.Click += new System.EventHandler(this.horizontalToolStripMenuItem_Click);
            // 
            // verticalToolStripMenuItem
            // 
            this.verticalToolStripMenuItem.Name = "verticalToolStripMenuItem";
            this.verticalToolStripMenuItem.Size = new System.Drawing.Size(129, 22);
            this.verticalToolStripMenuItem.Text = "Vertical";
            this.verticalToolStripMenuItem.Click += new System.EventHandler(this.verticalToolStripMenuItem_Click);
            // 
            // modulesToolStripMenuItem
            // 
            this.modulesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.matrixSolverToolStripMenuItem,
            this.cutSimToolStripMenuItem,
            this.roMonToolStripMenuItem});
            this.modulesToolStripMenuItem.Name = "modulesToolStripMenuItem";
            this.modulesToolStripMenuItem.Size = new System.Drawing.Size(65, 20);
            this.modulesToolStripMenuItem.Text = "Modules";
            // 
            // matrixSolverToolStripMenuItem
            // 
            this.matrixSolverToolStripMenuItem.Name = "matrixSolverToolStripMenuItem";
            this.matrixSolverToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.matrixSolverToolStripMenuItem.Text = "Matrix solver";
            this.matrixSolverToolStripMenuItem.Click += new System.EventHandler(this.matrixSolverToolStripMenuItem_Click);
            // 
            // cutSimToolStripMenuItem
            // 
            this.cutSimToolStripMenuItem.Name = "cutSimToolStripMenuItem";
            this.cutSimToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.cutSimToolStripMenuItem.Text = "CutSim";
            this.cutSimToolStripMenuItem.Click += new System.EventHandler(this.cutSimToolStripMenuItem_Click);
            // 
            // toolStrip_OCCT_examples
            // 
            this.toolStrip_OCCT_examples.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.toolStrip_OCCT_examples.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripRunButton,
            this.toolStripExampleIDTextBox,
            this.toolStripLabel1});
            this.toolStrip_OCCT_examples.Location = new System.Drawing.Point(0, 636);
            this.toolStrip_OCCT_examples.Name = "toolStrip_OCCT_examples";
            this.toolStrip_OCCT_examples.Size = new System.Drawing.Size(1184, 25);
            this.toolStrip_OCCT_examples.TabIndex = 4;
            this.toolStrip_OCCT_examples.Text = "toolStrip1";
            // 
            // toolStripRunButton
            // 
            this.toolStripRunButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripRunButton.Image = ((System.Drawing.Image)(resources.GetObject("toolStripRunButton.Image")));
            this.toolStripRunButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripRunButton.Name = "toolStripRunButton";
            this.toolStripRunButton.Size = new System.Drawing.Size(23, 22);
            this.toolStripRunButton.Text = "Запустить пример";
            this.toolStripRunButton.Click += new System.EventHandler(this.toolStripRunButton_Click);
            // 
            // toolStripExampleIDTextBox
            // 
            this.toolStripExampleIDTextBox.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.toolStripExampleIDTextBox.Name = "toolStripExampleIDTextBox";
            this.toolStripExampleIDTextBox.Size = new System.Drawing.Size(40, 25);
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(89, 22);
            this.toolStripLabel1.Text = "1-37 примеров";
            // 
            // toolStripPanel1
            // 
            this.toolStripPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.toolStripPanel1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.toolStripPanel1.Location = new System.Drawing.Point(0, 24);
            this.toolStripPanel1.Name = "toolStripPanel1";
            this.toolStripPanel1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.toolStripPanel1.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.toolStripPanel1.Size = new System.Drawing.Size(1184, 25);
            // 
            // toolStripPanel4
            // 
            this.toolStripPanel4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.toolStripPanel4.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.toolStripPanel4.Location = new System.Drawing.Point(0, 611);
            this.toolStripPanel4.Name = "toolStripPanel4";
            this.toolStripPanel4.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.toolStripPanel4.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.toolStripPanel4.Size = new System.Drawing.Size(1184, 25);
            // 
            // roMonToolStripMenuItem
            // 
            this.roMonToolStripMenuItem.Name = "roMonToolStripMenuItem";
            this.roMonToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.roMonToolStripMenuItem.Text = "RoMon";
            this.roMonToolStripMenuItem.Click += new System.EventHandler(this.roMonToolStripMenuItem_Click);
            // 
            // ParentMDIForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1184, 661);
            this.Controls.Add(this.toolStripPanel4);
            this.Controls.Add(this.toolStripPanel1);
            this.Controls.Add(this.toolStrip_OCCT_examples);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "ParentMDIForm";
            this.Text = "RustedNail";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip_OCCT_examples.ResumeLayout(false);
            this.toolStrip_OCCT_examples.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem createToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem windowsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cascadeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem horizontalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem verticalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeAllToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip_OCCT_examples;
        private System.Windows.Forms.ToolStripButton toolStripRunButton;
        private System.Windows.Forms.ToolStripTextBox toolStripExampleIDTextBox;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripMenuItem modulesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem matrixSolverToolStripMenuItem;
        public System.Windows.Forms.ToolStripPanel toolStripPanel1;
        public System.Windows.Forms.ToolStripPanel toolStripPanel4;
        private System.Windows.Forms.ToolStripMenuItem cutSimToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem roMonToolStripMenuItem;
    }
}

