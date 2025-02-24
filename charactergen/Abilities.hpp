//
//  Abiliites.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/9/23.
//

#ifndef Abiliites_h
#define Abiliites_h
#include <string_view>
#include <vector>
#include <stdio.h>
using namespace std;
typedef enum{
    MagicNONE,Arcane, Divine, Primal,Occult,
  } MagicTypes;
  typedef enum{
    MartialNONE,OrganizedRanged,OrganizedMelle, DisorganizedRanged,DisorganizedMelle,
  } MartialTypes;
vector<string_view> get_laborer_abilities(int Level);
vector<string_view> get_merchant_abilities(int Level);
vector<string_view> get_fighter_abilities(int Level,MartialTypes MartialType);
vector<string_view> get_gish_abilities(int Level, MagicTypes MagicType, MartialTypes MartialType);
vector<string_view> get_thief_abilities(int Level,MartialTypes MartialType);
vector<string_view> get_noble_abilities(int Level);
vector<string_view> get_magic_user_abilities(int Level, MagicTypes MagicType);
vector<string_view> get_magic_using_thief_abilities(int Level,MartialTypes MartialType, MagicTypes MagicType);
vector<string_view> get_priest_abilities(int Level);
# endif /* Abiliites_h */
