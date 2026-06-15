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
    //-------------------------exceptions--------------------------------
    class EmptyNameException
    {
    }; // Thrown when a string input is blank

    class DuplicateItemException // Thrown when duplicate filenames or foldernames are found
    {
    private:
        string itemName;

    public:
        DuplicateItemException(string name) { itemName = name; }
        string getName() const { return itemName; }
    };

    class ItemNotFoundException // Thrown when the searched item is not found
    {
    private:
        string targetName;

    public:
        ItemNotFoundException(string name) { targetName = name; }
        string getName() const { return targetName; }
    };
    // =================================================================

    Folder(string name, Folder *parent);
    ~Folder();

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
