#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encrypted(string password)
{
	return password;
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
	vector<string> passDb;
	int passDbSize = passDb.size();
	for(int i=0 ; i<=passDbSize-1 ; i++)
	{
		if(encrypted(newPassword) == passDb[i])
		{
			result = true;
			break;
		}
	}
	return result;
}

int checkTolerance(string newPassword, string oldPassword, int toleranceOfSimilarity)
{
	int tolerance = -1;
	// assume passDb has encrypted password.
	if(isDuplicate(newPassword))
		return 0;

	bool duplicate = false;
	
	for(int toleranceLevel = 1 ; toleranceLevel <= toleranceOfSimilarity ; toleranceLevel++)
	{
		
		// pick toleranceLevel number of characters, change them, and verify.
		
		// function to pick toleranceLevel number of characters.
		// function to manipulate them.
		vector<string> result;
		manipulatePassword(password, toleranceLevel, result);
		
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
	
		// make basic checks on password;
	
		// check if old password is correct
		// check if newPassword and confirmPassword match
		// check if newPassword satifies criteria for strong password
		// check if new password is tolerably distinct from old passwords.
		const int toleranceOfSimilarity = 3;
		int tolerance = checkTolerance(newPassword, oldPassword, toleranceOfSimilarity);
		if(tolerance != -1)
			cout << "More than " << toleranceOfSimilarity << " characters should be different than previous passwords." << endl;
		else
		{
			cout << "Password changed successfully." << endl;
			break;
		}
	}
	return 0;
}