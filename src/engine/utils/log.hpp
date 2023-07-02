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
void logErr(const char* m);
void logOK(const char* m);


#endif