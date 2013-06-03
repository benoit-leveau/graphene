
#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "NodeInterface.h"
#include "convenientNodes.h"
#include "list_classIds.h"

class ItoANodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_ITOA_NODE;}
	Node *createNode();

	static ItoANodeInterface *instance();
};

class ItoANode : public SingleInputSingleOutputNode
{
public:
	ItoANode();

	// input
	ValueType getSingleInputPortValueType();
	unsigned int allowedInputTypes(int index);

	// output
	ValueType getSingleOutputPortValueType();

	// edit
	void editParameters(const Value &setting){}

	// execute
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

#endif // !CONVERTERS_H
