
#include "common.h"
#include "fileNodes.h"

extern "C"
{
const char *getPluginDesc(void)
{
	static std::string strDescription("File nodes plug-in");
	return strDescription.c_str();
}

int getPluginNbInterfaces(void)
{
	return 2;
}

PluginInterface *getPluginInterface(int index)
{
	switch(index)
	{
		case 0: { return FileNodeInterface::instance(); break; }
		case 1: { return StreamFileNodeInterface::instance(); break; }
	}
	return NULL;
}
}
