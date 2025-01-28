/*
CSCI235 Spring 2024
Project 4 - Cavern Class
Jeremiah Gonzalez
Mar 18 2024 
Taven.cpp declares the Cavern class along with its private and public members
breaking down the cvs file using ifstream and sstream to get the information and display it in a different format 
*/
#include "Cavern.hpp"
#include "Creature.hpp"
#include "Ghoul.hpp"
#include "Mindflayer.hpp"
#include "Dragon.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
Cavern::Cavern() : ArrayBag<Creature* >(), level_sum_{0}, tame_count_{0} {
}

/**
    @param: the name of an input file (a string reference)
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
    1. TYPE: An uppercase string [DRAGON, GHOUL, MINDFLAYER]
    2. NAME: An uppercase string
    3. CATEGORY: An uppercase string [ALIEN, MYSTICAL, UNDEAD]
    4. HITPOINTS: A positive integer
    5. LEVEL: A positive integer
    6. TAME: 0 (False) or 1 (True)
    7. ELEMENT/FACTION: Uppercase string or strings representing the ELEMENT (For Dragons), or FACTION (For Ghouls) of the creature. If the creature is of a different subclass, the value will be NONE
    8. HEADS: A positive integer of the number of heads the Dragon has. If the creature is of a different subclass, the value will be 0
    9. FLIGHT/TRANSFORM/SUMMONING: 0 (False) or 1 (True) representing if the creature can fly (Dragons), transform (Ghouls), or summon a Thoughtspawn (Mindflayers).
    10. DECAY: A non-negative integer representing the level of decay of the Ghoul. If the creature is of a different subclass, the value will be 0
    11. AFFINITIES: Only applicable to Mindflayers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. The value may be NONE for a Mindflayer with no affinities, or creatures of other subclasses.
    12. PROJECTILES: Only applicable to Mindflayers. PROJECTILES are of the form [PROJECTILE TYPE1]-[QUANTITY];[PROJECTILE TYPE 2]-[QUANTITY] where multiple types of projectiles are separated by a semicolon. The value may be NONE for a Mindflayer with no projectiles, or creatures of other subclasses.
*/
  //Parameterized Constructor 
  Cavern::Cavern(const std::string& fileName){    //checking to see if file opens or not 

    std::ifstream read(fileName); //reads the file 

    if(!read.is_open()){
      std::cout << "Error: File can't be opened" << std::endl;  //file cant open 
    }
  
  std::string line;

  std::getline(read, line); //reading in the first line 
  
  
  while(std::getline(read, line)){
    
  std::stringstream ssline(line);


  std::string type, name, category, element_fraction, affinity, projectiles, tame, flight_transform_summoning, hitpoints, level, heads, decay;

    std::getline(ssline, type, ',');  // task 1 grabs the line until and stores their corresponding value to its variable, stores in 'type' in this case 
    std::getline(ssline, name, ',');  // task 2
    std::getline(ssline, category, ',');
    std::getline(ssline, hitpoints, ',');
    std::getline(ssline, level, ',');
    std::getline(ssline, tame, ',');
    std::getline(ssline, element_fraction, ',');
    std::getline(ssline, heads, ',');
    std::getline(ssline, flight_transform_summoning, ',');
    std::getline(ssline, decay, ',');
    std::getline(ssline, affinity, ',');
    std::getline(ssline, projectiles, ',');

    //task 3 processing category. converting string to category object. will pass cat into constructor
    Creature::Category cat;

    if(category == "ALIEN"){
      cat = Creature::Category::ALIEN;
    }
    else if(category == "UNDEAD"){
      cat = Creature::Category::UNDEAD;
    }
    else if(category == "MYSTICAL"){
      cat = Creature::Category::MYSTICAL;
    }
    else cat = Creature::Category::UNKNOWN;

    //task 4 process hitpoints. converting string to int. will pass gpts into constructor 
    int hpts = std::stoi(hitpoints);
   
    //task 5 process level . converting string to int.
    int lvl = std::stoi(level);

    //task 6 process tame. converting string to bool.
    bool tam = std::stoi(tame);

    //task 9 process flight, transform, and summoning into bool using sstream
    bool fl_tr_sum;
    std::istringstream(flight_transform_summoning) >> fl_tr_sum;

    //task 7 process element, fraction 

    if(type == "DRAGON"){ //if the object is a Dragon type check the elements and store into a new value ele

     Dragon::Element ele;

    if(element_fraction == "FIRE"){
      ele = Dragon::Element::FIRE;
    }
    else if (element_fraction == "WATER"){
      ele = Dragon::Element::WATER;
    }
    else if(element_fraction == "EARTH"){
      ele = Dragon::Element::EARTH;
    }
    else if(element_fraction == "AIR"){
      ele = Dragon::Element::AIR;
    }
    else ele = Dragon::Element::NONE;

    int drag_heads = std::stoi(heads);  //task 8 process heads. converting string to bool. will pass heads into constructor

    Dragon* New_Dragon = new Dragon(name, cat, hpts, lvl, tam, ele, drag_heads, fl_tr_sum);  //entering new dragon object into cavern  (testing functions)
    enterCavern(New_Dragon);
    }

    if(type == "GHOUL"){  //if the object is a Ghoul type check the fraction and store into a new value fra

    Ghoul::Faction fra; 

    if(element_fraction == "FLESHGORGER"){
      fra = Ghoul::Faction::FLESHGORGER;
    }
    else if (element_fraction == "SHADOWSTALKER"){
      fra = Ghoul::Faction::SHADOWSTALKER;
    }
    else if(element_fraction == "PLAGUEWEAVER"){
      fra = Ghoul::Faction::PLAGUEWEAVER;
    }
    else fra = Ghoul::Faction::NONE;

    int decay_num = std::stoi(decay); //10

    Ghoul* New_Ghoul = new Ghoul(name, cat, hpts, lvl, tam, decay_num, fra, fl_tr_sum);  //entering new Ghoul object into cavern  (testing functions)
    enterCavern(New_Ghoul);

  }

  //task 11 and 12 create projectile vector 
  if (type == "MINDFLAYER"){
  std::vector<Mindflayer::Projectile> vector_projectiles = {};
  std::vector<Mindflayer::Variant> vector_affinities= {};
  
  vector_affinities.clear();  //emptying the vectors 
  vector_projectiles.clear();

  std::string projectilestr; //new variable 
  std::stringstream mindflayerprojectile(projectiles);

  //std::vector<Mindflayer::Projectile> vector_projectiles;

  while(std::getline(mindflayerprojectile, projectilestr, ';')){  //seperate type from quantity 

  std::string quant; //dummy variable 
  std::string project_type;
  int str_quantities;
  std::stringstream mindflayerquantity(projectilestr);

  std::getline(mindflayerquantity, project_type, '-');  //breaking down the csv lines even further 
  std::getline(mindflayerquantity, quant, '-');
  std::istringstream(quant) >> str_quantities;

  //set up a projcetile with that quanitiy and type

    if(project_type == "PSIONIC"){
      vector_projectiles.push_back({Mindflayer::PSIONIC, str_quantities});    //manually pushing the quantities into the vector 
    }
    else if (project_type == "TELEPATHIC"){
     vector_projectiles.push_back({Mindflayer::TELEPATHIC, str_quantities});
    }
    else if(project_type == "ILLUSIONARY"){
     vector_projectiles.push_back({Mindflayer::ILLUSIONARY, str_quantities});
    }
  } 

  std::string affinityies;
  std::stringstream mindflayeraffinity(affinity);

  while(std::getline(mindflayeraffinity, affinityies, ';')){


  if(affinityies == "PSIONIC"){
      vector_affinities.push_back(Mindflayer::PSIONIC);

  }
  else if(affinityies == "TELEPATHIC"){
      vector_affinities.push_back(Mindflayer::TELEPATHIC);

  }
  else if(affinityies == "ILLUSIONARY"){
      vector_affinities.push_back(Mindflayer::ILLUSIONARY);
  } 
    }
    Mindflayer* New_Mindflayer = new Mindflayer(name, cat, hpts, lvl, tam, vector_projectiles, fl_tr_sum, vector_affinities);
    enterCavern(New_Mindflayer);
  }
    }     
      }

