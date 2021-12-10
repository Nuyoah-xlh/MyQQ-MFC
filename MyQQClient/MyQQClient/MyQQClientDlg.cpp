
// MyQQClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MyQQClient.h"
#include "MyQQClientDlg.h"
#include "CCSocket.h"
#include "afxdialogex.h"
#include "CMsg.h"
#include "Index.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class Index;
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


// CMyQQClientDlg 对话框



CMyQQClientDlg::CMyQQClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYQQCLIENT_DIALOG, pParent)
	, server_addr(_T(""))
	, server_port(0)
	, user_name(_T(""))
{

	// 变量初始化
	server_addr = _T("");
	server_port = 0;
	user_name = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 套接字相关指针初始化
	m_pSocket = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;

	// 只创建一次index对话框
	dlg_index = new Index(this);
}

void CMyQQClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SERVER_ADDR, server_addr);
	DDX_Text(pDX, IDC_SERVER_PORT, server_port);
	DDX_Text(pDX, IDC_USER, user_name);
	DDX_Control(pDX, IDC_BUTTON1, login);
}

BEGIN_MESSAGE_MAP(CMyQQClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyQQClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyQQClientDlg 消息处理程序

BOOL CMyQQClientDlg::OnInitDialog()
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
	user_name = "QQ用户-001";
	server_port = 8000;
	server_addr = _T("localhost");

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyQQClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyQQClientDlg::OnPaint()
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
HCURSOR CMyQQClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyQQClientDlg::OnBnClickedButton1()
{

	// TODO: 在此添加控件通知处理程序代码
	m_pSocket = new CCSocket(this); //创建套接字对象
	if (!m_pSocket->Create())       //创建套接字对象的底层套接字
	{
		delete m_pSocket;    //错误处理
		m_pSocket = NULL;
		AfxMessageBox("套接字创建错误！");
		return;
	}
	if (!m_pSocket->Connect(server_addr, server_port))
	{
		delete m_pSocket;    //错误处理
		m_pSocket = NULL;
		AfxMessageBox("无法连接服务器错误！");
		return;
	}
	// AfxMessageBox("ok");
	
	//创建CSocketFile类对象
	m_pFile = new CSocketFile(m_pSocket);
	//分别创建用于输入和用于输出的CArchive类对象
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
	//UpdateData(TRUE);
	sendMessage(user_name,user_name, 0);
	//CString s = "111111";
	//sendMessage(s, FALSE);
	// AfxMessageBox(tm.Format("%Y.%m.%d %X"));
	ShowWindow(SW_HIDE);
	// 创建Index对话框
	dlg_index = new Index(this);
	INT_PTR nResponse = dlg_index->Create(IDD_INDEX);
	dlg_index->ShowWindow(SW_SHOWNORMAL);
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	//MoveWindow(0, 0, 0, 0);

	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	// ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);    //显示
}


void CMyQQClientDlg::sendMessage(CString& recvname,CString& strText, int st) {
	if (m_pArchiveOut != NULL)
	{
		AfxMessageBox(strText);
		CMsg msg;  //创建一个消息对象
		//将要发送的信息文本赋给消息对象的成员变量
		msg.m_strBuf = strText;
		msg.m_bClose = st;
		msg.recv_name = recvname;
		//调用消息对象的系列化函数，发送消息
		msg.Serialize(*(m_pArchiveOut));
		//将CArchive对象中数据强制存储到CSocketFile对象中
		m_pArchiveOut->Flush();
	}
}

void CMyQQClientDlg::destory() {

	m_pSocket->Close();    //关闭套接字对象   
	delete m_pSocket;	   //删除CCSOcket对象  
	m_pSocket = NULL;

	ShowWindow(SW_SHOW);
	//UpdateData(FALSE);
}

//当套接字收到FD_READ消息时，它的OnReceive函数调用此函数
void CMyQQClientDlg::OnReceive()
{
	AfxMessageBox("onre");
	do
	{
		AfxMessageBox("receive");
		ReceiveMsg();    //调用ReceiveMsg函数实际接收消息
		if (m_pSocket == NULL)  return;
	} while (!m_pArchiveIn->IsBufferEmpty());
}

//实际接收消息的函数
void CMyQQClientDlg::ReceiveMsg()
{
	CMsg msg;   //创建消息对象
	TRY
	{
		//调用消息对象的序列化函数，接收消息
		msg.Serialize(*m_pArchiveIn);
		//if (dlg_index != NULL && dlg_index->m_chatDlg[0] != NULL) {
		//	AfxMessageBox("oo");
		//	dlg_index->m_chatDlg[0]->list_recv.AddString(msg.m_strBuf);
		//	UpdateData(FALSE);
		//}

		if (dlg_index == NULL) {
			return;
		}

		// 收到连接消息，创建一个好友
		if (msg.m_bClose == 0) {
			dlg_index->frind_list.InsertItem(1, msg.recv_name, 3);
		}
		else if (msg.m_bClose == 1&& dlg_index->m_chatDlg[0]!=NULL) {
			dlg_index->m_chatDlg[0]->ShowWindow(SW_SHOW);
			dlg_index->m_chatDlg[0]->list_recv.AddString(msg.m_strBuf);
			//UpdateData(FALSE);
		}
		else if (msg.m_bClose == 2) {
			AfxMessageBox("关闭");
		}
		else if (msg.m_bClose == 3) {
			AfxMessageBox("私聊");
		}

		//AfxMessageBox(msg.m_strBuf);
		//dlg_index->m_chatDlg[0].list_recv.AddString(msg.m_strBuf);  //将消息显示与列表框
	}
		CATCH(CFileException, e)    //错误处理
	{
		//显示处理服务器关闭的消息
		CString strTemp;
		strTemp = "服务器重置连接！连接关闭！";
		//m_listMsg.AddString(strTemp);
		AfxMessageBox(strTemp);
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort();
		//删除相应的对象
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
		delete m_pFile;
		m_pFile = NULL;
		delete m_pSocket;
		m_pSocket = NULL;
	}
	END_CATCH
}