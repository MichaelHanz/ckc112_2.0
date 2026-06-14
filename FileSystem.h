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
    //------------------------exception--------------------------------
    class RootNavigationException {}; 
    class FolderNavigationException {
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
