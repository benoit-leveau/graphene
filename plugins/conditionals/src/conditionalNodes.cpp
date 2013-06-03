
#include "common.h"
#include "conditionalNodes.h"

IfNodeInterface *IfNodeInterface::instance()
{
	static IfNodeInterface instance;
	return &instance;
}

Node *IfNodeInterface::createNode()
{
	return new IfNode();
};

IfNode::IfNode()
{
}

ValueType IfNode::getInputPortValueType(int index)
{
	switch(index)
	{
		case 0: return VALUE_BOOLEAN;
		case 1: return VALUE_DYNAMIC;
		case 2: return VALUE_DYNAMIC;
	}
	return VALUE_NONE;
}

void IfNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("IfNode::execute");
	multiConnection connection_condition(info->input_[0]);
	multiConnection connection_then(info->input_[1]);
	multiConnection connection_else(info->input_[2]);
	Value result;
	if (connection_condition[0]->isConnected())
	{
		const Value &value(connection_condition[0]->getValue());
		bool condition = value;
		if (condition)
		{
			if (connection_then[0]->isConnected())
				result = connection_then[0]->getValue();
		}
		else
		{
			if (connection_else[0]->isConnected())
				result = connection_else[0]->getValue();
		}
	}
	info->output_[0]->setValue(result);
}
