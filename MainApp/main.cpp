#include "plugin_loader.h"
#include <stdio.h>


void writeMessage(const char*);
int readInt();


int main(int argc, char** argv) {
	int running = 1;

	printf("=============================================\n");
	printf("Simple Plugin Loader\n");
	printf("=============================================\n");

	// enumerate plugins
	PluginList list = createPluginList();
	char option = 0;
	int number = 0;

	printPluginList(&list);

	while (running) {
		printf("------------------------------------\n");
		printf(" L - load a plugin\n");
		printf(" U - unload a plugin\n");
		printf(" S - show the list of plugins\n");
		printf(" R - run a plugin\n");
		printf(" Q - quit the program\n");
		printf("Select an option: ");
		
		scanf(" %c", &option);

		switch (option) {
		case 'L':
			printf("Plugin index: ");
			scanf("%d", &number);

			if (number<1 || number>list.size()) 
				printf("ERROR: Index out of bounds!\n");
			else if (loadPlugin(list[number-1])) 
				printf("%s plugin loaded successfully!\n", list[number-1]->m_pluginName);
			else
				printf("ERROR: Error loading plugin. It might have already been loaded before.\n");
			break;

		case 'U':
			printf("Plugin index: ");
			scanf("%d", &number);

			if (number<1 || number>list.size())
				printf("ERROR: Index out of bounds!\n");
			else if (unloadPlugin(list[number - 1]))
				printf("%s plugin unloaded successfully!\n", list[number - 1]->m_pluginName);
			else
				printf("ERROR: Error unloading plugin. It has not been loaded.\n");
			break;

		case 'S':
			printPluginList(&list);
			break;
			
		case 'R':
			printf("Plugin index: ");
			scanf("%d", &number);

			if (number<1 || number>list.size())
				printf("ERROR: Index out of bounds!\n");
			else if(!isPluginLoaded(list[number-1]))
				printf("ERROR: %s plugin is not loaded!\n", list[number - 1]->m_pluginName);
			else if(runPlugin(list[number-1]))
				printf("%s plugin ran successfully!\n", list[number - 1]->m_pluginName);
			else
				printf("%s plugin did not run successfully.\n", list[number - 1]->m_pluginName);
			break;

		case 'Q':
			running = 0;
			break;

		default:
			printf("ERROR: No such option!\n");
			break;
		}

		printf("\n");
	}

	freePluginList(&list);

	return 0;
}


