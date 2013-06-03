
#include "common.h"
#include "loops.h"

ForNodeInterface *ForNodeInterface::instance()
{
	static ForNodeInterface instance;
	return &instance;
}

Node *ForNodeInterface::createNode()
{
	return new ForNode();
};

ForNode::ForNode() : iteration_(-1)
{
}

Value ForNode::subExecute(boost::shared_ptr< ConnectionInfo > info)
{
	OUTPUT(">>>ForNode::subExecute");
	return Value(iteration_);
}

void ForNode::setSubOutputDirty(multiConnection &output)
{
	int nbInput = getNbInputPort();
	int nbSubInput = getNbSubInputPort();
	for (int i=nbInput; i<nbInput+nbSubInput; ++i)
	{
		output[i]->setDirty();
	}
}

void ForNode::execute(boost::shared_ptr< ConnectionInfo > info)
{
	OUTPUT("ForNode::execute");
	iteration_ = 0;
	boost::shared_ptr<Connection> iterations_connection(info->input_[0][0]);
	if (iterations_connection->isConnected())
	{
		int nb_iterations = iterations_connection->getValue();
		for (int i=0; i<nb_iterations; ++i)
		{
			iteration_ = i;
			info->input_[1][0]->getValue();
			setSubOutputDirty(info->output_);
		}
	}
}

// --------------------------------------------------
					
WhileNodeInterface *WhileNodeInterface::instance()
{
	static WhileNodeInterface instance;
	return &instance;
}

Node *WhileNodeInterface::createNode()
{
	return new WhileNode();
};

WhileNode::WhileNode()
{
}

ValueType WhileNode::getInputPortValueType(int index)
{
	switch(index)
	{
		case 0: return VALUE_BOOLEAN;
		case 1: return VALUE_DYNAMIC;
		case 2: return VALUE_DYNAMIC;
	}
	return VALUE_NONE;
}

void WhileNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("WhileNode::execute");
}
