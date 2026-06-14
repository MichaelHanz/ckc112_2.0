#include "FileSystem.h"
#include <algorithm>
#include <iostream>
#include <fstream>

FileSystem::FileSystem()
{
    root = new Folder("Root", nullptr);
    current = root;
    loadFile();
}

FileSystem::~FileSystem()
{
    delete root;

    root = nullptr;
    current = nullptr;
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
    if (current->getParent() == nullptr)
    {
        throw RootNavigationException();
    }
    current = current->getParent();
}

void FileSystem::enterFolder(const string &foldername)
{
    
    for (Folder *subfolder : current->getSubFolders())
    {
        if (subfolder->getFolderName() == foldername)
        {
            current = subfolder;
            return;
        }
    }
    throw FolderNavigationException(foldername);
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
                cin.ignore(); // Clears the newline left by the menu choice
                getline(cin, folderName);
                createFolder(folderName);
                break;

            case 2:
                cout << "Enter file name: ";
                cin.ignore(); // Clears the newline left by the menu choice
                getline(cin, fileName);
                cout << "Enter file extension (Example: pdf, docx or txt): ";
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
                cin.ignore();
                getline(cin, fileName);
                searchFile(fileName);
                break;

            case 6:
                cout << "Enter folder name to enter: ";
                cin.ignore();
                getline(cin, folderName);
                enterFolder(folderName);
                cout << "Moved into: " << folderName << endl;
                break;

            case 7:
                goBack();
                cout << "Moved back to: " << current->getFolderName() << endl;
                break;

            case 8:
                cout << "Enter file name to delete: ";
                cin.ignore();
                getline(cin, fileName);
                deleteFile(fileName);
                break;

            case 9:
                cout << "Enter folder name to delete: ";
                cin.ignore();
                getline(cin, folderName);
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
        
        catch (Folder::EmptyNameException)
        {
            cout << "\n[!] Execution Error: Names or formatting extensions cannot be left blank!\n";
        }
        // Extracting data from exception instances dynamically (Slide 25)
        catch (Folder::DuplicateItemException e)
        {
            cout << "\n[!] Conflict Error: '" << e.getName() << "' already exists in this folder location!\n";
        }
        catch (Folder::ItemNotFoundException e)
        {
            cout << "\n[!] Processing Error: Target item '" << e.getName() << "' could not be located anywhere in this context!\n";
        }
        catch (FileSystem::RootNavigationException)
        {
            cout << "\n[!] Navigation Error: You are already at the Root node. Cannot step back!\n";
        }
        catch (FileSystem::FolderNavigationException e)
        {
            cout << "\n[!] Navigation Error: Directory match failed. Target '" << e.getName() << "' does not exist here!\n";
            
    } while (choice != 11);
}

Folder *FileSystem::findFolder(vector<string> pathSegments)
{
    // 1. Create a temp Folder* pointing to root
    Folder *temp = root;

    // 2. Loop through pathSegments STARTING from index 1 (skip "Root")

    for (int i = 1; i < pathSegments.size(); i++)
    {
        // 3. Assume not found — set a flag
        bool found = false;

        // 4. Loop through temp's subfolders
        for (Folder *subfolder : temp->getSubFolders())
        {
            // if subfolder name matches current segment
            if (subfolder->getFolderName() == pathSegments[i])
            {
                // move temp into it, break
                temp = subfolder;
                found = true;
                break;
            }
        }

        // 5. If not found after inner loop → return nullptr
        if (!found)
        {
            return nullptr;
        }
    }
    // 6. After all segments processed → return temp
    return temp;
}

vector<string> FileSystem::splitString(string str, char delimiter)
{
    vector<string> segments;
    string segment = "";

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == delimiter)
        {
            segments.push_back(segment);
            segment = "";
        }
        else
        {
            segment += str[i];
        }
    }
    segments.push_back(segment);
    return segments;
}

