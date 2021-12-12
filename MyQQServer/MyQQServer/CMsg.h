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
	CString recv_name;		// 接受者名
	CString m_strText;      //字符串成员
	//消息类型 ，0表示群聊消息/连接消息，1为断开连接消息，2为私聊消息
	INT type;

//Implementation
public:
	virtual void Serialize(CArchive& ar);   //序列化函数
};

#endif // !defined(AFX_MSG_H__INCLUDED_)