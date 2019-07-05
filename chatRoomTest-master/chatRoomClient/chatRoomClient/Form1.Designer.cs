namespace chatRoomClient
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.lbMsg = new System.Windows.Forms.Label();
            this.txtName = new System.Windows.Forms.TextBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.txtReceiveMsg = new System.Windows.Forms.TextBox();
            this.txtSendMsg = new System.Windows.Forms.TextBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.labelIP = new System.Windows.Forms.Label();
            this.txtIP = new System.Windows.Forms.TextBox();
            this.btnBreak = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbMsg
            // 
            this.lbMsg.AutoSize = true;
            this.lbMsg.Font = new System.Drawing.Font("宋体", 10F);
            this.lbMsg.Location = new System.Drawing.Point(6, 22);
            this.lbMsg.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lbMsg.Name = "lbMsg";
            this.lbMsg.Size = new System.Drawing.Size(133, 14);
            this.lbMsg.TabIndex = 0;
            this.lbMsg.Text = "请设置你的用户名：";
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(131, 15);
            this.txtName.Margin = new System.Windows.Forms.Padding(2);
            this.txtName.Multiline = true;
            this.txtName.Name = "txtName";
            this.txtName.ShortcutsEnabled = false;
            this.txtName.Size = new System.Drawing.Size(151, 25);
            this.txtName.TabIndex = 1;
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(300, 15);
            this.btnConnect.Margin = new System.Windows.Forms.Padding(2);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(75, 24);
            this.btnConnect.TabIndex = 2;
            this.btnConnect.Text = "连接服务器";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // txtReceiveMsg
            // 
            this.txtReceiveMsg.Location = new System.Drawing.Point(32, 62);
            this.txtReceiveMsg.Margin = new System.Windows.Forms.Padding(2);
            this.txtReceiveMsg.Multiline = true;
            this.txtReceiveMsg.Name = "txtReceiveMsg";
            this.txtReceiveMsg.ReadOnly = true;
            this.txtReceiveMsg.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtReceiveMsg.Size = new System.Drawing.Size(369, 175);
            this.txtReceiveMsg.TabIndex = 3;
            this.txtReceiveMsg.TextChanged += new System.EventHandler(this.txtReceiveMsg_TextChanged);
            // 
            // txtSendMsg
            // 
            this.txtSendMsg.AcceptsReturn = true;
            this.txtSendMsg.Location = new System.Drawing.Point(32, 259);
            this.txtSendMsg.Margin = new System.Windows.Forms.Padding(2);
            this.txtSendMsg.Multiline = true;
            this.txtSendMsg.Name = "txtSendMsg";
            this.txtSendMsg.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtSendMsg.Size = new System.Drawing.Size(369, 75);
            this.txtSendMsg.TabIndex = 4;
            // 
            // btnSend
            // 
            this.btnSend.Location = new System.Drawing.Point(45, 359);
            this.btnSend.Margin = new System.Windows.Forms.Padding(2);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(116, 35);
            this.btnSend.TabIndex = 5;
            this.btnSend.Text = "发送";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // labelIP
            // 
            this.labelIP.AutoSize = true;
            this.labelIP.Font = new System.Drawing.Font("宋体", 10F);
            this.labelIP.Location = new System.Drawing.Point(399, 22);
            this.labelIP.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelIP.Name = "labelIP";
            this.labelIP.Size = new System.Drawing.Size(154, 14);
            this.labelIP.TabIndex = 6;
            this.labelIP.Text = "请输入服务器IP(可选):";
            // 
            // txtIP
            // 
            this.txtIP.Location = new System.Drawing.Point(554, 15);
            this.txtIP.Margin = new System.Windows.Forms.Padding(2);
            this.txtIP.Multiline = true;
            this.txtIP.Name = "txtIP";
            this.txtIP.Size = new System.Drawing.Size(135, 25);
            this.txtIP.TabIndex = 7;
            // 
            // btnBreak
            // 
            this.btnBreak.Location = new System.Drawing.Point(241, 359);
            this.btnBreak.Margin = new System.Windows.Forms.Padding(2);
            this.btnBreak.Name = "btnBreak";
            this.btnBreak.Size = new System.Drawing.Size(116, 34);
            this.btnBreak.TabIndex = 8;
            this.btnBreak.Text = "退出聊天";
            this.btnBreak.UseVisualStyleBackColor = true;
            this.btnBreak.Click += new System.EventHandler(this.btnBreak_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(698, 439);
            this.Controls.Add(this.btnBreak);
            this.Controls.Add(this.txtIP);
            this.Controls.Add(this.labelIP);
            this.Controls.Add(this.btnSend);
            this.Controls.Add(this.txtSendMsg);
            this.Controls.Add(this.txtReceiveMsg);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.txtName);
            this.Controls.Add(this.lbMsg);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Form1";
            this.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "聊天程序";
            this.Activated += new System.EventHandler(this.Form1_Activated);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbMsg;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.TextBox txtReceiveMsg;
        private System.Windows.Forms.TextBox txtSendMsg;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.Label labelIP;
        private System.Windows.Forms.TextBox txtIP;
        private System.Windows.Forms.Button btnBreak;
    }
}

