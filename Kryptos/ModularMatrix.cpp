#include "stdafx.h"
#include "ModularMatrix.h"
#include "Matrix.h"
#include <assert.h>
#include <vector>
#include <iostream>
#include <string>


/* PUBLIC CONSTRUCTOR(S)
 * These are the public constructors for the modular matrix class.
 */

ModularMatrix::ModularMatrix()
{
}

ModularMatrix::ModularMatrix(int rows, int columns, int modulus) : Matrix(rows, columns)
{
	this->matrix_rows = rows;
	this->matrix_columns = columns;
	this->modulus = modulus;
}

ModularMatrix::ModularMatrix(int rows, int columns, int modulus, int *arr_2d) : Matrix(rows, columns, arr_2d) {
	this->matrix_rows = rows;
	this->matrix_columns = columns;
	this->setMatrix(arr_2d);
	this->modulus = modulus;
}

ModularMatrix::ModularMatrix(int rows, int columns, int modulus, const int *arr_2d) : Matrix(rows, columns, arr_2d) {
	this->matrix_rows = rows;
	this->matrix_columns = columns;
	this->setMatrix(arr_2d);
	this->modulus = modulus;
}

ModularMatrix::ModularMatrix(int rows, int columns, int modulus, int *arr_2d, std::string matrixName) : Matrix(rows, columns, arr_2d, matrixName) {
	this->matrix_rows = rows;
	this->matrix_columns = columns;
	this->setMatrix(arr_2d);
	this->modulus = modulus;
	this->matrixName = matrixName;
}

ModularMatrix::ModularMatrix(int rows, int columns, int modulus, const int *arr_2d, std::string matrixName) : Matrix(rows, columns, arr_2d, matrixName) {
	this->matrix_rows = rows;
	this->matrix_columns = columns;
	this->setMatrix(arr_2d);
	this->modulus = modulus;
	this->matrixName = matrixName;
}

/* ARITHMETIC METHODS
* This portion will contain the basic arithmetic methods
* used on matricies. This will overload the operators
* to make code written using this class as neat as possible.
*/

ModularMatrix ModularMatrix::operator+(const ModularMatrix &M) {

	// Assert that the matrix dimensions be the same
	if (this->matrix_rows != M.matrix_rows) {
		throw std::domain_error("The matrices you are adding have mismatched dimensions!");
	}
	else if (this->matrix_columns != M.matrix_columns) {
		throw std::domain_error("The matrices you are adding have mismatched dimensions!");
	};

	// Assert that modulus is not 1 or 0
	assert((this->modulus != 0) || (this->modulus != 1));

	// Create a new Matrix to hold the output
	ModularMatrix sumMatrix(this->matrix_rows, this->matrix_columns, this->modulus);

	// Add the matricies element by element
	int result;

	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < this->matrix_columns; j++) {
			result = (this->matrix[i][j] + M.matrix[i][j]) % modulus;
			sumMatrix.setElement(i, j, result);
		}
	}

	return sumMatrix;

}

ModularMatrix ModularMatrix::operator-(const ModularMatrix &M) {

	// Assert that the matrix dimensions be the same
	if (this->matrix_rows != M.matrix_rows) {
		throw std::domain_error("The matrices you are subtracting have mismatched dimensions!");
	}
	else if (this->matrix_columns != M.matrix_columns) {
		throw std::domain_error("The matrices you are subtracting have mismatched dimensions!");
	};

	// Assert that modulus is not 1 or 0
	assert((this->modulus != 0) || (this->modulus != 1));

	// Create a new Matrix to hold the output
	ModularMatrix sumMatrix(this->matrix_rows, this->matrix_columns, M.modulus);

	// Add the matricies element by element
	int result;

	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < this->matrix_columns; j++) {
			result = (this->matrix[i][j] - M.matrix[i][j]) % modulus;
			sumMatrix.setElement(i, j, result);
		}
	}

	return sumMatrix;

}

ModularMatrix ModularMatrix::operator*(const ModularMatrix &M) {

	// Assert that the dimensions are correct
	if (this->matrix_columns != M.matrix_rows) {
		throw std::domain_error("The matrices you are trying to multiply have mismatched dimensions!");
	};

	// Assert that modulus is not 1 or 0
	assert((this->modulus != 0) || (this->modulus != 1));

	/* Short Description:
	If A is a matrix of dimensions (m x n)
	If B is a matrix of dimensions (n x k)
	Then C = A*B has dimensions (m x k)
	*/

	// Create a matrix to hold the product, of correct dimensions
	ModularMatrix productMatrix(this->matrix_rows, M.matrix_columns, M.modulus);

	// Loop through the matrices and calculate the product
	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < M.matrix_columns; j++) {
			for (int k = 0; k < M.matrix_rows; k++) {
				// Perform the modulus operation here
				// This is important to do the operation here, so that int does not potentially exceed its own range
				productMatrix.matrix[i][j] += (this->matrix[i][k] * M.matrix[k][j]) % modulus;
				// Take the modulus again to reduce it down to it's final value
				productMatrix.matrix[i][j] %= modulus;
			}
		}
	}

	return productMatrix;
}

/* GETTER METHODS
 * These methods get properties of the ModularMatrix object instantiated.
 */

int ModularMatrix::getModulus() {
	return this->modulus;
}

void ModularMatrix::setModulus(int modulus)
{
	this->modulus = modulus;
}


/* PUBLIC DESTRUCTOR(S)
 * These are the destructors for the class Modular Matrix.
 */

ModularMatrix::~ModularMatrix()
{
}
