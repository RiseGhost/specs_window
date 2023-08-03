#include"JSDataType.hpp"
#include"DriveSize.hpp"

napi_value MoveMouse(napi_env env, napi_callback_info info){
    size_t argc = 2;
    napi_value argv[2];
    int x,y;
    napi_get_cb_info(env,info,&argc,argv,NULL,NULL);
    if (!(CheckDataTypeJS(env,argv[1],napi_number) && CheckDataTypeJS(env,argv[1],napi_number)))    napi_throw_error(env,NULL,"The argument is not a number ❌");
    napi_get_value_int32(env,argv[0],&x);
    napi_get_value_int32(env,argv[1],&y);
    SetCursorPos(x,y);
    return NULL;
}

napi_value getScreenSize(napi_env env, napi_callback_info info){
    ScreenSize ss = Screen_Size();
    napi_value width, height;
    napi_create_int32(env,ss.width,&width);
    napi_create_int32(env,ss.height,&height);
    return ObjectScreenSize(env,width,height);
}

napi_value getMousePos(napi_env env, napi_callback_info info){
    POINT point = MousePos();
    napi_value x, y;
    napi_create_int32(env,point.x,&x);
    napi_create_int32(env,point.y,&y);
    return ObjectPointer(env,x,y);
}

napi_value getAvailableDrives(napi_env env, napi_callback_info info){
    vector<string> AvailableDrives = GetAvailableDrives();
    napi_value Units;
    napi_create_array_with_length(env,AvailableDrives.size(),&Units);
    for(int index = 0; index < AvailableDrives.size(); index++){
        napi_value unit;
        napi_create_string_utf8(env,AvailableDrives[index].c_str(),AvailableDrives[index].size(),&unit);
        napi_set_element(env,Units,index,unit);
    }
    return Units;
}

//Retorna o Espaço Livre e Total em cada DrivePath em MegaBytes:
//Input1:   'C:\\'
//Ouput1:    {'FreeMemory': 19865, 'FullMemory': 425668.99609375} (por exemplo)
//Input2:   ['C:\\','G:\\']
//Output2:  [{ 'FreeMemory': 19865, 'FullMemory': 425668.99609375 },{ 'FreeMemory': 49860, 'FullMemory': 985768.70009375 },] (por exemplo)
//Em caso de não conseguir obter os dados dos DrivePath a memória é identificada como -1
napi_value getSizeDrives(napi_env env, napi_callback_info DrivePath){
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env,DrivePath,&argc,argv,NULL,NULL);
    
    //Caso o usuário passe apenas um DrivePath:
    if(CheckDataTypeJS(env,argv[0], napi_string))
        return ObejctDiskSpace(env,FreeSizeDrives(env, argv[0]),SizeDrives(env, argv[0]));
    //Caso o usuário passe um array de DrivePaths:
    else if(IS_JS_ARRAY(env,argv[0])){
        if(IS_JS_STRING_ARRAY(env,argv[0])){
            int length = JSArrayLength(env,argv[0]);
            napi_value FreeSpaceArray;
            napi_create_array_with_length(env,length,&FreeSpaceArray);
            for(int index = 0; index < length; index++){
                napi_value element;
                napi_get_element(env,argv[0],index,&element);
                napi_set_element(env,FreeSpaceArray,index,ObejctDiskSpace(env,FreeSizeDrives(env,element),SizeDrives(env,element)));
            }
            return FreeSpaceArray;
        }
        else napi_throw_error(env,NULL,"Invalid arg");
    }
    napi_throw_error(env,NULL,"Invalid arg");
    return NULL;
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
    napi_value funcAvailableDrives,funcSizeDrives,funcMousePos,funcScreenSize,funcMoveMouse;

    napi_create_function(env,nullptr,0,getProcessorsNumber,nullptr,&funcProcessorNumber);
    napi_create_function(env,nullptr,0,getPCName,nullptr,&funcPCName);
    napi_create_function(env,nullptr,0,getProcessorArchitecture,nullptr,&funcArchitecture);
    napi_create_function(env,nullptr,0,getTotalMemory,nullptr,&funcTotalMemory);
    napi_create_function(env,nullptr,0,getTotalMemoryGB,nullptr,&funcTotalMemoryGB);
    napi_create_function(env,nullptr,0,getFreeMemory,nullptr,&funcFreeMemory);
    napi_create_function(env,nullptr,0,getFreeMemoryGB,nullptr,&funcFreeMemoryGB);
    napi_create_function(env,nullptr,0,getAvailableDrives,nullptr,&funcAvailableDrives);
    napi_create_function(env,nullptr,0,getSizeDrives,nullptr,&funcSizeDrives);
    napi_create_function(env,nullptr,0,getMousePos,nullptr,&funcMousePos);
    napi_create_function(env,nullptr,0,getScreenSize,nullptr,&funcScreenSize);
    napi_create_function(env,nullptr,0,MoveMouse,nullptr,&funcMoveMouse);
    napi_set_named_property(env,exports,"getProcessorsNumber",funcProcessorNumber);
    napi_set_named_property(env,exports,"getPCName",funcPCName);
    napi_set_named_property(env,exports,"getProcessorArchitecture",funcArchitecture);
    napi_set_named_property(env,exports,"getTotalMemory",funcTotalMemory);
    napi_set_named_property(env,exports,"getTotalMemoryGB",funcTotalMemoryGB);
    napi_set_named_property(env,exports,"getFreeMemory",funcFreeMemory);
    napi_set_named_property(env,exports,"getFreeMemoryGB",funcFreeMemoryGB);
    napi_set_named_property(env,exports,"getAvailableDrives",funcAvailableDrives);
    napi_set_named_property(env,exports,"getSizeDrives",funcSizeDrives);
    napi_set_named_property(env,exports,"getMousePos",funcMousePos);
    napi_set_named_property(env,exports,"getScreenSize",funcScreenSize);
    napi_set_named_property(env,exports,"MoveMouse",funcMoveMouse);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);