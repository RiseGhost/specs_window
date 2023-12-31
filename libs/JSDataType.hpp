#include<node_api.h>

//Create JS object with the following struct:
/*
{
    Bytes:          MemoryInBytes,
    KiloBytes:      MemoryInKiloBytes,
    MegaBytes:      MemoryInMegaBytes,
    GigaBytes:      MemoryInGigaBytes
}
*/
napi_value ObjectMemory(napi_env env, napi_callback_info info, double Memory){
    napi_value memory;
    napi_create_object(env,&memory);
    napi_value xBytes, xKiloBytes, xMegaBytes, xGigaBytes;
    napi_create_int64(env,Memory,&xBytes);
    napi_create_double(env,Memory / (1024),&xKiloBytes);
    napi_create_double(env,Memory / (1024 * 1024),&xMegaBytes);
    napi_create_double(env,Memory / (1024 * 1024 * 1024),&xGigaBytes);

    napi_set_named_property(env,memory,"Bytes",xBytes);
    napi_set_named_property(env,memory,"KiloBytes",xKiloBytes);
    napi_set_named_property(env,memory,"MegaBytes",xMegaBytes);
    napi_set_named_property(env,memory,"GigaBytes",xGigaBytes);
    return memory;
}

//Create JS object with the following struct:
/*
{
    PID:                PID,
    Name:               Name the Processe,
    MemoryCommit:       MemoryCommit use by Processe,
    MomoryWorkinSet:    MomoryWorkinSet use by Processe
}
*/
napi_value ObjectProcesse(napi_env env, napi_value PID, napi_value name, napi_value MemoryCommit, napi_value MemoryWorkingSet){
    napi_value Processe;
    napi_create_object(env,&Processe);
    napi_set_named_property(env,Processe,"PID",PID);
    napi_set_named_property(env,Processe,"Name",name);
    napi_set_named_property(env,Processe,"MemoryCommit",MemoryCommit);
    napi_set_named_property(env,Processe,"MemoryWorkingSet",MemoryWorkingSet);
    return Processe;
}

//Create JS object with following struct:
/*
{
    FreeMemory:    Memory Free in MegaBytes,
    FullMemory     Full Memory in MegaBytes,
}
*/
napi_value ObejctDiskSpace(napi_env env, napi_value MemoryFree, napi_value MemoryTotal){
    napi_value Disk;
    napi_create_object(env,&Disk);
    napi_set_named_property(env,Disk,"FreeMemory",MemoryFree);
    napi_set_named_property(env,Disk,"FullMemory",MemoryTotal);
    return Disk;
}

//Create JS object with following struct
/*
{
    X:  Posions X of mouse;
    Y:  Posions Y of mouse
}
*/
napi_value ObjectPointer(napi_env env, napi_value x, napi_value y){
    napi_value Pointer;
    napi_create_object(env,&Pointer);
    napi_set_named_property(env,Pointer,"X",x);
    napi_set_named_property(env,Pointer,"Y",y);
    return Pointer;
}

napi_value ObjectFile(napi_env env, napi_value Name, napi_value Type, napi_value Size){
    napi_value File;
    napi_create_object(env,&File);
    napi_set_named_property(env,File,"Name",Name);
    napi_set_named_property(env,File,"Type",Type);
    napi_set_named_property(env,File,"KB",Size);
    return File;
}

napi_value ObjectScreenSize(napi_env env, napi_value width, napi_value height){
    napi_value ScreenSize;
    napi_create_object(env,&ScreenSize);
    napi_set_named_property(env,ScreenSize,"width",width);
    napi_set_named_property(env,ScreenSize,"height",height);
    return ScreenSize;
}

napi_value CreateStringJS(napi_env env, char* str){
    napi_value msg;
    napi_create_string_utf8(env,str,NAPI_AUTO_LENGTH,&msg);
    return msg;
}

bool CheckDataTypeJS(napi_env env, napi_value value, napi_valuetype type){
    napi_valuetype DataType;
    napi_typeof(env,value,&DataType);
    return (DataType == type) ? true : false;
}

bool IS_JS_ARRAY(napi_env env, napi_value array){
    bool isArray;
    napi_is_array(env,array,&isArray);
    return isArray;
}

int JSArrayLength(napi_env env, napi_value array){
    uint32_t length;
    napi_get_array_length(env,array,&length);
    return length;
}

bool IS_JS_STRING_ARRAY(napi_env env, napi_value array){
    int length = JSArrayLength(env,array);
    for(int index = 0; index < length; index++){
        napi_value element;
        napi_get_element(env,array,index,&element);
        if(!CheckDataTypeJS(env,element,napi_string))   return false;
    }
    return true;
}