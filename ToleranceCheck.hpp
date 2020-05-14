#include <iostream>
#include <string>
#include <vector>

using namespace std;

void manipulateHelper(string password, int toleranceLevel, vector<string> &result, string prefix);

void manipulatePassword(string const &password, int toleranceLevel, vector<string> &result);

int checkTolerance(string const &newPassword, int toleranceOfSimilarity);