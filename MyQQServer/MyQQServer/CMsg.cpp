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
}

//��������
CMsg::~CMsg()
{
}

//���л�����
void CMsg::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		//AfxMessageBox("store");
		ar << (WORD)type;
		ar << m_strText;
		ar << recv_name;
	}
	else {
		//AfxMessageBox("store2");
		WORD wd;
		ar >> wd;
		type = (INT)wd;
		ar >> m_strText;
		ar >> recv_name;
	}
	CObject::Serialize(ar);
	//m_msgList.Serialize(ar);
}

IMPLEMENT_DYNAMIC(CMsg, CObject)