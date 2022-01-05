
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
	// 变量初始化
	listen_port = 0;
	for (int i = 0; i < 200; i++) {
		users[i] = NULL;
	}
	index = 0;
	// 加载程序ico图标
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_SERVER);
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

	// TODO: 在此添加额外的初始化代码
	// 设置此对话框的图标
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	listen_port = 8000;

	UpdateData(FALSE);

	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OFF)->EnableWindow(FALSE);

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
		// CDialogEx::OnPaint();
		// 绘制背景图
		CPaintDC dc(this);
		CRect rc;
		GetClientRect(&rc);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BK);

		BITMAP bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示
HCURSOR CMyQQServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyQQServerDlg::OnBnClickedButtonOn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);    //获得控件内容
	GetDlgItem(IDC_BUTTON_ON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OFF)->EnableWindow(TRUE);
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
	msg_list.AddString("服务器已启动...");
	CString strTemp = "在线人数：0人";
	user_num.SetWindowText(strTemp);
	UpdateData(FALSE);
}


void CMyQQServerDlg::OnBnClickedButtonOff()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON_OFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ON)->EnableWindow(TRUE);
	CMsg  msg;
	msg.type = 1;
	msg.m_strText = "服务器终止服务!";
	//对连接列表进行发送消息
	while (!m_connList.IsEmpty())
	{
		//向每一个连接的客户机发送"服务器终止服务！"的消息
		//并逐个删除已建立的连接
		CCSocket* pSocket = (CCSocket*)m_connList.RemoveHead();
		pSocket->sendMessage(&msg);
		delete pSocket;
		pSocket = NULL;
	}
	delete m_pLSocket;
	m_pLSocket = NULL;
	CString strTemp="服务器未开启...";
	user_num.SetWindowText(strTemp);
	UpdateData(FALSE);

	msg_list.AddString("服务器已关闭！！");

}

// 处理连接信息
void CMyQQServerDlg::OnAccept() {
	//创建用于与客户端连接并交换数据的套接字对象
	CCSocket* pSocket = new CCSocket(this);
	if (m_pLSocket->Accept(*pSocket))  //接受客户的连接请求
	{
		//对连接套接字初始化
		pSocket->Initialize();
		// 加入连接列表
		m_connList.AddTail(pSocket);
		// 更新在线人数
		CString strTemp;
		strTemp.Format("在线人数：%d人", m_connList.GetCount());
		user_num.SetWindowText(strTemp);
	}
	else delete pSocket;

}

// 处理客户机发送的消息
void CMyQQServerDlg::OnReceive(CCSocket* pSocket) {
	// 存储消息
	static CMsg msg;
	do {
		//接收客户发来的消息
		pSocket->ReceiveMessage(&msg);
		// 注册的消息
		if (msg.type == 5) {
			for (int i = 0; i < 200; i++) {
				if (users[i] == NULL) {
					continue;
				}
				else {
					// 已经存在
					if (users[i]->user_name == msg.recv_name) {
						msg.type = 6;
						backClients(&msg); 
						return;
					}
				}
			}
			// 注册成功
			users[index] = new User();
			users[index]->user_name = msg.recv_name;
			users[index]->pwd = msg.sendname;
			index++;
			msg.type = 7;
			backClients(&msg);
		}
		// 登录消息
		else if (msg.type == 0) {
			for (int i = 0; i < 200; i++) {
				if (users[i] == NULL) {
					continue;
				}
				else {
					// 已经存在
					if (users[i]->user_name == msg.recv_name) {
						// 登录成功
						if (users[i]->pwd == msg.sendname) {
							//将客户的信息显示在服务器的对话框中
							user_list.AddString(msg.m_strText);
							// 获取当前时间
							CTime tm = CTime::GetCurrentTime();
							CString tm_str = tm.Format("%X ");
							msg.m_strText = tm_str + msg.m_strText + "已成功连接...";
							// 显示内容
							msg_list.AddString(msg.m_strText);
							// 登录成功，同时更新所有客户端的用户列表                                    
							for (int i = 0; i < user_list.GetCount(); i++) {
								CString temp;
								user_list.GetText(i, temp);
								msg.type = 8;
								msg.m_strText = temp;
								msg.recv_name = temp;
								msg.sendname = temp;
								backClients(&msg);
							}
							break;
						}
						// 用户存在但密码错误
						else {
							msg.type = 9;
							//向所有客户返回消息                                    
							backClients(&msg);
							return;
						}
					}
				}
			}
			// 用户未注册
			if (msg.type == 0) {
				msg.type = 10;
				backClients(&msg);
				return;
			}
		}
		// 普通的群聊消息
		else if (msg.type == 1) {
			// 直接转发
			backClients(&msg);
		}
		// 连接断开消息
		else if (msg.type ==2)
		{
			// 获取当前时间
			CTime tm = CTime::GetCurrentTime();
			CString tm_str = tm.Format("%X ");
			for (int i = 0; i < user_list.GetCount(); i++) {
				CString temp;
				user_list.GetText(i, temp);
				if (temp == msg.m_strText) {
					user_list.DeleteString(i);
					break;
				}
			}
			msg.m_strText = tm_str + msg.m_strText + "已断开连接...";
			//将客户的信息显示在服务器的对话框中
			msg_list.AddString(msg.m_strText);
			//向所有客户返回该客户发来的消息
			backClients(&msg);
			//pSocket->Close();
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
					strTemp.Format("在线人数：%d人", m_connList.GetCount());
					user_num.SetWindowText(strTemp);
					break;
				}
			}
			delete pSocket;
			break;
		}
		else if (msg.type == 3||msg.type==4) {
			// 向所有客户返回该客户发来的消息
			backClients(&msg);
		}
	} while (!pSocket->m_pArchiveIn->IsBufferEmpty());
}

void CMyQQServerDlg::backClients(CMsg* pMsg) {
	// 遍历连接列表逐个转发
	for (POSITION pos = m_connList.GetHeadPosition(); pos != NULL;)
	{
		//获得连接列表的成员
		CCSocket* pSocket= (CCSocket*)m_connList.GetNext(pos);
		if (pSocket == NULL) {
			continue;
		}
		pSocket->sendMessage(pMsg);
	}
}