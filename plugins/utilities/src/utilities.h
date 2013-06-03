
#ifndef UTILITIES_H
#define UTILITIES_H

#include "NodeInterface.h"
#include "convenientNodes.h"
#include "list_classIds.h"

class ConsoleOutputNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_CONSOLE_OUTPUT_NODE;}
	Node *createNode();
	static ConsoleOutputNodeInterface *instance();
};

class ConsoleOutputNode : public SingleInputNoOutputNode
{
private:
	std::string consoleName_;
public:
	ConsoleOutputNode();
	
	// input
	ValueType getSingleInputPortValueType();
	PortConnectionType getInputPortConnectionType(int index){return CONNECTION_SINGLE;}

	// edit
	void editParameters(const Value &setting);

	// execute
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

#endif // !UTILITIES_H
