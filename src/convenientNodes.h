
#ifndef CONVENIENTNODES_H
#define CONVENIENTNODES_H

class SimpleNode : public Node
{
   public:
      // sub-inputs
      virtual int getNbSubInputPort(){return 0;}

      // sub-outputs
      virtual int getNbSubOutputPort(){return 0;}

      // sub execute
      Value subExecute(boost::shared_ptr< ConnectionInfo > info){return Value();}
};

class NoInputNode : public SimpleNode
{
   public:
      int getNbInputPort(){return 0;}
      PortConnectionType getInputPortConnectionType(int index){return CONNECTION_SINGLE;}
      ValueType getInputPortValueType(int index){return VALUE_NONE;}
};

class NoOutputNode : public SimpleNode
{
   public:
      int getNbOutputPort(){return 1;}
      ValueType getOutputPortValueType(int index){return VALUE_NONE;}
};

class SingleFixedOutputNode : public SimpleNode
{
   public:
      int getNbOutputPort(){return 1;}
      ValueType getOutputPortValueType(int index)
      {
	 return getSingleOutputPortValueType();
      }

      virtual ValueType getSingleOutputPortValueType() = 0;
};

class NoInputSingleFixedOutputNode : public NoInputNode
{
   public:
      int getNbOutputPort(){return 1;}
      ValueType getOutputPortValueType(int index)
      {
	 return getSingleOutputPortValueType();
      }

      virtual ValueType getSingleOutputPortValueType() = 0;
};

class SingleInputNoOutputNode : public NoOutputNode
{
   public:
      int getNbInputPort(){return 1;}
      ValueType getInputPortValueType(int index)
      {
	 return getSingleInputPortValueType();
      }

      virtual ValueType getSingleInputPortValueType() = 0;
};

class SingleInputSingleOutputNode : public SimpleNode
{
   public:
      int getNbInputPort(){return 1;}
      PortConnectionType getInputPortConnectionType(int index){return CONNECTION_SINGLE;}
      ValueType getInputPortValueType(int index)
      {
	 return getSingleInputPortValueType();
      }
      int getNbOutputPort(){return 1;}
      ValueType getOutputPortValueType(int index)
      {
	 return getSingleOutputPortValueType();
      }

      // to override
      virtual ValueType getSingleInputPortValueType() = 0;
      virtual ValueType getSingleOutputPortValueType() = 0;
};

#endif // !CONVENIENTNODES_H
