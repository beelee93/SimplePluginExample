#include "../MainApp/plugin.h"

#define PLUGIN_VERSION			0x00020003
#define PLUGIN_NAME				"Fibonacci"

#include <string>

// DLL Entry Point
BOOL WINAPI  DllMain(
	HANDLE    hModule,
	DWORD     dwFunction,
	LPVOID    lpNot)
{
	return TRUE;
}

DLL_EXPORT int GetSimplePluginVersion() {
	return PLUGIN_VERSION;
}

DLL_EXPORT void GetSimplePluginName(char* pszOutName, size_t size) {
	static char pluginName[] = PLUGIN_NAME;
	size_t i;
	for (i = 0; i < size && pluginName[i]; i++)
		pszOutName[i] = pluginName[i];
	pszOutName[i] = 0;
}

DLL_EXPORT int Execute(ParentInstance* pInst) {
	int op1, op2, temp, i,N;
	char msg[100] = { 0 };
	op1 = op2 = 1;

	pInst->WriteMessage("How many terms to display? ");
	N = pInst->ReadInt();

	for (i = 0; i < N; i++) {
		sprintf_s(msg, 100, "%d\n", op1);
		pInst->WriteMessage(msg);

		temp = op1 + op2;
		op1 = op2;
		op2 = temp;
	}
	return 1;
}