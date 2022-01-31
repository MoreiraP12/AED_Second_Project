#ifndef AED_PROJ_2_SHOWSTOP_H
#define AED_PROJ_2_SHOWSTOP_H
#include "stop.h"
#include <set>

struct ShowStop{
    Stop stop;
    std::set<std::string> lines;
};

#endif
