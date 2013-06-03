
#include "common.h"
#include "nodes.h"

extern "C"
{
const char *getPluginDesc(void)
{
	static std::string strDescription("Basic nodes plug-in");
	return strDescription.c_str();
}

int getPluginNbInterfaces(void)
{
	return 6;
}

PluginInterface *getPluginInterface(int index)
{
	switch(index)
	{
		case 0: { return BooleanNodeInterface::instance(); break; }
		case 1: { return IntegerNodeInterface::instance(); break; }
		case 2: { return FloatNodeInterface::instance(); break; }
		case 3: { return StringNodeInterface::instance(); break; }
		case 4: { return Point3NodeInterface::instance(); break; }
		case 5: { return Matrix3NodeInterface::instance(); break; }
	}
	return NULL;
}
}
