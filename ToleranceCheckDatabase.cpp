#include <iostream>
#include <string>

using namespace std;

#include "ToleranceCheckDatabase.hpp"
#include "ToleranceCheckHash.hpp"

bool isDuplicate(string newPassword, FILE * fpIn)
{
	cerr << "inside isDuplicate:" << endl;
	cerr << "new password is:" << newPassword << endl;

	bool result = false;
	const int PASSWORD_LENGTH = 65;

	char linestr[PASSWORD_LENGTH];
	rewind(fpIn);
	while(!feof(fpIn))
	{
		fgets(linestr, PASSWORD_LENGTH, fpIn);
		cerr << "linestr is:" << linestr << endl;

		string hashResult = hashSHA256(newPassword);
		cerr << "hashResult is:" << hashResult << endl;

		if(linestr == hashResult)
		{
			result = true;
			break;
		}
		// avoid comparison with \n
		fgets(linestr, PASSWORD_LENGTH, fpIn);
	}

	cerr << "Result is:" << result << endl;
	return result;
}

void storePassword(string newPassword)
{
	cerr << "inside storePassword:" << endl;
	cerr << "new password is:" << newPassword << endl;

	FILE * fpOut;
	fpOut = fopen("passwords.txt", "a");
	if(fpOut==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	
	string hashResult = hashSHA256(newPassword);
	cerr << "hashResult is:" << hashResult << endl;

	fputs("\n", fpOut);
	fputs(hashResult.c_str(), fpOut);
	fclose(fpOut);

	return;
}

