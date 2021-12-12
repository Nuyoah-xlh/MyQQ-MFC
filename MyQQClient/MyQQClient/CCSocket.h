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

// �Զ����׽����࣬�̳���CSocket��
class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);

//Construction
public:
	CCSocket(CMyQQClientDlg* pDlg);  //���캯��
	virtual ~CCSocket();     //��������

// Attributes
public:
	// ��󶨵Ĵ�����ָ��
	CMyQQClientDlg* m_pDlg;          //��Ա����

//Implementation
protected:
	// �׽��ֽ��յ���Ϣ����
	virtual void OnReceive(int nErrorCode);  
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)

