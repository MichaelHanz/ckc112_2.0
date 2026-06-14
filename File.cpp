#include "File.h"

using namespace std;

// Constructor that runs on every File object creation
File::File(const string &fileName, const string &fileExtension)
    : name(fileName), extension(fileExtension) {}

string File::getFullName() const
{
    return name + "." + extension;
}

string File::getName() const
{
    return name;
}

string File::getExtension() const
{
    return extension;
}