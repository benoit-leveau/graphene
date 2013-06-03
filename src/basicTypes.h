
#ifndef BASICTYPES_H
#define BASICTYPES_H

enum PortConnectionType
{
	CONNECTION_SINGLE		= 0,
	CONNECTION_MULTIPLE		= 1,
};

enum ValueType
{
	// special values
	VALUE_NONE		= 0,
	VALUE_DYNAMIC	= 1,

	// basic types
	VALUE_BOOLEAN	= 2,
	VALUE_INTEGER	= 3,
	VALUE_FLOAT		= 4,
	VALUE_STRING	= 5,

	// advanced types
	VALUE_POINT3	= 6,
	VALUE_MATRIX3	= 7
};

#endif // !BASICTYPES_H
