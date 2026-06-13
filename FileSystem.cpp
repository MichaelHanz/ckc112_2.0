#include "FileSystem.h"
#include <algorithm>
#include <iostream>

using namespace std;

FileSystem::FileSystem()
{
    root = new Folder("root", nullptr);
    current = root;
}

FileSystem::~FileSystem()
{
    if (root != nullptr)
    {
        delete root; 
    }
}

void FileSystem::showCurrentPath() const
{
    vector<string> path;
    Folder *temp = current;

    while (temp != nullptr)
    {
        path.push_back(temp->getFolderName());
        temp = temp->getParent();
    }

    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i < path.size() - 1)
            cout << "/";
    }
    cout << endl;
}

void FileSystem::goBack()
{
    if (current->getParent() != nullptr)
    {
        current = current->getParent();
    }
    else
    {
        throw runtime_error("Already at root folder.");
    }
}

void FileSystem::enterFolder(string foldername)
{
    for (Folder *subfolder : current->getSubFolders())
    {
        if (subfolder->getFolderName() == foldername)
        {
            current = subfolder;
            return;
        }
    }
    throw runtime_error("Folder not found: " + foldername);
}

void FileSystem::showCurrentFolder() const
{
    cout << "\nCurrent Folder: " << current->getFolderName() << endl;
    cout << "-----------------------------------" << endl;

    cout << "Folders:" << endl;
    if (current->getSubFolders().empty())
    {
        cout << "  (No subfolders)" << endl;
    }
    else
    {
        for (Folder *subfolder : current->getSubFolders())
        {
            cout << "  + " << subfolder->getFolderName() << "/" << endl;
        }
    }

    cout << endl;

    cout << "Files:" << endl;
    if (current->getFiles().empty())
    {
        cout << "  (No files)" << endl;
    }
    else
    {
        for (File file : current->getFiles())
        {
            cout << "  - " << file.getFullName() << endl;
        }
    }
    cout << "-----------------------------------" << endl;
}

void FileSystem::createFolder(string foldername) 
{
    Folder* newSubFolder = new Folder(foldername, current);
    current->addSubFolder(newSubFolder);
}

void FileSystem::createFile(string filename, string type) 
{
    File newFile(filename, type);
    current->addFile(newFile);
}

void FileSystem::deleteFile(string filename) 
{
    current->deleteFile(filename);
}

void FileSystem::deleteFolder(string foldername) 
{
    current->deleteFolder(foldername);
}

void FileSystem::displayFullTree() const 
{
    cout << "\n--- Full Directory Mapping Tree ---" << endl;
    current->displayTree("", true, 0, 0);
    cout << "-----------------------------------" << endl;
}

void FileSystem::searchFile(string filename) const 
{
    Folder* result = current->searchFile(0, 0, filename);
    if (result != nullptr)
    {
        cout << "Success: File '" << filename << "' located inside path: ";
        vector<string> foundPath;
        Folder* temp = result;
        while(temp != nullptr) {
            foundPath.push_back(temp->getFolderName());
            temp = temp->getParent();
        }
        reverse(foundPath.begin(), foundPath.end());
        for (size_t i = 0; i < foundPath.size(); i++) {
            cout << foundPath[i] << (i < foundPath.size() - 1 ? "/" : "");
        }
        cout << "/" << filename << endl;
    }
    else
    {
        cout << "Search Failed: File '" << filename << "' could not be tracked anywhere in this tree branch.\n";
    }
}

void FileSystem::loadFile() 
{
    cout << "[!] System Data Layer Initialized Successfully." << endl;
}

void FileSystem::run()
{
    int choice = 0;
    do
    {
        cout << "\n===================================" << endl;
        cout << "      Mini File System Explorer     " << endl;
        cout << "===================================" << endl;
        cout << "1. Create Folder" << endl;
        cout << "2. Create File" << endl;
        cout << "3. Display Current Folder" << endl;
        cout << "4. Display Full Folder Tree" << endl;
        cout << "5. Search File" << endl;
        cout << "6. Enter Folder" << endl;
        cout << "7. Go Back to Parent Folder" << endl;
        cout << "8. Delete File" << endl;
        cout << "9. Delete Folder" << endl;
        cout << "10. Show Current Path" << endl;
        cout << "11. Exit" << endl;
        cout << "===================================" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid input. Please enter a number." << endl;
            continue;
        }

        string folderName, fileName, fileExtensions;

        try
        {
            switch (choice)
            {
            case 1:
                cout << "Enter folder name: ";
                cin.ignore();
                getline(cin, folderName);
                createFolder(folderName);
                break;
            case 2:
                cout << "Enter file name: ";
                cin >> fileName;
                cout << "Enter file extension (e.g., pdf, docx): ";
                cin >> fileExtensions;
                createFile(fileName, fileExtensions);
                break;
            case 3:
                showCurrentFolder();
                break;
            case 4:
                displayFullTree();
                break;
            case 5:
                cout << "Enter file name to search (with extension, e.g., notes.txt): ";
                cin >> fileName;
                searchFile(fileName);
                break;
            case 6:
                cout << "Enter folder name to enter: ";
                cin >> folderName;
                enterFolder(folderName);
                break;
            case 7:
                goBack();
                break;
            case 8:
                cout << "Enter file name to delete (with extension, e.g., note.txt): ";
                cin >> fileName;
                deleteFile(fileName);
                break;
            case 9:
                cout << "Enter folder name to delete: ";
                cin >> folderName;
                deleteFolder(folderName);
                break;
            case 10:
                showCurrentPath();
                break;
            case 11:
                cout << "Goodbye! Exiting Mini File System Explorer..." << endl;
                break;
            default:
                cout << "Error: Invalid choice. Please select an option between 1 and 11." << endl;
                break;
            }
        }
        catch (const exception &e)
        {
            cout << "\n[!] Operation Failed: " << e.what() << endl;
        }
    } while (choice != 11);
}
