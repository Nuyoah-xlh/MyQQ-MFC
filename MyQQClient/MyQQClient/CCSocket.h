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
	CCSocket(CMyQQClientDlg* pDlg);  //���캯��
	virtual ~CCSocket();     //��������

// Attributes
public:
	CMyQQClientDlg* m_pDlg;          //��Ա����

//Implementation
protected:
	virtual void OnReceive(int nErrorCode);  //�¼�������
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)

