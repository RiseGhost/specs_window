#include"systeminfo.h"
#include<vector>
#include<iostream>
#include<bitset>
#include<node_api.h>

using namespace std;

//Este ficheiro dedica-se a implementação de código para a obtenção de dados
//sobre as unidades de armazenamento

//Retorna um vetor com todas as unidades de armazenamento que estão disponiveis:
vector<string> GetAvailableDrives(){
    vector<string> drives;
    DWORD drivesMash = GetLogicalDrives();
    for (char Unit = 'A'; Unit <= 'Z'; Unit++){
        if(drivesMash & 1){
            string drivePath = string(1,Unit) + ":\\";
            drives.push_back(drivePath);
        }
        drivesMash >>= 1;
    }
    return drives;
}

//Return MegaBytes Free in DrivePath:
double GetFreeSpaceDrive(string drivePath){
    wstring Path = wstring(drivePath.begin(),drivePath.end());
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
    if(GetDiskFreeSpaceExW(Path.c_str(),&freeBytesAvailable,&totalNumberOfBytes,&totalNumberOfFreeBytes))
        return freeBytesAvailable.QuadPart / (1024 * 1024);
    else
        return -1;
}

//Return MegaBytes Total Space of DrivePath:
double GetSpaceDrive(string DiskPath){
    wstring temp = wstring(DiskPath.begin(),DiskPath.end());
    LPCWSTR rootPath = temp.c_str();
    DWORD sectorsPerCluster, bytesPerSector, freeClusters, totalClusters;
    if (GetDiskFreeSpaceW(rootPath, &sectorsPerCluster, &bytesPerSector, &freeClusters, &totalClusters)) {
        ULONGLONG totalSize = static_cast<ULONGLONG>(totalClusters) * sectorsPerCluster * bytesPerSector;
        return static_cast<double>(totalSize) / (1024 * 1024);
    } else 
        return - 1;
}

//Return Free Space in Drive:
napi_value FreeSizeDrives(napi_env env, napi_value Drive){
    napi_value SizeFree;
    char Path[4];
    size_t strSize;
    napi_get_value_string_utf8(env,Drive,Path,4,&strSize);
    napi_create_double(env,GetFreeSpaceDrive(string(Path)),&SizeFree);
    return SizeFree;
}

//Return Total Space in Drive:
napi_value SizeDrives(napi_env env, napi_value Drive){
    napi_value SizeFree;
    char Path[4];
    size_t strSize;
    napi_get_value_string_utf8(env,Drive,Path,4,&strSize);
    napi_create_double(env,GetSpaceDrive(string(Path)),&SizeFree);
    return SizeFree;
}