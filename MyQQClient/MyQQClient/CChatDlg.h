#pragma once


// CChatDlg 对话框

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChatDlg();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString friend_name;
	CString msg_send;
	CListBox list_recv;
	CButton btn_send;
	CButton btn_cancel;
	int i_index;
	afx_msg void OnBnClickedBtnChatOff();
	afx_msg void OnBnClickedBtnSend();
//	CString friend_name;
	CStatic friend_name;
};
