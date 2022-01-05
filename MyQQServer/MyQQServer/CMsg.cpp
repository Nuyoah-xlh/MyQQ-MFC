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

CMsg::CMsg()
{
	recv_name = _T("");
	m_strText = _T("");         //��ʼ��
	type = 0;
	sendname = _T("");
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
		ar << m_strText;
		ar << recv_name;
		ar << sendname;
	}
	// ��ȡ��Ϣ
	else {
		WORD wd;
		ar >> wd;
		type = (INT)wd;
		ar >> m_strText;
		ar >> recv_name;
		ar >> sendname;
	}
	CObject::Serialize(ar);
	//m_msgList.Serialize(ar);
}

IMPLEMENT_DYNAMIC(CMsg, CObject)