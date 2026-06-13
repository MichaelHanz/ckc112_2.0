#include "File.h"

using namespace std; 

// Constructor to initialize file details using optimized memory passing
File::File(const string& fileName, const string& fileExtension) 
    : name(fileName), extension(fileExtension) {}

// Returns the raw string name
string File::getName() const {
    return name;
}

// Returns the raw string extension
string File::getExtension() const {
    return extension;
}

// Combines name and extension with a dot safely inside const operations
string File::getFullName() const {
    return name + "." + extension;
}
