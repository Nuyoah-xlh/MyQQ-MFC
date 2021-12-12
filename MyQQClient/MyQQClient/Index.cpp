// Index.cpp: 实现文件
//

#include "pch.h"
#include "MyQQClient.h"
#include "Index.h"
#include "afxdialogex.h"
#include "MyQQClientDlg.h"
#include "CMsg.h"


// Index 对话框

IMPLEMENT_DYNAMIC(Index, CDialogEx)

Index::Index( CMyQQClientDlg* qq_dlg, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INDEX, pParent)
{
	// 接收父窗口指针
	main_dlg = qq_dlg;
	count_pic = 1;
	// 聊天窗口初始化
	for (int i = 0; i < MAX_WINDOW_COUNT; i++) {
		m_chatDlg[i] = NULL;
	}
}

Index::~Index()
{
	
}


void Index::InitIndex(void)
{
	// 加入网络线 美观
	DWORD dwStyle = frind_list.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	frind_list.SetExtendedStyle(dwStyle);


	// 创建头像列表，存放icon头像
	m_imageList.Create(40, 40, ILC_MASK | ILC_COLOR32, 1, 1);
	// 添加头像
	m_imageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD1));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD2));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD3));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD4));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD5));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD6));

	// 绑定好友列表和图像列表
	frind_list.SetImageList(&m_imageList, LVSIL_SMALL);
	// 插入列名
	frind_list.InsertColumn(0, _T("在线用户/群聊"), LVCFMT_CENTER, 172);
	//增加第一行，为qq群的显示
	// 参数1：插入位置；参数2：文字；参数3：图像索引
	frind_list.InsertItem(0, _T("QQ聊天室"), 0); 

}

BOOL Index::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// index初始化
	InitIndex();
	// 设置本人头像
	HBITMAP   hBitmap;
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_MYHEAD)); 
	((CButton*)GetDlgItem(IDC_INDEX_HEAD))->SetBitmap(hBitmap);
	// 本人昵称
	CString temp_name = main_dlg->user_name+"  *在线";
	my_name.SetWindowText(temp_name);
	UpdateData(TRUE);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Index::OnPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 绘制背景图像
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_INDEX_BK);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void Index::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FRIEND, frind_list);
	DDX_Control(pDX, IDC_MYNAME, my_name);
}

void Index::OnClose() {
	//main_dlg->ShowWindow(SW_SHOW);
}

BEGIN_MESSAGE_MAP(Index, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_LIST_FRIEND, &Index::OnNMClickListFriend)
	ON_BN_CLICKED(IDC_BUTTON1, &Index::OnBnClickedButton1)
	// 支持拖动
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Index 消息处理程序
void Index::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialogEx::OnCancel();
}

// 调用父窗口的发送消息函数
void Index::sendMessage(CString& recvname, CString& strText, int st) {
	main_dlg->sendMessage(recvname,strText, st);
}

// 创建聊天窗口
void Index::CreateChatDlg(const CString sendUser, const CString recvUser, const UINT wndNum){
	dlg_num++;
	// 创建聊天窗口并显示
	m_chatDlg[wndNum] = new CChatDlg();
	m_chatDlg[wndNum]->Create(IDD_CHAT_DLG, this);
	m_chatDlg[wndNum]->ShowWindow(SW_SHOW);

	//群聊窗口
	if (wndNum == 0)
	{
		m_chatDlg[wndNum]->friend_name.SetWindowText("群聊");
		m_chatDlg[wndNum]->i_index = wndNum;
		m_chatDlg[wndNum]->frind_name_text = _T("群聊");
		UpdateData(FALSE);
	}
	// 私聊窗口
	else {
		m_chatDlg[wndNum]->friend_name.SetWindowText(sendUser);
		m_chatDlg[wndNum]->i_index = wndNum;
		m_chatDlg[wndNum]->frind_name_text = sendUser;
		UpdateData(FALSE);
	}


}

//单击该好友，然后就与该好友聊天，打开聊天对话框
void Index::OnNMClickListFriend(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 把pNMHDR强制转化成LPNMITEMACTIVATE类型
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	// NMHDR为传递的通知消息信息，在CListCtrl中为NM_LISTVIEW类型
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		//获取该用户名
		CString chatUserName = frind_list.GetItemText(pNMListView->iItem, 0);

		//先检测窗口是否创建,未创建则前往创建；否则直接显示
		if (m_chatDlg[pNMListView->iItem] == NULL)
		{
			CString friend_name;
			GetWindowText(friend_name);
			CreateChatDlg(friend_name, chatUserName, pNMListView->iItem);
		}
		else {
			m_chatDlg[pNMListView->iItem]->ShowWindow(SW_SHOW);
		}
		
	}
}

// 点击关闭index窗口
void Index::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 发送关闭连接类型的消息
	sendMessage(main_dlg->user_name, main_dlg->user_name, 2);
	// 销毁本窗口的相关资源
	main_dlg->destory();   
	//DestroyWindow();        

}

// 支持窗口拖动
void Index::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND, 0xF012, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}


