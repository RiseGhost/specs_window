#include"systeminfo.h"
#include<vector>
#include<iostream>
#include<bitset>

using namespace std;

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