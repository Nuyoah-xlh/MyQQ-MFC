#include "pch.h"
#include "CLSocket.h"

#include "MyQQServerDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLSocket::CLSocket(CMyQQServerDlg* pDlg)
{
	m_pDlg = pDlg;   //�Գ�Ա������ֵ
}

CLSocket::~CLSocket()
{
	m_pDlg = NULL;
}

//OnAccept�¼�������
void CLSocket::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);
	m_pDlg->OnAccept();  //�������Ի������е���Ӧ����
}

IMPLEMENT_DYNAMIC(CLSocket, CSocket)

