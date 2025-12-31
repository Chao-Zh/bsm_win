#pragma once

// 平台兼容性头文件
// 解决Windows和Linux之间的兼容性问题

#ifdef _WIN32
    // Windows平台定义
    #include <windows.h>
    
    // Windows版本的localtime_r替代
    #define localtime_r(tp, tm) localtime_s(tm, tp)
    
    // Windows版本的int64类型
    typedef long long __int64_t;
    
    // Windows清屏命令
    #define CLEAR_SCREEN "cls"
#else
    // Linux/Unix平台
    #include <unistd.h>
    
    // Linux清屏命令
    #define CLEAR_SCREEN "clear"
#endif

// 通用时间函数包装
inline struct tm* safe_localtime_r(const time_t* timer, struct tm* result) {
    #ifdef _WIN32
        return localtime_s(result, timer) == 0 ? result : nullptr;
    #else
        return localtime_r(timer, result);
    #endif
}