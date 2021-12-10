
// MyQQServerDlg.h: 头文件
//
#include "CLSocket.h"
#include "CCSocket.h"

#pragma once


// CMyQQServerDlg 对话框
class CMyQQServerDlg : public CDialogEx
{
// 构造
public:
	CMyQQServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYQQSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CLSocket* m_pLSocket; //侦听套接字指针变量
	CPtrList m_connList;   //连接列表

	// 接受客户机的连接请求
	void OnAccept();
	// 接收已经连接的客户机的消息
	void OnReceive(CCSocket* pSocket);

	void backClients(CMsg* pMsg);


	CListBox user_list;
	CListBox msg_list;
	CButton start_btn;
	CButton end_btn;
	UINT listen_port;
	afx_msg void OnBnClickedButtonOn();
	afx_msg void OnBnClickedButtonOff();
	CStatic user_num;
};
