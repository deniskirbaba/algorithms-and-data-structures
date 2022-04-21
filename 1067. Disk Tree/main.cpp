#include <iostream>
#include <string>
#include <sstream>
#include <map>

using std::cin, std::cout, std::map, std::string, std::stringstream;

class Directory {
private: map<string, Directory*> directories;
public:
    Directory() {}

    Directory* create(string name) {
        directories[name] = new Directory();
        return directories[name];
    }

    Directory* get(string name) { // check if there is a directory named *name* in the current directory
        if (directories.find(name) == directories.end()) return create(name); // if not, create
        else return directories[name]; // if there is, return part of the next level directory
    }

    void print(string separator = "") { // recursive output of the resulting structure
        string tabs = " ";
        tabs += separator; // incrementing the indent for the next iteration
        map<string, Directory*> contents(directories.begin(), directories.end()); // get current branch of the directory
        for (auto dir = contents.begin(); dir != contents.end(); dir++) { // go through tree
            cout << separator << dir->first << '\n'; // print margin and local root folder
            dir->second->print(tabs); // go next
        }
    }
};

int main() {
    uint16_t n;
    cin >> n;

    Directory* root = new Directory(); // create root directory
    for (uint16_t i = 0; i < n; i++) {
        Directory* currentDir = root; // За локальную дефолтную деректорию берем root
        string fullPath, name;
        cin >> fullPath;
        stringstream ss(fullPath); // extract data from the input stream
        while (getline(ss, name, '\\'))  // while there is a continuation of the path, we go further in the catalog
            currentDir = currentDir->get(name); // if it already exists, go to the next level, if not, create a new one
    }
    root->print(); // recursively print directory tree

    return 0;
}