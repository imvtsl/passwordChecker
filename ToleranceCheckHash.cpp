#include <iostream>
#include <string>

using namespace std;

#include "ToleranceCheckHash.hpp"

string formatData(string data)
{
	cerr << "inside formatData:" << endl;
	cerr << "data is:" << data << endl;

	string newData = data.substr(0, 64);
	cerr << "new data is:" << newData << endl;

	return newData;
}

string GetOutputFromCommand(string cmd)
{
	cerr << "inside GetOutputFromCommand:" << endl;
	cerr << "cmd is:" << cmd << endl;

	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");
	//cout << "command is:" << cmd << endl;
	stream = popen(cmd.c_str(), "r");
	if (stream)
	{
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL)
				data.append(buffer);
		pclose(stream);
	}
	// modify data
	cerr << "data is:" << data << endl;
	return(formatData(data));
}

string hashSHA256(string const &password)
{
	return (GetOutputFromCommand("echo -n "+password+" | sha256sum"));
}