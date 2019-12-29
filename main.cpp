#include <iostream>
#include <string>
#include <vector>

using namespace std;

string formatData(string data) {
	
	string newData = data.substr(0, 64);
	
	return newData;
}

string GetOutputFromCommand(string cmd) {
	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream)
	{
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL)
				data.append(buffer);
		pclose(stream);
	}
	// modify data
	return(formatData(data));
}

string hashSHA256(string password)
{
	return (GetOutputFromCommand("echo -n "+password+"| sha256sum"));
}

void manipulateHelper(string password, int toleranceLevel, vector<string> &result, string prefix)
{
	if(toleranceLevel == 0)
	{
		password.insert(0, prefix);
		result.push_back(password);
		return;
	}
	//vector<string> result;
	int stringSize = password.size();
	for(int i=0 ; i<=stringSize-toleranceLevel ; i++)
	{
		char temp = password[i];
		int substrLen = stringSize-i-1;
		int traversedLen = stringSize - substrLen;

		for(int ascii = 32 ; ascii<=126 ; ascii++)
		{
			char c = ascii;
			password[i] = c;
			// make new prefix
			

			string appendedPrefix = password.substr(0,traversedLen);
			string newPrefix = prefix;
			newPrefix.append(appendedPrefix);
		
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

bool isDuplicate(string newPassword)
{
	bool result = false;
	
	FILE * fpIn;
	fpIn = fopen("passwords.txt", "r");
	if(fpIn==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	char linestr[64];
	
	while(!feof(fpIn))
	{
		fgets(linestr, 64, fpIn);
		
		if(linestr == hashSHA256(newPassword))
		{
			result = true;
			break;
		}	
	}
	fclose(fpIn);

	return result;
}

int checkTolerance(string newPassword, string oldPassword, int toleranceOfSimilarity)
{
	int tolerance = -1;
	
	if(isDuplicate(newPassword))
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
			if(isDuplicate(result[i]))
			{
				tolerance = toleranceLevel;
				duplicate = true;
				break;
			}	
		}
		if(duplicate)
			break;
	}
	return tolerance;
}

void store(string newPassword)
{
	FILE * fpOut;
	fpOut = fopen("passwords.txt", "a");
	if(fpOut==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	
	fputs("\n", fpOut);
	fputs(hashSHA256(newPassword).c_str(), fpOut);
	fclose(fpOut);

	return;
}

int main() {
	
	char oldPassword[20];
	char newPassword[20];
	char confirmNewPassword[20];
	
	while(true)
	{
		cin.getline(oldPassword, 20);
		cin.getline(newPassword, 20);
		cin.getline(confirmNewPassword, 20);

		cout << "Entered old password is: " << oldPassword << endl;
		cout << "Entered new password is: " << newPassword << endl;
		cout << "Entered confirm password is: " << confirmNewPassword << endl;
	
		// make basic checks on password:
	
		// check if old password is correct
		// check if newPassword and confirmPassword match
		// check if newPassword satifies criteria for strong password..regex
		// check if new password is tolerably distinct from old passwords.
		const int toleranceOfSimilarity = 3;
		int tolerance = checkTolerance(newPassword, oldPassword, toleranceOfSimilarity);
		if(tolerance != -1)
			cout << "More than " << toleranceOfSimilarity << " characters should be different than previous passwords." << endl;
		else
		{
			store(newPassword);
			cout << "Password changed successfully." << endl;
			break;
		}
	}
	return 0;
}