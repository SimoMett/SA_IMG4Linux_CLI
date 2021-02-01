//
// Created by matteo on 03/04/19.
//

#ifndef SA_IMG4LINUX_CLI_IMGFILE_H
#define SA_IMG4LINUX_CLI_IMGFILE_H

#include <string>
#include <fstream>
#include <exception>
#include <vector>

using namespace std;

struct DirEntry
{
    uint					offset;
    ushort					fSize;
    char					fileName[24];
};

class IMGFile {

public:
    IMGFile(string path);
    ~IMGFile();

    unsigned int getNumberOfEntries() const {
        return numberOfEntries;
    }

    bool getEntryByName(string entryName, unsigned int &entryId);
    void extractFile(unsigned int entryId, string where = "");

private:
    string fileName;
    ifstream imgStream;
    unsigned int numberOfEntries;
    vector<DirEntry> entries;
};

#endif //SA_IMG4LINUX_CLI_IMGFILE_H
