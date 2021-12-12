#include "pch.h"
#include "CMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//���캯��
CMsg::CMsg()
{
	recv_name = _T("");
	m_strBuf = _T("");         //��ʼ��
	type = 0;
}

//��������
CMsg::~CMsg()
{
}

//���л�����
void CMsg::Serialize(CArchive& ar)
{
	// ������Ϣ
	if (ar.IsStoring())
	{
		ar << (WORD)type;
		ar << m_strBuf;
		ar << recv_name;
	}
	// ��ȡ��Ϣ
	else {
		WORD wd;
		ar >> wd;
		type = (INT)wd;
		ar >> m_strBuf;
		ar >> recv_name;
	}
	CObject::Serialize(ar);

}

IMPLEMENT_DYNAMIC(CMsg, CObject)