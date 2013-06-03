
#ifndef CONDITIONALNODES_H
#define CONDITIONALNODES_H

#include "connection.h"
#include "NodeInterface.h"
#include "convenientNodes.h"
#include "list_classIds.h"

// ------------------------------------------------

class IfNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_IF_NODE;}
	Node *createNode();
	static IfNodeInterface *instance();
};

class IfNode : public SingleFixedOutputNode
{
public:
	IfNode();

	// dynamic input
	int getNbInputPort(){return 3;}
	PortConnectionType getInputPortConnectionType(int index){return CONNECTION_SINGLE;}
	ValueType getInputPortValueType(int index);
		
	// dynamic output
	ValueType getSingleOutputPortValueType(){return VALUE_DYNAMIC;}
	
	void editParameters(const Value &setting){}

	void execute(boost::shared_ptr< ConnectionInfo > info);
};

#endif // !CONDITIONALNODES_H
