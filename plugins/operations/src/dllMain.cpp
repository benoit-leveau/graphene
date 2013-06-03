
#include "common.h"
#include "operations.h"

extern "C"
{
const char *getPluginDesc(void)
{
	static std::string strDescription("Add node plug-in");
	return strDescription.c_str();
}

int getPluginNbInterfaces(void)
{
	return 3;
}

PluginInterface *getPluginInterface(int index)
{
	switch(index)
	{
		case 0: { return ConcatNodeInterface::instance(); break; }
		case 1: { return AddMultIntNodeInterface::instance(); break; }
		case 2: { return GenericAddNodeInterface::instance(); break; }
	}
	return NULL;
}
}
