#ifndef FILE_H
#define FILE_H

#include <string>

using namespace std;

class File {
private:
    string name;       // e.g., "assignment"
    string extension;  // e.g., "docx"

public:
    // Constructor (Optimized with const references)
    File(const string& fileName, const string& fileExtension);

    string getName() const;
    string getExtension() const;
    
    // Returns the complete file name (e.g., "assignment.docx")
    string getFullName() const;
};

#endif
