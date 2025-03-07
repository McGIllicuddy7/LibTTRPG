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
std::ostream& operator<<(std::ostream& os, const MagicTypes magic_type);
std::ostream& operator<<(std::ostream& os, const MartialTypes martial_type);
vector<string_view> get_laborer_abilities(int Level,MartialTypes MartialType, MagicTypes magictype);
vector<string_view> get_merchant_abilities(int Level,MartialTypes MartialType, MagicTypes magictype);
vector<string_view> get_fighter_abilities(int Level,MartialTypes MartialType, MagicTypes magictype);
vector<string_view> get_gish_abilities(int Level,MartialTypes MartialType, MagicTypes MagicType);
vector<string_view> get_thief_abilities(int Level,MartialTypes MartialType, MagicTypes magic_type);
vector<string_view> get_noble_abilities(int Level,MartialTypes MartialType, MagicTypes magictype);
vector<string_view> get_magic_user_abilities(int Level, MartialTypes MartialType,MagicTypes MagicType);
vector<string_view> get_magic_using_thief_abilities(int Level,MartialTypes MartialType, MagicTypes MagicType);
vector<string_view> get_priest_abilities(int Level,MartialTypes MartialType, MagicTypes magictype);
typedef vector<string_view> Ability;
extern const Ability SneakAttack;
extern const Ability QuickDraw;
extern const Ability SurpiseAttack;
extern const Ability ScoundrelsFeint;
extern const Ability QuickRummage;
extern const Ability VersitilePerformace;
extern const Ability DenyAdvantage;
extern const Ability Mobility;
extern const Ability NimbleDodge;
extern const Ability BrutalBeating;
extern const Ability SnaggingStrike;
extern const Ability HealingHands;
extern const Ability SteadySpellcasting;
extern const Ability Smite;
extern const Ability CollaborativeTheivery;
extern const Ability Pickpocket;
extern const Ability YoureNext;
extern const Ability TrickAttack;
extern const Ability HuntPrey;
extern const Ability SuddenCharge;
extern const Ability AirOfAuthority;
extern const Ability Bravery;
extern const Ability AttackOfOpportunity;
extern const Ability ShieldBlock;
extern const Ability ShieldWarden;
extern const Ability CounterSpell;
extern const Ability AppraisingEye;
extern const Ability CallToAction;
extern const Ability CraftSnare ;
extern const Ability IntimidatingStrike;
extern const Ability Evasion;
extern const Ability GangUp;
extern const Ability BrutalRally;
extern const Ability FontOfKnowledge;
extern const Ability SentrysAim;
extern const Ability ForestWalker;
extern const Ability LieToMe;
extern const Ability CourtlyGrace;
# endif /* Abiliites_h */
