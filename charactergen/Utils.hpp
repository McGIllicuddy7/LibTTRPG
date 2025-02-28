//
//  Utils.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//
#pragma once
#ifndef Utils_h
#define Utils_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "libstrings.hpp"
typedef unsigned char byte_t;
unsigned long random_int(void);
int random_int_in_range(int min, int max);
double random_double(void);
int roll_dice(const char * die);


template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& obj)
{
    for(size_t i =0; i<obj.size(); i++){
        os<< obj[i];
        if (i<obj.size()-1){
            os<<",";
        }
    }
    return os;
}
#endif /* Utils_h */

