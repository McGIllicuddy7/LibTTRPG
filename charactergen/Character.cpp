//
//  Character.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//



#include "Utils.hpp"
#include "Abilities.hpp"
#include "Ancestries.hpp"
#include "spells.hpp"
#include "Spellcasting.hpp"
#include <string.h>
#include "types.hpp"
#include <string_view>
#include "character.hpp"
#include "personality.hpp"

using std::function;
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
int ability_score(void){
    int a = roll_dice("3d6");
    int b = roll_dice("3d6");
    if(a >b){
      return a;
    }
    return b;
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
    if(npc_type == Thief || npc_type == Magic_Using_Thief){
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
  for(size_t i = 0; i<out.size(); i++){
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
  SetUpSkills(stats,Survival,survival,Wisdom);
  SetUpSkills(stats, Stealth, stealth,Dexterity);
  SetUpSkills(stats, Thievery,thievery, Dexterity);
  stats.perception= 0+calculate_modifier(stats.wisdom)+stats.level;
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


const vector<int> SkillsList = { Acrobatics,Arcana,Athletics,Crafting,Deception,Diplomacy,Intimidation,Lore,Medicine,Nature,Occultism,Performance,Religion,
  Society,Stealth,Survival,Thievery};
const vector<int> DefaultSkillsList = SkillsList;

/*
    Laborer, Merchant, Noble, Fighter, Magic_User, Gish, Magic_using_Thief, Priest, Thief
*/

int num_expert_skills(size_t level){
    if (level>6) level =7;
    return (level<3)? 0 : ((level+1)/2)-1;
}
int num_mastered_skills(size_t level){
  if(level>14) level = 14;
  return (level<7)? 0 : ((level-6)/2)-1;
}
int num_legendary_skills(size_t level){
  return (level<15)? 0 : ((level-14)/2)-1;
}
int high_save_basis(int level){
  if(level<3){
    return 2+level;
  }
  if(level<7){
    return 4+level;
  }
  if(level<15){
    return 6+level;
  }
  return 8+level;
}
int save_basis(int level){
  if(level<3){
    return 0;
  }
  if(level<7){
    return 2+level;
  }
  if(level<15){
    return 4+level;
  }
  return 6+level;
}
StatSet generate_laborer_stats(NPC_Request request){
  StatSet out;
  out.level = request.level;
  out.strength = high_ability_score();
  out.constitution = very_high_ability_score();
  out.dexterity = ability_score();
  out.intelligence = ability_score();
  out.wisdom = ability_score();
  out.charisma = ability_score();
  out.ac = 12+calculate_modifier(out.dexterity)+out.level;
  out.hp = (8+calculate_modifier(out.constitution))*out.level;
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+save_basis(out.level);
  out.fort_save= calculate_modifier(out.constitution)+high_save_basis(out.level);
  out.will_save = calculate_modifier(out.wisdom)+save_basis(out.level);
  out.abilities = get_laborer_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 3+calculate_modifier(out.intelligence), num_expert_skills(out.level), num_mastered_skills(out.level), num_legendary_skills(out.level));
  return out;
}
StatSet generate_merchant_stats(NPC_Request request){
  StatSet out;
  out.level = request.level;
  out.strength = ability_score();
  out.constitution = ability_score();
  out.dexterity = ability_score();
  out.intelligence = high_ability_score();
  out.wisdom = ability_score();
  out.charisma = high_ability_score();
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.ac = 12+calculate_modifier(out.dexterity)+out.level;;
  out.hp = (6+calculate_modifier(out.constitution))*out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+save_basis(out.level);
  out.fort_save= calculate_modifier(out.constitution)+save_basis(out.level);
  out.will_save = calculate_modifier(out.wisdom)+high_save_basis(out.level);
  out.abilities = get_merchant_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 4+calculate_modifier(out.intelligence), num_expert_skills(out.level), num_mastered_skills(out.level), num_legendary_skills(out.level));
  return out;
}
StatSet generate_noble_stats(NPC_Request request){
  StatSet out;
  out.level = request.level;
  out.strength = high_ability_score();
  out.constitution = ability_score();
  out.dexterity = ability_score();
  out.intelligence = ability_score();
  out.wisdom = ability_score();
  out.charisma = high_ability_score();
  out.ac = 12+calculate_modifier(out.dexterity)+out.level;
  out.hp = (8+calculate_modifier(out.constitution))*out.level;
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+save_basis(out.level);
  out.fort_save= calculate_modifier(out.constitution)+save_basis(out.level);
  out.will_save = calculate_modifier(out.wisdom)+high_save_basis(out.level);
  out.abilities = get_noble_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 3+calculate_modifier(out.intelligence), num_expert_skills(out.level), num_mastered_skills(out.level), num_legendary_skills(out.level));
  return out;
}
StatSet generate_fighter_stats(NPC_Request request){
  StatSet out = {};
  out.level = request.level;
  bool ranged = request.martial_type == OrganizedRanged || request.martial_type == DisorganizedRanged;
  out.strength = ranged? ability_score():high_ability_score();
  out.constitution = high_ability_score();
  out.dexterity = ranged? high_ability_score(): ability_score();
  out.intelligence = ability_score();
  out.wisdom = ability_score();
  out.charisma = ability_score();
  out.ac = 12+calculate_modifier(out.dexterity)+out.level;;
  out.hp = (10+calculate_modifier(out.constitution))*out.level;
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+(ranged ? high_save_basis(out.level): save_basis(out.level));
  out.fort_save= calculate_modifier(out.constitution)+(ranged ? save_basis(out.level) : high_save_basis(out.level));
  out.will_save = calculate_modifier(out.wisdom)+save_basis(out.level);
  out.abilities = get_fighter_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 2+calculate_modifier(out.intelligence), num_expert_skills(out.level), num_mastered_skills(out.level), num_legendary_skills(out.level));
  return out;
}
StatSet generate_magic_user_stats(NPC_Request request){
  StatSet out;
  out.level = request.level;
  out.strength = ability_score();
  out.constitution = ability_score();
  out.dexterity = ability_score();
  out.intelligence = high_ability_score();
  out.wisdom = ability_score();
  out.charisma = ability_score();
  out.ac = 12+calculate_modifier(out.dexterity)+out.level;;
  out.hp = (6+calculate_modifier(out.constitution))*out.level;
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+save_basis(out.level);
  out.fort_save= calculate_modifier(out.constitution)+save_basis(out.level);
  out.will_save = calculate_modifier(out.wisdom)+high_save_basis(out.level);
  out.abilities = get_magic_user_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 3+calculate_modifier(out.intelligence), num_expert_skills(out.level), num_mastered_skills(out.level), num_legendary_skills(out.level));
  return out;
}
StatSet generate_gish_stats(NPC_Request request){
  StatSet out;
  out.level = request.level;
  bool ranged = request.martial_type == OrganizedRanged || request.martial_type == DisorganizedRanged;
  out.strength = ranged? ability_score():high_ability_score();
  out.constitution = ability_score();
  out.dexterity = ranged? high_ability_score(): ability_score();
  out.intelligence = high_ability_score();
  out.wisdom = ability_score();
  out.charisma = ability_score();
  out.ac = 10+calculate_modifier(out.dexterity)+out.level;;
  out.hp = (10+calculate_modifier(out.constitution))*out.level;
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+(ranged ? high_save_basis(out.level): save_basis(out.level));
  out.fort_save= calculate_modifier(out.constitution)+(ranged ? save_basis(out.level) : high_save_basis(out.level));
  out.will_save = calculate_modifier(out.wisdom)+save_basis(out.level);
  out.abilities = get_gish_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 2+calculate_modifier(out.intelligence), num_expert_skills(out.level), num_mastered_skills(out.level), num_legendary_skills(out.level));
  return out;
}
StatSet generate_magic_using_thief_stats(NPC_Request request){
  StatSet out;
  out.level = request.level;
  out.strength = ability_score();
  out.constitution = ability_score();
  out.dexterity = high_ability_score();
  out.intelligence = high_ability_score();
  out.wisdom = ability_score();
  out.charisma = ability_score();
  out.ac = 12+calculate_modifier(out.dexterity)+out.level;;
  out.hp = (8+calculate_modifier(out.constitution))*out.level;
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+high_save_basis(out.level);
  out.fort_save= calculate_modifier(out.constitution)+save_basis(out.level);
  out.will_save = calculate_modifier(out.wisdom)+save_basis(out.level);
  out.abilities = get_magic_using_thief_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 4+calculate_modifier(out.intelligence), num_expert_skills(out.level), num_mastered_skills(out.level), num_legendary_skills(out.level));
  return out;
}
StatSet generate_priest_stats(NPC_Request request){
  StatSet out;
  out.level = request.level;
  out.strength = ability_score();
  out.constitution = ability_score();
  out.dexterity = ability_score();
  out.intelligence = ability_score();
  out.wisdom = high_ability_score();
  out.charisma = high_ability_score();
  out.ac = 12+calculate_modifier(out.dexterity)+out.level;;
  out.hp = (8+calculate_modifier(out.constitution))*out.level;
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+high_save_basis(out.level);
  out.fort_save= calculate_modifier(out.constitution)+save_basis(out.level);
  out.will_save = calculate_modifier(out.wisdom)+save_basis(out.level);
  out.abilities = get_priest_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 3+calculate_modifier(out.intelligence), num_expert_skills(out.level), num_mastered_skills(out.level), num_legendary_skills(out.level));
  return out;
}
StatSet generate_thief_stats(NPC_Request request){
  StatSet out;
  memset(&out, 0, sizeof(out));
  out.level = request.level;
  out.strength = ability_score();
  out.constitution = high_ability_score();
  out.dexterity = high_ability_score();
  out.intelligence = ability_score();
  out.wisdom = ability_score();
  out.charisma = ability_score();
  out.ac = 12+calculate_modifier(out.dexterity)+out.level;
  out.hp = (8+calculate_modifier(out.constitution))*out.level;
  out.perception = 2+calculate_modifier(out.wisdom)+out.level;
  out.reflex_save = calculate_modifier(out.dexterity)+high_save_basis(out.level);
  out.fort_save= calculate_modifier(out.constitution)+save_basis(out.level);
  out.will_save = calculate_modifier(out.wisdom)+save_basis(out.level);
  out.abilities = get_thief_abilities(out.level, request.martial_type, request.magic_type);
  out = select_skills(out, DefaultSkillsList, 5+calculate_modifier(out.intelligence), num_expert_skills(out.level)*2, num_mastered_skills(out.level)*2, num_legendary_skills(out.level)*2);
  return out;
}
StatSet(*const stat_generator_table[])(NPC_Request)  = {
  generate_laborer_stats, 
  generate_merchant_stats, 
  generate_noble_stats, 
  generate_fighter_stats, 
  generate_magic_user_stats, 
  generate_gish_stats, 
  generate_magic_using_thief_stats, 
  generate_priest_stats, 
  generate_thief_stats,
};
StatSet generate_stats(NPC_Request request){
  return (stat_generator_table[request.npc_type])(request);
}

