// CChatDlg.cpp: 实现文件


#include "pch.h"
#include "MyQQClient.h"
#include "CChatDlg.h"
#include "afxdialogex.h"
#include "Index.h"


// CChatDlg 对话框
IMPLEMENT_DYNAMIC(CChatDlg, CDialogEx)

CChatDlg::CChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_DLG, pParent)
	, msg_send(_T(""))
{

}

CChatDlg::~CChatDlg()
{
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, msg_send);
	DDX_Control(pDX, IDC_LIST_RECV, list_recv);
	DDX_Control(pDX, IDC_BTN_SEND, btn_send);
	DDX_Control(pDX, IDC_BTN_CANCEL, btn_cancel);
	DDX_Control(pDX, IDC_MYNAME, friend_name);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_CHAT_OFF, &CChatDlg::OnBnClickedBtnChatOff)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CChatDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()





// CChatDlg 消息处理程序
void CChatDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND, 0xF012, 0);
	SetFocus();
	GetDlgItem(IDC_EDIT_SEND)->SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}


// 点击右上角关闭，则默认隐藏窗口，但不摧毁，方便下次开启
void CChatDlg::OnBnClickedBtnChatOff()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < MAX_WINDOW_COUNT;i++)
	{
		if (((Index*)GetParent())->m_chatDlg[i] == NULL)
		{
			continue;
		}
		else
		{
			// 匹配该句柄
			if (((Index*)GetParent())->m_chatDlg[i]->m_hWnd == m_hWnd)
			{
				// 隐藏本窗口
				((Index*)GetParent())->m_chatDlg[i]->ShowWindow(SW_HIDE);
				break;
			}
		}
	}
	//DestroyWindow();
}

// 点击发送触发函数
void CChatDlg::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	//取回用户输入的信息
	UpdateData(TRUE);       
	if (!msg_send.IsEmpty())
	{
		// 获取当前时间
		CTime tm = CTime::GetCurrentTime();
		CString tm_str = tm.Format("%X ");
		CString* recv_name = (CString*)GetDlgItem(IDC_MYNAME);
		// 群聊消息
		if (i_index==0) {
			tm_str = tm_str + ((Index*)GetParent())->main_dlg->user_name + ": "+msg_send;
			((Index*)GetParent())->sendMessage(tm_str, tm_str,tm_str, 1);
		}
		// 私聊消息
		else {
			tm_str = tm_str+ ((Index*)GetParent())->main_dlg->user_name +": "+ msg_send;
			list_recv.AddString(tm_str);
			((Index*)GetParent())->sendMessage(frind_name_text, ((Index*)GetParent())->main_dlg->user_name, tm_str, 3);
		}
		
		// 将编辑栏恢复为空
		msg_send = "";
		UpdateData(FALSE);
	}
}

// 发送窗口抖动
void CChatDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 群聊消息
	if (i_index == 0) {
		// 只抖动自己
		Shake(i_index);
	}
	// 私聊消息
	else {
		// 先抖动自己
		Shake(i_index);
		// 发送消息让对方抖动
		((Index*)GetParent())->sendMessage(frind_name_text, ((Index*)GetParent())->main_dlg->user_name, frind_name_text, 4);
		CTime tm = CTime::GetCurrentTime();
		CString tm_str = tm.Format("%X ");
		list_recv.AddString(tm_str + "你抖了抖对方");
		UpdateData(FALSE);
	}
}

void CChatDlg::Shake(int window_index) {
	// 定义一个矩形获取窗口
	CRect rect;
	((Index*)GetParent())->m_chatDlg[window_index]->GetWindowRect(&rect);
	int move = 10;
	// 循环实现抖动特效
	for (int z = 1; z < 9; z++)
	{
		rect.OffsetRect(0, move);
		((Index*)GetParent())->m_chatDlg[window_index]->MoveWindow(&rect);
		Sleep(50);
		rect.OffsetRect(move, 0);
		((Index*)GetParent())->m_chatDlg[window_index]->MoveWindow(&rect);
		Sleep(50);
		if (10 == move)
		{
			move = -10;
		}
		else
		{
			move = 10;
		}
	}
}


void CChatDlg::OnBnClickedBtnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	msg_send = "";
	UpdateData(FALSE);
	OnBnClickedBtnChatOff();
}
