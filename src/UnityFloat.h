#include "Arduino.h"

class UnityFloat
{
  private:
	unsigned short value = { 0 };
	static constexpr double max = 65536.0;

  public:
	UnityFloat();
	UnityFloat(double value);

	UnityFloat(const UnityFloat &rhs) = default; // copy constructor
	UnityFloat &operator=(const double &rhs);    // copy assignment operator

	template <typename T>
	double operator+(T rhs);

	template <typename T>
	double operator*(T rhs);

	template <typename T>
	operator T()
	{
		return (value / max);
	}

	// Vector operator-(Vector v); // Subtraction
	// int operator^(Vector v);    // Dot Product
	// Vector operator*(Vector v); // Cross Product
	// float magnitude()
	// {
	// 	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	// }
	// friend ostream &operator<<(ostream &out, const Vector &v);
	// // To output the Vector
};

// // Addition of vectors
// Vector Vector::operator+(Vector v)
// {
// 	int x1, y1, z1;
// 	x1 = x + v.x;
// 	y1 = y + v.y;
// 	z1 = z + v.z;
// 	return Vector(x1, y1, z1);
// }

// // Subtraction of vectors
// Vector Vector::operator-(Vector v)
// {
// 	int x1, y1, z1;
// 	x1 = x - v.x;
// 	y1 = y - v.y;
// 	z1 = z - v.z;
// 	return Vector(x1, y1, z1);
// }

// // Dot product of vectors
// int Vector::operator^(Vector v)
// {
// 	int x1, y1, z1;
// 	x1 = x * v.x;
// 	y1 = y * v.y;
// 	z1 = z * v.z;
// 	return (x1 + y1 + z1);
// }

// // Cross product of vectors
// Vector Vector::operator*(Vector v)
// {
// 	int x1, y1, z1;
// 	x1 = y * v.z - z * v.y;
// 	y1 = z * v.x - x * v.z;
// 	z1 = x * v.y - y * v.x;
// 	return Vector(x1, y1, z1);
// }

// // Display Vector
// ostream &operator<<(ostream &out, const Vector &v)
// {
// 	out << v.x << "i ";
// 	if (v.y >= 0)
// 		out << "+ ";
// 	out << v.y << "j ";
// 	if (v.z >= 0)
// 		out << "+ ";
// 	out << v.z << "k" << endl;
// 	return out;
// }