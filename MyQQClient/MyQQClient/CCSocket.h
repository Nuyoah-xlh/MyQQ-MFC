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

class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);


	//Construction
public:
	CCSocket(CMyQQClientDlg* pDlg);  //构造函数
	virtual ~CCSocket();     //析构函数

// Attributes
public:
	CMyQQClientDlg* m_pDlg;          //成员变量

//Implementation
protected:
	virtual void OnReceive(int nErrorCode);  //事件处理函数
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)

