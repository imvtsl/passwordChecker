#include <iostream>
#include <regex>
#include <string>

using namespace std;

#include "Validation.hpp"

void validateSHA256(string const &input)
{
	// validate it is 64 characters long
	// validate it has hexadecimal digits only
	string regEx = "[a-fA-F0-9]{64}";
	
	regex r(regEx);
	cerr << "the input string is:" << input << endl;
	cerr << "the regex is:" << regEx << endl;
	if(regex_match(input, r))
	{
		cerr << "It is a match." << endl;
	}
	else
	{
		//cerr << "It is not a match." << endl;
		throw runtime_error("Not a valid SHA256 hash");
	}

	return;
}