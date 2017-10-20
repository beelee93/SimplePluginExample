#include "../MainApp/plugin.h"

#define PLUGIN_VERSION			0x00010000
#define PLUGIN_NAME				"Addition"

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
	int op1, op2;
	char msg[100] = { 0 };

	pInst->WriteMessage("First operand: ");
	op1 = pInst->ReadInt();

	pInst->WriteMessage("Second operand: ");
	op2 = pInst->ReadInt();

	sprintf_s(msg, 100, "%d + %d = %d\n", op1, op2, op1 + op2);
	pInst->WriteMessage(msg);

	return 1;
}