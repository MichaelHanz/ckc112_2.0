#ifndef FILE_H
#define FILE_H

#include <string>

using namespace std;

class File {
private:
    string name;       // e.g., "assignment"
    string extension;  // e.g., "docx"

public:
    
    File(const string& fileName, const string& fileExtension);

    // Getters (Required for your duplicate checking logic in Folder.cpp)
    string getName() const;
    string getExtension() const;
    
    // Returns the complete file name (e.g., "assignment.docx")
    string getFullName() const;
};

#endif
