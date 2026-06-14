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

    
    void enterFolder(string foldername);
    void showCurrentPath() const;
    void showCurrentFolder() const;
    void goBack();

    
    void createFolder(string foldername);
    void createFile(string filename, string type);
    void deleteFile(string filename);
    void deleteFolder(string foldername);

    
    void displayFullTree() const;
    void searchFile(string filename) const;
};

#endif
