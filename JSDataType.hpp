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