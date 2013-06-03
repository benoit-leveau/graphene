
#ifndef NODES_H
#define NODES_H

#include "NodeInterface.h"
#include "convenientNodes.h"
#include "list_classIds.h"

class StringNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_STRING_NODE;}
	Node *createNode();

	static StringNodeInterface *instance();
};

class StringNode : public NoInputSingleFixedOutputNode
{
private:
	std::string myString_;
public:
	StringNode();

	// edit
	void editParameters(const Value &setting);

	// input
	ValueType getSingleOutputPortValueType();

	// execute
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// --------------------------------

class IntegerNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_INTEGER_NODE;}
	Node *createNode();

	static IntegerNodeInterface *instance();
};

class IntegerNode : public NoInputSingleFixedOutputNode
{
private:
	int myInt_;
public:
	IntegerNode();

	// input
	ValueType getSingleOutputPortValueType();

	// edit
	void editParameters(const Value &setting);

	// execute
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// --------------------------------

class BooleanNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_BOOLEAN_NODE;}
	Node *createNode();

	static BooleanNodeInterface *instance();
};

class BooleanNode : public NoInputSingleFixedOutputNode
{
private:
	bool myBool_;
public:
	BooleanNode();

	// input
	ValueType getSingleOutputPortValueType();

	// edit
	void editParameters(const Value &setting);

	// execute
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// --------------------------------

class FloatNodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_FLOAT_NODE;}
	Node *createNode();

	static FloatNodeInterface *instance();
};

class FloatNode : public NoInputSingleFixedOutputNode
{
private:
	float myFloat_;
public:
	FloatNode();

	// input
	ValueType getSingleOutputPortValueType();

	// edit
	void editParameters(const Value &setting);

	// execute
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// --------------------------------

class Point3NodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_POINT3_NODE;}
	Node *createNode();

	static Point3NodeInterface *instance();
};

class Point3Node : public NoInputSingleFixedOutputNode
{
private:
	Point3 myPoint_;
public:
	Point3Node();

	// input
	ValueType getSingleOutputPortValueType();

	// edit
	void editParameters(const Value &setting);

	// execute
	void execute(boost::shared_ptr< ConnectionInfo > info);
};

// --------------------------------

class Matrix3NodeInterface : public NodeInterface
{
public:
	void init(){}
	void exit(){}
	ClassID classID() const{return CID_MATRIX3_NODE;}
	Node *createNode();

	static Matrix3NodeInterface *instance();
};

class Matrix3Node : public NoInputSingleFixedOutputNode
{
private:
	Matrix3 myMatrix_;
public:
	Matrix3Node();

	// input
	ValueType getSingleOutputPortValueType();

	// edit
	void editParameters(const Value &setting);

	// execute
	void execute(boost::shared_ptr< ConnectionInfo > info);
};
#endif // !NODES_H
