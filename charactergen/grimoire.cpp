#include "grimoire.hpp"
#include "Utils.hpp"
#include "Spellcasting.hpp"
#include "spells.hpp"
static vector<string_view> CantripsLut[] = { Arcane_Cantrips, Divine_Cantrips,Primal_Cantrips, Occult_Cantrips};
static vector<string_view> Spells1stlevelLut[] = { Arcane_1st_Level, Divine_1st_Level, Primal_1st_Level, Occult_1st_Level};
static vector<string_view> Spells2ndlevelLut[] = { Arcane_2nd_Level, Divine_2nd_Level, Primal_2nd_Level, Occult_2nd_Level};
static vector<string_view> Spells3rdlevelLut[] = { Arcane_3rd_Level, Divine_3rd_Level, Primal_3rd_Level, Occult_3rd_Level};
static vector<string_view> Spells4thlevelLut[] = { Arcane_4th_Level, Divine_4th_Level, Primal_4th_Level, Occult_4th_Level};
static vector<string_view> Spells5thlevelLut[] = { Arcane_5th_Level, Divine_5th_Level, Primal_5th_Level, Occult_5th_Level};
static vector<string_view> Spells6thlevelLut[] = { Arcane_6th_Level, Divine_6th_Level, Primal_6th_Level, Occult_6th_Level};
static vector<string_view> Spells7thlevelLut[] = { Arcane_7th_Level, Divine_7th_Level, Primal_7th_Level, Occult_7th_Level};
static vector<string_view> Spells8thlevelLut[] = { Arcane_8th_Level, Divine_8th_Level, Primal_8th_Level, Occult_8th_Level};
static vector<string_view> Spells9thlevelLut[] = { Arcane_9th_Level, Divine_9th_Level, Primal_9th_Level, Occult_9th_Level};
static vector<string_view> Spells10thlevelLut[]= { Arcane_10th_Level, Divine_10th_Level, Primal_10th_Level, Occult_10th_Level};

#define SpellbookAdd(name, vec) for(auto&i : vec){name.spellbook.push_back(i);}
Grimoire generate_spells(int level, bool innate_caster, MagicTypes magic_type,ENPC_Type npc_type){
    Grimoire out;
    if(npc_type!= Magic_User){
      level = level/3;
      if(level<1){
        level = 1;
      }
    }
    if(innate_caster){
      SpellSlots Slots = innate_spellslots_by_level(level);
      out.cantrips = array_choose(CantripsLut[magic_type], Slots.Cantrips);
      out.first_level_spells = array_choose(Spells1stlevelLut[magic_type], Slots.level1);
      out.second_level_spells =array_choose(Spells2ndlevelLut[magic_type], Slots.level2);
      out.third_level_spells = array_choose(Spells3rdlevelLut[magic_type], Slots.level3);
      out.fourth_level_spells = array_choose(Spells4thlevelLut[magic_type], Slots.level4);
      out.fifth_level_spells = array_choose(Spells5thlevelLut[magic_type], Slots.level5);
      out.sixth_level_spells = array_choose(Spells6thlevelLut[magic_type], Slots.level6);
      out.seventh_level_spells = array_choose(Spells7thlevelLut[magic_type], Slots.level7);
      out.eighth_level_spells = array_choose(Spells8thlevelLut[magic_type], Slots.level8);
      out.ninth_level_spells = array_choose(Spells9thlevelLut[magic_type], Slots.level9);
      out.tenth_level_spells = array_choose(Spells10thlevelLut[magic_type], Slots.level10);
    }
    else{
      SpellSlots Book = prepared_spellbook_by_level(level);
      SpellSlots Slots = prepared_spellslots_by_level(level);
      vector<string_view> CantripBuff = array_choose(CantripsLut[magic_type], Book.Cantrips);
      vector<string_view> FirstlevelBuff = array_choose(Spells1stlevelLut[magic_type], Book.level1);
      vector<string_view> SecondlevelBuff = array_choose(Spells2ndlevelLut[magic_type], Book.level2);
      vector<string_view> ThirdlevelBuff = array_choose(Spells3rdlevelLut[magic_type], Book.level3);
      vector<string_view> FourthlevelBuff = array_choose(Spells4thlevelLut[magic_type], Book.level4);
      vector<string_view> FifthlevelBuff = array_choose(Spells5thlevelLut[magic_type], Book.level5);
      vector<string_view> SixthlevelBuff = array_choose(Spells6thlevelLut[magic_type], Book.level6);
      vector<string_view> SeventhlevelBuff = array_choose(Spells7thlevelLut[magic_type], Book.level7);
      vector<string_view> EightlevelBuff = array_choose(Spells8thlevelLut[magic_type], Book.level8);
      vector<string_view> NinthlevelBuff = array_choose(Spells9thlevelLut[magic_type], Book.level9);
      vector<string_view> TenthlevelBuff = array_choose(Spells10thlevelLut[magic_type], Book.level10);
      out.cantrips = array_choose(CantripsLut[magic_type], Slots.Cantrips);
      out.first_level_spells = array_select(Spells1stlevelLut[magic_type], Slots.level1);
      out.second_level_spells = array_select(Spells2ndlevelLut[magic_type], Slots.level2);
      out.third_level_spells = array_select(Spells3rdlevelLut[magic_type], Slots.level3);
      out.fourth_level_spells = array_select(Spells4thlevelLut[magic_type], Slots.level4);
      out.fifth_level_spells = array_select(Spells5thlevelLut[magic_type], Slots.level5);
      out.sixth_level_spells = array_select(Spells6thlevelLut[magic_type], Slots.level6);
      out.seventh_level_spells = array_select(Spells7thlevelLut[magic_type], Slots.level7);
      out.eighth_level_spells = array_select(Spells8thlevelLut[magic_type], Slots.level8);
      out.ninth_level_spells = array_select(Spells9thlevelLut[magic_type], Slots.level9);
      out.tenth_level_spells = array_select(Spells10thlevelLut[magic_type], Slots.level10);
      SpellbookAdd(out,CantripBuff);
      SpellbookAdd(out,FirstlevelBuff);
      SpellbookAdd(out,SecondlevelBuff);
      SpellbookAdd(out,ThirdlevelBuff);
      SpellbookAdd(out,FourthlevelBuff);
      SpellbookAdd(out,FifthlevelBuff);
      SpellbookAdd(out,SixthlevelBuff);
      SpellbookAdd(out,SeventhlevelBuff);
      SpellbookAdd(out,EightlevelBuff);
      SpellbookAdd(out,NinthlevelBuff);
      SpellbookAdd(out,TenthlevelBuff);
    }
  }