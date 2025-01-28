/*
CSCI235 Spring 2024
Project 6 - Creature Training! 
Jeremiah Gonzalez
April 16 2024
Cavern.cpp declares the Cavern class along with its private and public members
*/
#include "Cavern.hpp"
#include <queue>
#include <stack>


Cavern::Cavern() : ArrayBag<Creature*>(), level_sum_{0}, tame_count_{0} {
}

/**
    @param  : the name of an input file
    @pre    : Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
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
            11. AFFINITIES: Only applicable to Mindflayers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Mindflayer with no affinities, or creatures of other subclasses.
            12. PROJECTILES: Only applicable to Mindflayers. PROJECTILES are of the form [PROJECTILE TYPE1]-[QUANTITY];[PROJECTILE TYPE 2]-[QUANTITY] where multiple types of projectiles are separated by a semicolon. The value may be NONE for a Mindflayer with no projectiles, or creatures of other subclasses.
*/
Cavern::Cavern(const std::string& filename)
{
  std::ifstream fin(filename);
  std::string line;
  std::getline(fin, line); //getting junk header
  std::string type, name, str_category, str_hitpoints, str_level, str_tame, str_element, str_heads, str_flight, str_decay, str_affinities, str_projectiles;
  int hitpoints, level, heads, decay;
  bool tame, flight;
  Creature::Category category;
  Dragon::Element element;
  Ghoul::Faction faction;
  std::vector<Mindflayer::Variant> affinities;
  std::vector<Mindflayer::Projectile> projectiles;

  while(std::getline(fin, line))
  {
    std::istringstream iss(line);
    std::getline(iss, type, ',');
    std::getline(iss, name, ',');
    std::getline(iss, str_category, ',');
    std::getline(iss, str_hitpoints, ',');
    std::getline(iss, str_level, ',');
    std::getline(iss, str_tame, ',');
    std::getline(iss, str_element, ',');
    std::getline(iss, str_heads, ',');
    std::getline(iss, str_flight, ',');
    std::getline(iss, str_decay, ',');
    std::getline(iss, str_affinities, ',');
    std::getline(iss, str_projectiles, ',');

    std::istringstream(str_hitpoints) >> hitpoints;
    std::istringstream(str_level) >> level;
    std::istringstream(str_tame) >> tame;
    std::istringstream(str_heads) >> heads;
    std::istringstream(str_flight) >> flight;
    std::istringstream(str_decay) >> decay;

    // Convert the category to the category enum
    if(str_category == "ALIEN")
    {
      category = Creature::ALIEN;
    }
    else if(str_category == "MYSTICAL")
    {
      category = Creature::MYSTICAL;
    }
    else if(str_category == "UNDEAD")
    {
      category = Creature::UNDEAD;
    }
    else
    {
      category = Creature::UNKNOWN;
    }

    if(type == "DRAGON")
    {
      if(str_element == "FIRE")
      {
        element = Dragon::FIRE;
      }
      else if(str_element == "WATER")
      {
        element = Dragon::WATER;
      }
      else if(str_element == "EARTH")
      {
        element = Dragon::EARTH;
      }
      else if(str_element == "AIR")
      {
        element = Dragon::AIR;
      }
      else
      {
        element = Dragon::NONE;
      }
      Dragon* new_dragon = new Dragon(name, category, hitpoints, level, tame, element, heads, flight);
      enterCavern(new_dragon);
    }
    else if(type == "GHOUL")
    {
      if(str_element == "FLESHGORGER")
      {
        faction = Ghoul::FLESHGORGER;
      }
      else if(str_element == "SHADOWSTALKER")
      {
        faction = Ghoul::SHADOWSTALKER;
      }
      else if(str_element == "PLAGUEWEAVER")
      {
        faction = Ghoul::PLAGUEWEAVER;
      }
      
      else
      {
        faction = Ghoul::NONE;
      }

      Ghoul* new_ghoul = new Ghoul(name, category, hitpoints, level, tame, decay, faction, flight);
      enterCavern(new_ghoul);
    }
    else if(type == "MINDFLAYER")
    {
      //clear the affinities and projectiles vectors
      affinities.clear();
      projectiles.clear();
      // Read the affinities
      std::string affinity;
      std::istringstream iss_affinities(str_affinities);
      while(std::getline(iss_affinities, affinity, ';'))
      {
        // Convert the affinity to the enum
        if(affinity == "PSIONIC")
        {
          affinities.push_back(Mindflayer::PSIONIC);
        }
        else if(affinity == "TELEPATHIC")
        {
          affinities.push_back(Mindflayer::TELEPATHIC);
        }
        else if(affinity == "ILLUSIONARY")
        {
          affinities.push_back(Mindflayer::ILLUSIONARY);
        }
        
      }

      // Read the projectiles
      std::string projectile;
      std::istringstream iss_projectiles(str_projectiles);
      while(std::getline(iss_projectiles, projectile, ';'))
      {
        std::string type;
        int quantity;
        Mindflayer::Projectile new_projectile;
        std::istringstream iss_projectile(projectile);
        std::getline(iss_projectile, type, '-');
        std::getline(iss_projectile, str_projectiles, '-');
        std::istringstream(str_projectiles) >> quantity;
        if(type == "PSIONIC")
        {
          new_projectile.type_ = Mindflayer::PSIONIC;
        }
        else if(type == "TELEPATHIC")
        {
          new_projectile.type_ = Mindflayer::TELEPATHIC;
        }
        else if(type == "ILLUSIONARY")
        {
          new_projectile.type_ = Mindflayer::ILLUSIONARY;
        }
        new_projectile.quantity_ = quantity;
        projectiles.push_back(new_projectile);
      }
      Mindflayer* new_mindflayer = new Mindflayer(name, category, hitpoints, level, tame, projectiles, flight, affinities);
      enterCavern(new_mindflayer);
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
  return std::ceil(tame_percent*100.0) / 100.0; //round up to to decimal places
 
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
      if (items_[i]->getLevel() < level) {
        exitCavern(items_[i]);
        count++;
      }
    }
    return count;
  }
}

