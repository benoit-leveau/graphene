
#ifndef TYPES3D_H
#define TYPES3D_H

struct Point3
{
	float x, y, z;

	Point3(float x, float y, float z):x(x), y(y), z(z){}
	Point3():x(0), y(0), z(0){}

	bool operator<(const Point3 &other) const
	{
		if (x < other.x || (x == other.x && y < other.y) || (x == other.x && y == other.y && z < other.z))
			return true;
		return false;
	}

	bool operator==(const Point3 &other) const
	{
		return (x==other.x && y==other.y && z==other.z);
	}

	Point3 operator+(const Point3 &other) const
	{
		return Point3(x + other.x, y + other.y, z + other.z);
	}
};

struct Matrix3
{
	float x[3][3];

	Matrix3(float x1=1.f, float y1=0.f, float z1=0.f,
			float x2=0.f, float y2=1.f, float z2=0.f,
			float x3=0.f, float y3=0.f, float z3=1.f)
	{
		x[0][0] = x1;	x[0][1] = y1;	x[0][2] = z1;
		x[1][0] = x2;	x[1][1] = y2;	x[1][2] = z2;
		x[2][0] = x3;	x[2][1] = y3;	x[2][2] = z3;
	}

	bool operator<(const Matrix3 &other) const
	{
		for (int i=0; i<3; ++i)
			for (int j=0; j<3; ++j)
			{
				if (x[i][j] < other.x[i][j])
					return true;
				else if (x[i][j] > other.x[i][j])
					return false;
			}
		return false;
	}

	bool operator==(const Matrix3 &other) const
	{
		for (int i=0; i<3; ++i)
			for (int j=0; j<3; ++j)
				if (x[i][j] != other.x[i][j])
					return false;
		return true;
	}

	Matrix3 operator+(const Matrix3 &other) const
	{
		return Matrix3(
			x[0][0] + other.x[0][0], x[0][1] + other.x[0][1], x[0][2] + other.x[0][2],
			x[1][0] + other.x[1][0], x[1][1] + other.x[1][1], x[1][2] + other.x[1][2],
			x[2][0] + other.x[2][0], x[2][1] + other.x[2][1], x[2][2] + other.x[2][2]);
	}
};

#endif //!TYPES3D_H
