
#include "common.h"
#include "converters.h"
#include "connection.h"
#include "graph.h"

Node *ItoANodeInterface::createNode()
{
	return new ItoANode();
};

ItoANodeInterface *ItoANodeInterface::instance()
{
	static ItoANodeInterface instance;
	return &instance;
}

ItoANode::ItoANode()
{
}

ValueType ItoANode::getSingleInputPortValueType()
{
	return VALUE_DYNAMIC;
}

unsigned int ItoANode::allowedInputTypes(int index)
{
	return (1<<VALUE_INTEGER | 1<<VALUE_FLOAT | 1<<VALUE_POINT3 | 1<<VALUE_MATRIX3);
}

ValueType ItoANode::getSingleOutputPortValueType()
{
	return VALUE_STRING;
}

void ItoANode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("ItoANode::execute");
	boost::shared_ptr<Connection> connection(info->input_[0][0]);
	std::string result("");
	if (connection->isConnected())
	{
		const Value &value(connection->getValue());
		switch(value.getType())
		{
			case VALUE_INTEGER:
			{
				result = (boost::format("%d") % int(value)).str();
				break;
			}
			case VALUE_FLOAT:
			{
				result = (boost::format("%f") % float(value)).str();
				break;
			}
			case VALUE_POINT3:
			{
				Point3 p(value);
				result = (boost::format("(%f, %f, %f)") % p.x % p.y % p.z).str();
				break;
			}
			case VALUE_MATRIX3:
			{
				Matrix3 m(value.getMatrix3Value2());
				boost::format fmt("(%f, %f, %f) (%f, %f, %f) (%f, %f, %f)");
				for (int i=0; i<3; ++i)
					for (int j=0; j<3; ++j)
						fmt = fmt % m.x[i][j];
				result = fmt.str();
				break;
			}
		}
	}
	info->output_[0]->setValue(result);
}
