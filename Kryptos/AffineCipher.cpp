#include "stdafx.h"
#include "AffineCipher.h"
#include "ModularMatrix.h"
#include "Matrix.h"
#include <iostream>
#include <regex>
#include <string>

// Namespace
using namespace std;

/* PUBLIC CONSTRUCTOR(S)
 * These are the constructors of the class AffineCipher.
 */


AffineCipher::AffineCipher(int blockSize, std::string keyString)
{
	// Create empty matrices of blockSize x blockSize to hold diffusion matrices
	this->BLOCK_SIZE = blockSize;
	this->DiffusionM.setSize(BLOCK_SIZE, BLOCK_SIZE);
	this->InverseDiffusionM.setSize(BLOCK_SIZE, BLOCK_SIZE);

}

/* PUBLIC METHODS
 * This portion contains the encrypt and decrypt methods for the class
 * AffineCipher.
 */


std::string AffineCipher::encrypt(std::string plaintext) {

	// Regex's for mod29 and mod67 ciphers
	std::regex mod67regex("[^A-Za-z0-9\\. \\!\\?\\,]");

	// Filter the plaintext based on regex
	plaintext = regex_replace(plaintext, mod67regex, "");

	// Throw an error if the key string contains invalid chars
	// This will cause an issue with decryption
	if (regex_match(this->key, mod67regex)) {
		throw std::runtime_error("The key you entered contains invalid character for the cipher.");
	}


	// Create from the keystring


	return plaintext;
}

std::string AffineCipher::decrypt(std::string ciphertext) {
	// Until code is written, return empty string
	return "";
}

/* GETTER AND SETTER METHODS
 * These methods will get and set the diffusion matrices.
 */

ModularMatrix AffineCipher::getDiffusionMatrix()
{
	return this->DiffusionM;
}

ModularMatrix AffineCipher::getInverseDiffusionMatrix()
{
	return this->InverseDiffusionM;
}

void AffineCipher::setDiffusionMatrix(ModularMatrix matrix)
{
	this->DiffusionM = matrix;
}

void AffineCipher::setInverseDiffusionMatrix(ModularMatrix matrix)
{
	this->InverseDiffusionM = matrix;
}


/* STATIC METHODS
 * Static helper methods to encode and decode integers.
 */

std::string AffineCipher::decodeInts(std::vector<int> inputInts) {

	// Declare an empty output string
	std::string outputString = "";

	// Loop through integer vector
	for (int i = 0; i < inputInts.size(); i++) {
		// Implement a switch to represent characters 62 through 66
		switch (inputInts[i]) {
			case 62:
				outputString += " ";
				break;
			case 63:
				outputString += ".";
				break;
			case 64:
				outputString += "?";
				break;
			case 65:
				outputString += "!";
				break;
			case 66:
				outputString += ",";
				break;
		}

		// Decisions for all other characters
		if ((0 <= inputInts[i]) && (inputInts[i] <= 25)) {
			outputString += (char)(inputInts[i] + (int)('A'));
		}
		else if ((26 <= inputInts[i]) && (inputInts[i] <= 51)) {
			outputString += (char)(inputInts[i] - 26 + (int)('a'));
		}
		else if ((52 <= inputInts[i]) && (inputInts[i] <= 61)) {
			outputString += (char)(inputInts[i] - 52 + (int)('0'));
		}

	}


	// Return the output string
	return outputString;


}

std::vector<int> AffineCipher::encodeString(std::string inputString) {

	// Clean the string with a regular expression
	std::regex mod67regex("[^A-Za-z0-9\\. \\!\\?\\,]");
	inputString = regex_replace(inputString, mod67regex, "");

	// Create an output vector of appropriate length
	std::vector<int> outputVector(inputString.length());

	// Loop through array
	for (int i = 0; i < inputString.length(); i++) {

		// Switch for characters SPACE, ".", "!", "?" and "$"
		switch (inputString[i]) {
			case ' ':
				outputVector[i] = 62;
				break;
			case '.':
				outputVector[i] = 63;
				break;
			case '?':
				outputVector[i] = 64;
				break;
			case '!':
				outputVector[i] = 65;
				break;
			case ',':
				outputVector[i] = 66;
				break;
		}

		// If statement to check whether upper or lower case
		if (('A' <= inputString[i]) && (inputString[i] <= 'Z')) {
			outputVector[i] = (int)inputString[i] - (int)('A');
		}
		else if (('a' <= inputString[i]) && (inputString[i] <= 'z')) {
			outputVector[i] = (int)inputString[i] - (int)('a') + 26;
		}
		else if (('0' <= inputString[i]) && (inputString[i] <= '9')) {
			outputVector[i] = (int)inputString[i] - (int)('0') + 52;
		}

	}

	// Return the output vector
	return outputVector;
}


/* PUBLIC DESTRUCTOR(S)
 * These are the destructor(s) of the class AffineCipher.
 */

AffineCipher::~AffineCipher()
{
}
