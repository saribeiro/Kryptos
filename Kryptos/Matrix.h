#pragma once
#include <vector>

using namespace std;

class Matrix
{

// PUBLIC METHODS AND VARIABLES
public:
	// Constructor(s)
	Matrix();
	Matrix(int rows, int columns);
	Matrix(int rows, int columns, int *arr_2d);
	Matrix(int rows, int columns, const int *arr_2d);
	Matrix(int rows, int columns, int *arr_2d, std::string matrixName);
	Matrix(int rows, int columns, const int *arr_2d, std::string matrixName);

	// Getter/Setter Methods
	int getRows();
	int getColumns();
	int getElement(int row, int column);
	void setElement(int row, int column, int value);
	void setSize(int row, int column);
	void setMatrix(int *arr_2d);
	void setMatrix(const int *arr_2d);
	void setMatrix(int row, int column, std::vector<std::vector<int>> arr_2d);
	void setColumnVector(std::vector<int> arr);
	void setRowVector(std::vector<int> arr);

	// Display Method
	void displayMatrix();

	// Operator(s)
	Matrix operator+(const Matrix &M);
	Matrix operator-(const Matrix &M);
	Matrix operator*(const Matrix &M);
	bool operator==(const Matrix &M);
	bool operator!=(const Matrix &M);


	// Destructors(s)
	~Matrix();

// PRIVATE METHODS AND VARIABLES
protected:
	// Store the rows and columns as variables
	int matrix_rows;
	int matrix_columns;

	// Store matrix as a variable
	std::vector<std::vector<int>> matrix;

	// Create array name as a potential variable
	std::string matrixName = "";

};

