#include "character.hpp"
#include <iostream>
#include <string.h>
#include <gperftools/profiler.h>
#include "personality.hpp"
void static_npc(){
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
int main(void){
    ProfilerStart("dump.txt");
    for(int i =0; i<=(int)Orc; i++){
        size_t total =0; 
        size_t min = 100000;
        const size_t count = 1000000;
        for(size_t j =0; j<count; j++){
            size_t tmp =generate_age((EAncestries)i, 1);
            total += tmp;
            if(tmp<min){
                min = tmp;
            }
        }
        double expected= ((double)total)/((double)count);
        std::cout << (EAncestries)i <<" expected age: "<<expected<<" min age: "<<min <<"\n";
    }
}