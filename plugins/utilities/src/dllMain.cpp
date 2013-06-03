
#include "common.h"
#include "utilities.h"

extern "C"
{
const char *getPluginDesc(void)
{
	static std::string strDescription("Utilities nodes plug-in");
	return strDescription.c_str();
}

int getPluginNbInterfaces(void)
{
	return 1;
}

PluginInterface *getPluginInterface(int index)
{
	switch(index)
	{
		case 0: { return ConsoleOutputNodeInterface::instance(); break; }
	}
	return NULL;
}
}
