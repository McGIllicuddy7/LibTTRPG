//
//  Spellcasting.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Spellcasting_h
#define Spellcasting_h
#pragma once
#include <stdio.h>
typedef struct{
  unsigned char Cantrips;
  unsigned char level1;
  unsigned char level2;
  unsigned char level3;
  unsigned char level4;
  unsigned char level5;
  unsigned char level6;
  unsigned char level7;
  unsigned char level8;
  unsigned char level9;
  unsigned char level10;
} SpellSlots;
SpellSlots innate_spellslots_by_level(int level);
SpellSlots prepared_spellslots_by_level(int level);
SpellSlots prepared_spellbook_by_level(int level);
int get_element(SpellSlots t, int index);
#endif /* Spellcasting_h */
