
#include "common.h"
#include "conditionalNodes.h"

extern "C"
{
const char *getPluginDesc(void)
{
	static std::string strDescription("Conditional nodes plug-in");
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
		case 0: { return IfNodeInterface::instance(); break; }
	}
	return NULL;
}
}
