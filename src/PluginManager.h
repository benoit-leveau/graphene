
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "PluginInterface.h"

#if defined MACOS || defined LINUX
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

#endif

#ifdef WIN32
#define PluginHandle HMODULE
#define GetSymbolFromPlugin GetProcAddress
#define UnloadPlugin FreeLibrary

#else // MACOS OR LINUX
#define PluginHandle void*
#define GetSymbolFromPlugin dlsym
#define UnloadPlugin dlclose

#endif

#ifdef WIN32
#define PLUGIN_EXTENSION L".dll"
#elif defined MACOS
#define PLUGIN_EXTENSION L".dylib"
#else
#define PLUGIN_EXTENSION L".so"
#endif

struct Plugin
{
	PluginHandle hLibraryModule;
	std::wstring filename;
	std::string description;
	std::vector<PluginInterface*> interfaces;

	Plugin()
		:
		hLibraryModule(NULL),
		filename(L""),
		description("")
	{
	}
};

class PluginHandler
{
private:
	// data members
	bool bRegistered;
	PluginInterface::PluginType type;

public:

	// ctor/dtor
	PluginHandler(PluginInterface::PluginType type);
	virtual ~PluginHandler();

	// register the handler to the plugin manager, can't be done in the ctor
	// because the registration need to call the pure virtual hook() method
	// which would result in a pure virtual call
	void registerMyself();

	// unregister the handler in the plugin manager
	// you can call it explicitely but it's also called in the destructor
	void unregister();

	// hook to a specific interface, to be overriden
	virtual void hook(PluginInterface* interface_) = 0;

	// unhook to a specific interface, to be overriden
	virtual void unhook(PluginInterface* interface_) = 0;
};

class PluginManager
{
private:
	// data members
	std::vector< boost::shared_ptr<Plugin> > listOfPlugins;					// list of plugins loaded in memory
	std::map<PluginInterface::PluginType, std::stack<PluginHandler*> > listOfHandlers;	// list of plugin handlers
	boost::filesystem::wpath plugins_folder_path;

	// private methods
	PluginHandle loadPluginHandle(const boost::filesystem::wpath & plugin_path)const;
	void connectPluginsToHandler(PluginInterface::PluginType type, PluginHandler* handler, PluginHandler* handlerToRemove=NULL);
	void hookHandlerToPlugin(PluginInterface* interface_, bool bHook);

	// private ctor/dtor
	PluginManager();
	~PluginManager();

public:

	// ------------------------------------
	//	public methods
	void registerHandler(PluginInterface::PluginType type, PluginHandler* handler);
	void unregisterHandler(PluginInterface::PluginType type, PluginHandler* handler);
	void init(boost::filesystem::wpath & plugins_path);
	int loadPlugin(const boost::filesystem::wpath & plugin_path);
	boost::filesystem::wpath getFolder() const {return plugins_folder_path;}
	void getListOfPlugins(std::vector< boost::shared_ptr<Plugin> > &list) const{list = listOfPlugins;}
	void RemovePlugin(boost::shared_ptr<Plugin> p);
	// ------------------------------------

	// callback method
	static PluginManager* create();
};

#endif // !PLUGINMANAGER_H
