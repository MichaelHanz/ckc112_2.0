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
    ~Folder(); 

    // Student 2
    void addFile(File file);
    void addSubFolder(Folder *folder);
    void deleteFile(string filename);
    void deleteFolder(string foldername);

    // Student 1 
    void displayTree(string prefix, bool isLast, int folderIndex, int fileIndex) const;
    Folder* searchFile(int fileIndex, int folderIndex, string targetFile);
    Folder* deleteFile(int fileIndex, int folderIndex, string removeFile);
    Folder* deleteFolder(int folderIndex, string removeFolder);

    // Student 3
    vector<File> getFiles() const;
    Folder *getParent() const;
    vector<Folder *> getSubFolders() const;
    string getFolderName() const;
};

#endif
