#include "Triangle.h"

string Triangle::DetermineType(){

	if (lengthX == lengthY == lengthZ) 
	{
		return "Equilateral";
	}
	else if (lengthX == lengthY || lengthX == lengthZ || lengthY == lengthZ)
	{
		return "Isoceles";
	}
	return "Scalene";
}