#pragma once
#include "types.hpp"

  /*typedef struct{
 char * Name;
 char * Text;
 bool Finesse;
 bool Ranged,
 int Bonus;
 char * DamageDie;
 int DamageBonus;
} Weapon_T;
*/
#include <string>
#include <vector>
using std::string;
using std::vector;
string rand_first_name(vector<string> BaseArray, EGender Gender);
string rand_last_name(vector<string> BaseArray);
EGender generate_gender(void);
string generate_name(EAncestries Ancestry, EGender Gender);
vector<string> generate_personality(void);
size_t generate_age(EAncestries ancestry, size_t level);