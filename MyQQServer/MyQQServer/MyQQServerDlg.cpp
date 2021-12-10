﻿
// MyQQServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MyQQServer.h"
#include "MyQQServerDlg.h"
#include "afxdialogex.h"
#include "CMsg.h"
#include "CCSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyQQServerDlg 对话框



CMyQQServerDlg::CMyQQServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYQQSERVER_DIALOG, pParent)
	, listen_port(0)
{
	listen_port = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pLSocket = NULL;
}

void CMyQQServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, user_list);
	DDX_Control(pDX, IDC_LIST_MSG, msg_list);
	DDX_Control(pDX, IDC_BUTTON_ON, start_btn);
	DDX_Control(pDX, IDC_BUTTON_OFF, end_btn);
	DDX_Text(pDX, IDC_EDIT_PORT, listen_port);
	DDX_Control(pDX, IDC_NUM, user_num);
}

BEGIN_MESSAGE_MAP(CMyQQServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ON, &CMyQQServerDlg::OnBnClickedButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &CMyQQServerDlg::OnBnClickedButtonOff)
END_MESSAGE_MAP()


// CMyQQServerDlg 消息处理程序

BOOL CMyQQServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	listen_port = 8000;
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyQQServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyQQServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyQQServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyQQServerDlg::OnBnClickedButtonOn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);    //获得用户输入
	//创建侦听套接字对象
	m_pLSocket = new CLSocket(this);
	//创建监听套接字的底层套接字，在用户指定的端口上侦听
	if (!m_pLSocket->Create(listen_port))
	{
		delete m_pLSocket;   //错误处理
		m_pLSocket = NULL;
		AfxMessageBox("创建监听套接字错误");
		return;
	}
	//启动监听套接字，时刻准备接收客户端的连接请求
	if (!m_pLSocket->Listen())
	{
		delete m_pLSocket;   //错误处理
		m_pLSocket = NULL;
		AfxMessageBox("启动监听错误");
		return;
	}
	msg_list.AddString("启动！");
}


void CMyQQServerDlg::OnBnClickedButtonOff()
{
	// TODO: 在此添加控件通知处理程序代码
	CMsg  msg;
	msg.m_strText = "服务器终止服务!";
	//
	delete m_pLSocket;
	m_pLSocket = NULL;
	//对连接列表进行处理
	while (!m_connList.IsEmpty())
	{
		//向每一个连接的客户机发送"服务器终止服务！"的消息
		//并逐个删除已建立的连接
		CCSocket* pSocket
			= (CCSocket*)m_connList.RemoveHead();
		pSocket->sendMessage(&msg);
		delete pSocket;
	}
	CString strTemp="服务器未开启";
	user_num.SetWindowText(strTemp);
	UpdateData(TRUE);
	//CDialog::OnOK();
	//清除列表框
	//while (msg_list.GetCount() != 0)
		//msg_list.DeleteString(0);

	msg_list.AddString("服务器已关闭！！");

}


void CMyQQServerDlg::OnAccept() {
	//创建用于与客户端连接并交换数据的套接字对象
	CCSocket* pSocket = new CCSocket(this);
	if (m_pLSocket->Accept(*pSocket))  //接受客户的连接请求
	{
		//对连接套接字初始化
		pSocket->Initialize();
		m_connList.AddTail(pSocket);
		// user_list.AddString
		//更新在线人数
		CString strTemp;
		strTemp.Format("在线人数：%d", m_connList.GetCount());
		user_num.SetWindowText(strTemp);
	}
	else delete pSocket;

}

void CMyQQServerDlg::OnReceive(CCSocket* pSocket) {
	static CMsg  msg;
	 AfxMessageBox("receive");
	do {
		//接收客户发来的消息
		pSocket->ReceiveMessage(&msg);
		if (msg.m_bClose == 0) {
			//将客户的信息显示在服务器的对话框中
			user_list.AddString(msg.m_strText);
			//向所有客户返回该客户发来的消息
			msg.m_strText = msg.m_strText + "已连接...";
			msg_list.AddString(msg.m_strText);
			backClients(&msg);
		}
		//如果客户机关闭,将与该客户机的连接从连接列表中删除
		else if (msg.m_bClose == 1) {
			AfxMessageBox("www");
			msg_list.AddString(msg.recv_name);
			backClients(&msg);
		}
		else if (msg.m_bClose==2)
		{
			//将客户的信息显示在服务器的对话框中
			msg_list.AddString(msg.m_strText);
			//向所有客户返回该客户发来的消息
			backClients(&msg);
			pSocket->Close();
			POSITION pos, temp;
			for (pos = m_connList.GetHeadPosition(); pos != NULL;)
			{
				//对于已经关闭的客户机
				//在消息列表中将已经建立的连接删除
				temp = pos;
				CCSocket* pSock = (CCSocket*)m_connList.GetNext(pos);
				//匹配成功
				if (pSock == pSocket)
				{
					m_connList.RemoveAt(temp);
					CString strTemp;
					//更新在线人数
					strTemp.Format("在线人数：%d", m_connList.GetCount());
					user_num.SetWindowText(strTemp);
					break;
				}
			}
			delete pSocket;
			break;
		}
	} while (!pSocket->m_pArchiveIn->IsBufferEmpty());
}

void CMyQQServerDlg::backClients(CMsg* pMsg) {
	for (POSITION pos = m_connList.GetHeadPosition(); pos != NULL;)
	{
		AfxMessageBox(pMsg->m_strText);
		//获得连接列表的成员
		CCSocket* pSocket= (CCSocket*)m_connList.GetNext(pos);
		pSocket->sendMessage(pMsg);
	}
}