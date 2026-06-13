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
    Folder(string name, Folder *parent);
    // Student 2
    void addFile(File file);
    void addSubFolder(Folder *folder);
    void deleteFile(string filename);
    void deleteFolder(string foldername);

    // Student 1
    bool searchFile(string filename);
    void displayTree(int depth) const;

    // Student 3
    vector<File> getFiles() const;
    Folder *getParent() const;
    vector<Folder *> getSubFolders() const;
    string getFolderName() const;
};

#endif