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

	if (cipher == MOD29_UPPERCASE_CIPHER) {
		// Loop through the integer vector
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
	}
	else {
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

	}

	// Return the output string
	return outputString;


}

std::vector<int> AffineCipher::encodeString(std::string inputString, AffineCipher::CipherType cipher) {
	
	// Clean the string with a regular expression
	// Depending on the cipher used, the regex will be different
	if (cipher == MOD67_MIXEDCASE_CIPHER) {
		std::regex mod67regex("[^A-Za-z0-9\\. \\!\\?\\,]");
		inputString = regex_replace(inputString, mod67regex, "");
	}
	else {
		std::regex mod29regex("[^A-Z \\.\\? ]");
		inputString = regex_replace(inputString, mod29regex, "");
	}

	// Create an output vector of appropriate length
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
