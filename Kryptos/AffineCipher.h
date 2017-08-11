#pragma once
// Include these user defined classes
#include "Matrix.h"
#include "ModularMatrix.h"

// Include standard library components
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "ModularMatrix.h"

// Use std namespace
using namespace std;

class AffineCipher
{
// PUBLIC VARIABLES AND METHODS
public:

	// Constructor(s)
	AffineCipher(int blockSize, std::string keyString);

	// Methods of the class
	std::string encrypt(std::string plaintext);
	std::string decrypt(std::string ciphertext);

	// Getter/Setter methods
	ModularMatrix getDiffusionMatrix();
	ModularMatrix getInverseDiffusionMatrix();
	void setDiffusionMatrix(ModularMatrix matrix);
	void setInverseDiffusionMatrix(ModularMatrix matrix);

	// Static methods of the class
	static std::string decodeInts(std::vector<int> inputInts);
	static std::vector<int> encodeString(std::string inputString);

	// Destructor(s)
	~AffineCipher();

// PROTECTED VARIABLES AND METHODS
protected:
	// Key string
	std::string key;
	int BLOCK_SIZE;

	// Diffusion matrices
	ModularMatrix DiffusionM;
	ModularMatrix InverseDiffusionM;


};

