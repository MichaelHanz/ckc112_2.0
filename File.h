#ifndef FILE_H
#define FILE_H

#include <string>

using namespace std;

class File
{
    string name;
    string extension;

public:
    File(string name, string extension);
    string getFullName();
};

#endif