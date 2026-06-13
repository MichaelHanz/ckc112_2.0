#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Folder.h"
#include "File.h"

using namespace std;

class FileSystem
{
    Folder *root;
    Folder *current;
    vector<string> splitString(string str, char delimiter); // Helper function to split the root strings
    Folder *findFolder(vector<string> pathSegments);        // Helper Function for loadFromFile

public:
    FileSystem();
    void loadFile();
    void run();

    // Student 3
    void enterFolder(string foldername);
    void showCurrentPath() const;
    void showCurrentFolder() const;
    void goBack();

    // You guys punya
    void createFolder(string foldername);
    void createFile(string filename, string type);
    void displayFullTree() const;
    void searchFile(string filename) const;
    void deleteFile(string filename);
    void deleteFolder(string foldername);
};

#endif