void FileSystem::loadFile()
{
    // 1. Open "FileSystem.txt" using ifstream
    ifstream file("filesystem.txt");

    // 2. Check if file opened successfully, if not print error and return
    if (!file.is_open())
    {
        cout << "Error: Could not open filesystem.txt" << endl;
        return;
    }
    string line;

    // 3. Read line by line using getline()

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        // 4. Split line by space to get type and path
        vector<string> lineParts = splitString(line, ' ');

        // Safety check to ensure the line has at least a type and a path to avoid checking grammatical errors
        if (lineParts.size() < 2)
            continue;

        string type = lineParts[0];
        string fullPath = lineParts[1];

        // 5. Split path by "/" to get path segments
        vector<string> pathSegments = splitString(fullPath, '/');

        if (pathSegments.empty())
            continue;

        // 6. If type == "FOLDER":
        if (type == "FOLDER")
        {
            // get parent segments (all except last)
            vector<string> parentPath;
            for (size_t i = 0; i < pathSegments.size() - 1; i++)
            {
                parentPath.push_back(pathSegments[i]);
            }

            string newFolderName = pathSegments.back();

            // find parent folder using findFolder()
            Folder *parentFolder = findFolder(parentPath);

            if (parentFolder != nullptr)
            {
                // create new Folder* using new
                Folder *newFolder = new Folder(newFolderName, parentFolder);
                // add to parent's subfolders
                parentFolder->addSubFolder(newFolder);
            }
        }
        // 7. If type == "FILE":
        else if (type == "FILE")
        {
            // get parent segments (all except last)
            vector<string> parentPath;
            for (size_t i = 0; i < pathSegments.size() - 1; i++)
            {
                parentPath.push_back(pathSegments[i]);
            }

            // get last segment (e.g. "assignment.docx")
            string fileString = pathSegments.back();

            // split last segment by "." to get name and extension
            vector<string> fileParts = splitString(fileString, '.');

            string fileName = fileParts[0];
            string fileExt = "";

            // Ensure there is an extension before trying to access index 1
            if (fileParts.size() > 1)
            {
                fileExt = fileParts[1];
            }

            // find parent folder using findFolder()
            Folder *parentFolder = findFolder(parentPath);

            if (parentFolder != nullptr)
            {
                // create File object
                File newFile(fileName, fileExt);
                // add to parent's files
                parentFolder->addFile(newFile);
            }
        }
    }

    file.close();
    cout << "System structure loaded successfully from filesystem.txt." << endl;
}

void FileSystem::createFolder(const string &foldername)
{
    Folder *newFolder = new Folder(foldername, current);

    current->addSubFolder(newFolder);
}

void FileSystem::createFile(const string &filename, const string &type)
{
    File newFile(filename, type);

    current->addFile(newFile);
}

void FileSystem::displayFullTree() const
{
    cout << "\n===================================" << endl;
    cout << "        Full Folder Tree           " << endl;
    cout << "===================================" << endl;

    if (root != nullptr)
    {
        // Print the Root folder itself
        cout << root->getFolderName() << "/" << endl;

        // Kick off the recursion with an empty starting prefix
        root->displayTree("");
    }
    else
    {
        cout << "(File system is completely empty)" << endl;
    }

    cout << "===================================\n"
         << endl;
}
void FileSystem::searchFile(const string &filename) const
{
    cout << "\n===================================" << endl;
    cout << "  Searching for: " << filename << endl;
    cout << "===================================" << endl;

    if (root != nullptr)
    {

        Folder *foundFolder = root->searchFile(0, 0, filename);

        if (foundFolder != nullptr)
        {
            cout << "[+] Success! File found." << endl;
            cout << "[+] Location: Inside the '" << foundFolder->getFolderName() << "' folder." << endl;
        }
        else
        {
            cout << "[-] File not found: '" << filename << "' does not exist in the system." << endl;
        }
    }
    else
    {
        cout << "[-] Error: The file system is entirely empty." << endl;
    }

    cout << "===================================\n"
         << endl;
}
void FileSystem::deleteFile(const string &filename)
{
    if (root == nullptr)
    {
        cout << "Error: The file system is entirely empty.\n";
        return;
    }

    Folder *deletedFromFolder = root->deleteFile(0, 0, filename);

    if (deletedFromFolder != nullptr)
    {
        cout << "Success: File '" << filename << "' was deleted from the '"
             << deletedFromFolder->getFolderName() << "' folder.\n";
    }
    else
    {
        cout << "Error: File '" << filename << "' not found anywhere in the system.\n";
    }
}

void FileSystem::deleteFolder(const string &foldername)
{
    if (current == nullptr)
    {
        cout << "Error: No current directory selected.\n";
        return;
    }

    Folder *result = current->deleteFolder(0, foldername);

    if (result != nullptr)
    {
        cout << "Success: Folder '" << foldername << "' and all its contents were safely deleted.\n";
    }
    else
    {
        cout << "Error: Folder '" << foldername << "' not found in the current directory.\n";
    }
}
