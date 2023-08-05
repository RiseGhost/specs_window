#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#include <string>

using namespace std;

struct ProcessMemory{
    int Commit;
    int WorkingSet;
};

struct ProcessArray{
    DWORD Process[2048];    //Array em que cada posição representa um processo
    int size = 2048;
    int Number;             //Number of identifiers processes
};

ProcessMemory CreatePM(int Commit, int WorkingSet){
    ProcessMemory PM;
    PM.Commit = Commit;
    PM.WorkingSet = WorkingSet;
    return PM;
}

ProcessMemory MemoryInfo(HANDLE hProcess){
    PROCESS_MEMORY_COUNTERS pmc;

    if (NULL == hProcess)
        return CreatePM(-1,-1);
    
    if ( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
        return CreatePM(pmc.PagefileUsage / 1024,pmc.WorkingSetSize / 1024);

    CloseHandle( hProcess );
    return CreatePM(-1,-1);
}

string ProcessName(HANDLE hProcess){
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    if (NULL != hProcess){
        HMODULE hMod;
        DWORD cbNeeded;
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),&cbNeeded))
            GetModuleBaseName(hProcess, hMod, szProcessName,sizeof(szProcessName) / sizeof(TCHAR));
    }

    return string(szProcessName);
}

ProcessArray GetAllProcesses(){
    DWORD cbNeeded;
    ProcessArray PA;
    PA.size = 0;

    if (!EnumProcesses(PA.Process, sizeof(PA.Process), &cbNeeded))  return PA;
    // Calculate how many process identifiers were returned.
    PA.Number = cbNeeded / sizeof(DWORD);
    return PA;
}

bool Kill_Processe(HANDLE hProcesse, int Code){
    if(TerminateProcess(hProcesse, Code))   return true;
    return false;
}