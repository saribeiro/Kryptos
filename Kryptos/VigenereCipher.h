#pragma once
#include <string>

class VigenereCipher
{

// PUBLIC METHODS AND VARIABLES
public:
	// Public constructor(s)
	VigenereCipher();

	// Static method
	static std::string encrypt(std::string message, std::string key);
	static std::string decrypt(std::string message, std::string key);

	// Public destructor(s)
	~VigenereCipher();
};

