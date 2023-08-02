#include"StructData.h"
#include"DriveSize.hpp"

napi_value getAvailableDrives(napi_env env, napi_callback_info info){
    vector<string> AvailableDrives = GetAvailableDrives();
    napi_value Units;
    napi_create_array_with_length(env,AvailableDrives.size(),&Units);
    for(int index = 0; index < AvailableDrives.size(); index++){
        napi_value unit;
        napi_create_string_utf8(env,AvailableDrives[1].c_str(),AvailableDrives[1].size(),&unit);
        napi_set_element(env,Units,index,unit);
    }
    return Units;
}

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
    return ObjectMemory(env,info,GetTotalMemory());
}

napi_value getTotalMemoryGB(napi_env env, napi_callback_info info){
    double totalmemoryGB = GetTotalMemory() / (1024.0 * 1024.0 * 1024.0);
    napi_value memory;
    napi_create_double(env,totalmemoryGB,&memory);
    return memory;
}

napi_value getFreeMemory(napi_env env, napi_callback_info info){
    return ObjectMemory(env,info,GetFreeMemory());
}

napi_value getFreeMemoryGB(napi_env env, napi_callback_info info){
    double totalmemoryGB = GetFreeMemory() / (1024.0 * 1024.0 * 1024.0);
    napi_value memory;
    napi_create_double(env,totalmemoryGB,&memory);
    return memory;
}

napi_value init(napi_env env, napi_value exports){
    napi_value funcProcessorNumber,funcPCName,funcArchitecture,funcTotalMemory,funcTotalMemoryGB,funcFreeMemory,funcFreeMemoryGB;
    napi_value funcAvailableDrives;

    napi_create_function(env,nullptr,0,getProcessorsNumber,nullptr,&funcProcessorNumber);
    napi_create_function(env,nullptr,0,getPCName,nullptr,&funcPCName);
    napi_create_function(env,nullptr,0,getProcessorArchitecture,nullptr,&funcArchitecture);
    napi_create_function(env,nullptr,0,getTotalMemory,nullptr,&funcTotalMemory);
    napi_create_function(env,nullptr,0,getTotalMemoryGB,nullptr,&funcTotalMemoryGB);
    napi_create_function(env,nullptr,0,getFreeMemory,nullptr,&funcFreeMemory);
    napi_create_function(env,nullptr,0,getFreeMemoryGB,nullptr,&funcFreeMemoryGB);
    napi_create_function(env,nullptr,0,getAvailableDrives,nullptr,&funcAvailableDrives);
    napi_set_named_property(env,exports,"getProcessorsNumber",funcProcessorNumber);
    napi_set_named_property(env,exports,"getPCName",funcPCName);
    napi_set_named_property(env,exports,"getProcessorArchitecture",funcArchitecture);
    napi_set_named_property(env,exports,"getTotalMemory",funcTotalMemory);
    napi_set_named_property(env,exports,"getTotalMemoryGB",funcTotalMemoryGB);
    napi_set_named_property(env,exports,"getFreeMemory",funcFreeMemory);
    napi_set_named_property(env,exports,"getFreeMemoryGB",funcFreeMemoryGB);
    napi_set_named_property(env,exports,"getAvailableDrives",funcAvailableDrives);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);