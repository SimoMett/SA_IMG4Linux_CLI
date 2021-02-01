//
// Created by matteo on 03/04/19.
//

#include <iostream>
#include <string.h>
#include "IMGFile.h"



IMGFile::IMGFile(string path) : fileName(path), numberOfEntries(0)
{
    if(fileName.find(".img")==string::npos)
        throw std::runtime_error("Not a .IMG file");
    imgStream=ifstream(fileName, ifstream::binary);
    if(!imgStream.is_open())
        throw std::runtime_error("Invalid IMG archive");

    char word[4];
    imgStream.read(word,4);

    if(strcmp(word,"VER2"))
        throw std::runtime_error("Invalid IMG archive version. Required VER2");

    //Tutto ok
    imgStream.read(reinterpret_cast<char*>(&numberOfEntries), sizeof(int));

    for(int i=0;i<numberOfEntries;i++)
    {
        struct TmpEntry
        {
            unsigned int offset;
            unsigned short fSize;
            unsigned short fSize2;
            char fileName[24];
        } tmpEntry;

        DirEntry newentry;
        imgStream.read(reinterpret_cast<char*>(&tmpEntry), sizeof(TmpEntry));

        newentry.offset=tmpEntry.offset;
        newentry.fSize=tmpEntry.fSize;
        memcpy(newentry.fileName,tmpEntry.fileName,sizeof(newentry.fileName));

        entries.push_back(newentry);
    }
}

IMGFile::~IMGFile()
{
    if(imgStream.is_open())
    {
        imgStream.close();
    }
}

bool IMGFile::getEntryByName(string entryName, unsigned int &entryId)
{
    bool found=false;

    for(int i=0;i<entries.size();i++)
    {
        if(!strcmp(entries[i].fileName,entryName.c_str()))
        {
            entryId=i;
            found=true;
            break;
        }
    }
    return found;
}

void IMGFile::extractFile(unsigned int entryId, string where)
{
    if(entryId<0 || entryId>=entries.size())
    {
        cerr << "Invalid entry ID"<<endl;
    }
    else
    {
        imgStream.seekg(entries[entryId].offset * 2048);

        char *buffer = new char[entries[entryId].fSize * 2048];
        imgStream.read(buffer, entries[entryId].fSize * 2048);

        ofstream outputFile(where + entries[entryId].fileName);
        outputFile.write(buffer, entries[entryId].fSize * 2048);
        outputFile.close();
        delete[] buffer;
        cout << "Extracted "<<entries[entryId].fileName<<" in "<<where + entries[entryId].fileName<<endl;
    }
}