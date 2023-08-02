#include"systeminfo.h"
#include<vector>
#include<iostream>
#include<bitset>

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