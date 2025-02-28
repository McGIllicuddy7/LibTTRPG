#include "personality.hpp"
#include "Names.hpp"
#include "Utils.hpp"
#include "types.hpp"
 string rand_first_name(vector<string> BaseArray, EGender Gender){
    int s = random_int()%100;
    if(s<25){ return (Gender == Female ? random_element(HumanFemmeFirstNames) :random_element(HumanMascFirstNames));}
    if(s<50){return (Gender == Female ? random_element(GiffFemmeFirstnames) :random_element(GiffMascFirstNames));}
    if(s<75){return (Gender == Female ? random_element(TieflingFemmeFirstNames) :random_element(TieflingMascFirstNames));}
    return random_element(BaseArray);
  }
   string rand_last_name(vector<string> BaseArray){
    int s = random_int()%100;
    if(s<25){ return random_element(humanLastNames);}
    if(s<50){return random_element(GiffLastnames);}
    if(s<75){random_element(TieflingLastNames);}
    return random_element(BaseArray);
  }
    EGender generate_gender(void){
    int s = random_int()%100;
    if(s<45){
      return Female;
    }
    if(s<90){
      return  Male;
    }
    return Nonbinary;
  };
  string generate_name(EAncestries Ancestry, EGender Gender){
    EAncestries a = Ancestry;
    EGender g = Gender;
    if(Gender == Nonbinary){
      if(random_int()%100<50){
        g = Female;
      }
      else{
        g = Male;
      }
    }
    if(random_int()%100<90){a = random_ancestry();}
    vector<string> FnameArray = TieflingFemmeFirstNames;
    if(a == Catfolk){FnameArray = ( g == Female ? HalflingFemmeFirstNames : HalflingMascFirstNames);}
    if(a == Dwarf){FnameArray = ( g == Female ? DwarfFemmeFirstNames : DwarfMascFirstNames);}
    if(a == Elf){FnameArray =( g == Female ? ElfFemmeFirstNames : ElfMascFirstNames);}
    if(a == Goblin){FnameArray =( g == Female ? GoblinFemmeFirstNames : GoblinMascFirstNames);}
    if(a == Gnome){FnameArray = GnomeFirstNames;}
    if(a == Halfling){FnameArray = ( g == Female ? HalflingFemmeFirstNames : HalflingMascFirstNames);}
    if(a == Human){FnameArray = ( g == Female ? HumanFemmeFirstNames : HumanMascFirstNames);}
    if(a == Orc){FnameArray = ( g == Female ? OrcFemmeFirstNames : OrcMascFirstNames);}
    string FirstName = rand_first_name(FnameArray, g);
    EAncestries b = Ancestry;
    vector<string> LnameArray = TieflingLastNames;
    if(random_int()%100<80){b = random_ancestry();}
    if(b == Catfolk){LnameArray = HalflingLastNames;}
    if(b == Dwarf){LnameArray = DwarfLastNames;}
    if(b == Elf){LnameArray = ElfLastNames;}
    if(b == Goblin){LnameArray = GoblinLastNames;}
    if(b == Gnome){LnameArray = GnomeLastNames;}
    if(b == Halfling){LnameArray = HalflingLastNames;}
    if(b == Human){LnameArray = humanLastNames;}
    if(b == Orc){LnameArray = OrcLastNames;}
    string LastName = rand_last_name(LnameArray);
    return FirstName+" "+LastName;
  }
  static vector<string> Sanity = {"Sanity: Very Stable", "Sanity: Normal","Sanity: Normal", "Sanity: Normal","Sanity: Normal", "Sanity :Normal", "Sanity: Neurotic", "Sanity: Unstable", "Sanity: Insane", "Sanity: Maniacal"};
  static vector<string> GeneralTendencies = {"Optimist", "Pessimist", "Hedonist", "Altruist", "Kindly","Careless", "Carpcious", "Mischievious",
    "Sober", "Moody","Inquisitive","Trusting", "Suspicious","Cautious", "Precise", "Exacting", "Perceptive", "Opinionated", "Contrarian", "Violent", "Sudious",
    "Foul","Cruel","Callous", "Prankster","Servile","Obseqious","Fanatical", "Obsessive", "Maleovolent", "Loquacious"};
  static vector<string> AveragePersonality = {"Modest","Agoist", "Arrogant", "Friendly","Aloof","Hostile", "Well Spoken", "Diplomatic", "Abrasitve"};
  static vector<string> ExtrovertedPersonality = {"Forceful","Overbearing", "Friendly","Blustering","Antagonistic", "Rude", "Rash","Diplomatic"};
  static vector<string> IntrovertedPersonality = {"Retiring","Taciturn","Friendly","Aloof","Hostile","Rude","Courteous","Solidary","Secretive"};
  static vector<string> Disposition = {"Cheerful","Morose", "Compassionate","Sensitive","Unfeeling","Insensitive","Humble","Proud","Haughty","Even Tempered","Easy Going","Harsh"};
  static vector<string> PersonalityNature = {"Soft Hearted","Forgiving","Hard Hearted","Unforgiving","Jealous","Vengeful"};
  static vector<string> PersonalityMaterialism = {"Materialism: Aestethic","Materialism: Intellectualist", "Materialism: Average", "Materialism: Covetous","Materialism: Greedy",
    "Materialism: Avaricious"};
  static vector<string> PersonalityHonesty = {"Scrupulous", "Very Honorable","Truthful","Average Honesty","Average Honesty","Average Honesty","Liar","Decietful"};
  static vector<string> PersonalityBravery = {"Normal Bravery", "Normal Bravery", "Normal Bravery","Foolhardy","Brave","Fearless","Cowardly","Craven"};
  static vector<string> PersonalityEnergy = {"Slothful","Lazy","Normal Energy","Normal Energy","Normal Energy","Energetic","Energetic","Driven"};
  static vector<string> PersonalityThrift = {"Miserly","Mean Thrift","Thrifty","Average Thrift","Average Thrift","Spendthrift","Spendthrift","Wastrel"};
  static vector<string> PersonalityMorals = {"Aesthetic Morals","Virtous Morals","Normal Morals","Normal Morals","Lusty Morals","Lusty Morals","Lustful Morals","Immoral",
    "Amoral","Perverted","Depraved","Sadistic"};
  static vector<string> PersonalityPiety = {"Saintly","Zealot","Pious","Reverent","Average Piety","Average Piety","Average Piety","Average Piety","Average Piety","Impious",
    "Irreverent","Iconoclastic","Irreligious"};
  static vector<string> Interests = {"Interested in: Religion","Interested in: Legends","Interested in: History","Interested in: Nature",
    "Interested in: Horticulture","Interested in: Animal Husbandry","Interested in: Exotic Animals","Interested in: Hunting","Interested in: Fishing","Interested in: Handicrafts",
    "Interested in: Athletics","Interested in: Politics","Interested in: Wine and Spirits","Interested in: Foods and Preperation","Interested in: Gambling",
    "Interested in: Drugs","Knife and Dagger Collector","Sword Collector","Weapon Collector","Weapon Collector","Shield and Weapon Collector","Armor Collector","Book and Scroll Collector","Mineral and Gem Collector","Ornament and Jewelry Collector","Coin and Token Collector",
    "Trophy and Skin Collector","Porcelain,China, and Crystal Collector","Art Collector","Interested in: Community Service","Interested in: Altruism","Interested in: Not Much"
  };
  vector<string> generate_personality(void){
    vector<string> Personality;
    int r;
    r = roll_dice("1d10");
    if(r>8){ r = roll_dice("1d10");}
    Personality.push_back(Sanity[r-1]);
    Personality.push_back(random_element(GeneralTendencies));
    r = roll_dice("1d8");
    if(r<6){
      Personality.push_back(random_element(AveragePersonality));
    }
    else if(r<8){
      Personality.push_back(random_element(ExtrovertedPersonality));
    }
    else{
      Personality.push_back(random_element(IntrovertedPersonality));
    }
    Personality.push_back(random_element(Disposition));
    Personality.push_back(random_element(PersonalityNature));
    Personality.push_back(random_element(PersonalityMaterialism));
    Personality.push_back(random_element(PersonalityHonesty));
    Personality.push_back(random_element(PersonalityBravery));
    Personality.push_back(random_element(PersonalityEnergy));
    Personality.push_back(random_element(PersonalityThrift));
    r = roll_dice("1d12");
    if(r>9){
      r = roll_dice("1d12");
    }
    Personality.push_back(PersonalityMorals[r-1]);
    Personality.push_back(random_element(PersonalityPiety));
    Personality.push_back(random_element(Interests));
    return Personality;
  }
