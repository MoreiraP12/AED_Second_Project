//
// Created by danie on 30/01/2022.
//

#ifndef AED_PROJ_2_SHOWSTOP_H
#define AED_PROJ_2_SHOWSTOP_H

#include "Stop.h"
#include <set>

struct ShowStop{
    Stop stop;
    std::set<std::string> lines;
};

#endif //AED_PROJ_2_SHOWSTOP_H
