#ifndef FOLDER_H
#define FOLDER_H

#include "File.h"
#include <vector>
#include <string>

using namespace std;

class Folder
{
    string name;
    Folder *parent;
    vector<File> files;
    vector<Folder *> subfolders;

public:
    Folder(string name, Folder *parent); // Constructor For Folder Class
    ~Folder();                           // Destructor for Folder Class

    void addFile(const File &file);
    void addSubFolder(Folder *folder);

    void displayTree(const string &prefix) const;
    Folder *searchFile(int fileIndex, int folderIndex, const string &targetFile);
    Folder *deleteFile(int fileIndex, int folderIndex, const string &removeFile);
    Folder *deleteFolder(int folderIndex, const string &removeFolder);

    vector<File> getFiles() const;
    Folder *getParent() const;
    vector<Folder *> getSubFolders() const;
    string getFolderName() const;
};

#endif