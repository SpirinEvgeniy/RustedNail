
namespace RustedNail
{
    partial class ChildMDIForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        /// 

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // ChildMDIForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Name = "ChildMDIForm";
            this.Text = "ChildMDIForm";
            this.SizeChanged += new System.EventHandler(this.ChildMDIForm_SizeChanged);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.ChildMDIForm_Paint);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ChildMDIForm_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.ChildMDIForm_KeyUp);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ChildMDIForm_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ChildMDIForm_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ChildMDIForm_MouseUp);
            this.ResumeLayout(false);

        }

        #endregion
    }
}