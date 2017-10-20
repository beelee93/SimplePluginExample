#ifndef _PLUGIN_LOADER_H
#define _PLUGIN_LOADER_H

#include <Windows.h>
#include <vector>
#include "plugin.h"

#define PLUGIN_NAME_LENGTH		49

typedef struct {
	char m_fileName[MAX_PATH];
	char m_pluginName[PLUGIN_NAME_LENGTH + 1];
	int m_version;
	HMODULE m_module;
} Plugin;

typedef std::vector<Plugin*> PluginList;

// enumerates all compatible plugins within working directory
PluginList createPluginList();
void freePluginList(PluginList*);

void printPluginList(PluginList*);

int validatePlugin(Plugin*);

int loadPlugin(Plugin*);
int unloadPlugin(Plugin*);

int isPluginLoaded(Plugin*);
int runPlugin(Plugin*);

// function pointer typedefs
typedef int (*FN_PLUGIN_VER)();
typedef void(*FN_PLUGIN_NAME)(char*,size_t);
typedef int(*FN_EXECUTE)(ParentInstance*);

// interface functions
void writeMessage(const char *);
int readInt();

#endif
