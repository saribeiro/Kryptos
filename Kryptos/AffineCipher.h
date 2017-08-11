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

	// Enum types to declare which type of cipher we are using
	enum CipherType {
		MOD29_UPPERCASE_CIPHER,
		MOD67_MIXEDCASE_CIPHER
	};

	// Constructor(s)
	AffineCipher(ModularMatrix diffusionMatrix, ModularMatrix inverseDiffusionMatrix);
	AffineCipher(ModularMatrix diffusionMatrix, ModularMatrix inverseDiffusionMatrix, std::string keyString);

	// Methods of the class
	std::string encrypt(std::string plaintext);
	std::string decrypt(std::string ciphertext);

	// Getter methods
	CipherType getCipherType();

	// Static methods of the class
	static std::string decodeInts(std::vector<int> inputInts, CipherType cipher);
	static std::vector<int> encodeString(std::string inputString, CipherType cipher);

	// Destructor(s)
	~AffineCipher();

// PROTECTED VARIABLES AND METHODS
protected:
	std::string key;
	CipherType cipher;


};

