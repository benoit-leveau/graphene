
#ifndef CONDITIONALNODES_H
#define CONDITIONALNODES_H

#include "connection.h"
#include "NodeInterface.h"
#include "convenientNodes.h"
#include "list_classIds.h"

// ------------------------------------------------

class FileNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_FILE_NODE;}
	Node *createNode();
	static FileNodeInterface *instance();
};

class FileNode : public SingleFixedOutputNode
{
public:
	FileNode();

	// dynamic input
	int getNbInputPort(){return 1;}
	PortConnectionType getInputPortConnectionType(int index){return CONNECTION_SINGLE;}
      ValueType getInputPortValueType(int index){return VALUE_STRING;}
		
	// dynamic output
	ValueType getSingleOutputPortValueType(){return VALUE_STRING;}
	
	void editParameters(const Value &setting){}

	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// ------------------------------------------------

class StreamFileNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_STREAM_FILE_NODE;}
	Node *createNode();
	static StreamFileNodeInterface *instance();
};

class StreamFileNode : public SingleFixedOutputNode
{
public:
	StreamFileNode();

	// dynamic input
	int getNbInputPort(){return 1;}
	PortConnectionType getInputPortConnectionType(int index){return CONNECTION_SINGLE;}
    ValueType getInputPortValueType(int index){return VALUE_STRING;}
		
	// dynamic output
	bool getOutputPortStream(int index){return true;}
	ValueType getSingleOutputPortValueType(){return VALUE_STRING;}
	
	void editParameters(const Value &setting){}

	void execute(boost::shared_ptr< ConnectionInfo > info);
};

#endif // !CONDITIONALNODES_H
