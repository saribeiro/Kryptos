#pragma once
#include "Matrix.h"
#include <string>

class ModularMatrix :
	public Matrix
{
// PUBLIC METHODS AND VARIABLES
public:
	// Constructor(s)
	ModularMatrix();
	ModularMatrix(int rows, int columns, int modulus);
	ModularMatrix(int rows, int columns, int modulus, int *arr_2d);
	ModularMatrix(int rows, int columns, int modulus, const int *arr_2d);
	ModularMatrix(int rows, int columns, int modulus, int *arr_2d, std::string matrixName);
	ModularMatrix(int rows, int columns, int modulus, const int *arr_2d, std::string matrixName);

	// Arithmetic operators
	ModularMatrix ModularMatrix::operator+(const ModularMatrix &M);
	ModularMatrix ModularMatrix::operator-(const ModularMatrix &M);
	ModularMatrix ModularMatrix::operator*(const ModularMatrix &M);

	// Getter/Setter Methods
	int getModulus();
	void setModulus(int modulus);

	// Destructor(s)
	~ModularMatrix();

// PRIVATE METHODS AND VARIABLES
private:
	int modulus = 0;
};

