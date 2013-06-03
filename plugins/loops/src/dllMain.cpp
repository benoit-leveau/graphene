
#include "common.h"
#include "loops.h"

const char *getPluginDesc(void)
{
	static std::string strDescription("Loops nodes plug-in");
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
		case 0: { return ForNodeInterface::instance(); break; }
	}
	return NULL;
}
