#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Folder.h"
#include "File.h"
#include <string>

using namespace std;

class FileSystem
{
private:
    Folder *root;
    Folder *current;

public:
    FileSystem();
    ~FileSystem(); 
    
    void loadFile();
    void run();

    // Student 3
    void enterFolder(string foldername);
    void showCurrentPath() const;
    void showCurrentFolder() const;
    void goBack();

    // Student 2
    void createFolder(string foldername);
    void createFile(string filename, string type);
    void deleteFile(string filename);
    void deleteFolder(string foldername);

    // Student 1
    void displayFullTree() const;
    void searchFile(string filename) const;
};

#endif
