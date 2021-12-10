#pragma once

#include "MyQQClientDlg.h"
#include "CChatDlg.h"

class CMyQQClientDlg;

class CChatDlg;

// Index 对话框
class Index : public CDialogEx
{
	DECLARE_DYNAMIC(Index)

public:
	Index( CMyQQClientDlg *qq_dlg, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Index();
	void InitIndex(void);
	virtual BOOL OnInitDialog();
	void sendMessage(CString& recvname, CString& strText, int st);

	virtual void OnClose();

	CMyQQClientDlg* main_dlg;

	afx_msg void OnPaint();
	// 点击好友或群聊触发
	afx_msg void OnNMClickListFriend(NMHDR* pNMHDR, LRESULT* pResult);

	void CreateChatDlg(const CString sendUser, const CString recvUser, const UINT wndNum);
	int dlg_num;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INDEX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
//	virtual void PostNcDestroy();
	virtual void OnCancel();
public:
	CListCtrl frind_list;
	CImageList m_imageList;

	// 可能多个用户窗口
	CChatDlg* m_chatDlg[MAX_WINDOW_COUNT];
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

