#include "stdafx.h"
#include "VigenereCipher.h"
#include <regex>
#include <algorithm>
#include <string>
#include <iostream>


using namespace std;

VigenereCipher::VigenereCipher()
{
}

std::string VigenereCipher::encrypt(std::string message, std::string key)
{
	// First, clean the string of any non [A-Za-z] characters
	// Clean both the message and the key
	std::regex invalidChars("[^A-Za-z]");
	message = regex_replace(message, invalidChars, "");
	key = regex_replace(key, invalidChars, "");

	// Now that both strings have been cleaned, capitalize the strings
	transform(message.begin(), message.end(), message.begin(), ::toupper);
	transform(key.begin(), key.end(), key.begin(), ::toupper);

	// Create a vector of integers to represent the message and key
	vector<int> messageInts(message.length());
	vector<int> keyInts(key.length());

	// Parse message and key into integers
	for (int i = 0; i < messageInts.size(); i++) {
		messageInts[i] = (int)(message[i]) - (int)('A');
	}

	for (int i = 0; i < keyInts.size(); i++) {
		keyInts[i] = (int)(key[i]) - (int)('A');
	}

	// Create a vector of the ciphertext ints
	vector<int> ciphertextInts(message.length());

	// Add the message and key modulo 26
	for (int i = 0; i < message.length(); i++) {
		ciphertextInts[i] = (messageInts[i] + keyInts[i % key.length()]) % 26;
	}

	// Decode the ciphertext ints
	std:string ciphertext = "";

	for (int i = 0; i < ciphertextInts.size(); i++) {
		ciphertext += (char)(ciphertextInts[i] + (int)('A'));
	}

	return ciphertext;
}

std::string VigenereCipher::decrypt(std::string ciphertext, std::string key)
{
	// First, clean the string of any non [A-Za-z] characters
	// Clean both the message and the key
	std::regex invalidChars("[^A-Za-z]");
	ciphertext = regex_replace(ciphertext, invalidChars, "");
	key = regex_replace(key, invalidChars, "");

	// Now that both strings have been cleaned, capitalize the strings
	transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);
	transform(key.begin(), key.end(), key.begin(), ::toupper);

	// Parse both strings into integer arrays
	vector<int> ciphertextInts(ciphertext.length());
	vector<int> keyInts(key.length());

	for (int i = 0; i < ciphertextInts.size(); i++) {
		ciphertextInts[i] = (int)(ciphertext[i]) - (int)('A');
	}

	for (int i = 0; i < keyInts.size(); i++) {
		keyInts[i] = (int)(key[i]) - (int)('A');
	}

	// Create an array to hold the decrypted message
	vector<int> messageInts(ciphertext.length());

	// Perform the decryption process
	for (int i = 0; i < ciphertext.length(); i++) {
		messageInts[i] = ((ciphertextInts[i] - keyInts[i % key.length()]) % 26 + 26) % 26;
	}

	// Parse ints into a string
	std::string message = "";
	for (int i = 0; i < messageInts.size(); i++) {
		message += (char)(messageInts[i] + (int)('A'));
	}

	return message;
}


VigenereCipher::~VigenereCipher()
{
}
