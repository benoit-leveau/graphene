
#include "common.h"
#include "executeNode.h"
#include "connection.h"
#include "graph.h"

Node *ExecuteNodeInterface::createNode()
{
	return new ExecuteNode();
}

ValueType ExecuteNode::getSingleInputPortValueType()
{
	return VALUE_NONE;
}

void ExecuteNode::execute(boost::shared_ptr< ConnectionInfo > info)
{
	OUTPUT("ExecuteNode::execute");
	multiConnection &input(info->input_[0]);
	for (multiConnection::iterator it=input.begin(); it!=input.end(); ++it)
	{
		(*it)->getValue();
	}
}
