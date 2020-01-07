#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "logger.hpp"
#include "ToleranceCheck.hpp"
#include "ToleranceCheckDatabase.hpp"

bool checkPassword(string oldPassword, string newPassword, string confirmNewPassword)
{
	cerr << "inside checkPassword:" << endl;
	cerr << "Old password is: " << oldPassword << endl;
	cerr << "New password is: " << newPassword << endl;
	cerr << "Confirm password is: " << confirmNewPassword << endl;

	bool result = false;
	// make basic checks on password:
	
	// check if old password is correct
	// check if newPassword and confirmPassword match
	// check if newPassword satifies criteria for strong password
	// check if new password is tolerably distinct from old passwords.
	// following code should be run only if all above conditions are satisfied.
	const int toleranceOfSimilarity = 2;
	int tolerance = checkTolerance(newPassword, oldPassword, toleranceOfSimilarity);
	if(tolerance != -1)
		cout << "More than " << toleranceOfSimilarity << " characters should be different than previous passwords." << endl;
	else
	{
		storePassword(newPassword);
		cout << "Password changed successfully." << endl;
		result = true;
	}
	return result;
}

int main()
{
	// redirect cerr to log.txt
	fstream file; 
    file.open("log.txt", ios::out);
    streambuf * stream_buffer_cerr = redirectCerrToFile(file, cerr);
	
    cerr << endl << "inside main:" << endl;

	const int PASSWORD_LENGTH = 20;

	char oldPassword[PASSWORD_LENGTH];
	char newPassword[PASSWORD_LENGTH];
	char confirmNewPassword[PASSWORD_LENGTH];
	
	while(true)
	{
		cout << "Enter old password:";
		cin.getline(oldPassword, PASSWORD_LENGTH);
		cout << "Enter new password:";
		cin.getline(newPassword, PASSWORD_LENGTH);
		cout << "Please confirm password:";
		cin.getline(confirmNewPassword, PASSWORD_LENGTH);

		cerr << "Entered old password is: " << oldPassword << endl;
		cerr << "Entered new password is: " << newPassword << endl;
		cerr << "Entered confirm password is: " << confirmNewPassword << endl;

		if(checkPassword(oldPassword, newPassword, confirmNewPassword))
			break;
	}
	
	// redirect cerr back to console
	redirectCerrToConsole(cerr, stream_buffer_cerr);
	file.close();

	return 0;
}