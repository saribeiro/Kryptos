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
	// Set the block size to the class variable BLOCK_SIZE
	this->BLOCK_SIZE = blockSize;

	// Resize the matrices in the class
	this->DiffusionM.setSize(BLOCK_SIZE, BLOCK_SIZE);
	this->InverseDiffusionM.setSize(BLOCK_SIZE, BLOCK_SIZE);

	// Set the keyString
	this->key = keyString;

	// Regex's for mod67 cipher
	std::regex mod67regex("[^A-Za-z0-9\\. \\!\\?\\,]");

	// Throw an error if the key string contains invalid chars
	// This will cause an issue with decryption
	if (regex_match(this->key, mod67regex)) {
		throw std::runtime_error("The key you entered contains invalid character for the cipher.");
	}
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

	// Determine how many vectors are needed for the message
	int columnSize = (int)plaintext.length() / (int)BLOCK_SIZE + 1;
	int rowSize = BLOCK_SIZE;

	// Store these messages in a matrix rowSize x columnSize
	ModularMatrix plaintextMatrix(rowSize, columnSize, 67);

	// Parse the message string into a vector
	// Define the padding values (in our case SPACE)
	int paddingValue = AffineCipher::encodeString(" ")[0];
	vector<int> plaintextVector = AffineCipher::encodeString(plaintext);

	// Loop through the matrix by filling in the columns
	for (int j = 0; j < columnSize; j++) {
		for (int i = 0; i < rowSize; i++) {
			// Set the element from the vector into the matrix
			try {
				plaintextMatrix.setElement(i, j, plaintextVector.at(i + j * rowSize));
			}
			// If the vector goes out of bounds, put a padding value in the matrix
			catch (const std::out_of_range &exception) {
				plaintextMatrix.setElement(i, j, paddingValue);
			}
		}
	}

	// Parse the key string into a vector
	// No padding value in the key case
	vector<int> keyVector = AffineCipher::encodeString(this->key);
	int keyVectorSize = keyVector.size();

	// Create a matrix the size of the plaintextMatrix
	ModularMatrix keyMatrix(rowSize, columnSize, 67);

	// Fill in the matrix values
	// Loop through the matrix by filling in the columns
	for (int j = 0; j < columnSize; j++) {
		for (int i = 0; i < rowSize; i++) {
			// Set the element from the vector into the matrix
			keyMatrix.setElement(i, j, keyVector[(i + j * rowSize) % keyVectorSize]);
		}
	}

	// Hold the output in a ciphermatrix
	ModularMatrix ciphertextMatrix(rowSize, columnSize, 67);

	// Encryption process
	// Initialize ciphertextMatrix

	// Repeat encryption process 5 times
	ciphertextMatrix = plaintextMatrix;
	for (int i = 0; i < this->DIFFUSION_ROUNDS; i++) {
		ciphertextMatrix = this->DiffusionM * (ciphertextMatrix + keyMatrix);
	}

	// Create a vector to hold the output ciphertextMatrix
	vector<int> ciphertextVector(rowSize * columnSize);

	for (int j = 0; j < columnSize; j++) {
		for (int i = 0; i < rowSize; i++) {
			ciphertextVector[i + j * rowSize] = ciphertextMatrix.getElement(i, j);
		}
	}

	// String with cipherText
	std::string ciphertext = AffineCipher::decodeInts(ciphertextVector);

	return ciphertext;
}

std::string AffineCipher::decrypt(std::string ciphertext) {
	// Load the ciphertext into a matrix
	// Break it down into an appropriate sized matrix

	// Assert ciphertext has to be multiple of BLOCK_SIZE
	assert(ciphertext.length() % BLOCK_SIZE == 0);

	// Calculate row and column size of matrix
	int columnSize = (int)ciphertext.length() / (int)BLOCK_SIZE;
	int rowSize = BLOCK_SIZE;

	// Generate Modular matrix and vector of ciphertext
	vector<int> ciphertextVector = AffineCipher::encodeString(ciphertext);
	ModularMatrix ciphertextMatrix(rowSize, columnSize, 67);

	// Loop through matrix to fill in values from vector
	for (int j = 0; j < columnSize; j++) {
		for (int i = 0; i < rowSize; i++) {
			ciphertextMatrix.setElement(i, j, ciphertextVector[i + j * rowSize]);
		}
	}

	// Once this matrix is filled, make a keyMatrix
	vector<int> keyVector = AffineCipher::encodeString(this->key);
	int keyVectorSize = keyVector.size();
	ModularMatrix keyMatrix(rowSize, columnSize, 67);

	// Fill the keyMatrix
	for (int j = 0; j < columnSize; j++) {
		for (int i = 0; i < rowSize; i++) {
			keyMatrix.setElement(i, j, keyVector[(i + j * rowSize) % keyVectorSize]);
		}
	}

	// Perform the decryption operation
	// Declare the plaintextMatrix

	ModularMatrix plaintextMatrix(rowSize, columnSize, 67);
	plaintextMatrix = ciphertextMatrix;

	for (int i = 0; i < this->DIFFUSION_ROUNDS; i++) {
		plaintextMatrix = (this->InverseDiffusionM * plaintextMatrix) - keyMatrix;
	}

	// Parse the resulting plaintextMatrix into a vector
	vector<int> plaintextVector(rowSize * columnSize);

	for (int j = 0; j < columnSize; j++) {
		for (int i = 0; i < rowSize; i++) {
			plaintextVector[i + j * rowSize] = plaintextMatrix.getElement(i, j);
		}
	}

	// Parse the vector into a string
	std::string plaintext = AffineCipher::decodeInts(plaintextVector);
	return plaintext;
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

int AffineCipher::getBlockSize()
{
	return BLOCK_SIZE;
}

void AffineCipher::setDiffusionMatrix(ModularMatrix matrix)
{
	if (matrix.getModulus() != 67) {
		throw std::runtime_error("The modulus of this matrix is not equal to 67!");
	}
	else if ((matrix.getRows() != this->BLOCK_SIZE) || (matrix.getColumns() != this->BLOCK_SIZE)) {
		throw std::runtime_error("The matrix dimensions must match the block size of the cipher!");
	}

	this->DiffusionM = matrix;
}

void AffineCipher::setInverseDiffusionMatrix(ModularMatrix matrix)
{
	if (matrix.getModulus() != 67) {
		throw std::runtime_error("The modulus of this matrix is not equal to 67!");
	}
	else if ((matrix.getRows() != this->BLOCK_SIZE) || (matrix.getColumns() != this->BLOCK_SIZE)) {
		throw std::runtime_error("The matrix dimensions must match the block size of the cipher!");
	}

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
