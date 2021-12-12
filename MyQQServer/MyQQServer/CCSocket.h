#pragma once
#if !defined(AFX_CSOCKET_H__INCLUDED_)
#define AFX_CSOCKET_H__INCLUDED_

class  CMyQQServerDlg;
class  CMsg;

//用于建立连接和传送接收信息的客户套接字类定义
class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);

	//Construction
public:
	CCSocket(CMyQQServerDlg* pDlg);   //构造函数
	virtual ~CCSocket();      //析构函数

//Attributes
public:
	CMyQQServerDlg* m_pDlg;         //主对话框类指针变量
	CSocketFile* m_pFile;         //CSocketFile对象的指针变量
	CArchive* m_pArchiveIn;       //用于输入的CArchive对象的指针变量
	CArchive* m_pArchiveOut;      //用于输出的CArchive对象的指针变量

//Operations
public:
	void Initialize();               //初始化
	void sendMessage(CMsg* pMsg);    //发送消息
	void ReceiveMessage(CMsg* pMsg); //接收消息

//Overridable callbacks
 protected:
	 // 可重载的回调函数，当套接字收到数据时，自动调用此函数
	virtual void OnReceive(int nErrorCode);
};

#endif // !defined(AFX_CSOCKET_H__INCLUDED_)