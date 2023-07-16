#ifndef LOG

#define LOG

#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <stdio.h>

std::string dateAndTime();

#define red "\033[31m"
#define green "\033[32m"
#define def "\033[39m"

void log(const char* m);
void _logErr(const char* m);
void logOK(const char* m);
void _panic(const char* m);

#undef logErr
#define logErr printf("%s", dateAndTime().c_str());printf("\033[33min function %s (%d): ",__FUNCTION__, __LINE__);_logErr

#undef panic
#define panic printf("%s", dateAndTime().c_str());printf("\033[33min function %s (%d): ",__FUNCTION__, __LINE__);_panic



#endif