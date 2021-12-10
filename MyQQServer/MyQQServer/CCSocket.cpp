#include "pch.h"
#include "CCSocket.h"
#include "CMsg.h"
#include "MyQQServerDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

class CMyQQServerDlg;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//构造函数
CCSocket::CCSocket(CMyQQServerDlg* pDlg)
{
	m_pDlg = pDlg;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
	//Initialize();
}

//析构函数
CCSocket::~CCSocket()
{
	m_pDlg = NULL;
	if (m_pArchiveOut != NULL) delete m_pArchiveOut;
	if (m_pArchiveIn != NULL) delete m_pArchiveIn;
	if (m_pFile != NULL) delete m_pFile;
}

//初始化
void CCSocket::Initialize()
{
	//构造与此套接字相应的CSocketFile对象
	m_pFile = new CSocketFile(this,TRUE);
	//构造与此套接字相应的CArchive对象
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
}

//发送消息
void CCSocket::sendMessage(CMsg* pMsg)
{
	if (m_pArchiveOut != NULL)
	{
		AfxMessageBox("send");
		//调用消息类的序列化函数，发送消息
		pMsg->Serialize(*m_pArchiveOut);
		//将CArchive对象中的数据强制性写入CSocketFile文件中
		m_pArchiveOut->Flush();
	}
}

//接收消息
void CCSocket::ReceiveMessage(CMsg* pMsg)
{
	//调用消息类的序列化函数，接收消息
	pMsg->Serialize(*m_pArchiveIn);
}

//OnReceive事件处理函数，当套接字收到数据时，激发此事件
void CCSocket::OnReceive(int nErrorCode)
{
	//CSocket::OnReceive(nErrorCode);
	//调用主对话框类中的相应函数来处理
	// AfxMessageBox(nErrorCode);

	if (nErrorCode == 0) m_pDlg->OnReceive(this);
	AsyncSelect(FD_READ);
	CSocket::OnReceive(nErrorCode);
	
}

IMPLEMENT_DYNAMIC(CCSocket, CSocket)