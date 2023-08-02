#include<Windows.h>
#include<stdlib.h>
#include<stdio.h>

typedef const char* String;

SYSTEM_INFO sysinfo;

//Return the last valid index of buffer array
int ValitedCaracteres(String buffer){
    if (buffer[0] >= 0x20 && buffer[0] <= 0x7a) return 1 + ValitedCaracteres(&buffer[1]);
    else return 0;
}

int StringSize(String str){
    return (str[0] == '\0') ? 0 : 1 + StringSize(&str[1]);
}

String PCName(){
    char buffer[500];
    DWORD buffer_size = sizeof(buffer);
    return(GetComputerNameExA(ComputerNamePhysicalDnsFullyQualified,buffer,&buffer_size)) ? buffer : "Error to get Processor Name";
}

String ProcessorArchitecture(){
    switch (sysinfo.wProcessorArchitecture){
    case PROCESSOR_ARCHITECTURE_AMD64:
        return "64";
        break;
    case PROCESSOR_ARCHITECTURE_INTEL:
        return "32";
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        return "ARM";
        break;
    default:
        return "unknown";
        break;
    }
}

//Return the Total RAM Memory Install
DWORDLONG GetTotalMemory() {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (GlobalMemoryStatusEx(&memoryStatus))
        return memoryStatus.ullTotalPhys;

    return 0;
}