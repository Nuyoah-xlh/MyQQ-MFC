#pragma once
#if !defined(AFX_CSOCKET_H__INCLUDED_)
#define AFX_CSOCKET_H__INCLUDED_

class  CMyQQServerDlg;
class  CMsg;

//���ڽ������Ӻʹ��ͽ�����Ϣ�Ŀͻ��׽����ඨ��
class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);

	//Construction
public:
	CCSocket(CMyQQServerDlg* pDlg);   //���캯��
	virtual ~CCSocket();      //��������

//Attributes
public:
	CMyQQServerDlg* m_pDlg;         //���Ի�����ָ�����
	CSocketFile* m_pFile;         //CSocketFile�����ָ�����
	CArchive* m_pArchiveIn;       //���������CArchive�����ָ�����
	CArchive* m_pArchiveOut;      //���������CArchive�����ָ�����

//Operations
public:
	void Initialize();               //��ʼ��
	void sendMessage(CMsg* pMsg);    //������Ϣ
	void ReceiveMessage(CMsg* pMsg); //������Ϣ

//Overridable callbacks
 protected:
	 // �����صĻص����������׽����յ�����ʱ���Զ����ô˺���
	virtual void OnReceive(int nErrorCode);
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)