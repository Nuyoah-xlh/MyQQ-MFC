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
	CString sendname;      // ��������
	CString recv_name;		// ��������
	CString m_strText;      //�ַ�����Ա
	// ��Ϣ���� ��0��ʾ�����¼��Ϣ,1Ϊ��ͨȺ����Ϣ��2Ϊ�Ͽ�������Ϣ��3Ϊ��ͨ˽����Ϣ,4Ϊ���ڶ�����Ϣ,5��ʾ����ע����Ϣ
	// 6Ϊ�û��Ѵ��ڣ�ע��ʧ�ܣ���7Ϊע��ɹ���8Ϊ��¼�ɹ���9Ϊ�������10Ϊ�û�δע��
	INT type;

//Implementation
public:
	virtual void Serialize(CArchive& ar);   //���л�����
};

#endif // !defined(AFX_MSG_H__INCLUDED_)