#include "plugin_loader.h"

#include <stdio.h>

PluginList createPluginList() {
	PluginList pluginList;

	// enumerate files in working directory
	HANDLE hFind;
	WIN32_FIND_DATA data;
	Plugin* pTempPlugin;
	char path[MAX_PATH] = { 0 };

	GetCurrentDirectory(MAX_PATH, path);
	strcat_s(path, MAX_PATH, "\\*.dll");

	hFind = FindFirstFile(path, &data);
	
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			pTempPlugin = new Plugin();
			memset(pTempPlugin, 0, sizeof(Plugin));
			strcpy_s(pTempPlugin->m_fileName,MAX_PATH, data.cFileName);

			if (validatePlugin(pTempPlugin))
				pluginList.push_back(pTempPlugin);
			else
				delete pTempPlugin;
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}

	return pluginList;
}

void freePluginList(PluginList * pList)
{
	while (pList->size() > 0) {
		Plugin* pPlugin = pList->back();
		pList->pop_back();

		unloadPlugin(pPlugin);
		delete pPlugin;
	}
}

void printPluginList(PluginList * pList)
{
	printf("Detected %d compatible plugins\n", pList->size());
	for (size_t i = 0; i < pList->size(); i++) {
		Plugin* pPlugin = (*pList)[i];
		printf("  %2d: %s (v%d.%d) %s\n", i + 1, pPlugin->m_pluginName, 
			pPlugin->m_version >> 16,
			pPlugin->m_version & 0xFFFF,
			pPlugin->m_module ? "(Loaded)" : "");
	}
}

int validatePlugin(Plugin* pPlugin) {
	HMODULE mod = LoadLibrary(pPlugin->m_fileName);
	int success = 1;

	if (!mod) 
		return 0;

	FN_PLUGIN_NAME pfnPluginName;
	FN_PLUGIN_VER  pfnPluginVersion;
	pfnPluginName = (FN_PLUGIN_NAME) GetProcAddress(mod, "GetSimplePluginName");
	pfnPluginVersion = (FN_PLUGIN_VER)GetProcAddress(mod, "GetSimplePluginVersion");

	if (pfnPluginName && pfnPluginVersion) {
		pPlugin->m_version=pfnPluginVersion();
		pfnPluginName(pPlugin->m_pluginName,PLUGIN_NAME_LENGTH);
	}
	else
		success = 0;

	FreeLibrary(mod);
	return success;
}

int loadPlugin(Plugin* pPlugin) {
	if (pPlugin->m_module)
		return 0;

	pPlugin->m_module = LoadLibrary(pPlugin->m_fileName);
	if (pPlugin->m_module)
		return 1;
	else
		return 0;
}

int unloadPlugin(Plugin* pPlugin) {
	if (!pPlugin->m_module)
		return 0;

	FreeLibrary(pPlugin->m_module);
	pPlugin->m_module = 0;
	return 1;
}

int isPluginLoaded(Plugin* pPlugin) {
	return pPlugin->m_module ? 1 : 0;
}

int runPlugin(Plugin* pPlugin) {
	if (!isPluginLoaded(pPlugin))
		return 0;

	ParentInstance inst = { 0 };
	inst.ReadInt = readInt;
	inst.WriteMessage = writeMessage;

	FN_EXECUTE Execute = (FN_EXECUTE)GetProcAddress(pPlugin->m_module, "Execute");
	if (!Execute)
		return 0;
	else
		return Execute(&inst);
}

void writeMessage(const char * pcMsg)
{
	printf("%s", pcMsg);
}

int readInt()
{
	int x;
	scanf("%d", &x);
	return x;
}
