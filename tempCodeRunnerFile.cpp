#include "FileSystem.h"
#include <algorithm>
#include <iostream>

FileSystem::FileSystem()
{
    root = new Folder("root", nullptr);
    current = root;
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

    for (int i = 0; i < path.size(); i++)
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
        // Error handling: already at root
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
    // Error handling: folder not found
    throw runtime_error("Folder not found: " + foldername);
}

void FileSystem::showCurrentFolder() const
{

    cout << "Current Folder:" << current->getFolderName() << "" << endl;
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

void FileSystem::run()
{
    int choice = 0;

    do
    {
        // Print the menu options (1-11)
        cout << "\n===================================" << endl;
        cout << "     Mini File System Explorer     " << endl;
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

        // Asking user for choice
        cout << "Enter your choice: ";
        cin >> choice;

        // Robustness: Handle non-integer inputs (e.g., user types "a" instead of "1")
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid input. Please enter a number." << endl;
            continue;
        }

        // Declare any needed string variables for user input
        string folderName, fileName, fileExtensions;

        // 6. Use switch(choice) wrapped in try/catch
        try
        {
            switch (choice)
            {
            case 1:
                cout << "Enter folder name: ";
                cin.ignore();
                getline(cin, folderName);
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
                cout << "Enter file name to search: ";
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
                cout << "Enter file name to delete: ";
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
            // Catch any runtime_error or invalid_argument thrown by the functions
            cout << "\n[!] Operation Failed: " << e.what() << endl;
        }

    } while (choice != 11); // 7. While loop condition
}

void FileSystem::createFolder(string foldername) {}
void FileSystem::createFile(string filename, string type) {}
void FileSystem::displayFullTree() const {}
void FileSystem::searchFile(string filename) const {}
void FileSystem::deleteFile(string filename) {}
void FileSystem::deleteFolder(string foldername) {}
void FileSystem::loadFile() {}