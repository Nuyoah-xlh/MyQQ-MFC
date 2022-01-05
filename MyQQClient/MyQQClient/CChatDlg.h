#pragma once


// CChatDlg 对话框

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	// 标准构造函数
	CChatDlg(CWnd* pParent = nullptr);
	virtual ~CChatDlg();
	// 支持窗口拖动
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 要发送的信息内容
	CString msg_send;
	// 接受到需要显示的内容
	CListBox list_recv;
	// 发送与取消按钮
	CButton btn_send;
	CButton btn_cancel;
	// 本窗口的索引
	int i_index;
	afx_msg void OnBnClickedBtnChatOff();
	afx_msg void OnBnClickedBtnSend();
	// 窗口抖动函数
	void Shake(int window_index);
	// 左上角用于标识好友名
	CStatic friend_name;
	// 好友用户名
	CString frind_name_text;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnCancel();
};
