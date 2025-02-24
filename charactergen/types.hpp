#include "Ancestries.hpp"
#include "Spellcasting.hpp"
#include "Abilities.hpp"
#include <string>
#include <vector>
#include <string_view>

using std::vector;
using std::string;
using std::string_view;
typedef enum{
    Male, Female, Nonbinary
  }EGender;
  typedef enum{
    Laborer, Merchant, Noble, Fighter, Magic_User, Gish, Magic_using_Thief, Priest, Thief
  } ENPC_Type;
  typedef enum{
    Elite, Normal, Weak
  } NPC_Strength_t;
  typedef enum{
    Untrained, Trained,Expert,Master,Legendary
  }TrainingLevel_t;
  typedef struct{
    string Name;
    string Text;
    bool Finnese;
    bool Ranged;
    int Bonus;
    string DamageDie;
    int DamageBonus;
  } Weapon;

enum Skills{ Acrobatics,Arcana,Athletics,Crafting,Deception,Diplomacy,Intimidation,Lore,Medicine,Nature,Occultism,Performance,Religion,
Society,Stealth,Survival,Thievery};
struct StatSet{
    int level;
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int ac;
    int hp;
    int reflex_save;
    int fort_save;
    int will_save;
    int perception;
    int acrobatics;
    int arcana;
    int athletics;
    int crafting;
    int deception;
    int diplomacy;
    int intimidation;
    int lore;
    int medicine;
    int nature;
    int occultism;
    int performance;
    int religion;
    int society;
    int stealth;
    int survival;
    int thievery;
};