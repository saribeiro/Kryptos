#include "stdafx.h"
#include "Matrix.h"
#include <vector>
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

/* CONSTRUCTOR(S)
 * This portion contains the public constructors of
 * the class "Matrix".
 */

Matrix::Matrix(int rows, int columns) {
	// Define the rows and columns here
	matrix_rows = rows;
	matrix_columns = columns;

	// Create a double vector to hold the values
	matrix.resize(matrix_rows, std::vector<int>(matrix_columns));
}

Matrix::Matrix(int rows, int columns, int *arr_2d) {
	// Define the rows and columns here
	matrix_rows = rows;
	matrix_columns = columns;

	// Create a double vector to hold the values
	matrix.resize(matrix_rows, std::vector<int>(matrix_columns));

	// Pass pointer to double array to the <setMatrix()> method
	this->setMatrix(arr_2d);

}

Matrix::Matrix(int rows, int columns, const int *arr_2d) {
	// Define the rows and columns here
	matrix_rows = rows;
	matrix_columns = columns;

	// Create a double vector to hold the values
	matrix.resize(matrix_rows, std::vector<int>(matrix_columns));

	// Pass pointer to double array to the <setMatrix()> method
	this->setMatrix(arr_2d);
}

Matrix::Matrix(int rows, int columns, int *arr_2d, std::string matrixName) {
	// Define the rows and columns here
	matrix_rows = rows;
	matrix_columns = columns;

	// Create a double vector to hold the values
	matrix.resize(matrix_rows, std::vector<int>(matrix_columns));

	// Pass pointer to double array to the <setMatrix()> method
	this->setMatrix(arr_2d);

	// Set array name
	this->matrixName = matrixName;
}

Matrix::Matrix(int rows, int columns, const int *arr_2d, std::string matrixName) {
	// Define the rows and columns here
	matrix_rows = rows;
	matrix_columns = columns;

	// Create a double vector to hold the values
	matrix.resize(matrix_rows, std::vector<int>(matrix_columns));

	// Pass pointer to double array to the <setMatrix()> method
	this->setMatrix(arr_2d);

	// Set matrix name
	this->matrixName = matrixName;
}

/* GETTER/SETTER METHODS
* These methods will get and set basic properties of the matrix.
*/

int Matrix::getRows() {
	return matrix_rows;
}

int Matrix::getColumns() {
	return matrix_columns;
}

int Matrix::getElement(int row, int column) {
	return matrix[row][column];
}

void Matrix::setElement(int row, int column, int value) {
	matrix[row][column] = value;
}

void Matrix::setMatrix(int *arr_2d) {

	// Loop through the vector object created
	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < this->matrix_columns; j++) {
			// For the matrix set it to the dereferenced value
			this->matrix[i][j] = *arr_2d;
			// Increment the pointer
			arr_2d++;
		}
	}

}

void Matrix::setMatrix(const int *arr_2d) {

	// Loop through the vector object created
	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < this->matrix_columns; j++) {
			// For the matrix set it to the dereferenced value
			this->matrix[i][j] = *arr_2d;
			// Increment the pointer
			arr_2d++;
		}
	}
}

/* DISPLAY METHOD
 * This is the display method for the matrix.
 */

void Matrix::displayMatrix() {

	if (this->matrixName == "") {
		for (int i = 0; i < this->matrix_rows; i++) {
			cout << "{ ";
			for (int j = 0; j < this->matrix_columns; j++) {
				cout << this->matrix[i][j] << ", ";
			}
			cout << "} ";
			cout << "" << endl;
		}
	}
	else {

		// Print a line of stars
		for (int i = 0; i < this->matrixName.length(); i++) {
			cout << "*";
		}
		
		// Print the matrix name
		cout << "" << endl;
		cout << this->matrixName << endl;

		// Print another line of stars
		for (int i = 0; i < this->matrixName.length(); i++) {
			cout << "*";
		}
		cout << "" << endl;

		// Print out the number of rows and columns
		cout << "Rows: " << this->matrix_rows << " Columns: " << this->matrix_columns << endl;

		// Begin printing the matrices with braces and delimited by commas
		for (int i = 0; i < this->matrix_rows; i++) {
			cout << "{ ";
			for (int j = 0; j < this->matrix_columns; j++) {
				cout << this->matrix[i][j] << ", ";
			}
			cout << "} ";
			cout << "" << endl;
		}
	}

}


