// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
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
		MYFUNC youFuntionNameAlias = NULL; // youFuntionNameAlias 函数别名
		youFuntionNameAlias = (MYFUNC)GetProcAddress(hDllInst, "puls");
		// youFuntionName 在DLL中声明的函数名
		if (youFuntionNameAlias)
		{
			re = youFuntionNameAlias(1, 2);
		}
		FreeLibrary(hDllInst);
	}

	return re;
}

