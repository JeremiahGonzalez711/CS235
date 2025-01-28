/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/8/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 1

Project 1 is a program creating classes and useing them to name create and capture creatures, this part is the interface 
where we use the private variables and public functions to for the user
*/
#include "Creature.hpp"     

Creature::Creature() {      //initalizing all private members (making sure to change all variables to what was stated)

   name_ = "NAMELESS";  //default is nameless

   hitpoints_ = 1;      //default hit points is set to 1

   level_ = 1;      //default level is set to 1 

   is_tame_ = false;        //default tame status is set to false 

   category_ = UNKNOWN;     //default category 
}

Creature::Creature(const std::string &name, Category c_category, int hitpoints, int level, bool tame) 
{
   for (int c = 0; c < name.length(); c++) {        //for loop a reference to the name of the creature (a string)
            if (!isalpha(name[c])) {
               name_ = "NAMELESS";
               break;
            }
            else {
               name_ = name;
            } 
      }

      for (int i = 0; i < name_.length(); i++) {    //toupper converts lowercase to uppercase ones 
            name_[i] = toupper(name_[i]);
      }

      if (hitpoints <= 0) {     // Ensure hitpoints and level are at least 1
            hitpoints_ = 1;
      }
      else 
      {
            hitpoints_ = hitpoints;
      }

      if (level <= 0) {
            level_ = 1;
      }
      else 
      {
            level_ = level;
      }

      is_tame_ = tame;      // Set is_tame_ based on the provided boolean value

      switch(c_category) {  // Set category based on the provided enum value (c_category)
            case UNDEAD : category_ = UNDEAD; break;
            case MYSTICAL : category_ = MYSTICAL; break;
            case ALIEN : category_ = ALIEN; break;
            case UNKNOWN : category_ = UNKNOWN; break;
            default : category_ = UNKNOWN;
      }
}
/**
    @param : the name of the Creature, a reference to string
    @post  : sets the Creature's name to the value of the parameter in UPPERCASE. 
             (convert any lowercase character to uppercase)
             Only alphabetical characters are allowed. 
           : If the input contains non-alphabetic characters, do nothing.
    @return : true if the name was set, false otherwise
*/
bool Creature::setName(const std::string& name) {
   for (int q = 0; q < name.length(); q++) {
         if (!isalpha(name[q])) {
            return false;
            break;
         }
   }
   name_ = name;
   for (int k = 0; k < name_.length(); k++) {
      name_[k] = toupper(name_[k]);
   }
   return true;   
}

 /**
      @return : the name of the Creature
  */
std::string Creature::getName() const {
   return name_;
}

/**
      @param  : a reference to Category, the category of the Creature (an enum)
      @post   : sets the Creature's category to the value of the parameter
              : If the given category was invalid, set category_ to UNKNOWN.
*/
void Creature::setCategory(const Category& n_category) {
   switch(n_category) {
         case UNDEAD : category_ = UNDEAD; break;
         case MYSTICAL : category_ = MYSTICAL; break;
         case ALIEN : category_ = ALIEN; break;
         case UNKNOWN : category_ = UNKNOWN; break;
         default : category_ = UNKNOWN;
   }
}

/**
      @return : the category of the Creature (in string form)
 */
std::string Creature::getCategory() const {
   std::string category;
   switch (category_) {
         case UNDEAD : category = "UNDEAD"; break;
         case MYSTICAL : category = "MYSTICAL"; break;
         case ALIEN : category = "ALIEN"; break;
         case UNKNOWN : category = "UNKNOWN"; break;
   }
   return category;
}

/**
    @param  : a reference to integer that represents the creature's hitpoints
    @pre    : hitpoints >= 0 : Characters cannot have negative hitpoints 
              (do nothing for invalid input)
    @post   : sets the hitpoints private member to the value of the parameter
    @return : true if the hitpoints were set, false otherwise
 */
bool Creature::setHitpoints (const int& hitpoints) {
   if (hitpoints >= 0) {
         hitpoints_ = hitpoints;
         return true;
   }
   else {
         return false;
   }
}

/**
      @return : the value stored in hitpoints_
 */
int Creature::getHitpoints() const {
   return hitpoints_;
}

/**
    @param  : a reference to integer level
    @pre    : level >= 0 : Characters cannot have a negative level
    @post   : sets the level private member to the value of the parameter 
             (do nothing for invalid input)
    @return : true if the level was set, false otherwise
 */
bool Creature::setLevel(const int& level) {
   if (level >= 0) {
         level_ = level;
         return true;
   }
   else return false;
}

/**
      @return : the value stored in level_
*/
int Creature::getLevel() const {
   return level_;
}

/**
      @param  : a reference to boolean value
      @post   : sets the tame flag to the value of the parameter
  */
void Creature::setTame(const bool& tame) {
   is_tame_ = tame;
}

/**
    @return true if the creature is tame, false otherwise
    Note: this is an accessor function and must follow the same convention as all accessor functions even if it is not called getTame
 */
bool Creature::isTame() const {
   return is_tame_;
}

/**
    @post     : displays Creature data in the form:
              "[NAME]\n
               Category: [CATEGORY]\n
               Level: [LEVEL]\n
               Hitpoints: [Hitpoints]\n
               Tame: [TRUE/FALSE]"   
*/
void Creature::display() const {
   std::cout << getName() << std::endl;
   std::cout << "Category: " << getCategory() << std::endl;
   std::cout << "Level: " << getLevel() << std::endl;
   std::cout << "Hitpoints: " << getHitpoints() << std::endl;
   std::cout << "Tame: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
}