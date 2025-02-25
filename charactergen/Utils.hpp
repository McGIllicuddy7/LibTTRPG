//
//  Utils.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Utils_h
#define Utils_h
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <string>
using namespace std;
typedef unsigned char byte_t;
unsigned long random_int(void);
int random_int_in_range(int min, int max);
double random_double(void);
int roll_dice(const char * die);
template <typename T> T random_element(const std::vector<T>& value){
    return value[random_int()%value.size()];
}
template<typename T> vector<T> array_choose(vector<T> v, int num){
    vector<T> v1 = v;
    vector<T> out;
    for(int i =0 ; i<num; i++){
      int r = random_int()%v1.size();
      out.push_back(v[v1[r]]);
      v1.erase(v1.begin()+r);
    }
    return out;
}
template<typename T> bool array_contains(vector<T> v, T num){
    for(int i = 0; i<v.size(); i++){
        if(v[i] == num){
          return true;
        }
      }
      return false;
}
template<typename T> vector<T> array_select(vector<T> v, int num){
    vector<T> out;
    for(int i =0 ; i<num; i++){
      int r = random_int()%v.size();
      out.push_back(v[r]);
    }
    return out;
}

#endif /* Utils_h */

