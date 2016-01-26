// testdll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "testdll2.h"
#include <iostream>
using namespace std;

int puls(int plus1, int plus2)
{
	int add_result = plus1 + plus2;
	return add_result;
}