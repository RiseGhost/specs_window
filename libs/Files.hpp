#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

struct WFile{
    string Name;
    string FileType;
    double KB = -1;          //File Size i KiloBytes
};

// Função para converter uma string para TCHAR*
TCHAR* ConvertToWCHAR(string str) {
    TCHAR* charBuffer = new TCHAR[str.length() + 1];
    strcpy_s(charBuffer, str.length() + 1, str.c_str());
    return charBuffer;
}

vector<WFile> FilesPath(string path){
    vector<WFile> files;
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;
    TCHAR* szDir = (TCHAR*) malloc(sizeof(TCHAR) * MAX_PATH);
    szDir = ConvertToWCHAR(path);
    HANDLE hFind = INVALID_HANDLE_VALUE;
    
    // Append '\*' to the directory name.
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    // Find the first file in the directory.
    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
       return files;

    
    // List all the files in the directory with some info about them.
    do{
        WFile WF;
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            WF.FileType = "DIR";
        else{
           filesize.LowPart = ffd.nFileSizeLow;
           filesize.HighPart = ffd.nFileSizeHigh;
           WF.FileType = "File";
           WF.KB = filesize.QuadPart;
        }
        WF.Name = ffd.cFileName;
        files.push_back(WF);
    }
    while (FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);
    return files;
}