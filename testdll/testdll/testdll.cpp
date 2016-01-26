// testdll.cpp : 定义 DLL 应用程序的导出函数。
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
		MYFUNC youFuntionNameAlias = NULL; // youFuntionNameAlias 函数别名
		youFuntionNameAlias = (MYFUNC)GetProcAddress(hDllInst, "puls");
		// youFuntionName 在DLL中声明的函数名
		if (youFuntionNameAlias)
		{
			re = youFuntionNameAlias(plus2, plus3);
		}
		FreeLibrary(hDllInst);
	}

	int add_result = plus1 + re;
	return add_result;
}