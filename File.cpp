#include "File.h"

using namespace std;

File::File(string name, string extension)
    : name(name), extension(extension) {}

string File::getFullName()
{
    return name + "." + extension;
}
