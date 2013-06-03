
#ifndef CONDITIONALNODES_H
#define CONDITIONALNODES_H

#include "connection.h"
#include "NodeInterface.h"
#include "convenientNodes.h"
#include "list_classIds.h"

// ------------------------------------------------

class ForNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_FOR_NODE;}
	Node *createNode();
	static ForNodeInterface *instance();
};

class ForNode : public Node
{
private:
	int iteration_;

	void setSubOutputDirty(multiConnection &output);

public:
	ForNode();

	// inputs
	virtual int getNbInputPort(){return 1;}
  virtual PortConnectionType getInputPortConnectionType(int index){return CONNECTION_SINGLE;}
  virtual ValueType getInputPortValueType(int index){return (index==0) ? VALUE_INTEGER : VALUE_NONE;}
  unsigned virtual int allowedInputTypes(int index){return 0;}

  // outputs
  virtual int getNbOutputPort(){return 1;}
  virtual ValueType getOutputPortValueType(int index){return (index==0) ? VALUE_NONE : VALUE_INTEGER;}
  unsigned virtual int allowedOutputTypes(int index){return 0;}

  // sub-inputs
  virtual int getNbSubInputPort(){return 1;}

  // outputs
  virtual int getNbSubOutputPort(){return 1;}

  // customization
	void editParameters(const Value &setting){}

	Value subExecute(boost::shared_ptr< ConnectionInfo > info);
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// ------------------------------------------------

class WhileNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_WHILE_NODE;}
	Node *createNode();
	static WhileNodeInterface *instance();
};

class WhileNode : public SingleFixedOutputNode
{
public:
	WhileNode();

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
