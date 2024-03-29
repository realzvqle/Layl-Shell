#include "headers/fileio.h"
#include "headers/tools.h"
#include <stdio.h>


BOOL createFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fcreate [filename]\n");
        return FALSE;
    }
    WCHAR fileNameBuffer[BUFSIZE];
    if(data->path == NULL){
        swprintf(fileNameBuffer, BUFSIZE, L"%s", data->arg);
    }
    else{
        swprintf(fileNameBuffer, BUFSIZE, L"%s\\%s", data->path,  data->arg);
    }
    debugPrint(data, L"File is %s\n", fileNameBuffer);

    HANDLE hFile = CreateFileW(fileNameBuffer, 
                              GENERIC_READ | GENERIC_WRITE, 
                              0,
                              NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        wprintf(L"Failed Creating File, Error Code %d\n", GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);
    return TRUE;
}

BOOL deleteFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fdelete [filename]\n");
        return FALSE;
    }
    WCHAR fileNameBuffer[BUFSIZE];
    if(data->path == NULL){
        swprintf(fileNameBuffer, BUFSIZE, L"%s", data->arg);
    }
    else{
        swprintf(fileNameBuffer, BUFSIZE, L"%s\\%s", data->path,  data->arg);
    }
    BOOL result = DeleteFileW(fileNameBuffer);
    debugPrint(data, L"File is %s\n", fileNameBuffer);
    if(result == FALSE){
        wprintf(L"Failed Deleting File, Error Code %d\n", GetLastError());\
        return FALSE;
    }
    return TRUE;
}

BOOL copyFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fcopy [filename1] [filename2]\n");
        return FALSE;
    }
    WCHAR* firstFile;
    WCHAR* secondFile;
    WCHAR* holder;
    firstFile = wcstok(data->arg, L" ", &holder);
    secondFile = wcstok(NULL, L"\n", &holder);
    if(!secondFile){
        wprintf(L"Usage: fcopy [filename1] [filename2]\n");
        return FALSE;
    }
    WCHAR fileName1Buffer[BUFSIZE];
    if(data->path == NULL){
        swprintf(fileName1Buffer, BUFSIZE, L"%s", firstFile);
    }
    else{
        swprintf(fileName1Buffer, BUFSIZE, L"%s\\%s", data->path,  firstFile);
    }
    WCHAR fileName2Buffer[BUFSIZE];
    if(data->path == NULL){
        swprintf(fileName2Buffer, BUFSIZE, L"%s", secondFile);
    }
    else{
        swprintf(fileName2Buffer, BUFSIZE, L"%s\\%s", data->path,  secondFile);
    }

    debugPrint(data, L"First File is %s, Second is %s\n", fileName1Buffer, fileName2Buffer);
    BOOL result = CopyFileW(fileName1Buffer, fileName2Buffer, FALSE);
    if(result == FALSE){
        wprintf(L"Failed Copying File, Error Code %d\n", GetLastError());
        return FALSE;
    }
    return TRUE;
}

BOOL writeFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fprint [filename] [content]\n");
        return FALSE;
    }
    WCHAR* firstFile;
    WCHAR* content;
    WCHAR* holder;
    firstFile = wcstok(data->arg, L" ", &holder);
    content = wcstok(NULL, L"\n", &holder);
    WCHAR fileNameBuffer[BUFSIZE];
    if(data->path == NULL){
        swprintf(fileNameBuffer, BUFSIZE, L"%s", firstFile);
    }
    else{
        swprintf(fileNameBuffer, BUFSIZE, L"%s\\%s", data->path,  firstFile);
    }
    if(!content){
        wprintf(L"Usage: fwrite [filename] [content]\n");
        return FALSE;
    }
    debugPrint(data, L"First File is %s, Content is %s\n", fileNameBuffer, content);
    char* normalContent = wcharToChar(content);
    HANDLE hFile = CreateFileW(fileNameBuffer, 
                             GENERIC_WRITE, 
                             0, 
                             NULL,
                             OPEN_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        wprintf(L"Failed Creating File, Error Code %d\n", GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    BOOL result = WriteFile(hFile, 
             normalContent, 
             strlen(normalContent), 
             NULL, 
             NULL);
    if(result == FALSE){
        wprintf(L"Failed Writing File, Error Code %d\n", GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    free(normalContent);
    CloseHandle(hFile);
    return TRUE;
}

BOOL writeFileNoReset(data* data){
    if(!data->arg){
        wprintf(L"Usage: fwrite [filename] [content]\n");
        return FALSE;
    }
    WCHAR* firstFile;
    WCHAR* content;
    WCHAR* holder;
    firstFile = wcstok(data->arg, L" ", &holder);
    content = wcstok(NULL, L"\n", &holder);
    WCHAR fileNameBuffer[BUFSIZE];
    if(data->path == NULL){
        swprintf(fileNameBuffer, BUFSIZE, L"%s", firstFile);
    }
    else{
        swprintf(fileNameBuffer, BUFSIZE, L"%s\\%s", data->path,  firstFile);
    }
    if(!content){
        wprintf(L"Usage: fwrite [filename] [content]\n");
        return FALSE;
    }
    debugPrint(data, L"File is %s\n", fileNameBuffer);
    FILE* file = _wfopen(fileNameBuffer, L"a");
    if(file == NULL){
        wprintf(L"Failed Opening File\n");
        return FALSE;
    }
    fwprintf(file, content);
    fwprintf(file, L"\n");
    fclose(file);
    return TRUE;
}

BOOL readFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fread [filename]\n");
        return FALSE;
    }
    WCHAR buffer[BUFSIZE];
    WCHAR fileNameBuffer[BUFSIZE];
    if(data->path == NULL){
        swprintf(fileNameBuffer, BUFSIZE, L"%s", data->arg);
    }
    else{
        swprintf(fileNameBuffer, BUFSIZE, L"%s\\%s", data->path,  data->arg);
    }
    debugPrint(data, L"File is %s\n", fileNameBuffer);
    HANDLE hFile = CreateFileW(fileNameBuffer, 
                              GENERIC_READ | GENERIC_WRITE, 
                              0,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        wprintf(L"Failed Creating File, Error Code %d\n", GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    BOOL result = ReadFile(hFile,
                          buffer,
                          BUFSIZE,
                          NULL,
                          NULL);
    if(result == FALSE){
        CloseHandle(hFile);
        wprintf(L"Failed Reading File, Error Code %d\n", GetLastError());
        return FALSE;
    }
    wprintf(L"%hs\n", buffer);
    CloseHandle(hFile);
    return TRUE;
}