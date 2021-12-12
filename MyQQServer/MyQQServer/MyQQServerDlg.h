
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
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	// 程序ico图标
	HICON m_hIcon;

	// 监听套接字指针
	CLSocket* m_pLSocket; 
	// 已连接列表
	CPtrList m_connList;  

	// 接受客户机的连接请求
	void OnAccept();
	// 接收客户机的消息并进行相应处理和转发
	void OnReceive(CCSocket* pSocket);
	// 将消息转发给所有客户机
	void backClients(CMsg* pMsg);

	// 已连接的用户列表
	CListBox user_list;
	// 实时消息列表
	CListBox msg_list;
	// 开启服务按钮
	CButton start_btn;
	// 关闭服务按钮
	CButton end_btn;
	// 监听端口
	UINT listen_port;
	// 用户数量
	CStatic user_num;
	// 按钮触发函数
	afx_msg void OnBnClickedButtonOn();
	afx_msg void OnBnClickedButtonOff();
	
};