int Cavern::releaseCreaturesOfCategory(std::string category) {
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
    if (items_[i]->getCategory() == category) {
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

void Cavern::displayCreatures() const {
  for (int i = 0; i < getCurrentSize(); i++) {
    items_[i]->display();
  }
}

void Cavern::displayCategory(const std::string& category) const {
  if(category != "UNKNOWN" && category != "UNDEAD" && category != "MYSTICAL" && category != "ALIEN") {
    return;
  }
  for (int i = 0; i < getCurrentSize(); i++) {
    if (items_[i]->getCategory() == category) {
      items_[i]->display();
    }
  }
}

void Cavern::mycoMorselFeast() {
  int size = getCurrentSize();
  for (int i = 0; i < size; i++) {
    if(items_[i]->eatMycoMorsel()) {
      exitCavern(items_[i]);
    }
  }
}

/**
* @post: Stores the ALIEN Creatures of highest level in the cavern's alien stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 ALIEN creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 ALIEN Creatures on the stack)       
*      : Empty the stack before beginning.
*/
void Cavern::initializeAlienStack(){

  clearAlienStack();

  int maximum = 0;  //temp variable that hold maximum 

  for(int i = 0; i < getCurrentSize(); i++){  //if the current level is greater than 0 we take it 
    if(items_[i]->getCategory() == "ALIEN"){
      if(items_[i]->getLevel() > maximum){
        maximum = items_[i]->getLevel();  //refresh maximum 
      }
    }
  }
  for(int i = 0; i < getCurrentSize(); i++){  //pushback anything that equals to the highest 
    if(items_[i]->getCategory() == "ALIEN"){
      if(items_[i]->getLevel() == maximum){
        alien_stack_.push(items_[i]);
      }
    }
  }

}

/**
* @post: Stores the UNDEAD Creatures of highest level in the cavern's undead stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 UNDEAD creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 UNDEAD Creatures on the stack)
      : Empty the stack before beginning.
*/
void Cavern::initializeUndeadStack(){

  clearUndeadStack(); //clear stack 

  int maximum = 0;  //temp variable that hold maximum 

  for(int i = 0; i < getCurrentSize(); i++){  //if the current level is greater than 0 we take it 
    if(items_[i]->getCategory() == "UNDEAD"){
      if(items_[i]->getLevel() > maximum){
        maximum = items_[i]->getLevel();  //refresh maximum 
      }
    }
  }
  for(int i = 0; i < getCurrentSize(); i++){  //pushback anything that equals to the highest 
    if(items_[i]->getCategory() == "UNDEAD"){
      if(items_[i]->getLevel() == maximum){
        undead_stack_.push(items_[i]);
      }
    }
  }
}

/**
* @post: Stores the MYSTICAL Creatures of highest level in the cavern's mystical stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 MYSTICAL creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 MYSTICAL Creatures on the stack)
*      : Empty the stack before beginning.
*/
void Cavern::initializeMysticalStack(){

  clearMysticalStack(); //clear stack 

  int maximum = 0;  //temp variable that hold maximum 

  for(int i = 0; i < getCurrentSize(); i++){  //if the current level is greater than 0 we take it 
    if(items_[i]->getCategory() == "MYSTICAL"){
      if(items_[i]->getLevel() > maximum){
        maximum = items_[i]->getLevel();  //refresh maximum 
      }
    }
  }
  for(int i = 0; i < getCurrentSize(); i++){  //pushback anything that equals to the highest 
    if(items_[i]->getCategory() == "MYSTICAL"){
      if(items_[i]->getLevel() == maximum){
        mystical_stack_.push(items_[i]);
      }
    }
  }
}

/**
* @post: Stores the UNKNOWN Creatures of highest level in the cavern's unknown stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 UNKNOWN creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 UNKNOWN Creatures on the stack)
*      : Empty the stack before beginning.
*/
void Cavern::initializeUnknownStack(){

  clearUnknownStack(); //clear stack 

  int maximum = 0;  //temp variable that hold maximum 

  for(int i = 0; i < getCurrentSize(); i++){  //if the current level is greater than 0 we take it 
    if(items_[i]->getCategory() == "UNKNOWN"){
      if(items_[i]->getLevel() > maximum){
        maximum = items_[i]->getLevel();  //refresh maximum 
      }
    }
  }
  for(int i = 0; i < getCurrentSize(); i++){  //pushback anything that equals to the highest 
    if(items_[i]->getCategory() == "UNKNOWN"){
      if(items_[i]->getLevel() == maximum){
       unknown_stack_.push(items_[i]);
      }
    }
  }

}

/**
* @return: A copy of the stack of highest level Aliens in the cavern
*/ 
std::stack<Creature*> Cavern::getAlienStack() const{
    return alien_stack_;
}

/**
* @return: A copy of the stack of highest level Undeads in the cavern
*/
std::stack<Creature*> Cavern::getUndeadStack()const{
    return undead_stack_;
}

/**
* @return: A copy of the stack of highest level Mysticals in the cavern
*/
std::stack<Creature*> Cavern::getMysticalStack()const{
    return mystical_stack_;
}

/**
* @return: A copy of the stack of highest level Unknowns in the cavern
*/
std::stack<Creature*> Cavern::getUnknownStack()const{
    return unknown_stack_;
}

/**
* @post: clears the stack of highest level Aliens in the cavern
*/ 
void Cavern::clearAlienStack(){
  while(!alien_stack_.empty()){
    alien_stack_.pop();
  }
}

/**
* @post: clears the stack of highest level Undeads in the cavern
*/
void Cavern::clearUndeadStack(){
  while(!undead_stack_.empty()){
    undead_stack_.pop();
  }
}

/**
* @post: clears the stack of highest level Mysticals in the cavern
*/
void Cavern::clearMysticalStack(){
  while(!mystical_stack_.empty()){
    mystical_stack_.pop();
  }
}

/**
* @post: clears the stack of highest level Unknowns in the cavern 
*/
void Cavern::clearUnknownStack(){
  while(!unknown_stack_.empty()){
    unknown_stack_.pop();
  }
}

/**
  * @param: A stack of creature pointers 
  * @pre:  All the creature on the input stack are of same category and same (highest) level
  * @post: For each creature in the stack, rebuild the Cavern's appropriate stack. (For example, if the creatures given are of category ALIEN, this function should build the Cavern's Alien stack.)
  *        Clear the Cavern's stack of the given category before adding the creatures to the stack.
  *        Before adding each creature to the Cavern's stack, prompt the user to select 2 attacks for the creature.
  *        Preserve the order of the creatures in the stack given. (E.g. The creature at the top of the given stack should also become the creature at the top of the Cavern's stack)
  *        If the input is invalid (valid inputs will be 1,2 or 3 only), keep prompting for a non-negative number that is within range, by printing "INVALID INPUT. TRY AGAIN.\n" and prompt for input again.
  *        When a valid action is read, it is passed to the creature's addAttack function to add the corresponding attack to the creature's attack queue.
  *        Prompting for attacks should be done in the following form (hint: use the creature's displayAttacks function):
  *        SELECT 2 ATTACKS FOR [CREATURE NAME] (1-3):
  *        1: [ATTACK 1 NAME]\t\t2: [ATTACK 2 NAME]\t\t3: [ATTACK 3 NAME]
*/
void Cavern::setAttacks(std::stack<Creature*> Creature_stack){

     std::string creature_top = Creature_stack.top()->getCategory(); //saving it into a variable to hold the top

    //clearing each creature stack  
    if(creature_top == "ALIEN"){
      clearAlienStack();
    }
     if(creature_top == "MYSTICAL"){
      clearMysticalStack();
    }
     if(creature_top == "UNDEAD"){
      clearUndeadStack();
    }
     if(creature_top == "UNKNOWN"){
      clearUnknownStack();
    }
    //storing Creatures into new stack 
    std::stack<Creature*> new_stack;

    // Loop through each creature in the input stack
    while (!Creature_stack.empty()) {
        Creature* current_Creature = Creature_stack.top();
        Creature_stack.pop(); //removes top creature from the stack (after I pop I no longer have access to top)

        // Prompt the user to select 2 attacks for the creature
        std::cout << "SELECT 2 ATTACKS FOR " << current_Creature->getName() << "\n";
        current_Creature->displayAttacks();
        // Add attacks to the creature's attack queue
        int attack_1;
        int attack_2;
        
        bool valid_user_Input = false;

        //While the input is true it sets in the attack of the users input 
        while (!valid_user_Input) {
            std::cin >> attack_1;
            if (attack_1 >= 1 && attack_1 <= 3) { //if attack is 1,2,3
                valid_user_Input = true;
            } 
            else {
                std::cout << "INVALID INPUT. TRY AGAIN.\n";
            }
        }
        current_Creature->addAttack(attack_1);  //valid action is read its passed to the creatures addAttack function

        bool valid_user_Input2 = false;
        current_Creature->displayAttacks();

         while (!valid_user_Input2) {
            std::cin >> attack_2;
            if (attack_2 >= 1 && attack_2 <= 3) { //if attack is 1,2,3
                valid_user_Input2 = true;
            } 
            else {
                std::cout << "INVALID INPUT. TRY AGAIN.\n";
            }
        }
        current_Creature->addAttack(attack_2);   //valid action is read its passed to the creatures addAttack function
        new_stack.push(current_Creature); // Add the creature to the temp stack

    }
    //storing new objects into new stacks 
    while(!new_stack.empty())
    {
      if(creature_top == "ALIEN"){
          alien_stack_.push(new_stack.top());
        }
      
      if(creature_top == "MYSTICAL"){
          mystical_stack_.push(new_stack.top());
        }
      
      if(creature_top == "UNDEAD"){
          undead_stack_.push(new_stack.top());
      }
      if(creature_top == "UNKNOWN"){
          unknown_stack_.push(new_stack.top());
      }
      new_stack.pop();
  }
}
