
#include "common.h"
#include "application.h"
#include "graph.h"
#include "NodeFactory.h"
#include "PluginManager.h"

#ifndef WIN32
#include <sys/stat.h>
#endif // WIN32

#define PLUGINS_DIR "plugins/"

Application::Application()
{
#ifdef WIN32
	wchar_t wszAppPath[260];
	GetModuleFileNameW(NULL, wszAppPath, 260);
	wchar_t *c = wcsrchr(wszAppPath, '\\');
	c[1] = 0;
	boost::filesystem::path pluginsPath(wszAppPath);
#else
    char linkname[200];
    ssize_t r = readlink("/proc/self/exe", linkname, 200);
    linkname[r] = '\0';
    boost::filesystem::path pluginsPath = boost::filesystem::path(linkname).parent_path();
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
