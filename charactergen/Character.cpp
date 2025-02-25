//
//  Character.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//


#include "Names.hpp"
#include "Utils.hpp"
#include "Abilities.hpp"
#include "spells.hpp"
#include "Spellcasting.hpp"
#include <string.h>
#include "types.hpp"
#include <string_view>

int very_high_ability_score(void){
  int val = roll_dice("1d4")+14;
  if(val>20){
    val = 20;
  }
  return val;
}
int high_ability_score(void){
  int val = roll_dice("2d4")+10;
  return val;
}
int medium_ability_score(void){
  return roll_dice("2d4")+6;
}
int low_ability_score(void){
  return roll_dice("4d4")+2;
}
int calculate_modifier(int StatValue){
  return (StatValue-10)/2;
};
int calculate_ac_and_per_bonus(int level){
  int numexpert = level/5*(level>4);
  int nummastered = level/10 * (level>9);
  int numLegendary = level/15 *(level>14);
  return 2*((numexpert>0)+(nummastered>0)+(numLegendary>0)+1)+level;
}

const Weapon Club = {"Club","Thrown 10 ft.",false,false,0,"1d4",0};
const Weapon Dagger = {"Dagger","Agile, finesse, thrown 10 ft., versatile S.",true,false,0,"1d4",0};
const Weapon LongSpear = {"Long Spear","Reach",false,false,0,"1d6",0};
const Weapon Staff = {"Staff","Two-hand d8",false,false,0,"1d4",0};
const Weapon BastardSword = {"Bastard sword","Two-hand d12",false,false,0,"1d8",0};
const Weapon BattleAxe = {"Battle axe","Sweep",false,false,0,"1d8",0};
const Weapon Greatsword = {"Greatsword","Versatile P",false,false,0,"1d12",0};
const Weapon Longsword = {"Longsword", "Versatile P",false,false,0,"1d8",0};
const Weapon Rapier = {"Rapier","Deadly d8, disarm, finesse",true,false, 0,"1d6",0};
const Weapon Shortsword = {"Shortsword","Agile, finesse, versatile S",true,false,0,"1d6",0};
const Weapon Crossbow = {"Crossbow","Range 120",false,true,0,"1d8",0};
const Weapon HeavyCrossbow = {"Heavy Crossbow","Range 120",false,true,0,"1d10",0};
const Weapon Longbow = {"Longbow","Range 100",false,true,0,"1d8",0};
const Weapon Shortbow = {"Shortbow","Range 60",false,true,0,"1d6",0};
vector<Weapon> weapon_calculation(MartialTypes mt, ENPC_Type npc_type, int level, int strength,int dexterity){
  vector<Weapon> out;
  if(mt == MartialNONE){
    if(npc_type == Thief || npc_type == Magic_using_Thief){
      if(random_int()%3 == 0){
        out.push_back(Rapier);
      }
      else{
        out.push_back(Shortsword);
      }
      if(random_int()%3 == 0){
        out.push_back(Longbow);
      }
      else{
        out.push_back(Shortbow);
      }
      out.push_back( Dagger);
    }
    else{
      if(random_int()%2 == 0){
        out.push_back(Dagger);
      }
      else{
        out.push_back(Staff);
      }
    }
  }
  else if(mt == OrganizedMelle){
    int r = random_int()%5;
    if(r == 0){
      out.push_back(LongSpear);
    }
    if(r == 1){
      out.push_back(Greatsword);
    }
    if(r == 2){
      out.push_back(Rapier);
    }
    if(r>2){
      out.push_back(Longsword);
    }
    if(random_int()%3 == 0){
      out.push_back(Longbow);
    }
    else{
      out.push_back(Crossbow);
    }
    out.push_back(Dagger);
  }
  else if(mt == OrganizedRanged){
    if(random_int()%3 == 0){
      out.push_back(HeavyCrossbow);
    }
    else{
      out.push_back(Longbow);
    }
    if(random_int()%3 == 0){
      out.push_back(Rapier);
    }
    else{
      out.push_back(Dagger);
    }
  }
  else if(mt ==DisorganizedRanged){
    if(random_int()%3 == 0){
      out.push_back(Longbow);
    }
    else{
      out.push_back(Crossbow);
    }
    out.push_back(Dagger);
  }
  else if(mt == DisorganizedMelle){
    if(random_int()%3 == 0){
      out.push_back(Shortsword);
    }
    else{
      if(dexterity>strength){
        out.push_back(Dagger);
      }
      else{
        out.push_back(Club);
      }
    }
  }
  for(int i = 0; i<out.size(); i++){
      bool fin = out[i].Finnese;
      bool ran = out[i].Ranged;
      out[i].Bonus = calculate_ac_and_per_bonus(level)+calculate_modifier(strength)*(!fin && !ran)+calculate_modifier(dexterity)*(fin ||ran);
      out[i].DamageBonus = calculate_modifier(strength)*(!ran);
  }
  return out;
}


