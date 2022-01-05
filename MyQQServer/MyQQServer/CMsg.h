#pragma once
#include <afx.h>
#if !defined(AFX_MSG_H__INCLUDED_)
#define AFX_MSG_H__INCLUDED_

//消息类定义
class CMsg : public CObject
{
	DECLARE_DYNCREATE(CMsg);

	//Construction
public:
	CMsg();
	virtual ~CMsg();

	//Attributes
public:
	CString sendname;      // 发送者名
	CString recv_name;		// 接受者名
	CString m_strText;      //字符串成员
	// 消息类型 ，0表示请求登录消息,1为普通群聊消息，2为断开连接消息，3为普通私聊消息,4为窗口抖动消息,5表示请求注册消息
	// 6为用户已存在（注册失败），7为注册成功，8为登录成功，9为密码错误，10为用户未注册
	INT type;

//Implementation
public:
	virtual void Serialize(CArchive& ar);   //序列化函数
};

#endif // !defined(AFX_MSG_H__INCLUDED_)