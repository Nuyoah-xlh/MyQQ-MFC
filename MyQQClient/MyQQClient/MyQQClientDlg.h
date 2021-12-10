
// MyQQClientDlg.h: 头文件
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
	CMyQQClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

	void sendMessage(CString& recvname, CString& strText, int st);
	void destory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYQQCLIENT_DIALOG };
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
	CString server_addr;
	UINT server_port;
	CString user_name;
	CButton login;

	CCSocket* m_pSocket;    //套接字对象指针
	CSocketFile* m_pFile;    //CSocketFile对象指针
	CArchive* m_pArchiveIn;  //用于输入的CArchive对象指针
	CArchive* m_pArchiveOut; //用于输出的CArchive对象指针
	afx_msg void OnBnClickedButton1();

	void OnReceive();               //接收信息
	void ReceiveMsg();              //接收服务器发来的信息


	Index* dlg_index;	//登录成功后的默认对话框,非模态对话框
};
