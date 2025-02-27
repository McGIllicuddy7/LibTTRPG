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
#include <stdint.h>
struct SpellSlots{
  uint8_t Cantrips;
  uint8_t level1;
  uint8_t level2;
  uint8_t level3;
  uint8_t level4;
  uint8_t level5;
  uint8_t level6;
  uint8_t level7;
  uint8_t level8;
  uint8_t level9;
  uint8_t level10;
};
SpellSlots innate_spellslots_by_level(int level);
SpellSlots prepared_spellslots_by_level(int level);
SpellSlots prepared_spellbook_by_level(int level);
int get_element(SpellSlots t, int index);
#endif /* Spellcasting_h */
