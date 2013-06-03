
#ifndef CLASSID_H
#define CLASSID_H

class ClassID
{
private:
	unsigned int a, b;
public:
	ClassID(unsigned int a, unsigned int b) : a(a), b(b){}
	bool operator==(const ClassID &other) const{return (a==other.a && b==other.b); }
	bool operator<(const ClassID &other) const
	{
		if (a  < other.a || (a == other.a && b < other.b))
			return true;
		return false;
	}
};

#endif //!CLASSID_H
