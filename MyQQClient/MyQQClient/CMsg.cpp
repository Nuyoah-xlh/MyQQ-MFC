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
	m_bClose = 0;
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
		ar << (WORD)m_bClose;
		ar << m_strBuf;
		ar << recv_name;
	}
	else {
		//AfxMessageBox("store2");
		WORD wd;
		ar >> wd;
		m_bClose = (INT)wd;
		ar >> m_strBuf;
		ar >> recv_name;
	}
	CObject::Serialize(ar);
	//m_msgList.Serialize(ar);
}

IMPLEMENT_DYNAMIC(CMsg, CObject)