bool Cavern::enterCavern(Creature* new_creature) {  
  if (getIndexOf(new_creature) == -1) {
    if (add(new_creature)){
      level_sum_ += new_creature->getLevel();
      if (new_creature->isTame()) {
        tame_count_++;
      }
      return true;
    }
  }
  return false;
}

bool Cavern::exitCavern(Creature* creature_to_remove) {
  if (remove(creature_to_remove)) {
    level_sum_ -= creature_to_remove->getLevel();
    if (creature_to_remove->isTame()) {
      tame_count_--;
    }
    return true;
  }
  return false;
}

int Cavern::getLevelSum() const {
  return level_sum_;
}

int Cavern::calculateAvgLevel() const {
  if (isEmpty()) {
    return 0;
  }
  return round(level_sum_ / getCurrentSize());
}

int Cavern::getTameCount() const {
  return tame_count_;
}

double Cavern::calculateTamePercentage() const {
  if (isEmpty()) {
    return 0;
  }
  double tame_percent = (tame_count_>0) ?  (double(tame_count_) / item_count_) * 100: 0.0;
  // return the tame percentage rounded up to two decimal places

  return std::ceil(tame_percent * 100) / 100;
 
}

int Cavern::tallyCategory(const std::string& category) const {
  if(category != "UNKNOWN" && category != "UNDEAD" && category != "MYSTICAL" && category != "ALIEN") {
    return 0;
  }
  int count = 0;
  for (int i = 0; i < getCurrentSize(); i++) {
    if (items_[i]->getCategory() == category) {
      count++;
    }
  }
  return count;
}

