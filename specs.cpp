#include<node_api.h>
#include"systeminfo.h"

napi_value getPCName(napi_env env, napi_callback_info info){
    napi_value Name;
    napi_create_string_utf8(env,PCName(),StringSize(PCName()),&Name);
    return Name;
}

napi_value getProcessorArchitecture(napi_env env, napi_callback_info info){
    napi_value Architecture;
    char* arq = (char*) ProcessorArchitecture();
    napi_create_string_utf8(env,arq,StringSize(arq),&Architecture);
    return Architecture;
}

napi_value getProcessorsNumber(napi_env env, napi_callback_info info){
    GetSystemInfo(&sysinfo);
    napi_value ProcessorsNumber;
    napi_create_int32(env,sysinfo.dwNumberOfProcessors,&ProcessorsNumber);
    return ProcessorsNumber;
}

napi_value getTotalMemory(napi_env env, napi_callback_info info){
    double totalmemory = GetTotalMemory();
    napi_value memory;
    napi_create_object(env,&memory);
    napi_value xBytes, xKiloBytes, xMegaBytes, xGigaBytes;
    napi_create_int64(env,totalmemory,&xBytes);
    napi_create_double(env,totalmemory / (1024),&xKiloBytes);
    napi_create_double(env,totalmemory / (1024 * 1024),&xMegaBytes);
    napi_create_double(env,totalmemory / (1024 * 1024 * 1024),&xGigaBytes);

    napi_set_named_property(env,memory,"Bytes",xBytes);
    napi_set_named_property(env,memory,"KiloBytes",xKiloBytes);
    napi_set_named_property(env,memory,"MegaBytes",xMegaBytes);
    napi_set_named_property(env,memory,"GigaBytes",xGigaBytes);

    return memory;
}

napi_value getTotalMemoryGB(napi_env env, napi_callback_info info){
    double totalmemoryGB = GetTotalMemory() / (1024 * 1024 * 1024);
    napi_value memory;
    napi_create_int32(env,totalmemoryGB,&memory);
    return memory;
}

napi_value init(napi_env env, napi_value exports){
    napi_value funcProcessorNumber,funcPCName,funcArchitecture,funcTotalMemory,funcTotalMemoryGB;

    napi_create_function(env,nullptr,0,getProcessorsNumber,nullptr,&funcProcessorNumber);
    napi_create_function(env,nullptr,0,getPCName,nullptr,&funcPCName);
    napi_create_function(env,nullptr,0,getProcessorArchitecture,nullptr,&funcArchitecture);
    napi_create_function(env,nullptr,0,getTotalMemory,nullptr,&funcTotalMemory);
    napi_create_function(env,nullptr,0,getTotalMemoryGB,nullptr,&funcTotalMemoryGB);
    napi_set_named_property(env,exports,"getProcessorsNumber",funcProcessorNumber);
    napi_set_named_property(env,exports,"getPCName",funcPCName);
    napi_set_named_property(env,exports,"getProcessorArchitecture",funcArchitecture);
    napi_set_named_property(env,exports,"getTotalMemory",funcTotalMemory);
    napi_set_named_property(env,exports,"getTotalMemoryGB",funcTotalMemoryGB);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);