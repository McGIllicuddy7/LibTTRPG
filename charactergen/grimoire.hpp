#pragma once
#include "Utils.hpp"
#include "types.hpp"
struct Grimoire{
    vector<string_view> cantrips;
    vector<string_view> first_level_spells;
    vector<string_view> second_level_spells;
    vector<string_view> third_level_spells;
    vector<string_view> fourth_level_spells;
    vector<string_view> fifth_level_spells;
    vector<string_view> sixth_level_spells;
    vector<string_view> seventh_level_spells;
    vector<string_view> eighth_level_spells;
    vector<string_view> ninth_level_spells;
    vector<string_view> tenth_level_spells;
    vector<string_view> spellbook;
    bool innate_caster;
    SpellSlots spellslots;
};
std::ostream& operator<<(std::ostream& os, const Grimoire & grim);
Grimoire generate_spells(int level, bool innate_caster, MagicTypes magic_type,ENPC_Type npc_type);