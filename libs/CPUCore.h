#include <windows.h>


typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);


int CPUCores(){
    LPFN_GLPI glpi;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
    DWORD returnLength = 0;
    DWORD processorCoreCount = 0;
    DWORD byteOffset = 0;
    PCACHE_DESCRIPTOR Cache;

    glpi = (LPFN_GLPI) GetProcAddress(GetModuleHandle(TEXT("kernel32")),"GetLogicalProcessorInformation");
    
    if (NULL == glpi) 
        return -1;    //Error
    while (true){
        DWORD rc = glpi(buffer, &returnLength);
        if (FALSE == rc) {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
                if (buffer)     free(buffer);

                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);
            }
            else 
                return -1;   //Error
        } 
        else break;
    }

    ptr = buffer;

    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength) {
        switch (ptr->Relationship) {
        case RelationProcessorCore:
            processorCoreCount++;
            break;
        default:
            break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        ptr++;
    }
    
    free(buffer);
    return processorCoreCount;
}