#pragma once
#include "types.hpp"
#include "grimoire.hpp"
#include "Ancestries.hpp"
struct NPC{
    std::string name;
    EGender gender;
    EAncestries ancestry;
    ENPC_Type npc_type;
    MagicTypes magic_type;
    MartialTypes martial_type;
    bool innate_caster;
    size_t age;
    StatSet stats;
    Grimoire grimoire;
    std::vector<Weapon> weapons;
    std::vector<std::string> personality;
};
struct NPC_Request{
    ENPC_Type npc_type;
    MagicTypes magic_type;
    bool innate_caster;
    MartialTypes martial_type;
    bool use_requested_gender;
    bool use_requested_ancestry;
    EGender requested_gender;
    EAncestries requested_ancestry;
    size_t level;
};

constexpr size_t npc_size =sizeof(NPC);
NPC generate_character(NPC_Request request);
std::string format_npc(const NPC& npc);