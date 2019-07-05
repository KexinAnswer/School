using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace chatRoomClient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            ipadr = IPAddress.Loopback;
        }

        Socket clientSocket = null;
        static Boolean isListen = true;
        Thread thDataFromServer;
        IPAddress ipadr;

        private void btnSend_Click(object sender, EventArgs e)
        {
            SendMessage();
        }
        private void SendMessage()
        {
            if (String.IsNullOrWhiteSpace(txtSendMsg.Text.Trim()))
            {
                MessageBox.Show("发送内容不能为空哦~");
                return;
            }
            if (clientSocket != null && clientSocket.Connected)
            {
                Byte[] bytesSend = Encoding.UTF8.GetBytes(txtSendMsg.Text + "$");
                clientSocket.Send(bytesSend);
                txtSendMsg.Text  = "";
            }
            else
            {
                MessageBox.Show("未连接服务器或者服务器已停止，请联系管理员~");
                return;
            }
        }


       
        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(txtName.Text.Trim()))
            {
                MessageBox.Show("请设置个用户名哦亲");
                return;
            }
            if (txtName.Text.Length>=17 && txtName.Text.ToString().Trim().Substring(0, 17).Equals("Server has closed"))
            {
                MessageBox.Show("该用户名中包含敏感词，请更换用户名后重试");
                return;
            }

            if (clientSocket == null || !clientSocket.Connected)
            {
                try
                {
                    clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    
                    if (!String.IsNullOrWhiteSpace(txtIP.Text.ToString().Trim()))
                    {
                        try
                        {
                            ipadr = IPAddress.Parse(txtIP.Text.ToString().Trim());
                        }
                        catch
                        {
                            MessageBox.Show("请输入正确的IP后重试");
                            return;
                        }
                    }
                    else
                    {
                        ipadr = IPAddress.Loopback;
                    }
                    //IPAddress ipadr = IPAddress.Parse("192.168.1.100");
                    clientSocket.BeginConnect(ipadr, 8080, (args) =>
                    {
                        if (args.IsCompleted)   //判断该异步操作是否执行完毕
                        {
                            Byte[] bytesSend = new Byte[4096];
                            txtName.BeginInvoke(new Action(() =>
                            {
                                bytesSend = Encoding.UTF8.GetBytes(txtName.Text.Trim() + "$");  //用户名，这里是刚刚连接上时需要传过去
                                if (clientSocket != null && clientSocket.Connected)
                                {
                                    clientSocket.Send(bytesSend);
                                    txtName.Enabled = false;    //设置为不能再改名字了
                                    txtSendMsg.Focus();         //将焦点放在
                                    thDataFromServer = new Thread(DataFromServer);
                                    thDataFromServer.IsBackground = true;
                                    thDataFromServer.Start();
                                }
                                else
                                {
                                    MessageBox.Show("服务器已关闭");
                                }

                            }));
                            txtIP.BeginInvoke(new Action(() =>
                            {
                                if (clientSocket != null && clientSocket.Connected)
                                {
                                    txtIP.Enabled = false;
                                }
                            }));
                        }
                    },null);
                }
                catch (SocketException ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
            else
            {
                MessageBox.Show("你已经连接上服务器了");
            }
        }

        private void ShowMsg(String msg)
        {
            txtReceiveMsg.BeginInvoke(new Action(() =>
            {
                txtReceiveMsg.Text += Environment.NewLine + msg;    // 在 Windows 环境中，C# 语言 Environment.NewLine == "\r\n" 结果为 true
            
            }));
        }


        private void DataFromServer()
        {
            ShowMsg("Connected to the Chat Server...");
            isListen = true;
            try
            {
                while (isListen)
                {
                    Byte[] bytesFrom = new Byte[4096];
                    Int32 len = clientSocket.Receive(bytesFrom);

                    String dataFromClient = Encoding.UTF8.GetString(bytesFrom, 0, len);
                    if (!String.IsNullOrWhiteSpace(dataFromClient))
                    {
                        
                        if (dataFromClient.ToString().Length >=17 && dataFromClient.ToString().Substring(0, 17).Equals("Server has closed"))
                        {
                            clientSocket.Close();
                            clientSocket = null;

                            txtReceiveMsg.BeginInvoke(new Action(() =>
                            {
                                txtReceiveMsg.Text += Environment.NewLine + "服务器已关闭";
                            }));

                            txtName.BeginInvoke(new Action(() =>
                            {
                                txtName.Enabled = true;
                            }));    //重连当然可以换用户名啦

                            txtIP.BeginInvoke(new Action(() =>
                            {
                                
                                    txtIP.Enabled = true;
                                
                            }));

                            thDataFromServer.Abort();  
                          
                            return;
                        }


                        if (dataFromClient.StartsWith("#") && dataFromClient.EndsWith("#"))
                        {
                            String userName = dataFromClient.Substring(1, dataFromClient.Length - 2);
                            this.BeginInvoke(new Action(() =>
                            {
                                MessageBox.Show("用户名：[" + userName + "]已经存在，请尝试其他用户名并重试");

                            }));
                            isListen = false;

                            txtName.BeginInvoke(new Action(() =>
                            {
                                txtName.Enabled = true;
                                clientSocket.Send(Encoding.UTF8.GetBytes("$"));
                                clientSocket.Close();
                                clientSocket = null;
                            }));
                            txtIP.BeginInvoke(new Action(() =>
                            {
                                
                                    txtIP.Enabled = true;
                                
                            }));

                        }
                        else
                        {
                           
                            ShowMsg(dataFromClient);
                        }
                    }
                }
            }
            catch (SocketException ex)
            {
                isListen = false;
                if (clientSocket != null && clientSocket.Connected)
                {
                   
                    clientSocket.Send(Encoding.UTF8.GetBytes("$"));
                    MessageBox.Show(ex.ToString());
                }
            }
        }

        private void Form1_Activated(object sender, EventArgs e)
        {
            txtSendMsg.Focus();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (clientSocket != null && clientSocket.Connected)
            {
                clientSocket.Send(Encoding.UTF8.GetBytes("$"));
            }
        }

        private void btnBreak_Click(object sender, EventArgs e)
        {
            if (clientSocket != null && clientSocket.Connected)
            {
                thDataFromServer.Abort();
                clientSocket.Send(Encoding.UTF8.GetBytes("$"));

                clientSocket.Close();
                clientSocket = null;
           
                txtReceiveMsg.BeginInvoke(new Action(() =>
                {
                    txtReceiveMsg.Text += Environment.NewLine + "已断开与服务器的连接";
                    
                }));

                txtName.BeginInvoke(new Action(() =>
                {
                    txtName.Enabled = true;
                }));    //重连当然可以换用户名啦
                txtIP.BeginInvoke(new Action(() =>
                {
                    
                       txtIP.Enabled = true;
                    
                }));

                  
            }
        }

        private void txtReceiveMsg_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
