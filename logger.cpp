#include <iostream>
#include <fstream>

using namespace std;

#include "logger.hpp"

streambuf * redirectCerrToFile(fstream &file, ostream &cerr)
{
	//streambuf* stream_buffer_cout = cout.rdbuf(); 
    //streambuf* stream_buffer_cin = cin.rdbuf();
    streambuf * stream_buffer_cerr = cerr.rdbuf(); 
  
    // Get the streambuffer of the file 
    streambuf * stream_buffer_file = file.rdbuf(); 
  
    // Redirect cerr to file 
    cerr.rdbuf(stream_buffer_file); 
  	
    cerr << "This line written to file" << endl; 
    //cout << "This from cout to console." << endl;

	return stream_buffer_cerr;
}

void redirectCerrToConsole(ostream &cerr, streambuf * stream_buffer_cerr)
{
	// Redirect cerr back to screen 
    cerr.rdbuf(stream_buffer_cerr);

    //cout << "This from cout to console." << endl;
	cerr << "This from cerr to console." << endl;

	return;
}