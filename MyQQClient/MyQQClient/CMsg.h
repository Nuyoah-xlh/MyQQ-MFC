#pragma once
#include <afx.h>
#if !defined(AFX_MSG_H__INCLUDED_)
#define AFX_MSG_H__INCLUDED_

//消息类的定义
class CMsg : public CObject
{
	DECLARE_DYNCREATE(CMsg);

public:
	CMsg();            //构造函数
	virtual ~CMsg();   //析构函数
	virtual void Serialize(CArchive& ar);  //序列化函数

//Attributes
public:
	CString sendname;	// 发送者名
	CString recv_name;		// 接收者名
	CString m_strBuf;       // 要发送消息的内容
	//消息类型 ，，0表示连接消息,1为群聊消息，2为断开连接消息，3为私聊消息,4为窗口抖动消息,5表示注册消息，6为用户已存在，7为注册成功，
	INT type;   
};

#endif // !defined(AFX_MSG_H__INCLUDED_)
