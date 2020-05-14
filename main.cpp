#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "logger.hpp"
#include "ToleranceCheck.hpp"
#include "ToleranceCheckDatabase.hpp"

void checkPassword(string const &oldPassword, string const &newPassword, string const &confirmNewPassword)
{
	cerr << "inside checkPassword:" << endl;
	cerr << "Old password is: " << oldPassword << endl;
	cerr << "New password is: " << newPassword << endl;
	cerr << "Confirm password is: " << confirmNewPassword << endl;

	// make basic checks on password:
	
	// check if old password is correct
	// check if newPassword and confirmPassword match
	// check if newPassword satifies criteria for strong password and is valid
	// check if new password is tolerably distinct from old passwords.
	// following code should be run only if all above conditions are satisfied.

	const int toleranceOfSimilarity = 2;
	
	int tolerance;

	try
	{
		tolerance = checkTolerance(newPassword, toleranceOfSimilarity);
	} catch(exception const &e) {
		cout << "Exception caught:" << e.what() << endl;
		cout << "Tolerance could not be checked." << endl;
		cerr << "Exception caught:" << e.what() << endl;
		cerr << "Tolerance could not be checked." << endl;
		return;
	}

	if(tolerance>=0 && tolerance <= toleranceOfSimilarity)
		cout << "More than " << toleranceOfSimilarity << " characters should be different than previous passwords." << endl;
	else
	{
		try
		{
			storePassword(newPassword);
			cout << "Password changed successfully." << endl;
		} catch(exception const &e) {
			cout << "Exception caught:" << e.what() << endl;
			cout << "Password not updated." << endl;
			cerr << "Exception caught:" << e.what() << endl;
			cerr << "Password not updated." << endl;
		}
	}
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
	
	
	cout << "Enter old password:";
	cin.getline(oldPassword, PASSWORD_LENGTH);
	cout << "Enter new password:";
	cin.getline(newPassword, PASSWORD_LENGTH);
	cout << "Please confirm password:";
	cin.getline(confirmNewPassword, PASSWORD_LENGTH);

	cerr << "Entered old password is: " << oldPassword << endl;
	cerr << "Entered new password is: " << newPassword << endl;
	cerr << "Entered confirm password is: " << confirmNewPassword << endl;

	checkPassword(oldPassword, newPassword, confirmNewPassword);
	
	// redirect cerr back to console
	redirectCerrToConsole(cerr, stream_buffer_cerr);
	file.close();

	return 0;
}