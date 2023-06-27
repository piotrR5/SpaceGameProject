#include "log.hpp"

std::string dateAndTime(){
   time_t now = time(0);
   char* dt = ctime(&now);
   auto gmtm = gmtime(&now);
   return std::asctime(gmtm);
}


void log(const char* msg){
    printf("[%s]: %s ", dateAndTime().c_str(), msg);
}