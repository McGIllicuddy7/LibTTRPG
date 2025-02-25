//
//  Ancestries.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include "Ancestries.hpp"
#include "Utils.hpp"
EAncestries random_ancestry(void){
  int DwarfMin = DwarfPopulationPercent;
  int ElfMin = DwarfMin+ElfPopulationPercent;
  int GnomeMin = ElfMin+GnomePopulationPercent;
  int GoblinMin = GnomeMin+GoblinPopulationPercent;
  int HalflingMin = GoblinMin+HalflingPopulationPercent;
  int HumanMin = HalflingMin+HumanPopulationPercent;
  int CatfolkMin =HumanMin+CatfolkPopulationPercent;
  int OrcMin = CatfolkMin+OrcPopulationPercent;
  int s = random_int()%100;
  if(s<DwarfMin){
    return Dwarf;
  }
  if(s<ElfMin){
    return Elf;
  }
  if(s<GnomeMin){
    return Gnome;
  }
  if(s<GoblinMin){
    return Goblin;
  }
  if(s<HalflingMin){
    return Halfling;
  }
  if(s<HumanMin){
    return Human;
  }
  if(s<CatfolkMin){
    return Catfolk;
  }
  if(s<OrcMin){
    return Orc;
  }
  return Human;
};
void randomize_ancestries(void){
  
};
