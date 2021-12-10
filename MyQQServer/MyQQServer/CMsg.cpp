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
	m_strText = _T("");         //初始化
	m_bClose = 0;
}

//析构函数
CMsg::~CMsg()
{
}

//序列化函数
void CMsg::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		//AfxMessageBox("store");
		ar << (WORD)m_bClose;
		ar << m_strText;
		ar << recv_name;
	}
	else {
		//AfxMessageBox("store2");
		WORD wd;
		ar >> wd;
		m_bClose = (INT)wd;
		ar >> m_strText;
		ar >> recv_name;
	}
	CObject::Serialize(ar);
	//m_msgList.Serialize(ar);
}

IMPLEMENT_DYNAMIC(CMsg, CObject)