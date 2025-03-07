//
//  Abiliites.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/9/23.
//

#include "Abilities.hpp"
#include "Utils.hpp"
#include <stdlib.h>
#include <vector>
#include <string_view>
#include <stddef.h>
using namespace std;
typedef vector<string_view> Ability;
const Ability SneakAttack = {
  "Sneak Attack: Deals an extra 1d6 precision damage to flat-footed creature",  "Sneak Attack: Deals an extra 2d6 precision damage to flat-footed creature",
  "Sneak Attack: Deals an extra 3d6 precision damage to flat-footed creature",  "Sneak Attack: Deals an extra 4d6 precision damage to flat-footed creature",
  "Sneak Attack: Deals an extra 5d6 precision damage to flat-footed creature",
};
const Ability QuickDraw = {"Quick Draw[1 action]: The character Interacts to draw a weapon, then Strikes with that weapon"};
const Ability SurpiseAttack = {"Surprise Attack: On the first round of combat, creatures that haven’t acted yet are flat footed to the charcater."};
const Ability ScoundrelsFeint = {"Scoundrels Feint: When the character successfully Feints, their target is flat-footed against the character’s attacks until the end of the characters’s next turn. On a critical success, the target is flat-footed against all attacks until the end of the charcater's next turn"};
const Ability QuickRummage = {"Quick Rummage: The character always has a few items close at hand. The character Interacts to draw a weapon or item that takes a single action to activate, and then Strikes with the weapon or Activates the Item."};
const Ability VersitilePerformace = {"Versitile Performance: The character can use Performance instead of Diplomacy to Make an Impression and instead of Intimidation to Demoralize. They can also use an acting Performance instead of Deception to Impersonate."};
const Ability DenyAdvantage = { "Deny Advantage: The character isn’t flat-footed to creatures of it's level or lower that are hidden, undetected, flanking, or using surprise attack."};
const Ability Mobility = { "Mobility: When the character Strides half their Speed or less, that movement does not trigger reactions"};
const Ability NimbleDodge = {"Nimble Dodge[Reaction]: Trigger The character is targeted with a melee or ranged attack by an attacker it can see; Effect The character gains a +2 circumstance bonus to AC against the triggering attack."};
const Ability BrutalBeating = {"Brutal Beating: The character's brutality shakes foes’ confidence. When the character deals damage on a critical hit, the target is frightened 1, and the character can knock the target up to 10 feet away (this is forced movement)."};
const Ability SnaggingStrike = {"Snagging Strike[1 action]: Trigger The character has one hand free, and its target is within reach of that hand; Effect The character makes a melee Strike while keeping one hand free. If this Strike hits, the target is flat-footed until the start of the character's next turn or until it leaves the character's reach, whichever comes first."};
const Ability HealingHands = {"Healing Hands: When the character casts heal, they roll d10s instead of d8s."};
const Ability SteadySpellcasting = {"If another creature’s reaction would disrupt the character’s spellcasting action, the character attempts a DC 15 flat check. If they succeed, their action isn’t disrupted."};
const Ability Smite = {"Smite[2 Actions]: the character expends a prepared damaging spell and makes one melle or ranged attack, instead of its usual effect the spell's damage and any side effects of it on its target is added to the attack"};
const Ability CollaborativeTheivery = {" Collaborative Thievery: The character gains a +1 circumstance bonus to Steal or Palm an Object while within 10 feet of an ally who has the pickpocket ability."};
const Ability Pickpocket = {"Pickpocket: The character can Steal or Palm an Object that’s closely guarded without taking the usual –5 penalty. They can Steal objects that would be extremely noticeable or time-consuming to remove (like worn shoes, armor, or actively wielded object."};
const Ability YoureNext = { "You're Next: [reaction] (emotion, fear, mental) Trigger character reduces a creature to 0 Hit Points; Effect The character attempts an Intimidation check with a +2 circumstance bonus to Demoralize a single creature it can see and that can see them."};
const Ability TrickAttack = {"Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 1d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow).",
  "Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 2d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow).",
  "Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 3d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow).",
  "Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 4d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow).",
  "Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 5d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow).",
};
const Ability HuntPrey = {"Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 1d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again.",
  "Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 2d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again.",
  "Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 3d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again.",
  "Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 4d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again.",
  "Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 5d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again."
};
const Ability SuddenCharge = {"Sudden Charge[2 Actions]: The character Strides twice and makes a melee Strike."};
const Ability AirOfAuthority = {"Air of Authority: (aura, emotion, mental) 10 feet. Creatures in the aura who are the same or lower level than the character take a –2 status penalty to their Will DC against the character's attempts to Coerce or Demoralize them."};
const Ability Bravery = {"Bravery: When the character rolls a success on a Will save against a fear effect, they get a critical success instead. In addition, any time they gain the frightened condition, reduce its value by 1"};
const Ability AttackOfOpportunity = {"Attack of Opportunity: The character can make opportunity Attacks as a reaction"};
const Ability ShieldBlock = {"The Charcater can Shield Block as a reaction"};
const Ability ShieldWarden = {"Shield Warden[Reaction]: When the character has their shield raised, they can Shield Block when an attack is made against an adjacent ally. If they do, the shield prevents that ally from taking damage instead of the character."};
const Ability CounterSpell = {"Counterspell [Reaction] Trigger A creature Casts a Spell the character has can currently cast; Effect The character  expends the spell to counter the triggering creature’s casting of that same spell. The character loses its spell slot as if it had cast the triggering spell. the character then attempts to counteract the triggering spell."};
const Ability AppraisingEye = {"Appraising Eye: The character can use Mercantile Lore to Recall Knowledge about items,including determining their value. They can also attempt to Identify Magic using Mercantile Lore and can do so without first knowing whether the item is magical."};
const Ability CallToAction = {"Call to Action[1 action] (auditory, concentrate, emotion, mental) The character gives a speech to inspire themself and all allies within 60 feet, granting them a +1 status bonus to attack and damage rolls until the start of the character’s next turn."};
const Ability CraftSnare = {"Craft Snare: the character can Craft snares and has the supplies to make up to two caltrop snares and up to two hampering snares."};
const Ability IntimidatingStrike = {"Intimidating Strike[2 actions] The character makes a melee Strike. If they hit and deal damage, the target is frightened 1, or frightened 2 on a critical hit."};
const Ability Evasion = {"Evasion: When the character rolls a success on a Reflex save, they get a critical success instead."};
const Ability GangUp = {"Gang Up: Any enemy is flat‐footed against the character’s melee attacks due to flanking as long as the enemy is within melee reach of both the character and one of the character’s allies."};
const Ability BrutalRally = {"Brutal Rally [Reaction]:(auditory, emotion, linguistic, mental) Trigger The character rolls a critical hit against a creature; Effect All allies that can see the character gain a +1 circumstance bonus to attack rolls until the start of the character’s next turn."};
const Ability FontOfKnowledge = {"Font of Knowledge: The character can attempt to Recall Knowledge on any general subject with a +10 modifier."};
const Ability SentrysAim = {"Sentry’s Aim[2 actions] (concentrate):The character aims carefully and fires. They make a ranged weapon Strike with a +1 circumstance bonus. The Strike ignores the concealed condition, lesser cover, and standard cover, and reduces greater cover to standard cover."};
const Ability ForestWalker = {"Forest Walker The character ignores the effects of difficult terrain from a forest environment. They can Sneak through underbrush without the need to attempt a Stealth check as long as the hunter moves no more than 5 feet at a time and is not within 10 feet of an enemy at any point during their movement."};
const Ability LieToMe = {"The character can use Deception to weave traps to trip up anyone trying to deceive them. If they can engage in conversation with someone trying to Lie to them, use their deception DC if it is higher than their Perception DC to determine whether they succeed. This doesn’t apply if they don’t have a back-and-forth dialogue, such as when someone attempts to Lie during a long speech. "};
const Ability CourtlyGrace = {"The character were raised among the nobility or have learned proper etiquette and bearing, allowing them to present themself as a noble and play games of influence and politics. They can use Society to Make an Impression on a noble, as well as with Impersonate to pretend to be a noble if they aren’t one. If they want to impersonate a specific noble, they still need to use Deception to Impersonate normally, and to Lie when necessary."};

