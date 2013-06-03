
std::string Value::getStringValue2() const
{
	try
	{
		if (type_ == VALUE_STRING)
			return any_cast<std::string>(value_);
	}
	catch(...){}
	return std::string("");
}

int Value::getIntegerValue2() const
{
	try
	{
		if (type_ == VALUE_INTEGER)
			return any_cast<int>(value_);
	}
	catch(...){}
	return int(0);
}

bool Value::getBooleanValue2() const
{
	try
	{
		if (type_ == VALUE_BOOLEAN)
			return any_cast<bool>(value_);
	}
	catch(...){}
	return false;
}

float Value::getFloatValue2() const
{
	try
	{
		if (type_ == VALUE_FLOAT)
			return any_cast<float>(value_);
	}
	catch(...){}
	return 0.f;
}

Point3 Value::getPoint3Value2() const
{
	try
	{
		if (type_ == VALUE_POINT3)
			return any_cast<Point3>(value_);
	}
	catch(...){}
	return Point3();
}

Matrix3 Value::getMatrix3Value2() const
{
	try
	{
		if (type_ == VALUE_MATRIX3)
			return any_cast<Matrix3>(value_);
	}
	catch(...){}
	return Matrix3();
}
