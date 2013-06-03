
#include "common.h"
#include "nodes.h"
#include "connection.h"

Node *StringNodeInterface::createNode()
{
	return new StringNode();
};

StringNodeInterface *StringNodeInterface::instance()
{
	static StringNodeInterface instance;
	return &instance;
}

StringNode::StringNode() : myString_("")
{
}

void StringNode::editParameters(const Value &setting)
{
	if (setting.getType() == VALUE_STRING)
		myString_ = setting.getStringValue2();
}

ValueType StringNode::getSingleOutputPortValueType()
{
	return VALUE_STRING;
}

void StringNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("StringNode::execute");
	info->output_[0]->setValue(myString_);
}

// ---------------------------------------------

Node *IntegerNodeInterface::createNode()
{
	return new IntegerNode();
};

IntegerNodeInterface *IntegerNodeInterface::instance()
{
	static IntegerNodeInterface instance;
	return &instance;
}

IntegerNode::IntegerNode() : myInt_(0)
{
}

void IntegerNode::editParameters(const Value &setting)
{
	if (setting.getType() == VALUE_INTEGER)
		myInt_ = setting;
}

ValueType IntegerNode::getSingleOutputPortValueType()
{
	return VALUE_INTEGER;
}

void IntegerNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("IntegerNode::execute");
	info->output_[0]->setValue(myInt_);
}

// ---------------------------------------------

Node *BooleanNodeInterface::createNode()
{
	return new BooleanNode();
};

BooleanNodeInterface *BooleanNodeInterface::instance()
{
	static BooleanNodeInterface instance;
	return &instance;
}

BooleanNode::BooleanNode() : myBool_(false)
{
}

void BooleanNode::editParameters(const Value &setting)
{
	if (setting.getType() == VALUE_BOOLEAN)
		myBool_ = setting;
}

ValueType BooleanNode::getSingleOutputPortValueType()
{
	return VALUE_BOOLEAN;
}

void BooleanNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("BooleanNode::execute");
	info->output_[0]->setValue(myBool_);
}

// -----------------------------------

Node *FloatNodeInterface::createNode()
{
	return new FloatNode();
};

FloatNodeInterface *FloatNodeInterface::instance()
{
	static FloatNodeInterface instance;
	return &instance;
}

FloatNode::FloatNode() : myFloat_(0.f)
{
}

void FloatNode::editParameters(const Value &setting)
{
	if (setting.getType() == VALUE_FLOAT)
		myFloat_ = setting;
}

ValueType FloatNode::getSingleOutputPortValueType()
{
	return VALUE_FLOAT;
}

void FloatNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("FloatNode::execute");
	info->output_[0]->setValue(myFloat_);
}

// -----------------------------------

Node *Point3NodeInterface::createNode()
{
	return new Point3Node();
};

Point3NodeInterface *Point3NodeInterface::instance()
{
	static Point3NodeInterface instance;
	return &instance;
}

Point3Node::Point3Node()
{
}

void Point3Node::editParameters(const Value &setting)
{
	if (setting.getType() == VALUE_POINT3)
		myPoint_ = setting;
}

ValueType Point3Node::getSingleOutputPortValueType()
{
	return VALUE_POINT3;
}

void Point3Node::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("Point3Node::execute");
	info->output_[0]->setValue(myPoint_);
}

// -----------------------------------

Node *Matrix3NodeInterface::createNode()
{
	return new Matrix3Node();
};

Matrix3NodeInterface *Matrix3NodeInterface::instance()
{
	static Matrix3NodeInterface instance;
	return &instance;
}

Matrix3Node::Matrix3Node()
{
}

void Matrix3Node::editParameters(const Value &setting)
{
	if (setting.getType() == VALUE_MATRIX3)
		myMatrix_ = setting;
}

ValueType Matrix3Node::getSingleOutputPortValueType()
{
	return VALUE_MATRIX3;
}

void Matrix3Node::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("Matrix3Node::execute");
	info->output_[0]->setValue(myMatrix_);
}
