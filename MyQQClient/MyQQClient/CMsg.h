#pragma once
#include <afx.h>
#if !defined(AFX_MSG_H__INCLUDED_)
#define AFX_MSG_H__INCLUDED_

//��Ϣ��Ķ���
class CMsg : public CObject
{
	DECLARE_DYNCREATE(CMsg);

public:
	CMsg();            //���캯��
	virtual ~CMsg();   //��������
	virtual void Serialize(CArchive& ar);  //���л�����

//Attributes
public:
	CString recv_name;		// ��������
	CString m_strBuf;       // Ҫ������Ϣ������
	//��Ϣ���� ��0��ʾ������Ϣ,1ΪȺ����Ϣ��2Ϊ�Ͽ�������Ϣ��3Ϊ˽����Ϣ
	INT type;          
};

#endif // !defined(AFX_MSG_H__INCLUDED_)