int calculate_skill_mod(int index, StatSet stats,AbilityScores Score, vector<int> TrainedSkills, vector<int> ExpertSkills, vector<int> MasteredSkills,vector<int> LegendarySkills){
  int base = 0;
  if(Score == Strength){
    base += calculate_modifier(stats.strength);
  }
  if(Score == Constitution){
    base += calculate_modifier(stats.constitution);
  }
  if(Score == Dexterity){
    base += calculate_modifier(stats.dexterity);
  }
  if(Score == Intelligence){
    base += calculate_modifier(stats.intelligence);
  }
  if(Score == Wisdom){
    base += calculate_modifier(stats.wisdom);
  }
  if(Score == Charisma){
    base += calculate_modifier(stats.charisma);
  }
  if(array_contains(LegendarySkills,index)){
    base += 8+stats.level;
  }
  else if(array_contains(MasteredSkills,index)){
    base += 6+stats.level;
  }
  else if(array_contains(ExpertSkills,index)){
    base += 4+stats.level;
  }
  else if(array_contains(TrainedSkills,index)){
    base += 2+stats.level;
  }
  return base;
}
#define SetUpSkills(NPC, T, t,Ability) NPC.t = calculate_skill_mod(T,NPC, Ability, TrainedSkills,ExpertSkills, MasteredSkills, LegendarySkills)

StatSet calculate_skills(StatSet stats, vector<int> TrainedSkills, vector<int> ExpertSkills,vector<int> MasteredSkills,vector<int> LegendarySkills){
  SetUpSkills(stats, Arcana, arcana,Intelligence);
  SetUpSkills(stats, Athletics,athletics, Strength);
  SetUpSkills(stats, Acrobatics, acrobatics,Dexterity);
  SetUpSkills(stats, Crafting, crafting,Intelligence);
  SetUpSkills(stats, Deception,deception, Charisma);
  SetUpSkills(stats,Diplomacy, diplomacy,Charisma);
  SetUpSkills(stats,Intimidation,intimidation, Charisma);
  SetUpSkills(stats, Lore,lore, Intelligence);
  SetUpSkills(stats, Medicine,medicine, Wisdom);
  SetUpSkills(stats, Nature,nature,Wisdom);
  SetUpSkills(stats, Occultism, occultism,Intelligence);
  SetUpSkills(stats, Performance,performance, Charisma);
  SetUpSkills(stats, Religion, religion,Wisdom);
  SetUpSkills(stats,Society,society,Charisma);
  SetUpSkills(stats, Stealth, stealth,Dexterity);
  SetUpSkills(stats, Thievery,thievery, Dexterity);
  stats.perception= 0+calculate_modifier(stats.wisdom);
  if(LegendarySkills.size()>0){
    stats.perception +=8;
  } else if (MasteredSkills.size()>0){
    stats.perception +=6;
  }
  else if (ExpertSkills.size()>0){
    stats.perception +=4;
  }
  else if (TrainedSkills.size()>0){
    stats.perception +=2;
  }
  return stats;
}
StatSet select_skills(StatSet stats,vector<int> Skills, int numskills,int numexpert,int nummastered, int numlegendary){
  vector<int> TrainedSkills = array_choose(Skills, numskills);
  vector<int> ExpertSkills = array_choose(TrainedSkills, numexpert);
  vector<int> MasteredSkills = array_choose(ExpertSkills,nummastered);
  vector<int> LegendarySkills = array_choose(MasteredSkills, numlegendary);
  stats = calculate_skills(stats, TrainedSkills, ExpertSkills, MasteredSkills,LegendarySkills);
  return stats;
}
#define CasterAbilityScores(Highest)\
if(MagicType == Arcane){Out->Intelligence = Highest; Out->Wisdom = medium_ability_score(); Out->Charisma = medium_ability_score();}\
if(MagicType == Divine || MagicType == Primal){Out->Intelligence =medium_ability_score(); Out->Wisdom = Highest;Out->Charisma = medium_ability_score();}\
if(MagicType == Occult){Out->Intelligence =medium_ability_score();  Out->Wisdom = medium_ability_score(); Out->Charisma = Highest;}

const vector<int> SkillsList = { Acrobatics,Arcana,Athletics,Crafting,Deception,Diplomacy,Intimidation,Lore,Medicine,Nature,Occultism,Performance,Religion,
  Society,Stealth,Survival,Thievery};
const vector<int> DefaultSkillsList = SkillsList;

/*
    Laborer, Merchant, Noble, Fighter, Magic_User, Gish, Magic_using_Thief, Priest, Thief
*/

StatSet generate_laborer_stats(){
  
}