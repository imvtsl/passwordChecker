#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "ToleranceCheckDatabase.hpp"
#include "ToleranceCheckHash.hpp"
#include "Validation.hpp"

bool isDuplicate(string const &newPassword, fstream &file)
{
	cerr << "inside isDuplicate:" << endl;
	cerr << "new password is:" << newPassword << endl;

	bool result = false;
	//const int PASSWORD_LENGTH = 65;

	string linestr;
	
	file.clear();
	file.seekg(0, ios::beg);
	
	string hashResult = hashSHA256(newPassword);
	cerr << "hashResult is:" << hashResult << endl;

	while(getline (file, linestr))
	{
		cerr << "linestr is:" << linestr << endl;
		// validate linestr
		validateSHA256(linestr);

		if(linestr == hashResult)
		{
			result = true;
			break;
		}
	}

	cerr << "Result is:" << result << endl;
	return result;
}

void storePassword(string const &newPassword)
{
	cerr << "inside storePassword:" << endl;
	cerr << "new password is:" << newPassword << endl;

	fstream file;
	file.open("passwords.txt", ios::app);
	
	if(!file.is_open())
	{
		cout << "couldn't open file" << endl;
		// throw exception
		return;
	}
	
	string hashResult = hashSHA256(newPassword);
	cerr << "hashResult is:" << hashResult << endl;

	file << endl;
	file << hashResult;
	
	file.close();

	return;
}