NPC generate_character(NPC_Request request){
    NPC out;
    if (request.use_requested_gender){
        out.gender = request.requested_gender;
    } else{
        out.gender = generate_gender();
    }
    if (request.use_requested_ancestry){
        out.ancestry = request.requested_ancestry;
    } else{
        out.ancestry = random_ancestry();
    }
    out.name = generate_name(out.ancestry,out.gender);
    out.npc_type = request.npc_type;
    out.martial_type = request.martial_type;
    out.magic_type = request.magic_type;  
    out.stats = generate_stats(request);
    if(out.magic_type != MagicNONE){
      out.grimoire = generate_spells(request.level, request.innate_caster,request.magic_type, request.npc_type);
    }
    out.weapons = weapon_calculation(request.martial_type, request.npc_type,request.level, out.stats.strength, out.stats.dexterity);
    out.personality = generate_personality();
    out.age = generate_age( out.ancestry,out.stats.level);
    return out;
}

std::string format_npc(const NPC& npc){
  const auto bonus = [](int value){
      stringstream out;
      if (value<0){
        out << value;
      } else{
        out<<"+";
        out << value;
      }
      return out.str();
  };
  return utils::format("{}\nlevel:{} {} {} {}\nmartial_type:{}\nmagic_type:{}\nage:{}\nac:{} hp:{} reflex:{} fortitude:{} will:{}\nstrength: {}\ndexterity:{}\nconstitution:{}\nintelligence:{}\nwisdom:{}\ncharisma:{}\nperception:{}\nskills:acrobatics {}, arcana {}, athletics {},crafting {}, deception {}, diplomacy {}, intimidation {}, lore {}, medicine {}, nature {}, occultism {}, performance {}, religion {}, society {}, stealth {}, survival {}, thievery {}\nabilities:{}\n{}\nweapons:{}\npersonality:{}\n", npc.name,npc.stats.level, npc.gender, npc.ancestry, npc.npc_type, npc.martial_type,npc.magic_type,npc.age, npc.stats.ac, npc.stats.hp, bonus(npc.stats.reflex_save), bonus(npc.stats.fort_save), bonus(npc.stats.will_save), npc.stats.strength, npc.stats.dexterity, npc.stats.constitution, npc.stats.intelligence, npc.stats.wisdom, npc.stats.charisma, bonus(npc.stats.perception),bonus(npc.stats.acrobatics), bonus(npc.stats.arcana), bonus(npc.stats.athletics), bonus(npc.stats.crafting), bonus(npc.stats.deception), bonus(npc.stats.diplomacy), bonus(npc.stats.intimidation), bonus(npc.stats.lore), bonus(npc.stats.medicine), bonus(npc.stats.nature), bonus(npc.stats.occultism), bonus(npc.stats.performance), bonus(npc.stats.religion), bonus(npc.stats.society), bonus(npc.stats.stealth), bonus(npc.stats.survival), bonus(npc.stats.thievery),npc.stats.abilities, npc.grimoire, npc.weapons,npc.personality);
}