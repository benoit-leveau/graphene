
#ifndef NODEINTERFACE_H
#define NODEINTERFACE_H

#include "PluginInterface.h"
#include "basicTypes.h"
#include "value.h"
#include "classId.h"

class Graph;
class ConnectionInfo;

// abstract class used to derive node plug-ins from
class Node
{
public:
  Node(){}
  virtual ~Node(){}

  // inputs
  virtual int getNbInputPort() = 0;
  virtual int getNbSubInputPort() = 0;
  virtual PortConnectionType getInputPortConnectionType(int index) = 0;
  virtual ValueType getInputPortValueType(int index) = 0;
  unsigned virtual int allowedInputTypes(int index){return 0;}

  // outputs
  virtual int getNbOutputPort() = 0;
  virtual int getNbSubOutputPort() = 0;	
  virtual bool getOutputPortStream(int index){return false;}
  virtual ValueType getOutputPortValueType(int index) = 0;
  unsigned virtual int allowedOutputTypes(int index){return 0;}

  // customization
  virtual void editParameters(const Value &setting) = 0;

  // execute
  virtual void execute(boost::shared_ptr< ConnectionInfo > info) = 0;
  virtual Value subExecute(boost::shared_ptr< ConnectionInfo > info) = 0;
};

// abstract class used to derive node interface plug-ins from
class NodeInterface : public PluginInterface
{
public:
  NodeInterface(){}
  virtual ~NodeInterface(){};

  //virtual void init() = 0;
  //virtual void exit() = 0;
  virtual ClassID classID() const = 0;

  virtual Node *createNode() = 0;
  PluginType getInterfaceType() const { return PT_Node; }
};

#endif // !NODEINTERFACE_H
