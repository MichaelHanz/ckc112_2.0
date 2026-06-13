#include "Folder.h"
#include <iostream>

using namespace std;

// Constructor
Folder::Folder(string name, Folder *parent)
    : name(name), parent(parent) {}


vector<File> Folder::getFiles() const {
    return files;
}

Folder *Folder::getParent() const {
    return parent;
}

string Folder::getFolderName() const {
    return name;
}

vector<Folder *> Folder::getSubFolders() const {
    return subfolders;
}



void Folder::addFile(File file) {
    // Check for empty values inside the passed object
    if (file.getName().empty() || file.getExtension().empty()) {
        cout << "Error: File name or extension cannot be empty!\n";
        return;
    }

    // Check for duplicates
    for (const File& existingFile : files) {
        if (existingFile.getName() == file.getName() && existingFile.getExtension() == file.getExtension()) {
            cout << "Error: A file named '" << file.getFullName() << "' already exists.\n";
            return;
        }
    }

    files.push_back(file);
    cout << "File '" << file.getFullName() << "' created successfully.\n";
}


void Folder::addSubFolder(Folder *folder) {
    if (folder == nullptr) return;

    if (folder->getFolderName().empty()) {
        cout << "Error: Folder name cannot be empty!\n";
        return;
    }

    // Check for duplicates
    for (Folder* const& sub : subfolders) {
        if (sub->getFolderName() == folder->getFolderName()) {
            cout << "Error: A folder named '" << folder->getFolderName() << "' already exists here.\n";
            return;
        }
    }

    // Link the parent relationship manually since the folder was created outside
    folder->parent = this; 
    
    subfolders.push_back(folder); 
    cout << "Folder '" << folder->getFolderName() << "' created successfully.\n";
}


void Folder::deleteFile(string filename) {
    for (vector<File>::iterator it = files.begin(); it != files.end(); ++it) {
        if (it->getFullName() == filename || it->getName() == filename) {
            files.erase(it); 
            cout << "File '" << filename << "' has been deleted.\n";
            return;
        }
    }
    cout << "Error: File '" << filename << "' not found in current folder.\n";
}


void Folder::deleteFolder(string foldername) {
    for (vector<Folder*>::iterator it = subfolders.begin(); it != subfolders.end(); ++it) {
        if ((*it)->getFolderName() == foldername) {
            delete *it;           // Deletes physical memory allocation from the Heap
            subfolders.erase(it); // Wipes the empty slot out of the tracker array
            cout << "Folder '" << foldername << "' removed from directory list.\n";
            return;
        }
    }
    cout << "Error: Folder '" << foldername << "' not found in current folder.\n";
}


void Folder::clearVectors() {
    files.clear();
    for (Folder* sub : subfolders) {
        delete sub; 
    }
    subfolders.clear();
}



Folder* Folder::searchFile(int fileIndex, int folderIndex, string targetFile) {
    if (fileIndex < files.size()) {
        if (files[fileIndex].getFullName() == targetFile) {
            return this;
        }
        return searchFile(fileIndex + 1, folderIndex, targetFile);
    }
   
    if (folderIndex < subfolders.size()) {
        Folder* result = subfolders[folderIndex]->searchFile(0, 0, targetFile);
        if (result != nullptr) {
            return result;
        }
        return searchFile(fileIndex, folderIndex + 1, targetFile);
    }
    return nullptr;
}

Folder* Folder::deleteFile(int fileIndex, int folderIndex, string removeFile) {
    if (fileIndex < files.size()) {
        if (files[fileIndex].getFullName() == removeFile) {
            files.erase(files.begin() + fileIndex);
            return this;
        }
        return deleteFile(fileIndex + 1, folderIndex, removeFile);
    }
   
    if (folderIndex < subfolders.size()) {
        Folder* result = subfolders[folderIndex]->deleteFile(0, 0, removeFile);
        if (result != nullptr) {
            return result;
        }
        return deleteFile(fileIndex, folderIndex + 1, removeFile);
    }
    return nullptr;
}

Folder* Folder::deleteFolder(int folderIndex, string removeFolder) {
    if (folderIndex < subfolders.size()) {
        if (subfolders[folderIndex]->getFolderName() == removeFolder) {
            Folder* folderToDelete = subfolders[folderIndex];
            subfolders.erase(subfolders.begin() + folderIndex);
            delete folderToDelete;
            return this;
        }
        return deleteFolder(folderIndex + 1, removeFolder); 
    }
    return nullptr;
}

void Folder::displayTree(string prefix, bool isLast, int folderIndex, int fileIndex) const {
    if (folderIndex == 0 && fileIndex == 0) {
        if (prefix.empty()) {
            cout << name << endl;
        } else {
            cout << prefix << (isLast ? " |__ " : " |-- ") << name << endl;
        }
    }

    string nextPrefix = prefix;
    if (!prefix.empty()) {
        nextPrefix += (isLast ? "    " : " |   ");
    }

    if (folderIndex < subfolders.size()) {
        bool isLastChild = (folderIndex == subfolders.size() - 1);
        subfolders[folderIndex]->displayTree(nextPrefix, isLastChild, 0, 0);
        displayTree(prefix, isLast, folderIndex + 1, fileIndex);
        return;
    }

    if (fileIndex < files.size()) {
        bool isLastFile = (fileIndex == files.size() - 1);
        cout << nextPrefix << (isLastFile ? " |-- " : " |__ ") << files[fileIndex].getFullName() << endl;
        displayTree(prefix, isLast, folderIndex, fileIndex + 1);
        return;
    }
}
