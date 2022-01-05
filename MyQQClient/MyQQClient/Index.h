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
	// 标准构造函数
	Index( CMyQQClientDlg *qq_dlg, CWnd* pParent = nullptr);   
	// 析构函数
	virtual ~Index();
	// 初始化相关内容
	void InitIndex(void);

	virtual BOOL OnInitDialog();

	// 发送消息时调用
	void sendMessage(CString& recvname, CString& sendname, CString& strText, int st);

	virtual void OnClose();

	afx_msg void OnPaint();

	// 点击好友或群聊触发
	afx_msg void OnNMClickListFriend(NMHDR* pNMHDR, LRESULT* pResult);

	// 创建来聊天对话框
	void CreateChatDlg(const CString sendUser, const CString recvUser, const UINT wndNum);
	// 记录聊天窗口数
	int dlg_num;
	// 其所属的父窗口
	CMyQQClientDlg* main_dlg;
	// 程序的ico图标
	HICON m_hIcon;
	// 好友列表
	CListCtrl frind_list;
	// 头像列表
	CImageList m_imageList;
	// 用于记录图像索引
	int count_pic;

	// 可能多个聊天窗口
	CChatDlg* m_chatDlg[MAX_WINDOW_COUNT];

	// 本机用户名
	CStatic my_name;

	// 点击发送触发
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INDEX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual void OnCancel();

};

