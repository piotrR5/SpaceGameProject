#ifndef LOG

#define LOG

#include <stdio.h>
#include <ctime>
#include <string>

// struct tm {
//    int tm_sec;
//    int tm_min;   
//    int tm_hour;  
//    int tm_mday;  
//    int tm_mon;   
//    int tm_year;  
//    int tm_wday;  
//    int tm_yday;  
//    int tm_isdst; 

   
// };

std::string dateAndTime();

void log(const char* msg);

#endif