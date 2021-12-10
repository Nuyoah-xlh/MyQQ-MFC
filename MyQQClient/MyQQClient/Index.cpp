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
	//AfxMessageBox("111");
	main_dlg = qq_dlg;
	// 对话窗口初始化
	for (int i = 0; i < MAX_WINDOW_COUNT; i++) {
		m_chatDlg[i] = NULL;
	}
}

Index::~Index()
{
	
}


void Index::InitIndex(void)
{
	DWORD dwStyle = frind_list.GetExtendedStyle(); //显示网格线
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	frind_list.SetExtendedStyle(dwStyle);
	// frind_list.InsertColumn(0, _T("在线用户"), LVCFMT_CENTER, 120);
	// frind_list.InsertItem(0, _T("QQ群"), 0); //第三个参数为图标的索引

	//加入头像列表
	m_imageList.Create(40, 40, ILC_MASK | ILC_COLOR32, 1, 1);

	m_imageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD1));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD2));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD3));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD4));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD5));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_HEAD6));

	//m_friendList.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
	frind_list.SetImageList(&m_imageList, LVSIL_SMALL);

	frind_list.InsertColumn(0, _T("在线用户/群聊"), LVCFMT_CENTER, 120);

	//增加一项，群的显示
	frind_list.InsertItem(0, _T("QQ聊天室"), 0); //第三个参数为图标的索引

}

BOOL Index::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//设置标题栏为自己的用户名，以标识哪个是自己，自己是哪个对话框
	InitIndex();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Index::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// AfxMessageBox("pant");
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
}

void Index::OnClose() {
	//main_dlg->ShowWindow(SW_SHOW);
}

BEGIN_MESSAGE_MAP(Index, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_LIST_FRIEND, &Index::OnNMClickListFriend)
	ON_BN_CLICKED(IDC_BUTTON1, &Index::OnBnClickedButton1)
	//ON_WM_SYSCOMMAND()
	// 支持拖动
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Index 消息处理程序



void Index::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	//AfxMessageBox("444");
	CDialogEx::OnCancel();
}

void Index::sendMessage(CString& recvname, CString& strText, int st) {
	// AfxMessageBox("发送、！");
	main_dlg->sendMessage(recvname,strText, st);
}

void Index::CreateChatDlg(const CString sendUser, const CString recvUser, const UINT wndNum){
	dlg_num++;
	m_chatDlg[wndNum] = new CChatDlg();
	m_chatDlg[wndNum]->Create(IDD_CHAT_DLG, this);

	m_chatDlg[wndNum]->ShowWindow(SW_SHOW);

	//群聊的话
	if (wndNum == 0)
	{
		m_chatDlg[wndNum]->friend_name.SetWindowText("群聊");
		m_chatDlg[wndNum]->i_index = wndNum;
		UpdateData(TRUE);
		UpdateData(FALSE);
		AfxMessageBox("创建完成");
	}
	else {
		AfxMessageBox("222");
	}


}

//单击该好友，然后就与该好友聊天，打开聊天对话框
void Index::OnNMClickListFriend(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		//获取该用户名
		CString chatUserName = frind_list.GetItemText(pNMListView->iItem, 0);

		AfxMessageBox(chatUserName);

		//先检测窗口是否创建
		if (m_chatDlg[pNMListView->iItem] == NULL)
		{
			CString friend_name;
			GetWindowText(friend_name);
			//AfxMessageBox(pNMListView->iItem);
			CreateChatDlg(friend_name, chatUserName, pNMListView->iItem);
		}
		else {
			AfxMessageBox("have");
			m_chatDlg[pNMListView->iItem]->ShowWindow(SW_SHOW);
		}

		
	}

	//*pResult = 0;
}


void Index::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime tm = CTime::GetCurrentTime();
	CString tm_str = tm.Format("%X  ");
	CString strTemp = tm_str + main_dlg->user_name + ":已断开服务器...";
	UpdateData(TRUE);
	CString tt = _T("");
	sendMessage(tt, strTemp, 2);

	main_dlg->destory();
	DestroyWindow();

}

void Index::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND, 0xF012, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}
