// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <tchar.h>
#include <windows.h>
#include <iostream>
using namespace std;

int main()
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
			re = youFuntionNameAlias(1, 2);
		}
		FreeLibrary(hDllInst);
	}

	return re;
}

