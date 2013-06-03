
#include "common.h"
#include "PluginManager.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

namespace fs = boost::filesystem;

PluginHandler::PluginHandler(PluginInterface::PluginType type)
:
    bRegistered(false),
	type(type)
{
}

PluginHandler::~PluginHandler()
{
	unregister();
}

void PluginHandler::unregister()
{
	if (bRegistered)
	{
		PluginManager::create()->unregisterHandler(type, this);
		bRegistered = false;
	}
}

void PluginHandler::registerMyself()
{
	if (!bRegistered)
	{
		PluginManager::create()->registerHandler(type, this);
		bRegistered = true;
	}
}

void PluginManager::init(fs::wpath& pluginFolder)
{
	std::cout << "initializing plugin manager with folder: " << toAscii(pluginFolder.string()).c_str() << std::endl;
	if (is_directory(pluginFolder))
	{
		plugins_folder_path = pluginFolder;
		for (fs::wdirectory_iterator itr(plugins_folder_path); itr != fs::wdirectory_iterator(); ++itr)
		{
			std::cout << ">>> loading plugin: " << toAscii(itr->path().string()).c_str() << std::endl;

			// skip folders and non-dll files
			if (is_directory(itr->path()) || (fs::extension(itr->path()) != std::wstring(PLUGIN_EXTENSION))) continue;

			// try to load the dll
			loadPlugin(itr->path());
		}
	}
}

PluginHandle PluginManager::loadPluginHandle(const fs::wpath& plugin_path) const
{
#ifdef WIN32
	return LoadLibraryExW(plugin_path.string().c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
#elif defined MACOS
	const char* szPath = toAscii(plugin_path.string()).c_str();
	return dlopen(szPath, RTLD_LAZY);
#else
	const char* szPath = toAscii(plugin_path.string()).c_str();
	return dlopen(szPath, RTLD_LAZY);
#endif
}

int PluginManager::loadPlugin(const fs::wpath& plugin_path)
{
	PluginHandle hLibraryModule = loadPluginHandle(plugin_path);

	if (hLibraryModule)
	{
		// try to get the standard functions every plugin need to implement
		fgetPluginDesc fptrGetPluginDesc = (fgetPluginDesc)GetSymbolFromPlugin(hLibraryModule, "getPluginDesc");
		fgetPluginNbInterfaces fptrGetPluginNbInterfaces = (fgetPluginNbInterfaces)GetSymbolFromPlugin(hLibraryModule, "getPluginNbInterfaces");
		fgetPluginInterface fptrGetPluginInterface = (fgetPluginInterface)GetSymbolFromPlugin(hLibraryModule, "getPluginInterface");

		// if all three functions are there, register the plugin
		if (fptrGetPluginDesc && fptrGetPluginNbInterfaces && fptrGetPluginInterface)
		{
			// fill the new entry
			boost::shared_ptr<Plugin> plugin(new Plugin);
			plugin->hLibraryModule = hLibraryModule;
			plugin->filename = plugin_path.string();
			plugin->description = std::string(fptrGetPluginDesc());

			std::cout <<"Loading plugin: " << plugin->description << std::endl;
			
			for (int i = 0; i < fptrGetPluginNbInterfaces(); ++i)
			{
				PluginInterface* interface_ = fptrGetPluginInterface(i);

				if (interface_)
				{
					// add the interface
					plugin->interfaces.push_back(interface_);

					// initialize the interface
					interface_->init();

					// connect the plugin to the top handler
					hookHandlerToPlugin(interface_, true);
				}
			}

			if (plugin->interfaces.size() > 0)
			{
				// add the plugin to the list if at least one interface was registered
				listOfPlugins.push_back(plugin);

				// so that when we load manually we know everything went well
				return int(plugin->interfaces.size());
			}
		}

		// not a compatible plugin so unload the plugin (useless to keep it in memory)
		UnloadPlugin(hLibraryModule);

		// file loaded, but no interface was found
		return 0;
	}

	// in case of a manual loading, inform the user the plugin could not be loaded
	return -1;
}

PluginManager::PluginManager()
{
// nothing to do
}

void PluginManager::hookHandlerToPlugin(PluginInterface* interface_, bool bHook)
{
	// search for handlers managing interfaces of the same type as this one
	std::map<PluginInterface::PluginType, std::stack<PluginHandler*> >::iterator it = listOfHandlers.find(interface_->getInterfaceType());
	if (it != listOfHandlers.end())
	{
		std::stack<PluginHandler*> &handlers= (*it).second;
		// if stack is not empty, then hook the interface to the handler at the top
		if (handlers.size()>0)
		{
			if (bHook)
				handlers.top()->hook(interface_);
			else
				handlers.top()->unhook(interface_);
		}
	}
}

void PluginManager::registerHandler(PluginInterface::PluginType type, PluginHandler* handler)
{
	PluginHandler *handlerToRemove = NULL;

	std::map<PluginInterface::PluginType, std::stack<PluginHandler*> >::iterator it = listOfHandlers.find(type);
	if (it == listOfHandlers.end())
	{
		std::stack<PluginHandler*> handlers;
		handlers.push(handler);
		listOfHandlers[type] = handlers;
	}
	else
	{
		std::stack<PluginHandler*> &handlers((*it).second);
		handlerToRemove = handlers.top();
		handlers.push(handler);
	}
	
	connectPluginsToHandler(type, handler, handlerToRemove);
}

void PluginManager::connectPluginsToHandler(PluginInterface::PluginType type, PluginHandler* handler, PluginHandler* handlerToRemove/*=NULL*/)
{
	// then, connect already loaded plugins to this handler
	for (size_t i = 0; i < listOfPlugins.size(); ++i)
	{
		boost::shared_ptr<Plugin> p(listOfPlugins[i]);

		for (size_t j = 0; j < p->interfaces.size(); ++j)
		{
			if (p->interfaces[j]->getInterfaceType() == type)
			{
				if (handlerToRemove)
					handlerToRemove->unhook(p->interfaces[j]);
				handler->hook(p->interfaces[j]);
			}
		}
	}
}

void PluginManager::unregisterHandler(PluginInterface::PluginType type, PluginHandler* handler)
{
	// unregister the handler
	std::map<PluginInterface::PluginType, std::stack<PluginHandler*> >::iterator it = listOfHandlers.find(type);

	if (it != listOfHandlers.end())
	{
		std::stack<PluginHandler*> &handlers((*it).second);
		
		if (handlers.top() == handler)
		{
			handlers.pop();
			if (handlers.size()>0)
				connectPluginsToHandler(type, handlers.top());
		}
		else
		{
			assert(false);
		}
	}
}

void PluginManager::RemovePlugin(boost::shared_ptr<Plugin> p)
{
	for (size_t j = 0; j < p->interfaces.size(); ++j)
	{
		// unhook all interfaces
		hookHandlerToPlugin(p->interfaces[j], false);

		// then exit() them
		p->interfaces[j]->exit();
	}

	// then, release the library
	UnloadPlugin(p->hLibraryModule);

	// finally, remove the entry from the list
	std::vector<boost::shared_ptr<Plugin> >::iterator it = std::find(listOfPlugins.begin(), listOfPlugins.end(), p);
	if (it != listOfPlugins.end())
		listOfPlugins.erase(it);
}

PluginManager::~PluginManager()
{
	for (size_t i = 0; i < listOfPlugins.size(); ++i)
	{
		boost::shared_ptr<Plugin> p(listOfPlugins[i]);
		RemovePlugin(p);
	}
}

PluginManager *PluginManager::create()
{
	static PluginManager instance;
	return &instance;
}
