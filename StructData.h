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