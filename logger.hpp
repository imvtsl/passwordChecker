#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>

using namespace std;

streambuf * redirectCerrToFile(fstream &file, ostream &cerr);

void redirectCerrToConsole(ostream &cerr, streambuf * stream_buffer_cerr);

#endif /* LOGGER_HPP */