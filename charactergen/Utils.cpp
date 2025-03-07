//
//  Utils.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include "Utils.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
static unsigned long Seed = 0;
unsigned long random_int(void){
  if(Seed == 0){
    struct timespec res;
    long nano1;
    clock_gettime(CLOCK_REALTIME,&res);
    nano1 = res.tv_nsec;
    Seed = nano1;
  }
  Seed ^= Seed >> 7;
  Seed ^= Seed << 9;
  Seed ^= Seed >> 13;
  return Seed;
}
int random_int_in_range(int min, int max){
  return random_int()%(max-min)+min;
}
double random_double(void){
  return ((double)random_int())/((double)0xFFFFFFFFFFFFFFFF);
}
double random_double_in_range(double min, double max){
  return random_double()*(max+min)+min;
}
int roll_dice(const char * die){
  int cur = 0;
  int len = (int)strlen(die);
  char nd[10] = {0};
  char  ds[10] = {0};
  for(int i = 0; i<len; i++){
    if(die[i]== 'd'){
      cur = i;
      break;
    }
  }
  memcpy(nd, die, cur);
  memcpy(ds, die+cur+1, len-cur);
  int numdice = atoi(nd);
  int diesize = atoi(ds);
  int total = 0;
  for(int i = 0; i<numdice; i++){
    total += random_int()%diesize+1;
  }
  return total;
}