size_t generate_age(EAncestries ancestry, size_t level){
    size_t out = 0;
    size_t lv_mult = 1;
    if(ancestry == Dwarf){
      lv_mult = 5;
      out = 30+roll_dice("15d20");
      for(int i =0; i<6; i++){
        size_t tmp = 30+roll_dice("15d20");
        if(tmp<out){
          out = tmp;
        }
      }
    } else if (ancestry == Elf){
      lv_mult = 10;
      out = 30+roll_dice("40d20");
      for(int i =0; i<6; i++){
        size_t tmp = 30+roll_dice("40d20");
        if(tmp<out){
          out = tmp;
        }
      }
    } else if (ancestry == Halfling){
      lv_mult = 2;
      out = 30+roll_dice("5d20");
        for(int i =0; i<2; i++){
          size_t tmp = 30+roll_dice("5d20");
          if(tmp<out){
            out = tmp;
          }
        }
    } else if(ancestry == Gnome){
      lv_mult = 3;
      out = 30+roll_dice("20d20");
      for(int i =0; i<6; i++){
        size_t tmp = 30+roll_dice("20d20");
        if(tmp<out){
          out = tmp;
        }
      }
    } else if(ancestry == Human || ancestry ==Goblin || ancestry == Orc || ancestry == Catfolk){       
      out = 14+roll_dice("4d20");
      for(int i =0; i<50; i++){
        size_t tmp = 14+roll_dice("4d20");
        if(tmp<out){
          out = tmp;
        }
      }
    } 
    out += lv_mult*level;
    return out;
}