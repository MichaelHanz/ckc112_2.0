#include "Folder.h"
#include <iostream>

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


Folder* Folder::searchFile(int fileIndex, int folderIndex, string targetFile){
    
    if(fileIndex < files.size()){

        if(files[fileIndex].getFullName() == targetFile){
            return this;
        }

        return searchFile(fileIndex + 1, folderIndex, targetFile);
    }
   
    if(folderIndex < subfolders.size()){

        Folder* result = subfolders[folderIndex] -> searchFile(0, 0, targetFile);

        if(result != nullptr){
            return result;
        }

        return searchFile(fileIndex, folderIndex + 1, targetFile);
    }

    return nullptr;
}

Folder* Folder::deleteFile(int fileIndex, int folderIndex, string removeFile){
    
    if(fileIndex < files.size()){

        if(files[fileIndex].getFullName() == removeFile){
            files.erase(files.begin() + fileIndex);

            return this;
        }

        return deleteFile(fileIndex + 1, folderIndex, removeFile);
    }
   
    if(folderIndex < subfolders.size()){
        
        Folder* result = subfolders[folderIndex] -> deleteFile(0, 0, removeFile);

        if(result != nullptr){
            return result;
        }

        return deleteFile(fileIndex, folderIndex + 1, removeFile);
    }

    return nullptr;
}

Folder* Folder::deleteFolder(int folderIndex, string removeFolder){

    if(folderIndex < subfolders.size()){

        if(subfolders[folderIndex] -> getFolderName() == removeFolder){
            
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
    
    if(folderIndex == 0 && fileIndex == 0){
        if(prefix.empty()){
            cout << name << endl;
        }
        else{
            cout << prefix << (isLast ? " |__ " : " |-- ") << name << endl;
        }
    }

    string nextPrefix = prefix;
    if(!prefix.empty()){
        nextPrefix += (isLast ? "    " : " |   ");
    }

    if(folderIndex < subfolders.size()){

        bool isLastChild = (folderIndex == subfolders.size() - 1);

        subfolders[folderIndex] -> displayTree(nextPrefix, isLastChild, 0, 0);

        displayTree(prefix, isLast, folderIndex + 1, fileIndex);

        return;
    }

    if(fileIndex < files.size()){

        bool isLastFile = (fileIndex == files.size() - 1);

        cout << nextPrefix << (isLastFile ? " |-- " : " |__ ") << files[fileIndex].getFullName() << endl;

        displayTree(prefix, isLast, folderIndex , fileIndex + 1);
        
        return;
    }
}