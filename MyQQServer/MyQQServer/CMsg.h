#pragma once
#include <afx.h>
#if !defined(AFX_MSG_H__INCLUDED_)
#define AFX_MSG_H__INCLUDED_

//��Ϣ�ඨ��
class CMsg : public CObject
{
	DECLARE_DYNCREATE(CMsg);

	//Construction
public:
	CMsg();
	virtual ~CMsg();

	//Attributes
public:
	CString recv_name;		// ��������
	CString m_strText;      //�ַ�����Ա
	//��Ϣ���� ��0��ʾȺ����Ϣ/������Ϣ��1Ϊ�Ͽ�������Ϣ��2Ϊ˽����Ϣ
	INT type;

//Implementation
public:
	virtual void Serialize(CArchive& ar);   //���л�����
};

#endif // !defined(AFX_MSG_H__INCLUDED_)