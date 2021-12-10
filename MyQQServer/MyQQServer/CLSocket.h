#pragma once
#include <afxsock.h>
#if !defined(AFX_LSOCKET_H__INCLUDED_)
#define AFX_LSOCKET_H__INCLUDED_

class  CMyQQServerDlg;

//ר���ڼ����ͻ�����������������׽����ඨ��
class CLSocket : public CSocket
{
	DECLARE_DYNAMIC(CLSocket);

	//Construction
public:
	CLSocket(CMyQQServerDlg* pDlg);
	virtual ~CLSocket();

	// Attributes
public:
	CMyQQServerDlg* m_pDlg;   //��Ա����

// Overridable Callbacks
//�����صĻص����������׽����յ���������ʱ���Զ����ô˺���
protected:
	virtual void OnAccept(int nErrorCode);
};

#endif // !defined(AFX_LSOCKET_H__INCLUDED_)


