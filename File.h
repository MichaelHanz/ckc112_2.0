#ifndef FILE_H
#define FILE_H

#include <string>

using namespace std;

class File
{
    string name;
    string extension;

public:
    File(const string &fileName, const string &fileExtension);

    string getName() const;
    string getExtension() const;

    string getFullName() const;
};

#endif