/* ARITHMETIC OPERATORS
 * This portion will contain the basic arithmetic methods
 * used on matricies. This will overload the operators
 * to make code written using this class as neat as possible.
 */

Matrix Matrix::operator+(const Matrix &M) {

	// Assert that the matrix dimensions be the same
	if (this->matrix_rows != M.matrix_rows) {
		throw std::domain_error("The matrices you are adding have mismatched dimensions!");
	}
	else if (this->matrix_columns != M.matrix_columns) {
		throw std::domain_error("The matrices you are adding have mismatched dimensions!");
	};

	// Create a new Matrix to hold the output
	Matrix sumMatrix(this->matrix_rows, this->matrix_columns);

	// Add the matricies element by element
	int result;

	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < this->matrix_columns; j++) {
			result = this->matrix[i][j] + M.matrix[i][j];
			sumMatrix.setElement(i, j, result);
		}
	}

	return sumMatrix;

}

Matrix Matrix::operator-(const Matrix &M) {

	// Assert that the matrix dimensions be the same
	if (this->matrix_rows != M.matrix_rows) {
		throw std::domain_error("The matrices you are subtracting have mismatched dimensions!");
	}
	else if (this->matrix_columns != M.matrix_columns) {
		throw std::domain_error("The matrices you are subtracting have mismatched dimensions!");
	};

	// Create a new Matrix to hold the output
	Matrix sumMatrix(this->matrix_rows, this->matrix_columns);

	// Add the matricies element by element
	int result;

	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < this->matrix_columns; j++) {
			result = this->matrix[i][j] - M.matrix[i][j];
			sumMatrix.setElement(i, j, result);
		}
	}

	return sumMatrix;

}

Matrix Matrix::operator*(const Matrix &M) {

	// Assert that the dimensions are correct
	if (this->matrix_columns != M.matrix_rows) {
		throw std::domain_error("The matrices you are trying to multiply have mismatched dimensions!");
	};

	/* Short Description:
	If A is a matrix of dimensions (m x n)
	If B is a matrix of dimensions (n x k)
	Then C = A*B has dimensions (m x k)
	*/

	// Create a matrix to hold the product, of correct dimensions
	Matrix productMatrix(this->matrix_rows, M.matrix_columns);

	// Loop through the matrices and calculate the product
	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < M.matrix_columns; j++) {
			for (int k = 0; k < M.matrix_rows; k++) {
				productMatrix.matrix[i][j] += this->matrix[i][k] * M.matrix[k][j];
			}
		}
	}

	return productMatrix;
}

/* EQUALITY OPERATORS
 * These two methods define the equality operators. Returns a boolean
 * true or false. Overloading for the operators "==" and "!=". "A == B"
 * means Matrix A equals Matrix B. "!=" implies inequality of matrices.
 */

bool Matrix::operator==(const Matrix &M) {

	// If the matrix dimensions do not match, return false for equality
	if (this->matrix_rows != M.matrix_rows) {
		return false;
	}
	else if (this->matrix_columns != M.matrix_columns) {
		return false;
	}

	// Loop through both matrices element by element
	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < this->matrix_columns; j++) {
			// If one element does not equal it's corresponding element, return false
			if (this->matrix[i][j] != M.matrix[i][j]) {
				return false;
			}
		}
	}

	// If after these three basic requirements are fulfilled, return true
	return true;


}


bool Matrix::operator!=(const Matrix &M) {

	// If the matrix dimensions do not match, return true for non-equality
	if (this->matrix_rows != M.matrix_rows) {
		return true;
	}
	else if (this->matrix_columns != M.matrix_columns) {
		return true;
	}

	// Loop through both matrices element by element
	for (int i = 0; i < this->matrix_rows; i++) {
		for (int j = 0; j < this->matrix_columns; j++) {
			// If one element does not equal it's corresponding element, return true
			if (this->matrix[i][j] != M.matrix[i][j]) {
				return true;
			}
		}
	}

	// If after these three basic requirements are fulfilled, return false for non-equality
	return false;
}


/* DESTRUCTOR(S)
 * This portion contains the public destructors of
 * the class "Matrix"
 */

Matrix::~Matrix()
{
}
