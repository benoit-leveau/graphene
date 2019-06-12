
#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

class PluginInterface
{
	public:

    enum PluginType
        {
			PT_Node = 0,
		};

    // abstract class used to derive plug-ins from
    virtual void init() = 0;
    virtual void exit() = 0;
    virtual PluginType getInterfaceType() const = 0;
    virtual ~PluginInterface(){}
};

// needed exported function "getPluginDesc"
typedef const char *(*fgetPluginDesc) (void);

// needed exported function "getPluginNbInterfaces"
typedef int (*fgetPluginNbInterfaces) (void);

// needed exported function "getPluginInterface"
typedef PluginInterface* (*fgetPluginInterface) (int index);


#endif // !PLUGININTERFACE_H
