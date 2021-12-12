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

//构造函数
CCSocket::CCSocket(CMyQQClientDlg* pDlg)
{
	m_pDlg = pDlg;       // 成员变量赋值
}

CCSocket::~CCSocket()
{
	m_pDlg = NULL;
}

//事件处理函数，当套接字收到FD_READ消息时，执行此函数
void CCSocket::OnReceive(int nErrorCode)
{
	// 正常接收
	if (nErrorCode == 0) m_pDlg->OnReceive();
	// 设置Socket感兴趣的网络事件
	AsyncSelect(FD_READ);
	CSocket::OnReceive(nErrorCode);
}
