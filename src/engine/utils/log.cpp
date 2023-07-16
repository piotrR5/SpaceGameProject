#include "log.hpp"

std::string dateAndTime(){
    time_t now = time(0);
    auto gmtm = gmtime(&now);

    std::string ret(std::asctime(gmtm));

    ret=std::string(ret.begin(), ret.end()-1);
    ret.erase(ret.begin()+19, ret.end());
    ret.erase(ret.begin(), ret.begin()+11);

    return "["+ret+"]: ";
}

void log(const char* m){
    std::string msg(m);
    msg=dateAndTime()+msg;
    msg+='\n';
    std::cout<<msg;
}

void _logErr(const char* m){
    std::string msg(m);
    msg=def+msg;
    msg="Error: "+msg;
    msg=red+msg;
    msg+='\n';
    std::cout<<msg;
}

void logOK(const char* m){
    std::string msg(m);
    msg=def+msg;
    msg="OK: "+msg;
    msg=green+msg;
    msg=dateAndTime()+msg;
    msg+='\n';
    std::cout<<msg;
}

void _panic(const char* m){
    std::string msg(m);
    msg=def+msg;
    msg="Panic: "+msg;
    msg=red+msg;
    msg+='\n';
    std::cout<<msg;
    exit(0);
}