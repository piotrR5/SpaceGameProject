#include "log.hpp"

std::string dateAndTime(){
   time_t now = time(0);
   char* dt = ctime(&now);
   auto gmtm = gmtime(&now);
   std::string ret(std::asctime(gmtm));
   ret = std::string(ret.begin(), ret.end()-1);
   return ret;
}


void log(const char* msg){
    printf("[%s]: %s\n", dateAndTime().c_str(), msg);
}