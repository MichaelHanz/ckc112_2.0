#include "Folder.h"
#include <iostream>

using namespace std;

Folder::Folder(string name, Folder *parent)
    : name(name), parent(parent) {}

Folder::~Folder()
{
    for (Folder *sub : subfolders)
    {
        delete sub;
    }
}

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

void Folder::addFile(const File &file)
{
    if (file.getName().empty() || file.getExtension().empty())
    {
        cout << "Error: File name or extension cannot be empty!\n";
        return;
    }

    for (const File &existingFile : files)
    {
        if (existingFile.getName() == file.getName() && existingFile.getExtension() == file.getExtension())
        {
            cout << "Error: A file named '" << file.getFullName() << "' already exists.\n";
            return;
        }
    }

    files.push_back(file);
    cout << "File '" << file.getFullName() << "' created successfully.\n";
}

void Folder::addSubFolder(Folder *folder)
{
    if (folder == nullptr)
        return;

    if (folder->getFolderName().empty())
    {
        cout << "Error: Folder name cannot be empty!\n";
        delete folder;
        return;
    }

    for (Folder *sub : subfolders)
    {
        if (sub->getFolderName() == folder->getFolderName())
        {
            cout << "Error: A folder named '" << folder->getFolderName() << "' already exists here.\n";
            delete folder; // Clean memory Once an error occurred
            return;
        }
    }

    folder->parent = this;
    subfolders.push_back(folder);
    cout << "Folder '" << folder->getFolderName() << "' created successfully.\n";
}

Folder *Folder::deleteFile(int fileIndex, int folderIndex, const string &removeFile)
{
    if (fileIndex < files.size())
    {
        if (files[fileIndex].getFullName() == removeFile)
        {
            files.erase(files.begin() + fileIndex);
            return this;
        }
        return deleteFile(fileIndex + 1, folderIndex, removeFile);
    }

    if (folderIndex < subfolders.size())
    {
        Folder *result = subfolders[folderIndex]->deleteFile(0, 0, removeFile);
        if (result != nullptr)
        {
            return result;
        }
        return deleteFile(fileIndex, folderIndex + 1, removeFile);
    }
    return nullptr;
}

Folder *Folder::deleteFolder(int folderIndex, const string &removeFolder)
{
    if (folderIndex < subfolders.size())
    {
        if (subfolders[folderIndex]->getFolderName() == removeFolder)
        {
            Folder *folderToDelete = subfolders[folderIndex];
            subfolders.erase(subfolders.begin() + folderIndex);
            delete folderToDelete;
            return this;
        }
        return deleteFolder(folderIndex + 1, removeFolder);
    }
    return nullptr;
}

Folder *Folder::searchFile(int fileIndex, int folderIndex, const string &targetFile)
{
    if (fileIndex < files.size())
    {
        if (files[fileIndex].getFullName() == targetFile)
        {
            return this;
        }
        return searchFile(fileIndex + 1, folderIndex, targetFile);
    }

    if (folderIndex < subfolders.size())
    {
        Folder *result = subfolders[folderIndex]->searchFile(0, 0, targetFile);
        if (result != nullptr)
        {
            return result;
        }
        return searchFile(fileIndex, folderIndex + 1, targetFile);
    }
    return nullptr;
}

void Folder::displayTree(const string &prefix) const
{
    // 1. Print all Files first
    for (size_t i = 0; i < files.size(); i++)
    {
        // Check if this is the very last item in the entire folder
        bool isLastItem = (i == files.size() - 1) && subfolders.empty();

        cout << prefix << (isLastItem ? "|__ " : "|-- ") << files[i].getFullName() << "\n";
    }

    // 2. Print all Subfolders (and trigger RECURSION)
    for (size_t i = 0; i < subfolders.size(); i++)
    {
        // Check if this is the last subfolder
        bool isLastItem = (i == subfolders.size() - 1);

        cout << prefix << (isLastItem ? "|__ " : "|-- ") << subfolders[i]->getFolderName() << "\n";

        // 3. THE RECURSIVE CALL
        // If it's the last item, we add blank spaces to the prefix.
        // If it's not, we add a vertical bar '|' to keep the line going down.
        string nextPrefix = prefix + (isLastItem ? "    " : "|   ");
        subfolders[i]->displayTree(nextPrefix);
    }
}