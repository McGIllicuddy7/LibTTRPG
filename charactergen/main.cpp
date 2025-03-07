#include "character.hpp"
#include <iostream>
#include <string.h>
#include <gperftools/profiler.h>
#include "personality.hpp"
#include <stdio.h>
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
void usage_message(){
    printf("usage: <program name> --class <class> --level <level> (optional) --magic-type <magic type> --martial-type <martial type> --innate --prepared --ancestry <ancestry>\n    optional arguments may be required depending on class. Class is one of laborer, merchant, noble, fighter(requires martial type), magic_user(requires magic type and innate or prepared), gish(requires magic type and martial type and innate or prepared), magic_using_thief(requires magic type and martial type and innate or prepared), priest, thief(requires martial type).\n  Level is an integer between 1 and 20(inclusive). magic types are: arcane(a), divine(a), occult(o), primal(p).\n   Martial types are organized-melle(om), disorganized-melle(om), organized-ranged(om), disorganized-ranged(dr).\n   Gender arguments can be female(f),nonbinary(nb) and male(m).\n  Ancestry arguments can be catfolk, dwarf, elf, goblin, gnome, halfing, human and orc.\n");
    exit(0);
}

NPC_Request parse_request(const std::vector<std::string_view>& args){
    NPC_Request out;
    memset(&out, 0, sizeof(out));
    size_t index = 0;
    bool class_set = false;
    bool level_set = false;
    bool innate_caster_set = false;
    bool magic_type_set = false;
    bool martial_type_set = false;
    while(index<args.size()){
        std::string_view a = args[index];
        if(a == "--class"){
            index += 1;
            if(index>= args.size()){
                throw new std::string("--class requires an argument");
            }
            std::string_view b = args[index];
            if(b == "laborer"){
                out.npc_type = Laborer;
            } else if(b == "merchant"){
                out.npc_type = Merchant;
            } else if(b == "noble"){
                out.npc_type = Noble;
            } else if(b == "fighter"){
                out.npc_type = Fighter;
            } else if(b == "magic_user"){
                out.npc_type = Magic_User;
            } else if(b== "gish"){
                out.npc_type = Gish;
            } else if(b == "magic-using-thief"){
                out.npc_type = Magic_Using_Thief;
            } else if(b == "priest"){
                out.npc_type = Priest;
            } else if (b == "thief"){
                out.npc_type = Thief;
            } else{
                std::string v= "unknown class name:";
                std::string t = std::string(b);
                throw new std::string(v+t);
            }
            class_set = true;
        } else if(a == "--level"){
            index += 1;
            if(index>= args.size()){
                throw new std::string("--level requires an argument");
            } 
            std::stringstream b;
            b<<args[index];
            b>>out.level;
            level_set = true;
        } else if(a == "--magic-type"){
            index += 1;
            if(index>= args.size()){
                throw new std::string("--magic-type requires an argument");
            }
            std::string_view b = args[index];
            if(b == "arcane" || b == "a"){
                out.magic_type = Arcane;
            } else if(b == "divine" || b == "d"){
                out.magic_type = Divine;
            } else if(b == "primal" || b == "p"){
                out.magic_type = Primal;
            } else if(b == "occult" || b=="o"){
                out.magic_type = Occult;
            } else{
                std::string v= "unknown magic type:";
                std::string t = std::string(b);
                throw new std::string(v+t);
            }
            magic_type_set = true;
        } else if(a == "--martial-type"){
            index += 1;
            if(index>= args.size()){
                throw new std::string("--martial-type requires an argument");
            }
            std::string_view b = args[index];
            if(b == "organized-melle" || b == "om"){
                out.martial_type = OrganizedMelle;
            }  else if(b == "disorganized-melle" || b == "dm"){
                out.martial_type = DisorganizedMelle;
            } else if(b == "organized-ranged" || b == "or"){
                out.martial_type = OrganizedRanged;
            } else if(b == "disorganized-ranged" || b == "dr"){
                out.martial_type = DisorganizedRanged;
            }
            else{
                std::string v= "unknown martial type:";
                std::string t = std::string(b);
                throw new std::string(v+t);
            }
            martial_type_set = true;
        } else if(a == "--gender"){
            index += 1;
            if(index>= args.size()){
                throw new std::string("--gender requires an argument");
            }
            std::string_view b = args[index]; 
            if(b == "m" || b == "male"){
                out.requested_gender = Male;
            } else if(b == "f" || b == "female"){
                out.requested_gender = Female;
            } else if(b == "nb" || b == "nonbinary"){
                out.requested_gender = Nonbinary;
            } else{
                std::string v= "unknown gender:";
                std::string t = std::string(b);
                throw new std::string(v+t);
            }
            out.use_requested_gender = true;
        } else if(a == "--ancestry"){
            index += 1;
            if(index>= args.size()){
                throw new std::string("--ancestry requires an argument");
            }
            std::string_view b = args[index];  
            if(b == "dwarf"){
                out.requested_ancestry = Dwarf;
            }else if(b == "elf"){
                out.requested_ancestry = Elf;
            } else if(b == "gnome"){
                out.requested_ancestry =Gnome;
            } else if(b == "goblin"){
                out.requested_ancestry = Goblin;
            } else if(b == "human"){
                out.requested_ancestry = Human;
            } else if(b == "catfolk"){
                out.requested_ancestry =Catfolk;
            } else if(b == "orc"){
                out.requested_ancestry = Orc;
            } else{
                std::string v= "unknown ancestry:";
                std::string t = std::string(b);
                throw new std::string(v+t); 
            }
            out.use_requested_ancestry = true;
        }else if(a == "--innate"){
            out.innate_caster = true;
            innate_caster_set = true;
        } else if(a == "--prepared"){
            out.innate_caster = false;
            innate_caster_set = true;
        } 
        else if (a == "--help"){
            usage_message();
        } else if(a == "h"){
            usage_message();
        } else if(a == "help"){
            usage_message();
        } else if(a == "laborer"){
            out.npc_type = Laborer;
            class_set = true;
            index += 1;
            if(index>= args.size()){
                throw new std::string("class requires level argument");
            } 
            std::stringstream b;
            b<<args[index];
            b>>out.level;
            level_set = true;
        } else if(a == "merchant"){
            out.npc_type = Merchant;
            class_set = true;
            index += 1;
            if(index>= args.size()){
                throw new std::string("class requires level argument");
            } 
            std::stringstream b;
            b<<args[index];
            b>>out.level;
            level_set = true;
        } else if(a == "noble"){
            out.npc_type = Noble;
            class_set = true;
            index += 1;
            if(index>= args.size()){
                throw new std::string("class requires level argument");
            } 
            std::stringstream b;
            b<<args[index];
            b>>out.level;
            level_set = true;
        } else if(a == "fighter"){
            out.npc_type = Fighter;           
             class_set = true;
             index += 1;
             if(index>= args.size()){
                 throw new std::string("class requires level argument");
             } 
             std::stringstream b;
             b<<args[index];
             b>>out.level;
             level_set = true;
        } else if(a == "magic_user"){
            out.npc_type = Magic_User;           
             class_set = true;
             index += 1;
             if(index>= args.size()){
                 throw new std::string("class requires level argument");
             } 
             std::stringstream b;
             b<<args[index];
             b>>out.level;
             level_set = true;
        } else if(a== "gish"){
            out.npc_type = Gish;
            class_set = true;
            index += 1;
            if(index>= args.size()){
                throw new std::string("class requires level argument");
            } 
            std::stringstream b;
            b<<args[index];
            b>>out.level;
            level_set = true;
        } else if(a == "magic-using-thief"){
            out.npc_type = Magic_Using_Thief;
            class_set = true;
            index += 1;
            if(index>= args.size()){
                throw new std::string("class requires level argument");
            } 
            std::stringstream b;
            b<<args[index];
            b>>out.level;
            level_set = true;
        } else if(a == "priest"){
            out.npc_type = Priest;
            class_set = true;
            index += 1;
            if(index>= args.size()){
                throw new std::string("class requires level argument");
            } 
            std::stringstream b;
            b<<args[index];
            b>>out.level;
            level_set = true;
        } else if (a == "thief"){
            out.npc_type = Thief;
            class_set = true;
            index += 1;
            if(index>= args.size()){
                throw new std::string("class requires level argument");
            } 
            std::stringstream b;
            b<<args[index];
            b>>out.level;
            level_set = true;
        }
        else{
            std::string v= "unknown arg:";
            std::string t = std::string(a);
            throw new std::string(v+t);
        }
        index += 1;
    }
    if(!class_set){
        throw new std::string("character creation requires a class");
    } 
    if(!level_set){
        throw new std::string("character creation requires a level");
    }
    if(out.npc_type == Magic_User || out.npc_type == Gish || out.npc_type == Magic_Using_Thief){
        if(!magic_type_set){
            throw new std::string("magic using classes require magic_type"); 
        }
        if(!innate_caster_set){
            throw new std::string("magic using classes require prepared or innate to be set "); 
        }
    }
    if(out.npc_type == Fighter || out.npc_type == Gish || out.npc_type == Magic_Using_Thief || out.npc_type == Thief){
        if(!martial_type_set){
            throw new std::string("martial classes require a martial type"); 
        } 
    }
    return out;
}
int main(int argc, const char ** argv){
    std::vector<std::string_view> args = {};
    if (argc< 2){
        usage_message();
    }
    for(int i =1; i<argc; i++){
        args.push_back(argv[i]);
    }
    try{   
        NPC_Request request = parse_request(args);
        NPC npc =generate_character(request);
        std::cout << format_npc(npc)<<"\n";
    } catch(std::string* v){
        std::cout <<"Error:"<<*v<<"\n";
        exit(1);
    }

}