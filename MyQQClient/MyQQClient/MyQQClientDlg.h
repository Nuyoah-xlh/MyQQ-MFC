
// 
// ClientDlg.h: 头文件
//

#pragma once

#include "CCSocket.h"
#include "Index.h"

class Index;

// CMyQQClientDlg 对话框
class CMyQQClientDlg : public CDialogEx
{
// 构造
public:
	// 标准构造函数
	CMyQQClientDlg(CWnd* pParent = nullptr);	
	// 发送消息的函数，recvname：接收方用户名；strText:消息内容；st:消息类型，0为连接消息，1为群聊消息，2为连接断开消息，3为私聊消息；
	void sendMessage(CString& recvname, CString& sendname, CString& strText, int st);
	// 销毁Index窗口
	void destory();
	// 点击登录按钮触发函数
	afx_msg void OnBnClickedButton1();
	// 接收信息
	void OnReceive();               
	// 接收信息并进行相关逻辑处理的函数
	void ReceiveMsg();              


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYQQCLIENT_DIALOG };
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
	// 服务器地址
	CString server_addr;
	// 服务器端口
	UINT server_port;
	// 本机用户名
	CString user_name;
	// 登录按钮
	CButton login;
	
	// 套接字对象指针
	CCSocket* m_pSocket;    
	// CSocketFile对象指针
	CSocketFile* m_pFile;    
	// 用于输入的CArchive对象指针
	CArchive* m_pArchiveIn;  
	// 用于输出的CArchive对象指针
	CArchive* m_pArchiveOut; 
	
	// 程序的ico图标
	HICON m_hIcon;

	//登录成功后的默认对话框,非模态对话框
	Index* dlg_index;	
	CString pwd;
	afx_msg void OnBnClickedButton2();
};
