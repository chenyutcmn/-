
// ˫Ŀ�Ӿ��ⶨ��ά����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C˫Ŀ�Ӿ��ⶨ��ά����App: 
// �йش����ʵ�֣������ ˫Ŀ�Ӿ��ⶨ��ά����.cpp
//

class C˫Ŀ�Ӿ��ⶨ��ά����App : public CWinApp
{
public:
	C˫Ŀ�Ӿ��ⶨ��ά����App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C˫Ŀ�Ӿ��ⶨ��ά����App theApp;