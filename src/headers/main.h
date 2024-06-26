#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <Windows.h>
#include <wchar.h>
#include <DbgHelp.h>

#define BUFSIZE 4096
#define VER 0.360


typedef struct _fileInfo{
    WCHAR* fileName;
    WCHAR* fileContentBuffer;
    WCHAR* nonNewLineChar;
} fileInfo;

typedef struct _cliInfo{
    WCHAR buffer[BUFSIZE];
    WCHAR* nonNewLineChar;
} cliInfo;

typedef struct _data{
    WCHAR* cmd;
    WCHAR* arg;
    BOOL isDebug;
    int currentCmd;
    int state;
} data;

#endif