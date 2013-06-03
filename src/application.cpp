
#include "common.h"
#include "application.h"
#include "graph.h"
#include "NodeFactory.h"
#include "PluginManager.h"

#define PLUGINS_DIR L"plugins/"

Application::Application()
{
#ifdef WIN32
	wchar_t wszAppPath[260];
	GetModuleFileNameW(NULL, wszAppPath, 260);
	wchar_t *c = wcsrchr(wszAppPath, '\\');
	c[1] = 0;
	boost::filesystem::wpath pluginsPath(wszAppPath);
#else
    boost::filesystem::wpath pluginsPath( boost::filesystem::current_path<boost::filesystem::wpath>() );
#endif
	pluginsPath /= PLUGINS_DIR;
	PluginManager::create()->init(pluginsPath);
}

Application::~Application()
{
}

boost::shared_ptr<ClientGraph> Application::createGraph()
{
	return boost::shared_ptr<Graph>(new Graph());
}
