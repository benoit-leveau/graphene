
#include "common.h"
#include "utilities.h"
#include "connection.h"
#include "graph.h"

Node *ConsoleOutputNodeInterface::createNode()
{
	return new ConsoleOutputNode();
};

ConsoleOutputNodeInterface *ConsoleOutputNodeInterface::instance()
{
	static ConsoleOutputNodeInterface instance;
	return &instance;
}

ConsoleOutputNode::ConsoleOutputNode() : consoleName_("")
{
}

void ConsoleOutputNode::editParameters(const Value &setting)
{
	if (setting.getType() == VALUE_STRING)
		consoleName_ = setting.getStringValue2();
}

ValueType ConsoleOutputNode::getSingleInputPortValueType()
{
	return VALUE_STRING;
}

void ConsoleOutputNode::execute(boost::shared_ptr< ConnectionInfo > info)
{
	OUTPUT("ConsoleOutput::execute");
	boost::shared_ptr<Connection> connection(info->input_[0][0]);
	std::string prefix = (consoleName_.empty()) ? "" : "[" + consoleName_ + "]: ";
	if (!connection->isConnected())
		std::cout << prefix << "No connection!" << std::endl;
	else
	{
		const Value &value(connection->getValue());
		std::cout << prefix << std::string(value).c_str() << std::endl;
	}
	info->output_[0]->setValue(Value());
}
