
#include "common.h"

#include "NodeFactory.h"
#include "NodeInterface.h"
#include <iostream>

NodeFactory::NodeFactory() :
	PluginHandler(PluginInterface::PT_Node)
{
	// register the handler in the plugin manager
	registerMyself();
}

NodeFactory::~NodeFactory()
{

}

void NodeFactory::hook(PluginInterface *pluginInterface)
{
	// a new plugin interface is connected
	NodeInterface * node_interface = static_cast<NodeInterface *>(pluginInterface);
	mapOfRegisteredNodes_[node_interface->classID()] = node_interface;
	OUTPUT("adding a node interface");
}

void NodeFactory::unhook(PluginInterface *pluginInterface)
{
	// an existing plugin interface is disconnected
	NodeInterface * node_interface = static_cast<NodeInterface *>(pluginInterface);
	std::map<ClassID, NodeInterface *>::iterator it = mapOfRegisteredNodes_.find(node_interface->classID());
	if (it != mapOfRegisteredNodes_.end())
	{
		// check if the plugin node is used in the scene!
		// ...

		// remove the interface from the list
		mapOfRegisteredNodes_.erase(it);
	}
}

Node *NodeFactory::createNode(ClassID id)
{
	std::map<ClassID, NodeInterface *>::iterator it = mapOfRegisteredNodes_.find(id);
	if (it != mapOfRegisteredNodes_.end())
	{
		NodeInterface *interface_((*it).second);
		return interface_->createNode();
	}
	return NULL;
}

NodeFactory &NodeFactory::instance()
{
	static NodeFactory instance;
	return instance;
}
