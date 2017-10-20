// Header file for a plugin
#ifndef _PLUGIN_H
#define _PLUGIN_H

typedef struct {
	void(*WriteMessage)(const char*);
	int(*ReadInt)();
} ParentInstance;

#ifndef _MAIN_APP

#define DLL_EXPORT extern "C" __declspec(dllexport)

#include <Windows.h>

BOOL WINAPI  DllMain(HANDLE    hModule,	DWORD     dwFunction,	LPVOID    lpNot);
DLL_EXPORT int GetSimplePluginVersion();
DLL_EXPORT void GetSimplePluginName(char* pszOutName, size_t size);

DLL_EXPORT int Execute(ParentInstance* pInst);

#endif
#endif