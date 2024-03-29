#include "headers/dirio.h"
#include "headers/tinydir.h"
#include "headers/tools.h"

#include <tchar.h>

static CHAR* getDirectoryA(){
    CHAR* path;
    path = (CHAR*)malloc(BUFSIZE);
    GetCurrentDirectoryA(BUFSIZE, path);
    return path;
}

static WCHAR* getDirectory(){
    WCHAR* path;
    path = (WCHAR*)malloc(BUFSIZE);
    GetCurrentDirectoryW(BUFSIZE, path);
    return path;
}

VOID printCurrentDirectory(){
    WCHAR* path = getDirectory();
    wprintf(L"Current Directory is %s\n", path);
    free(path);
}


VOID moveDirectory(data* data){
    if(!data->arg){
        wprintf(L"Usage: moveto [direcotry], moves to that directory\n");
        return;
    }
    
    BOOL result = SetCurrentDirectoryW(data->arg);
    if(!result){
        wprintf(L"Error Changing Directory, Error Code %d\n", GetLastError());
        return;
    }
    if(data->path == NULL){
        data->path = (WCHAR*)malloc(BUFSIZE);
        GetCurrentDirectoryW(BUFSIZE, data->path);
        goto PRINT;
        return;
    }
    GetCurrentDirectoryW(BUFSIZE, data->path);
PRINT:
    wprintf(L"Moved To %s\n", data->path);
}

VOID createDirectory(data* data){
    if(!data->arg){
        wprintf(L"Usage: dcreate [direcotry], creates that directory\n");
        return;
    }
    BOOL result = CreateDirectoryW(data->arg, NULL);
    if(!result){
        wprintf(L"Failed Creating Direcotry, Error Code %d\n", GetLastError());
    }
    return;
}

VOID deleteDirectory(data* data){
    if(!data->arg){
        wprintf(L"Usage: ddelete [direcotry], deletes that directory\n");
        return;
    }
    BOOL result = RemoveDirectoryW(data->arg);
    if(!result){
        wprintf(L"Failed Removing Direcotry, Error Code %d\n", GetLastError());
    }
    return;
}

VOID printDirectory(data* data) {
    tinydir_dir dir;
    int i = 0;
    unsigned long directorySize = 0;
    char* path;
    BOOL isAllocated = FALSE;
    if(data->arg) path = wcharToChar(data->arg);
    else {
        path = getDirectoryA();
        isAllocated = TRUE;
    }
    const TCHAR* tcharPath = _T(path);
    tinydir_open(&dir, tcharPath);
    _tprintf("\n");
    while(dir.has_next){
        i++;
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if(file.is_dir) _tprintf("[%s] ", file.name);
        else _tprintf("%s ", file.name);
        if(i % 7 == 0) _tprintf("\n\n");
        tinydir_next(&dir);
    }
    _tprintf("\n");
    tinydir_close(&dir);
    if(isAllocated == TRUE){
        free(path);
    }
}