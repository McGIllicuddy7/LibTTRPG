#include "character.hpp"
#include <iostream>
#include <string.h>
int main(void){
    NPC_Request request;
    memset(&request,0, sizeof(request));
    request.npc_type = Magic_User;
    request.magic_type = Arcane;
    request.innate_caster = false;
    request.martial_type = OrganizedMelle;
    request.level= 5;
    NPC npc = generate_character(request);
    std::cout << format_npc(npc)<<"\n";
}