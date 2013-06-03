
#ifndef EXECUTENODE_H
#define EXECUTENODE_H

#include "NodeInterface.h"
#include "convenientNodes.h"

#define CID_EXECUTE_NODE ClassID(0,0)

class ExecuteNodeInterface : public NodeInterface
{
	virtual void init(){}
	virtual void exit(){}
	ClassID classID() const{return CID_EXECUTE_NODE;}

	Node *createNode();
};

class ExecuteNode : public SingleInputNoOutputNode
{
public:
	ValueType getSingleInputPortValueType();
	PortConnectionType getInputPortConnectionType(int index){return CONNECTION_MULTIPLE;}
	void execute(boost::shared_ptr< ConnectionInfo > info);
	void editParameters(const Value &){}
};

#endif //!EXECUTENODE_H
