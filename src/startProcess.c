#include "headers/startProcess.h"



VOID createProcess(WCHAR* process, WCHAR* arguments){
    WCHAR buffer[BUFSIZE];
    STARTUPINFOW sif;
    PROCESS_INFORMATION lpi;
    ZeroMemory(&sif, sizeof(sif));
    sif.cb = sizeof(sif);
    ZeroMemory(&lpi, sizeof(lpi));
    if(arguments == NULL){
        swprintf(buffer, BUFSIZE, L"%s", process);
    }
    else{
        swprintf(buffer, BUFSIZE, L"%s %s", process, arguments);
    }
    BOOL result = CreateProcessW(NULL, buffer, NULL, NULL, FALSE, 0, NULL, NULL, &sif, &lpi);
    if(!result){
        wprintf(L"Failed Creating Process %s, Error Code %d\n", process, GetLastError());
    }
}


static VOID createProcessWithAdminPerms(WCHAR* process, WCHAR* arguments){
    ShellExecuteW(NULL, L"runas", process, arguments, NULL, SW_SHOW);
}

VOID startProcess(data* data){
    WCHAR* token;
    if(!data->arg){
        wprintf(L"usage: start [type] [processName] [processArgumemnts]\n\ntype can be admin or user\n");
        return;
    }
    WCHAR* type = wcstok(data->arg, L" ", &token);
    WCHAR* cmd = wcstok(NULL, L" ", &token);
    if(!cmd){
        wprintf(L"usage: start [type] [processName] [processArgumemnts]\n\ntype can be admin or user\n");
        return;
    }
    WCHAR* arg = wcstok(NULL, L"\n", &token);
    if(wcscmp(type, L"admin") == 0){
        createProcessWithAdminPerms(cmd, arg);
    }
    else{
        createProcess(cmd, arg);
    }
}

VOID quickStartProcess(data* data){
    WCHAR* token;
    WCHAR* cmd = wcstok(data->cmd, L",,", &token);
    if(!cmd){
        return;
    }
    createProcess(cmd, data->arg);

}
