#include "stdafx.h"
#include "AffineCipher.h"
#include "ModularMatrix.h"
#include "Matrix.h"
#include <iostream>
#include <string>

// Namespace
using namespace std;

/* PUBLIC CONSTRUCTOR(S)
 * These are the constructors of the class AffineCipher.
 */


AffineCipher::AffineCipher(ModularMatrix diffusionMatrix, ModularMatrix inverseDiffusionMatrix)
{

	// By default, use MOD29_UPPERCASE_CIPHER
	this->cipher = MOD29_UPPERCASE_CIPHER;

	// Throw an error if moduli are not equal
	if (diffusionMatrix.getModulus() != inverseDiffusionMatrix.getModulus()) {
		throw std::domain_error("The modular matrices must have the same modulus! All arithmetic must occur in the ring Z/pZ!");
	}
	// Throw an error if moduli are not equal to 29
	else if ((diffusionMatrix.getModulus() != 29) && (inverseDiffusionMatrix.getModulus() != 29)) {
		throw std::domain_error("The class <AffineCipher> is undefined for modulus not equal to 29!");
	}

}

AffineCipher::AffineCipher(ModularMatrix diffusionMatrix, ModularMatrix inverseDiffusionMatrix, std::string keyString)
{
	
	// By default, use MOD29_UPPERCASE_CIPHER
	this->cipher = MOD29_UPPERCASE_CIPHER;
	
	// Throw an error if moduli are not equal
	if (diffusionMatrix.getModulus() != inverseDiffusionMatrix.getModulus()) {
		throw std::domain_error("The modular matrices must have the same modulus! All arithmetic must occur in the ring Z/pZ!");
	}
	// Throw an error if moduli are not equal to 29
	else if ((diffusionMatrix.getModulus() != 29) && (inverseDiffusionMatrix.getModulus() != 29)) {
		throw std::domain_error("The class <AffineCipher> is undefined for modulus not equal to 29!");
	}
}

/* PUBLIC METHODS
 * This portion contains the encrypt and decrypt methods for the class
 * AffineCipher.
 */


std::string AffineCipher::encrypt(std::string plaintext) {
	// Until code is written, return empty string
	return "";
}

std::string AffineCipher::decrypt(std::string ciphertext) {
	// Until code is written, return empty string
	return "";
}


/* GETTER METHODS
 * Get methods for the attributes of the AffineCipher class.
 */
AffineCipher::CipherType AffineCipher::getCipherType() {
	return this->cipher;
}


/* STATIC METHODS
 * Static helper methods to encode and decode integers.
 */

std::string AffineCipher::decodeInts(std::vector<int> inputInts, AffineCipher::CipherType cipher) {

	// Declare an empty output string
	std::string outputString = "";

	// Loop through the integer array
	for (int i = 0; i < inputInts.size(); i++) {
		switch (inputInts[i]) {
			case 26:
				outputString += " ";
				break;
			case 27:
				outputString += ".";
				break;
			case 28:
				outputString += "?";
				break;
			default:
				outputString += (char)(inputInts[i] + (int)('A'));
		}
	}

	// Return the output string
	return outputString;


}

std::vector<int> AffineCipher::encodeString(std::string inputString, AffineCipher::CipherType cipher) {
	
	// Create an output vector
	std::vector<int> outputVector(inputString.length());
	
	if (cipher == MOD29_UPPERCASE_CIPHER) {
		// Loop through string
		for (int i = 0; i < inputString.length(); i++) {
			// Replace SPACE, "." and "?" with appropriate numeric value
			// Default case applies to [A-Z] input
			switch (inputString[i]) {
				case ' ':
					outputVector[i] = 26;
					break;
				case '.':
					outputVector[i] = 27;
					break;
				case '?':
					outputVector[i] = 28;
					break;
				default:
					outputVector[i] = (int)inputString[i] - (int)('A');
			}

		}
	}
	// Code for MOD67 cipher
	else {
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
			if ( ((int)('A') <= (int)inputString[i]) && ((int)inputString[i] <= (int)('Z')) ) {
				outputVector[i] = (int)inputString[i] - (int)('A');
			}
			else if (((int)('a') <= (int)inputString[i]) && ((int)inputString[i] <= (int)('z'))) {
				outputVector[i] = (int)inputString[i] - (int)('a') + 25;
			}
			else if (((int)('0') <= (int)inputString[i]) && ((int)inputString[i] <= (int)('9'))) {
				outputVector[i] = (int)inputString[i] - (int)('0') + 52;
			}

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
