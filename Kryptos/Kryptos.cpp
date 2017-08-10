// Kryptos.cpp : Defines the entry point for the console application.
// Include standard libraries
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <assert.h>

// Diffusion and Inverse Diffusion matrices
// These are program constants
const int DIFFUSION_MATRIX[4][4] = {
	{ 3, 8, 18, 9 },
	{ 28, 25, 16, 27 },
	{ 22, 17, 11, 8 },
	{ 3, 21, 15, 9 }
};
const int INVERSE_DIFFUSION_MATRIX[4][4] = {
	{ 13, 26, 25, 6 },
	{ 21, 0, 27, 13 },
	{ 14, 0, 1, 27 },
	{ 20, 1, 14, 13 }
};

// Include user defined classes
#include "Matrix.h"
#include "ModularMatrix.h"
#include "AffineCipher.h"

// Use the standard namespace
using namespace std;

int main()
{
	return EXIT_SUCCESS;
}

