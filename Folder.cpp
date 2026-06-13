#include "Folder.h"

using namespace std;

Folder::Folder(string name, Folder *parent)
    : name(name), parent(parent) {}

vector<File> Folder::getFiles() const
{
    return files;
}

Folder *Folder::getParent() const
{
    return parent;
}

string Folder::getFolderName() const
{
    return name;
}

vector<Folder *> Folder::getSubFolders() const
{
    return subfolders;
}