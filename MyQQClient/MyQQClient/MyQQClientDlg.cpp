
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

	// 加载程序图标
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	// 套接字相关指针初始化
	m_pSocket = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;

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

	// TODO: 在此添加额外的初始化代码
	// 设置此对话框的图标
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 默认服务器端口和地址绑定
	user_name = "MyQQ用户-001";
	server_port = 8000;
	server_addr = _T("localhost");


	// 设置默认头像
	HBITMAP   hBitmap;
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_LOGIN_HEAD)); // IDB_BITMAP_TEST为资源图片ID
	((CButton*)GetDlgItem(IDC_BUTTON_HEAD))->SetBitmap(hBitmap);

	// true为将控件的值赋给变量，false为将变量的值赋给控件
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

// 绘图函数
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
		//CDialogEx::OnPaint();
		// 为图像绘制背景图
		CPaintDC dc(this);
		CRect rc;
		GetClientRect(&rc);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BTK);

		BITMAP bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


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
	// 创建index对话框
	dlg_index = new Index(this);
	// 获取用户输入
	UpdateData(TRUE);
	//创建套接字对象
	m_pSocket = new CCSocket(this); 
	// 创建套接字对象的底层套接字
	if (!m_pSocket->Create())       
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
	
	// 创建CSocketFile类对象
	m_pFile = new CSocketFile(m_pSocket);
	//分别创建用于输入和用于输出的CArchive类对象
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
	// 连接成功，则发送消息，内容为本机用户名，接受者可忽略，类型为连接成功消息
	sendMessage(user_name,user_name, 0);
	// 隐藏本窗口
	ShowWindow(SW_HIDE);
	// 创建Index对话框
	dlg_index = new Index(this);
	INT_PTR nResponse = dlg_index->Create(IDD_INDEX);
	dlg_index->ShowWindow(SW_SHOWNORMAL);
	// 创建成功与否的相关处理
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

}

// 发送消息的函数
void CMyQQClientDlg::sendMessage(CString& recvname,CString& strText, int st) {
	// 用于发送消息的m_pArchiveOut不为NULL
	if (m_pArchiveOut != NULL)
	{
		// 创建一个消息对象
		CMsg msg;  
		// 将要发送的信息内容、类型和接收方赋给消息对象的成员变量
		msg.m_strBuf = strText;
		msg.type = st;
		msg.recv_name = recvname;
		// 调用消息对象的系列化函数，发送消息
		msg.Serialize(*(m_pArchiveOut));
		// 将CArchive对象中数据强制存储到CSocketFile对象中
		m_pArchiveOut->Flush();
	}
}


void CMyQQClientDlg::destory() {

	//关闭套接字对象 
	m_pSocket->Close();    
	//删除CCSOcket对象  
	delete m_pSocket;	   
	m_pSocket = NULL;
	// 删除index窗口释放资源
	delete dlg_index;
	dlg_index = NULL;

	// 显示本窗口
	ShowWindow(SW_SHOW);
}

//当套接字收到FD_READ消息时，它的OnReceive函数调用此函数
void CMyQQClientDlg::OnReceive()
{
	do{
		// 套接字已经关闭，则直接返回
		if (m_pSocket == NULL)  return;
		//调用ReceiveMsg函数接收消息并进行逻辑处理
		ReceiveMsg();    
	} while (!m_pArchiveIn->IsBufferEmpty());
}

//实际接收消息和逻辑处理的函数
void CMyQQClientDlg::ReceiveMsg()
{
	//创建消息对象
	CMsg msg;   
	TRY
	{
		//调用消息对象的序列化函数，接收消息
		msg.Serialize(*m_pArchiveIn);
		
		// 如果不存在index窗口，则直接返回
		if (dlg_index == NULL) {
			return;
		}

		// 收到0，为连接成功的消息，则在index窗口列表创建一个好友
		if (msg.type == 0) {
			// 查询是否已经存在该好友
			for (int i = 0; i < MAX_WINDOW_COUNT; i++) {
				// 如果和msg的接收方匹配，则直接返回，不创建
				if (dlg_index->m_chatDlg[i] != NULL && dlg_index->m_chatDlg[i]->frind_name_text == msg.recv_name) {
					return;
				}
			}
			// 在好友列表插入一个好友，参数1：插入位置索引，参数2：好友用户名，参数3：图片列表的索引
			dlg_index->frind_list.InsertItem(dlg_index->count_pic,msg.recv_name, dlg_index->count_pic%7);
			// 索引值+1
			dlg_index->count_pic += 1;
		}
		// 收到1,为普通群聊消息，且已经创建了群聊窗口，则显示群聊消息
		else if (msg.type == 1&& dlg_index->m_chatDlg[0]!=NULL) {
			// 显示群聊窗口
			dlg_index->m_chatDlg[0]->ShowWindow(SW_SHOW);
			// 添加消息内容
			dlg_index->m_chatDlg[0]->list_recv.AddString(msg.m_strBuf);
			UpdateData(FALSE);
		}
		// 收到2,为连接断开消息
		else if (msg.type == 2) {
			// 群聊窗口存在
			if (dlg_index->m_chatDlg[0] != NULL) {
				dlg_index->m_chatDlg[0]->ShowWindow(SW_SHOW);
				dlg_index->m_chatDlg[0]->list_recv.AddString(msg.m_strBuf);
				UpdateData(FALSE);
			}
			// 查询是否存在该好友
			int len = dlg_index->frind_list.GetItemCount();
			for (int i = 0; i < len; i++) {
				CString temp = dlg_index->frind_list.GetItemText(i, 0);
				// 匹配，则从好友列表删除该好友
				if (temp == msg.m_strBuf) {
					dlg_index->frind_list.DeleteItem(i);
					break;
				}
			}
		}
		// 收到3，为私聊消息，选择性接收
		else if (msg.type == 3) {
			// 查询应该由谁接收
			for (int i = 0; i < MAX_WINDOW_COUNT; i++) {
				// 如果和msg的接收方匹配，则显示消息
				if (dlg_index->m_chatDlg[i] != NULL && dlg_index->m_chatDlg[i]->frind_name_text == msg.recv_name) {
					dlg_index->m_chatDlg[i]->ShowWindow(SW_SHOW);
					dlg_index->m_chatDlg[i]->list_recv.AddString(msg.m_strBuf);
					UpdateData(FALSE);
					break;
				}
			}
		}

	}
	CATCH(CFileException, e)    //错误处理
	{
		// 提示消息
		AfxMessageBox("接收消息失败！");
	}
	END_CATCH
}