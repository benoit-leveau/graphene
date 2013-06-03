
#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "connection.h"
#include "graph.h"
#include "NodeInterface.h"
#include "convenientNodes.h"
#include "list_classIds.h"

// ------------------------------------------------

class ConcatNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_CONCAT_NODE;}
	Node *createNode();
	static ConcatNodeInterface *instance();
};

class ConcatNode : public SingleFixedOutputNode
{
public:
	ConcatNode();

	// 
	int getNbInputPort(){return 1;}
	PortConnectionType getInputPortConnectionType(int index){return CONNECTION_MULTIPLE;}
	ValueType getInputPortValueType(int index){return VALUE_STRING;}

	ValueType getSingleOutputPortValueType();

	void editParameters(const Value &setting){}

	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// ---------------------------

class AddMultIntNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_MULTADD_NODE;}
	Node *createNode();
	static AddMultIntNodeInterface *instance();
};

class AddMultIntNode : public SingleFixedOutputNode
{
public:
	AddMultIntNode();

	// 
	int getNbInputPort(){return 1;}
	PortConnectionType getInputPortConnectionType(int index){return CONNECTION_MULTIPLE;}
	ValueType getInputPortValueType(int index){return VALUE_INTEGER;}

	void editParameters(const Value &setting){}

	ValueType getSingleOutputPortValueType();
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// ---------------------------

class GenericAddNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_GENERICADD_NODE;}
	Node *createNode();
	static GenericAddNodeInterface *instance();
};

class GenericAddNode : public SingleFixedOutputNode
{
public:
	GenericAddNode();

	// 
	int getNbInputPort(){return 1;}
	PortConnectionType getInputPortConnectionType(int index){return CONNECTION_MULTIPLE;}
	
	// dynamic input
	ValueType getInputPortValueType(int index){return VALUE_DYNAMIC;}
	unsigned int allowedInputTypes(int index);
	
	// dynamic output
	ValueType getSingleOutputPortValueType(){return VALUE_DYNAMIC;}
	unsigned int allowedOutputTypes(int index);

	void editParameters(const Value &setting){}
	
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

#endif // !OPERATIONS_H
