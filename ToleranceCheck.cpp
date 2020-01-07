#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "ToleranceCheck.hpp"
#include "ToleranceCheckDatabase.hpp"

void manipulateHelper(string password, int toleranceLevel, vector<string> &result, string prefix)
{
	cerr << "inside manipulateHelper:" << endl;
	cerr << "password is:" << password << endl;
	cerr << "tolerance level is:" << toleranceLevel << endl;
	cerr << "prefix is:" << prefix << endl;

	if(toleranceLevel == 0)
	{
		password.insert(0, prefix);
		result.push_back(password);
		return;
	}
	
	int stringSize = password.size();
	for(int i=0 ; i<=stringSize-toleranceLevel ; i++)
	{
		cerr << "i is:" << i << endl;

		char temp = password[i];
		int substrLen = stringSize-i-1;
		int traversedLen = stringSize - substrLen;

		for(int ascii = 97 ; ascii<=122 ; ascii++)
		{
			char c = ascii;
			password[i] = c;
			
			// make new prefix			
			string appendedPrefix = password.substr(0,traversedLen);
			string newPrefix = prefix;
			newPrefix.append(appendedPrefix);

			cerr << "substrLen is:" << substrLen << endl;
			cerr << "traversedLen is:" << traversedLen << endl;
			cerr << "new prefix is:" << prefix << endl;
		
			manipulateHelper(password.substr(i+1, substrLen), toleranceLevel-1, result, newPrefix);
		}
		password[i] = temp;
	}
	return;
}

void manipulatePassword(string password, int toleranceLevel, vector<string> &result)
{
	manipulateHelper(password, toleranceLevel, result, "");
	return;
}

int checkTolerance(string newPassword, string oldPassword, int toleranceOfSimilarity)
{
	cerr << "inside checkTolerance:" << endl;
	cerr << "Old password is:" << oldPassword << endl;
	cerr << "New password is:" << newPassword << endl;
	cerr << "tolerance of similarity is: " << toleranceOfSimilarity << endl;


	int tolerance = -1;

	FILE * fpIn;
	fpIn = fopen("passwords.txt", "r");
	if(fpIn==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	
	if(isDuplicate(newPassword, fpIn))
		return 0;

	bool duplicate = false;
	
	for(int toleranceLevel = 1 ; toleranceLevel <= toleranceOfSimilarity ; toleranceLevel++)
	{
		
		// pick toleranceLevel number of characters, change them, and verify.
		
		// function to pick toleranceLevel number of characters.
		// function to manipulate them.
		vector<string> result;
		manipulatePassword(newPassword, toleranceLevel, result);
		
		for(int i=0 ; i<=result.size()-1 ; i++)
		{
			cerr << "Manipulated password is:" << result[i] << endl;
			if(isDuplicate(result[i], fpIn))
			{
				tolerance = toleranceLevel;
				duplicate = true;
				break;
			}	
		}
		if(duplicate)
			break;
	}
	fclose(fpIn);

	cerr << "Tolerance is:" << tolerance << endl;

	return tolerance;
}