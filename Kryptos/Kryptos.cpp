// Kryptos.cpp : Defines the entry point for the console application.
// Include standard libraries
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

// Diffusion and Inverse Diffusion matrices
// These are program constants
const int DIFFUSION_MATRIX[10][10] = {
	{42, 36, 35, 7, 46, 21, 12, 28, 9, 10},
	{5, 32, 10, 45, 22, 47, 16, 3, 9, 30},
	{65, 16, 19, 24, 54, 1, 23, 20, 63, 20},
	{18, 31, 14, 60, 13, 6, 35, 17, 45, 27},
	{26, 33, 49, 52, 41, 66, 6, 46, 34, 20},
	{40, 33, 61, 4, 62, 13, 26, 59, 41, 55},
	{20, 13, 33, 20, 23, 62, 31, 35, 2, 43},
	{20, 11, 29, 49, 7, 65, 13, 5, 64, 65},
	{27, 31, 55, 63, 48, 8, 6, 62, 44, 60},
	{11, 37, 0, 43, 31, 38, 5, 15, 59, 9}
};
const int INVERSE_DIFFUSION_MATRIX[10][10] = {
		{ 48, 42, 7, 25, 60, 16, 53, 61, 14, 23 },
		{ 44, 16, 12, 32, 13, 8, 50, 59, 47, 59 },
		{ 31, 31, 60, 33, 27, 59, 45, 7, 30, 54 },
		{ 47, 50, 39, 58, 50, 55, 60, 14, 36, 46 },
		{ 31, 47, 41, 33, 43, 24, 49, 45, 65, 7 },
		{ 42, 44, 55, 15, 13, 50, 22, 49, 52, 18 },
		{ 4, 63, 24, 20, 22, 43, 53, 39, 43, 13 },
		{ 5, 20, 46, 19, 48, 35, 20, 49, 65, 2 },
		{ 61, 4, 40, 7, 20, 50, 49, 54, 61, 66 },
		{ 25, 43, 50, 47, 12, 53, 48, 40, 64, 16 }
};

// Include user defined classes
#include "Matrix.h"
#include "ModularMatrix.h"
#include "AffineCipher.h"

// Use the standard namespace
using namespace std;

int main()
{
	// Diffusion matrices
	ModularMatrix M(10, 10, 67, *DIFFUSION_MATRIX);
	ModularMatrix InverseM(10, 10, 67, *INVERSE_DIFFUSION_MATRIX);

	// Key vectors and data vectors
	ModularMatrix Key(10, 1, 67);
	ModularMatrix Data(10, 1, 67);
	ModularMatrix CipherVector(10, 1, 67);

	std::string message = "10l3tter10";
	std::string key = "0123456789";

	cout << "Message: " << message << endl;
	cout << "Key:     " << key << endl;

	// Fill vectors with the data
	std::vector<int> m_vector = AffineCipher::encodeString(message, AffineCipher::MOD67_MIXEDCASE_CIPHER);
	std::vector<int> k_vector = AffineCipher::encodeString(key, AffineCipher::MOD67_MIXEDCASE_CIPHER);

	// Populate modular matrix vectors with data
	for (int i = 0; i < 10; i++) {
		Key.setElement(i, 0, k_vector[i]);
		Data.setElement(i, 0, m_vector[i]);
	}

	CipherVector = M * Data + Key;

	// Convert cipher vector to output string
	std::vector<int> c_vector(10);

	for (int i = 0; i < 10; i++) {
		c_vector[i] = CipherVector.getElement(i, 0);
	}

	// Print the result
	cout << "Cipher:  " << AffineCipher::decodeInts(c_vector, AffineCipher::MOD67_MIXEDCASE_CIPHER) << endl;


	return EXIT_SUCCESS;
}

