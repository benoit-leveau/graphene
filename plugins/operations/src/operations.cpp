
#include "common.h"
#include "operations.h"

ConcatNodeInterface *ConcatNodeInterface::instance()
{
	static ConcatNodeInterface instance;
	return &instance;
}

Node *ConcatNodeInterface::createNode()
{
	return new ConcatNode();
};

ConcatNode::ConcatNode()
{
}

ValueType ConcatNode::getSingleOutputPortValueType()
{
	return VALUE_STRING;
}

void ConcatNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("ConcatNode::execute");
	std::string result("");
	multiConnection connection(info->input_[0]);
	for (multiConnection::iterator it = connection.begin(); it != connection.end(); ++it)
	{
		boost::shared_ptr<Connection> connection(*it);
		if (connection->isConnected())
		{
			result += std::string(connection->getValue());
		}
	}
	info->output_[0]->setValue(result);
}

// -------------------

AddMultIntNodeInterface *AddMultIntNodeInterface::instance()
{
	static AddMultIntNodeInterface instance;
	return &instance;
}

Node *AddMultIntNodeInterface::createNode()
{
	return new AddMultIntNode();
};

AddMultIntNode::AddMultIntNode()
{
}

ValueType AddMultIntNode::getSingleOutputPortValueType()
{
	return VALUE_INTEGER;
}

void AddMultIntNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("AddMultIntNode::execute");
	int result = 0;

	multiConnection connection(info->input_[0]);
	for (multiConnection::iterator it = connection.begin(); it != connection.end(); ++it)
	{
		boost::shared_ptr<Connection> connection(*it);
		if (connection->isConnected())
		{
			result += int(connection->getValue());
		}
	}
	info->output_[0]->setValue(result);
}

// -------------------

GenericAddNodeInterface *GenericAddNodeInterface::instance()
{
	static GenericAddNodeInterface instance;
	return &instance;
}

Node *GenericAddNodeInterface::createNode()
{
	return new GenericAddNode();
};

GenericAddNode::GenericAddNode()
{
}

unsigned int GenericAddNode::allowedInputTypes(int index)
{
	return (1<<VALUE_INTEGER | 1<<VALUE_FLOAT | 1<<VALUE_STRING | 1<<VALUE_POINT3 | 1<<VALUE_MATRIX3);
}

unsigned int GenericAddNode::allowedOutputTypes(int index)
{
	return (1<<VALUE_INTEGER | 1<<VALUE_FLOAT | 1<<VALUE_STRING | 1<<VALUE_POINT3 | 1<<VALUE_MATRIX3);
}

void GenericAddNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("GenericAddNode::execute");

	Value result;
	multiConnection connection(info->input_[0]);
	ValueType dynamicType = VALUE_DYNAMIC;
	for (multiConnection::iterator it = connection.begin(); it != connection.end(); ++it)
	{
		boost::shared_ptr<Connection> connection(*it);
		if (connection->isConnected())
		{
			const Value &value(connection->getValue());
			ValueType currentType = value.getType();
			
			if (!(1<<currentType & allowedInputTypes(0)))
			{
				// type not compatible
				std::cout << "[GenericAddNode] warning: type not compatible!" << std::endl;
				continue;
			}
			else if (dynamicType == VALUE_DYNAMIC)
			{
				// type not yet chosen
				dynamicType = currentType;
				switch(dynamicType)
				{
					case VALUE_INTEGER:
					{
						result = int(value);
						break;
					}
					case VALUE_FLOAT:
					{
						result = float(value);
						break;
					}
					case VALUE_STRING:
					{
						result = std::string(value);
						break;
					}
					case VALUE_POINT3:
					{
						result = Point3(value);
						break;
					}
					case VALUE_MATRIX3:
					{
						result = Matrix3(value.getMatrix3Value2());
						break;
					}
				}
			}
			else if (currentType != dynamicType)
			{
				// ignore this input
				std::cout << "[GenericAddNode] warning: different types in input!" << std::endl;
				continue;
			}
			else
			{
				switch(dynamicType)
				{
					case VALUE_INTEGER:
					{
						result = Value(int(result) + int(value));
						break;
					}
					case VALUE_FLOAT:
					{
						result = Value(float(result) + float(value));
						break;
					}
					case VALUE_STRING:
					{
						result = Value(std::string(result) + std::string(value));
						break;
					}
					case VALUE_POINT3:
					{
						result = Value(Point3(result) + Point3(value));
						break;
					}
					case VALUE_MATRIX3:
					{
						result = Value(Matrix3(result.getMatrix3Value2()) + Matrix3(value.getMatrix3Value2()));
						break;
					}
				}
			}
		}
	}
	info->output_[0]->setValue(result);
}
