using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Threading;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Security.Cryptography;



namespace chatRoomServer
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            ipadr = IPAddress.Loopback;
        }

        
        public static Dictionary<String, Socket> clientList = null;
      
        Socket serverSocket = null;
    
        Boolean isListen = true;

        Thread thStartListen;

        IPAddress ipadr;

        IPEndPoint endPoint;


        private void btnStart_Click(object sender, EventArgs e)
        {
            if (serverSocket == null)
            {
                try
                {
                    isListen = true;
                    clientList = new Dictionary<string, Socket>();



                   
                    serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);     //AddressFamily.InterNetwork代表IPV4地址，不包含IPV6   参考网址：http://bbs.csdn.net/topics/390283656?page=1
                    
                   
                  
                    endPoint = new IPEndPoint(ipadr, 8080);     //IPAddress.loopback是本地环回接口，其实是虚拟接口，物理不存在的  参考网址：http://baike.sogou.com/v7893363.htm?fromTitle=loopback



                    try
                    {
                        serverSocket.Bind(endPoint);



                        
                        serverSocket.Listen(100);


                        thStartListen = new Thread(StartListen);
                        thStartListen.IsBackground = true;
                        thStartListen.Start();

                       
                        txtMsg.BeginInvoke(new Action(() =>
                        {
                            txtMsg.Text += "服务启动成功...\r\n";
                        }));
                    }
                    catch (Exception eg)
                    {
                        MessageBox.Show("输入的IP地址无效，请重新输入!");
                        txtMsg.BeginInvoke(new Action(() =>
                        {
                            txtMsg.Text += "服务启动失败...\r\n";
                        }));


                        if (serverSocket != null)
                        {
                            serverSocket.Close();
                            thStartListen.Abort();  

                            BroadCast.PushMessage("Server has closed", "", false, clientList);
                            foreach (var socket in clientList.Values)
                            {
                                socket.Close();
                            }
                            clientList.Clear();

                            serverSocket = null;
                            isListen = false;
                           
                        }
                    }


                }
                catch(SocketException ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }

        }



        private  void StartListen()
        {
            isListen = true;
           
            Socket clientSocket = default(Socket);      

            while (isListen)
            {
                try
                {
                   
                    if (serverSocket == null)   
                    {
                        return;
                    }
                    clientSocket = serverSocket.Accept();   
                }
                catch (SocketException e)
                {
                    File.AppendAllText("E:\\Exception.txt", e.ToString() + "\r\nStartListen\r\n" + DateTime.Now.ToString() + "\r\n");
                }

             
                Byte[] bytesFrom = new Byte[4096];
                String dataFromClient = null;

                if (clientSocket != null && clientSocket.Connected)
                {
                    try
                    {
                       

                        Int32 len = clientSocket.Receive(bytesFrom);    

                        if (len > -1)
                        {
                            String tmp = Encoding.UTF8.GetString(bytesFrom, 0, len);  //将字节流转换成字符串
                            
                            dataFromClient = tmp;
                            Int32 sublen = dataFromClient.LastIndexOf("$");
                            if (sublen > -1)
                            {
                                dataFromClient = dataFromClient.Substring(0, sublen);   //获取用户名

                                if (!clientList.ContainsKey(dataFromClient))
                                {
                                    clientList.Add(dataFromClient, clientSocket);   //如果用户名不存在，则添加用户名进去

                                   
                                    BroadCast.PushMessage(dataFromClient + "Joined", dataFromClient, false, clientList);

                                    //HandleClient也是一个自己定义的类，用来负责接收客户端发来的消息并转发给所有的客户端
                                    //StartClient(Socket inClientSocket, String clientNo, Dictionary<String, Socket> cList)
                                    HandleClient client = new HandleClient(txtMsg);

                                    client.StartClient(clientSocket, dataFromClient, clientList);

                                    txtMsg.BeginInvoke(new Action(() =>
                                    {
                                        txtMsg.Text += dataFromClient + "连接上了服务器\r" + DateTime.Now + "\r\n";
                                    }));
                                }
                                else
                                {
                                    //用户名已经存在
                                    clientSocket.Send(Encoding.UTF8.GetBytes("#" + dataFromClient + "#"));
                                }
                            }
                        }
                    }
                    catch (Exception ep)
                    {
                        File.AppendAllText("E:\\Exception.txt", ep.ToString() + "\r\n\t\t" + DateTime.Now.ToString() + "\r\n");
                    }



                }
            }

        }


    





        private void btnStop_Click(object sender, EventArgs e)
        {
            if (serverSocket != null)
            {
                serverSocket.Close();
                thStartListen.Abort();  //将监听进程关掉
                
                BroadCast.PushMessage("Server has closed", "", false, clientList);
                foreach (var socket in clientList.Values)
                {
                    socket.Close();
                }
                clientList.Clear();
                
                serverSocket = null;
                isListen = false;
                txtMsg.Text += "服务停止，断开所有客户端连接\t"+DateTime.Now.ToString()+"\r\n";
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                clientList = new Dictionary<string, Socket>();
                serverSocket = new Socket(AddressFamily.InterNetwork,SocketType.Stream,ProtocolType.Tcp);//实例，监听套接字
                //IPAddress ipadr = IPAddress.Parse("192.168.1.100");
         
                endPoint = new IPEndPoint(ipadr,8080);//端点
                serverSocket.Bind(endPoint);//绑定
                serverSocket.Listen(100);   //设置最大连接数
                thStartListen = new Thread(StartListen);
                thStartListen.IsBackground = true;
                thStartListen.Start();
                txtMsg.BeginInvoke(new Action(() =>
                {
                    txtMsg.Text += "服务启动成功...\r\n";
                }
                ));
                labIPnow.BeginInvoke(new Action(() => {
                    labIPnow.Text = endPoint.Address.ToString();
                }));
            }
            catch (SocketException ep)
            {
                MessageBox.Show(ep.ToString());
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serverSocket != null)
            {
                BroadCast.PushMessage("Server has closed", "", false, clientList);
                foreach (var socket in clientList.Values)
                {
                    socket.Close();
                }
                clientList.Clear();
                serverSocket.Close();
                serverSocket = null;
                isListen = false;
                txtMsg.Text += "服务停止\r\n";
            }

        }

        //重置监听的IP地址
        private void btnResetIp_Click(object sender, EventArgs e)
        {
            
                //如果txtIP里面有值，就选择填入的IP作为服务器IP，不填的话就默认是本机的
                if (!String.IsNullOrWhiteSpace(txtIP.Text.ToString().Trim()))
                {
                    try
                    {
                        ipadr = IPAddress.Parse(txtIP.Text.ToString().Trim());
                        btnStop_Click(sender, e);
                        txtMsg.BeginInvoke(new Action(() =>
                        {
                            txtMsg.Text += "服务器重启中，请稍候...\r\n";
                        }));

                        btnStart_Click(sender, e);


                        labIPnow.BeginInvoke(new Action(() =>
                        {
                            labIPnow.Text = endPoint.Address.ToString();
                        }));
                    }
                    catch (Exception ep)
                    {
                        MessageBox.Show("请输入正确的IP后重试");
                    }
                }
                else
                {
                    MessageBox.Show("请输入重置后的IP地址后重试！");
                }
            
            
        }

        private void btnRcv_Click(object sender, EventArgs e)
        {
            if (ipadr == IPAddress.Loopback)
            {
                MessageBox.Show("当前已经处于默认状态，无需修改");
            }
            else
            {
                ipadr = IPAddress.Loopback;
                btnStop_Click(sender, e);
                txtMsg.BeginInvoke(new Action(() =>
                {
                    txtMsg.Text += "服务器重启中，请稍候...\r\n";
                }));
                btnStart_Click(sender, e);
                labIPnow.BeginInvoke(new Action(() =>
                {
                    labIPnow.Text = endPoint.Address.ToString();
                }));
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtMsg.BeginInvoke(new Action(() =>
            {
                txtMsg.Text = "-----------已清屏-----------\r\n";
            }));
        }

        private void txtMsg_TextChanged(object sender, EventArgs e)
        {

        }
    }



    public class HandleClient
    {
        Socket clientSocket;
        String clNo;
        Dictionary<String, Socket> clientList = new Dictionary<string, Socket>();
        TextBox txtMsg;
        public HandleClient() { }
        public HandleClient(TextBox tb) 
        {
            txtMsg = tb;
        }

        
        public void StartClient(Socket inClientSocket, String clientNo, Dictionary<String, Socket> cList)
        {
            clientSocket = inClientSocket;
            clNo = clientNo;
            clientList = cList;

            Thread th = new Thread(Chat);
            th.IsBackground = true;
            th.Start();
        }

        private void Chat()
        {
            Byte[] bytesFromClient = new Byte[4096];
            String dataFromClient;
            String msgTemp = null;
            Byte[] bytesSend = new Byte[4096];
            Boolean isListen = true;

            while (isListen)
            {
                try
                {
                    if (clientSocket == null || !clientSocket.Connected)
                    {
                        return;
                    }
                    if (clientSocket.Available > 0)
                    {
                        Int32 len = clientSocket.Receive(bytesFromClient);
                        if (len > -1)
                        {
                            dataFromClient = Encoding.UTF8.GetString(bytesFromClient, 0, len);
                            if (!String.IsNullOrWhiteSpace(dataFromClient))
                            {
                                dataFromClient = dataFromClient.Substring(0, dataFromClient.LastIndexOf("$"));   //这里的dataFromClient是消息内容，上面的是用户名
                                if (!String.IsNullOrWhiteSpace(dataFromClient))
                                {
                                    BroadCast.PushMessage(dataFromClient, clNo, true, clientList);
                                    msgTemp = clNo + ":" + dataFromClient + "\t\t" + DateTime.Now.ToString();
                                    String newMsg = msgTemp;
                                    File.AppendAllText("E:\\MessageRecords.txt", newMsg + "\r\n", Encoding.UTF8);
                                }
                                else
                                {
                                    isListen = false;
                                    clientList.Remove(clNo);
                                    txtMsg.BeginInvoke(new Action(() =>
                                    {
                                        txtMsg.Text += clNo+ "已断开与服务器连接\r" + DateTime.Now + "\r\n";
                                    }));
                                    BroadCast.PushMessage(clNo + "已下线\r","",false,clientList);
                                    clientSocket.Close();
                                    clientSocket = null;
                                }
                            }

                        }
                    }
                }
                catch (Exception e)
                {
                    isListen = false;
                    clientList.Remove(clNo);

                    
                    clientSocket.Close();
                    clientSocket = null;
                    File.AppendAllText("E:\\Exception.txt",e.ToString()+"\r\nChat\r\n"+DateTime.Now.ToString()+"\r\n");
                }
            }

        }

    }

    //向所有客户端发送信息
    public class BroadCast
    {
        //flag是用来判断传进来的msg前面是否需要加上uName:，也就是判断是不是系统信息，是系统信息的话就设置flag为false
        public static void PushMessage(String msg, String uName, Boolean flag, Dictionary<String, Socket> clientList)
        {
            foreach (var item in clientList)
            {
                Socket brdcastSocket = (Socket)item.Value;
                String msgTemp = null;
                Byte[] castBytes = new Byte[4096];
                if (flag == true)
                {
                    msgTemp = uName + ":" + msg + "\t\t" + DateTime.Now.ToString();
                    castBytes = Encoding.UTF8.GetBytes(msgTemp);
                }
                else
                {
                    msgTemp = msg + "\t\t" + DateTime.Now.ToString();
                    castBytes = Encoding.UTF8.GetBytes(msgTemp);
                }
                try
                {
                    brdcastSocket.Send(castBytes);
                }
                catch (Exception e)
                {
                    brdcastSocket.Close();
                    brdcastSocket = null;
                    File.AppendAllText("E:\\Exception.txt",e.ToString()+"\r\nPushMessage\r\n"+DateTime.Now.ToString()+"\r\n");
                    continue;
                }
            }
        }
    }

}
