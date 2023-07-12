#include "log.hpp"

std::string dateAndTime(){
    time_t now = time(0);
    auto gmtm = gmtime(&now);

    std::string ret(std::asctime(gmtm));

    ret=std::string(ret.begin(), ret.end()-1);
    ret.erase(ret.begin()+19, ret.end());
    ret.erase(ret.begin(), ret.begin()+11);

    return ret;
}

void log(const char* m){
    std::string msg(m);
    std::cout<<"["<<dateAndTime()<<"]: "<<msg<<"\n";
}

void logErr(const char* m){
    std::string msg(m);
    std::cout<<"["<<dateAndTime()<<"]: "<<red<<"Error: "<<def<<msg<<"\n";
}

void logOK(const char* m){
    std::string msg(m);
    std::cout<<"["<<dateAndTime()<<"]: "<<green<<"[OK] "<<def<<msg<<"\n";
}