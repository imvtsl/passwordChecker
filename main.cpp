#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encrypted(string password)
{
	return password;
}

string manipulatePassword(string newPassword, int toleranceLevel)
{
	string manipulatedPassword = newPassword;
	int passwordSize = newPassword.size();
	// choose a character
	// choose a character from remaining string until tolerance level is 0.
	// manipulate character at these indices.

	return manipulatedPassword;
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

int checkTolerance(string newPassword, string oldPassword, int toleranceOfCharacters)
{
	int result = -1;
	// assume passDb has encrypted password.
	if(isDuplicate(newPassword))
		return 0;

	for(int toleranceLevel = 1 ; toleranceLevel <= toleranceOfCharacters ; toleranceLevel++)
	{
		
		// pick toleranceLevel number of characters, change them, and verify.
		
		// function to pick toleranceLevel number of characters.
		// function to manipulate them.
		string manipulatedPassword = manipulatePassword(newPassword, toleranceLevel);
		cout << "Manipulated password is: " << manipulatedPassword << endl;
		// function to check.
		if(isDuplicate(manipulatedPassword)) {
			result = toleranceLevel;
			break;
		}
	}
	return result;
}

int main() {
	// should password checked be in continuous loop?
	char oldPassword[20];
	char newPassword[20];
	char confirmNewPassword[20];
	
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
	const int toleranceOfCharacters = 3;
	int tolerance = checkTolerance(newPassword, oldPassword, toleranceOfCharacters);
	if(tolerance != -1)
		cout << "More than " << tolerance << " characters should be different than previous passwords." << endl;
	else
		cout << "Password changed successfully." << endl;
	return 0;

}