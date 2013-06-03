
#ifndef VALUE_H
#define VALUE_H

#include "basicTypes.h"
#include "types3d.h"

using boost::any_cast;

class Value
{
private:
	ValueType type_;
	boost::any value_;
public:
	Value() : type_(VALUE_NONE){}

	Value(int a)
	{
		type_ = VALUE_INTEGER;
		value_ = a;
	}

	Value(bool a)
	{
		type_ = VALUE_BOOLEAN;
		value_ = a;
	}

	Value(const std::string &a)
	{
		type_ = VALUE_STRING;
		value_ = a;
	}

	Value(float a)
	{
		type_ = VALUE_FLOAT;
		value_ = a;
	}
	
	Value(const Point3 &a)
	{
		type_ = VALUE_POINT3;
		value_ = a;
	}

	Value(const Matrix3 &a)
	{
		type_ = VALUE_MATRIX3;
		value_ = a;
	}

	ValueType getType() const { return type_; }

	operator std::string() const {return getStringValue2();}
	operator int() const {return getIntegerValue2();}
	operator bool() const {return getBooleanValue2();}
	operator float() const {return getFloatValue2();}
	operator Point3() const {return getPoint3Value2();}
	operator Matrix3() const {return getMatrix3Value2();}

	inline std::string getStringValue2() const;
	inline int getIntegerValue2() const;
	inline bool getBooleanValue2() const;
	inline float getFloatValue2() const;
	inline Point3 getPoint3Value2() const;
	inline Matrix3 getMatrix3Value2() const;
};

#include "value.inl"

#endif //!VALUE_H
