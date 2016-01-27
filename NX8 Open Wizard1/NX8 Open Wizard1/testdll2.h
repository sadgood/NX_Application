#pragma once

#pragma once

#ifndef TestDll_H_
#define TestDll_H_

#ifdef MYLIBDLL
#define MYLIBDLL extern "C" _declspec(dllimport)
#else
#define MYLIBDLL extern "C" _declspec(dllexport)
#endif

MYLIBDLL int puls(int plus1, int plus2);

//You can also write like this:

//extern "C" {
//_declspec(dllexport) int Add(int plus1, int plus2);
//};
#endif