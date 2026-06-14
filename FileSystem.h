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
    ~FileSystem();

    // The one time run functions in the "FileSystem" Object
    void loadFile();
    void run();

    // Student 3
    void enterFolder(const string &foldername);
    void showCurrentPath() const;
    void showCurrentFolder() const;
    void goBack();

    // Student 2
    void createFolder(const string &foldername);
    void createFile(const string &filename, const string &type);
    void deleteFile(const string &filename);
    void deleteFolder(const string &foldername);

    // Student 1
    void displayFullTree() const;
    void searchFile(const string &filename) const;
};

#endif