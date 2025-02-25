#pragma once
#include "types.hpp"
#include "grimoire.hpp"
#include "Ancestries.hpp"
struct NPC{
    std::string name;
    EGender gender;
    EAncestries ancestry;
    ENPC_Type npc_type;
    StatSet stats;
    Grimoire grimoire;
    std::vector<Weapon> weapons;
    std::vector<std::string> personality;
};
constexpr size_t npc_size =sizeof(NPC);