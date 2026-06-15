#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Folder.h"
#include "File.h"

using namespace std;

class FileSystem
{
    Folder *root;
    Folder *current;
    vector<string> splitString(string str, char delimiter);
    Folder *findFolder(vector<string> pathSegments);

public:
    //------------------------exceptions--------------------------------
    class RootNavigationException
    {
    }; // Throw when the user is in the root folder
    class FolderNavigationException // Thrown when the name isnt on the folder vector
    {
    private:
        string missingFolder;

    public:
        FolderNavigationException(string name) { missingFolder = name; }
        string getName() const { return missingFolder; }
    };
    // =================================================================

    FileSystem();
    ~FileSystem();

    void loadFile();
    void run();

    void enterFolder(const string &foldername);
    void showCurrentPath() const;
    void showCurrentFolder() const;
    void goBack();

    void createFolder(const string &foldername);
    void createFile(const string &filename, const string &type);
    void deleteFile(const string &filename);
    void deleteFolder(const string &foldername);

    void displayFullTree() const;
    void searchFile(const string &filename) const;
};

#endif