string_view AbilityText(const Ability * Ab, const int level){
  if(Ab->size()>1){
    if(level<5){
      return (*Ab)[0];
    }
    if(level<11){
      return (*Ab)[1];
    }
    if(level<17){
      return (*Ab)[2];
    }
    if(level<20){
      return (*Ab)[3];
    }
    else{
      return (*Ab)[4];
    }
  }
  return (*Ab)[0];
}
vector<string_view> abilities_text(const Ability * default_ability, const vector<Ability> list, const int level, int NumToChoose){
  vector<string_view> out;
  if(default_ability){
    out.push_back((*default_ability)[0]);
  }
  vector<int> indicies;
  for(size_t i = 0; i<list.size(); i++){
    indicies.push_back(i);
  }
  for(int i = 0; i<NumToChoose; i++){
    int r = random_int()%indicies.size();
    string_view v = AbilityText(&list[r], level);
    out.push_back(v);
    indicies.erase(indicies.begin()+r);
  }
  return out;
}
vector<string_view> get_laborer_abilities(int level,MartialTypes martial_type, MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  vector<Ability> LaborerAbilities = {QuickDraw, QuickRummage,Bravery, AirOfAuthority, BrutalBeating, GangUp,SnaggingStrike,AppraisingEye,IntimidatingStrike};
  return abilities_text(NULL, LaborerAbilities, level, 1);
}
vector<string_view> get_merchant_abilities(int level,MartialTypes martial_type, MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  const Ability * default_ability = &AppraisingEye;
  vector<Ability> MerchantAbilites = {AirOfAuthority, FontOfKnowledge,VersitilePerformace,Bravery,CallToAction};
  return abilities_text(default_ability, MerchantAbilites, level, 1);
}
vector<string_view> get_fighter_abilities(int level,MartialTypes martial_type, MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  const Ability * default_ability;
 vector<Ability> FighterAbilities;
  if(martial_type == OrganizedMelle){
    default_ability = NULL;
    vector<Ability> OrgMelleAbilities = {SuddenCharge, SnaggingStrike, AttackOfOpportunity, ShieldWarden,GangUp,TrickAttack};
    FighterAbilities = OrgMelleAbilities;
  }
  else if(martial_type == DisorganizedRanged){
    default_ability = NULL;
    vector<Ability> DisorganizedRangedAbilites = {SurpiseAttack, HuntPrey, Evasion,SneakAttack,TrickAttack,CraftSnare};
    FighterAbilities = DisorganizedRangedAbilites;
  }
  else if(martial_type == OrganizedRanged){
    default_ability = &SentrysAim;
    vector<Ability> DisorganizedRangedAbilites = {Bravery,SurpiseAttack, Evasion,SneakAttack,TrickAttack};
    FighterAbilities = DisorganizedRangedAbilites;
  }
  else{
    default_ability = NULL;
    vector<Ability> DisorganizedMelleAbilitiers = {QuickDraw, QuickRummage, Bravery, AirOfAuthority, BrutalBeating, GangUp,SnaggingStrike,AppraisingEye,IntimidatingStrike};
    FighterAbilities = DisorganizedMelleAbilitiers;
  }
  return abilities_text(default_ability, FighterAbilities,level, 2);
}
vector<string_view>  get_gish_abilities(int level, MartialTypes martial_type,MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  vector<Ability> MartialAbilities;
  if(martial_type == OrganizedMelle){
    vector<Ability> OrgMelleAbilities = {SuddenCharge, SnaggingStrike, AttackOfOpportunity, ShieldWarden,GangUp,TrickAttack,
      ScoundrelsFeint, CourtlyGrace, LieToMe};
    MartialAbilities = OrgMelleAbilities;
  }
  else if(martial_type == DisorganizedRanged){
    vector<Ability> DisorganizedRangedAbilites = {SurpiseAttack, HuntPrey, Evasion,SneakAttack,TrickAttack,CraftSnare};
    MartialAbilities = DisorganizedRangedAbilites;
  }
  else if(martial_type == OrganizedRanged){
    vector<Ability> DisorganizedRangedAbilites = {SentrysAim,Bravery,SurpiseAttack, Evasion,SneakAttack,TrickAttack};
    MartialAbilities = DisorganizedRangedAbilites;
  }
  else{
    vector<Ability> DisorganizedMelleAbilities = {QuickDraw, QuickRummage, Bravery, AirOfAuthority, BrutalBeating, GangUp,SnaggingStrike,AppraisingEye,IntimidatingStrike};
    MartialAbilities = DisorganizedMelleAbilities;
  }
  vector<Ability> MagicAbilities;
  if(magic_type == Arcane || magic_type == Occult){
    vector<Ability> ArcaneAbilites = { SteadySpellcasting,Smite,CounterSpell};
    MagicAbilities = ArcaneAbilites;
  }
  else if(magic_type == Divine){
    vector<Ability> DivineAbilites = {SteadySpellcasting,Smite,CounterSpell,HealingHands};
    MagicAbilities = DivineAbilites;
  }
  else{
  vector<Ability> PrimalAbilites = {SteadySpellcasting,Smite,CounterSpell,HealingHands,ForestWalker,HuntPrey};
    MagicAbilities = PrimalAbilites;
  }
  vector<string_view> out =  abilities_text(NULL,MartialAbilities, level, 1);
  vector<string_view> maot = abilities_text(NULL, MagicAbilities, level,1);
  for(size_t i = 0; i<maot.size(); i++){
    out.push_back(maot[i]);
  }
  return out;
}
vector<string_view>  get_thief_abilities(int level,MartialTypes martial_type, MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  const Ability * default_ability = &SneakAttack;
  vector<Ability> Abilities;
  if(martial_type == OrganizedMelle){
    vector<Ability> OrgMelleAbilities ={ QuickDraw ,SurpiseAttack, ScoundrelsFeint,CourtlyGrace,CollaborativeTheivery,Pickpocket, DenyAdvantage ,Mobility, NimbleDodge,TrickAttack,GangUp};
    Abilities = OrgMelleAbilities;
  }
  if(martial_type == DisorganizedMelle){
    vector<Ability> DisOrgMelleAbilities ={ QuickDraw ,SurpiseAttack, ScoundrelsFeint,CollaborativeTheivery, Pickpocket, DenyAdvantage ,Mobility, NimbleDodge,TrickAttack,SentrysAim,CraftSnare, HuntPrey,ForestWalker,GangUp};
    Abilities = DisOrgMelleAbilities;
  }
  if(martial_type == OrganizedRanged){
    vector<Ability> OrgRangedAbilities ={ QuickDraw ,SurpiseAttack, ScoundrelsFeint,CourtlyGrace,CollaborativeTheivery, Pickpocket, DenyAdvantage ,Mobility, NimbleDodge,TrickAttack,SentrysAim,GangUp};
    Abilities = OrgRangedAbilities;
  }
  else{
    vector<Ability> DisOrgRangedAbilities ={ QuickDraw ,SurpiseAttack, ScoundrelsFeint,CollaborativeTheivery, Pickpocket, DenyAdvantage ,Mobility, NimbleDodge,TrickAttack,SentrysAim,CraftSnare, HuntPrey,ForestWalker,SentrysAim,GangUp};
    Abilities = DisOrgRangedAbilities;
  }
  return abilities_text(default_ability, Abilities, level,2);
}
vector<string_view>  get_noble_abilities(int level,MartialTypes martial_type, MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  const Ability * default_ability = &CourtlyGrace;
  vector<Ability> Abilities = {CallToAction,LieToMe, AirOfAuthority,Bravery,TrickAttack};
  return abilities_text(default_ability, Abilities, level,2);
}
vector<string_view>  get_magic_user_abilities(int level,MartialTypes martial_type, MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  const Ability *default_ability = &FontOfKnowledge;
  vector<Ability> MagicAbilities;
  if(magic_type == Arcane || magic_type == Occult){
    vector<Ability> ArcaneAbilites = { SteadySpellcasting,Smite,CounterSpell};
    MagicAbilities = ArcaneAbilites;
  }
  else if(magic_type == Divine){
  vector<Ability> DivineAbilites = {SteadySpellcasting,Smite,CounterSpell,HealingHands};
    MagicAbilities = DivineAbilites;
  }
  else{
    vector<Ability> PrimalAbilites = {SteadySpellcasting,Smite,CounterSpell,HealingHands,ForestWalker,HuntPrey};
    MagicAbilities = PrimalAbilites;
  }
  return abilities_text(default_ability, MagicAbilities, level,2);
}
vector<string_view> get_magic_using_thief_abilities(int level,MartialTypes martial_type, MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  const Ability * default_ability = &SneakAttack;
  vector<Ability> Abilities;
  if(martial_type == OrganizedMelle){
    vector<Ability> OrgMelleAbilities ={ QuickDraw ,SurpiseAttack, ScoundrelsFeint,CourtlyGrace,CollaborativeTheivery, Pickpocket, DenyAdvantage ,Mobility, NimbleDodge,TrickAttack,GangUp};
    Abilities = OrgMelleAbilities;
  }
  if(martial_type == DisorganizedMelle){
    vector<Ability> OrgMelleAbilities ={ QuickDraw ,SurpiseAttack, ScoundrelsFeint,CollaborativeTheivery, Pickpocket, DenyAdvantage ,Mobility, NimbleDodge,TrickAttack,SentrysAim,CraftSnare, HuntPrey,ForestWalker,GangUp};
    Abilities = OrgMelleAbilities;
  }
  if(martial_type == OrganizedRanged){
    vector<Ability> OrgMelleAbilities ={ QuickDraw ,SurpiseAttack, ScoundrelsFeint,CourtlyGrace,CollaborativeTheivery, Pickpocket, DenyAdvantage ,Mobility, NimbleDodge,TrickAttack,SentrysAim,GangUp};
    Abilities = OrgMelleAbilities;
  }
  else{
    vector<Ability> OrgMelleAbilities ={ QuickDraw ,SurpiseAttack, ScoundrelsFeint,CollaborativeTheivery, Pickpocket, DenyAdvantage ,Mobility, NimbleDodge,TrickAttack,SentrysAim,CraftSnare, HuntPrey,ForestWalker,SentrysAim,GangUp};
    Abilities = OrgMelleAbilities;
  }
  vector<Ability> MagicAbilities;
  if(magic_type == Arcane || magic_type == Occult){
    vector<Ability> ArcaneAbilites = { SteadySpellcasting,Smite,CounterSpell};
    MagicAbilities = ArcaneAbilites;
  }
  else if(magic_type == Divine){
    vector<Ability> DivineAbilites = {SteadySpellcasting,Smite,CounterSpell,HealingHands};
    MagicAbilities = DivineAbilites;
  }
  else{
    vector<Ability> PrimalAbilites = {SteadySpellcasting,Smite,CounterSpell,HealingHands,ForestWalker,HuntPrey};
    MagicAbilities = PrimalAbilites;
  }
  vector<string_view> out =  abilities_text(default_ability,Abilities, level, 1);
  vector<string_view> maot = abilities_text(NULL, MagicAbilities, level,1);
  for(size_t i = 0; i<maot.size(); i++){
    out.push_back(maot[i]);
  }
  return out;
}
vector<string_view>  get_priest_abilities(int level, MartialTypes martial_type, MagicTypes magic_type){
  (void)martial_type;
  (void)magic_type;
  vector<Ability>Abilities = {CallToAction,LieToMe, AirOfAuthority, Bravery,Bravery,TrickAttack};
  return abilities_text(NULL, Abilities, level,1);
}

std::ostream& operator<<(std::ostream& os, const MagicTypes magic_type){
    const std::string_view lut[] = {"MagicNONE","Arcane", "Divine", "Primal","Occult"};
    os<<lut[magic_type];
    return os;
}
std::ostream& operator<<(std::ostream& os, const MartialTypes martial_type){
  const std::string_view lut[] = {"MartialNONE","OrganizedRanged","OrganizedMelle", "DisorganizedRanged","DisorganizedMelle"};
  os <<lut[martial_type];
  return os;
}