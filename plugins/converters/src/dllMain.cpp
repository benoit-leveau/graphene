
#include "common.h"
#include "converters.h"

const char *getPluginDesc(void)
{
	static std::string strDescription("Converter nodes plug-in");
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
		case 0: { return ItoANodeInterface::instance(); break; }
	}
	return NULL;
}
