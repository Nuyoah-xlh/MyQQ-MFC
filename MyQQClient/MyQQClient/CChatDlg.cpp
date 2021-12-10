// CChatDlg.cpp: 实现文件
//

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
	//  DDX_Text(pDX, IDC_MYNAME, friend_name);
	DDX_Text(pDX, IDC_EDIT_SEND, msg_send);
	DDX_Control(pDX, IDC_LIST_RECV, list_recv);
	//  DDX_Control(pDX, IDC_BTN_CANCEL, btn_send);
	//  DDX_Control(pDX, IDC_BTN_SEND, btn_send);
	DDX_Control(pDX, IDC_BTN_SEND, btn_send);
	DDX_Control(pDX, IDC_BTN_CANCEL, btn_cancel);
	DDX_Control(pDX, IDC_MYNAME, friend_name);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_CHAT_OFF, &CChatDlg::OnBnClickedBtnChatOff)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()





// CChatDlg 消息处理程序
void CChatDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND, 0xF012, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CChatDlg::OnBnClickedBtnChatOff()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < MAX_WINDOW_COUNT;)
	{
		if (((Index*)GetParent())->m_chatDlg[i] == NULL)
		{
			i++;
		}
		else
		{
			if (((Index*)GetParent())->m_chatDlg[i]->m_hWnd == m_hWnd)
			{
				// delete ((Index*)GetParent())->m_chatDlg[i];
				//AfxMessageBox("00");
				((Index*)GetParent())->m_chatDlg[i]->ShowWindow(SW_HIDE);
				break;
			}
			else
			{
				i++;
			}
		}
	}
	//DestroyWindow();
}


void CChatDlg::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);       //取回用户输入的信息
	if (!msg_send.IsEmpty())
	{
		CTime tm = CTime::GetCurrentTime();
		CString tm_str = tm.Format("%X  ");
		AfxMessageBox("frinedn");
		//AfxMessageBox(friend_name);
		CString* recv_name = (CString*)GetDlgItem(IDC_MYNAME);
		if (i_index==0) {
			AfxMessageBox("11");
			tm_str = tm_str + ((Index*)GetParent())->main_dlg->user_name + ": "+msg_send;
			((Index*)GetParent())->sendMessage(tm_str,tm_str, 1);
		}
		else {
			AfxMessageBox("00");
			tm_str = "()" + ((Index*)GetParent())->main_dlg->user_name + ")" + tm_str;
		}
		//list_recv.AddString("111"+tm_str +msg_send);
		//AfxMessageBox(msg_send);
		
		SetDlgItemText(IDC_EDIT_SEND, _T(""));
	}
}