int Cavern::releaseCreaturesBelowLevel(int level) {
  int count = 0;
  if (level < 0) {
    return 0;
  }
  else if (level == 0) {
    count = getCurrentSize();
    clear();
    return count;
  }
  else {
    int size = getCurrentSize();
    for (int i = 0; i < size; i++) {
      if (items_[i]->getLevel() < level) {  //.
        exitCavern(items_[i]);
        count++;
      }
    }
    return count;
  }
}

int Cavern::releaseCreaturesOfCategory(const std::string& category) {
  int count = 0;
  if (category == "ALL") {
    count = getCurrentSize();
    clear();
    return count;
  }
  else if (category != "UNKNOWN" && category != "UNDEAD" && category != "MYSTICAL" && category != "ALIEN") {
    return 0;
  }
  else {
    int size = getCurrentSize();
    for (int i = 0; i < size; i++) {
    if (items_[i]->getCategory() == category) { //.
      exitCavern(items_[i]);
      count++;
    }
  }
  return count;
  }
}

void Cavern::cavernReport() const {
  std::cout << "UNKNOWN: " << tallyCategory("UNKNOWN") << std::endl;
  std::cout << "UNDEAD: " << tallyCategory("UNDEAD") << std::endl;
  std::cout << "MYSTICAL: " << tallyCategory("MYSTICAL") << std::endl;
  std::cout << "ALIEN: " << tallyCategory("ALIEN") << std::endl;
  std::cout << std::endl;

  std::cout << "AVERAGE LEVEL: " << calculateAvgLevel() << std::endl;
  std::cout << "TAME: " << calculateTamePercentage() << "%" << std::endl;
}

    /**
    @post: For every creature in the cavern, displays each creature's information
    */
    void Cavern::displayCreatures() const{
        for(int i = 0; i < getCurrentSize(); i++){
          items_[i]->display();  //items_[i]->display();
        }
    }

    /**
    @param: a string reference to a category
    @post: For every creature in the cavern of the given category (only exact matches to the input string), displays each creature's information

    */
    void Cavern::displayCategory(const std::string& category) const {
        for(int i = 0; i< getCurrentSize(); i++){    //getCurrentSize()    
          if(items_[i]->getCategory() == category){
            items_[i]->display();    //instead of . do I use ->  ?????
          }
        }

    }

    /**
    @post: Every creature in the cavern eats a MycoMorsel.
    */
   void Cavern::mycoMorselFeast() {
      for (int i = 0; i < getCurrentSize(); i++){
        items_[i]->eatMycoMorsel();
      }
   }
