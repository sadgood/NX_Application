// testdll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "testdll.h"
#include <tchar.h>
#include <windows.h>
#include <iostream>
using namespace std;

int Add(int plus1, int plus2, int plus3)
{
	int re = 0;
	HINSTANCE hDllInst = LoadLibrary(_T("d:\\testdll2.dll"));
	if (hDllInst)
	{
		typedef DWORD(WINAPI *MYFUNC)(DWORD, DWORD);
		MYFUNC youFuntionNameAlias = NULL; // youFuntionNameAlias ��������
		youFuntionNameAlias = (MYFUNC)GetProcAddress(hDllInst, "puls");
		// youFuntionName ��DLL�������ĺ�����
		if (youFuntionNameAlias)
		{
			re = youFuntionNameAlias(plus2, plus3);
		}
		FreeLibrary(hDllInst);
	}

	int add_result = plus1 + re;
	return add_result;
}