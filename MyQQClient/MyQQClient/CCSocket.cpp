#include "pch.h"
#include "CCSocket.h"
#include "MyQQClientDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CCSocket, CSocket)

//���캯��
CCSocket::CCSocket(CMyQQClientDlg* pDlg)
{
	m_pDlg = pDlg;       //��Ա������ֵ
}

CCSocket::~CCSocket()
{
	m_pDlg = NULL;
}

//�¼������������׽����յ�FD_READ��Ϣʱ��ִ�д˺���
void CCSocket::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0) m_pDlg->OnReceive();
	AsyncSelect(FD_READ);
	CSocket::OnReceive(nErrorCode);
}
