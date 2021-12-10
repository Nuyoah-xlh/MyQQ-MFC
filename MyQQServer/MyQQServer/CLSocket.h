#pragma once
#include <afxsock.h>
#if !defined(AFX_LSOCKET_H__INCLUDED_)
#define AFX_LSOCKET_H__INCLUDED_

class  CMyQQServerDlg;

//专用于监听客户端连接请求的侦听套接字类定义
class CLSocket : public CSocket
{
	DECLARE_DYNAMIC(CLSocket);

	//Construction
public:
	CLSocket(CMyQQServerDlg* pDlg);
	virtual ~CLSocket();

	// Attributes
public:
	CMyQQServerDlg* m_pDlg;   //成员变量

// Overridable Callbacks
//可重载的回调函数，当套接字收到连接请求时，自动调用此函数
protected:
	virtual void OnAccept(int nErrorCode);
};

#endif // !defined(AFX_LSOCKET_H__INCLUDED_)


