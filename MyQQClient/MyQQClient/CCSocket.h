#pragma once
#include <afxsock.h>
// CSocket.h: interface for the CCSocket class.
//
//////////////////////////////////////////////////////////////////////
#include <afxsock.h>
//#include"MyQQSerDlg.h"
#if !defined(AFX_CSOCKET_H__INCLUDED_)
#define AFX_CSOCKET_H__INCLUDED_

class CMyQQClientDlg;

// 自定义套接字类，继承自CSocket类
class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);

//Construction
public:
	CCSocket(CMyQQClientDlg* pDlg);  //构造函数
	virtual ~CCSocket();     //析构函数

// Attributes
public:
	// 其绑定的窗口类指针
	CMyQQClientDlg* m_pDlg;          //成员变量

//Implementation
protected:
	// 套接字接收到消息触发
	virtual void OnReceive(int nErrorCode);  
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)

