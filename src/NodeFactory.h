
#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include "PluginManager.h"
#include "NodeInterface.h"

class NodeFactory : public PluginHandler
{
private:
	std::map<ClassID, NodeInterface *> mapOfRegisteredNodes_;

public:
	NodeFactory();
	~NodeFactory();

	// from PluginHandler interface
	void hook(PluginInterface *pluginInterface);
	void unhook(PluginInterface *pluginInterface);

	Node *createNode(ClassID id);
	static NodeFactory &instance();
};


#endif // !NODEFACTORY_H
