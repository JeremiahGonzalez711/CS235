/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 3/1/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 3

Project 3 is creating the Cavern class 
this part is to define the constructors and private and public function implementation of the Cavern class
*/
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Cavern.hpp"

/**
  Default constructor.
  Default-initializes all private members. 
*/

Cavern::Cavern():ArrayBag<Creature>(){

    level_sum_ = 0;
    tame_count_ = 0;
}

/** 
  * @param   :   A reference to a Creature entering the Cavern
  * @post    :   If the given Creature is not already in the Cavern, add Creature to the Cavern and updates the level sum and the tame Creature count if the creature is tame.
  * @return  :   returns true if a Creature was successfully added to the Cavern, false otherwise
            :    Hint: Use the above definition of equality will help determine if a Creature is already in the Cavern
**/
//Ta help 
bool Cavern::enterCavern(const Creature& enterCreature){
    if(contains(enterCreature)){    //checking if anything is in the cavern beforehand 
        return false;
    }
    if (add(enterCreature)){     //attempting to add the creature if its not already added 
        level_sum_ += enterCreature.getLevel();     //increase tavern level by creature level 
        if(enterCreature.isTame()){     //check if creature is tamed and adds it to the count 
            tame_count_++;
        }
        return true;        //return if it successfully etered 
    }
    return false;       //return false if not 
}  



/** 
  * @param   :   A  reference to a Creature leaving the Cavern
  * @return  :  returns true if a creature was successfully removed from the Cavern (i.e. items_), false otherwise
  * @post    :   removes the creature from the Cavern and updates the level sum. 
                If the Creature is tame it also updates the tame count.
**/
//Ta help
bool Cavern::exitCavern(const Creature& exitCreature){
    if(remove(exitCreature)){
        //std::cout << "worked";
        level_sum_ -= exitCreature.getLevel();
        if(exitCreature.isTame()){
            tame_count_--;
        }
        return true;
    }
    //std::cout << "didn not work";
    return false;
}

/** 
    * @return   :  The integer level count of all the creatures currently in the Cavern
**/

int Cavern::getLevelSum() const{
    return level_sum_;
}

/**
  * @return   :  The average level (int) of all the creatures in the Cavern
  * @post     :  Computes the average level (double) of the Cavern rounded to the NEAREST integer.
 **/

int Cavern::calculateAvgLevel() const{

    if(getCurrentSize() == 0 ){
        return 0;
    }

    if(getLevelSum() == 0 ){
        return 0;
    }

    int roundedAverage = std::round(( getLevelSum() / getCurrentSize()));

    return roundedAverage;
}

/**
  * @return   :  The integer count of tame Creatures in the Cavern
**/
int Cavern::getTameCount() const{
    return tame_count_;
}

/**
  * @return   :  The percentage (double) of all the tame creatures in the Cavern
  * @post     :   Computes the percentage of tame creatures in the Cavern rounded up to 2 decimal places.
**/
double Cavern::calculateTamePercentage() const{

    if(getCurrentSize() == 0 ){
        return 0;
    }

    double enemyPercentage = (tame_count_ * 100.0) / item_count_;
    return std::ceil(enemyPercentage * 100) /100.0;       //rounding 2 decimal places 
}

/**
  * @param  :  A reference to a string representing a creature Category with value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"]
  * @return :  An integer tally of the number of creatures in the Cavern of the given category. 
              If the argument string does not match one of the expected category values, the tally is zero. 
              NOTE: no pre-processing of the input string necessary, only uppercase input will match.
**/
//Ta help 
int Cavern::tallyCategory(const std::string& category) const{
    int creatureTally = 0;

    for(int i = 0; i <item_count_; i++){
        if(items_[i].getCategory() == category){
            creatureTally++;
        }
    }
    return creatureTally;
}

/**
    @param  :   An integer representing the level threshold of the creatures to be removed from the Cavern, with default value 0
    @post   :   Removes all creatures from the Cavern whose level is less than the given level. If no level is given, removes all creatures from the Cavern. Ignore negative input.
    @return :   The number of creatures removed from the Cavern
*/
//Ta help 
int Cavern::releaseCreaturesBelowLevel( int low_lvl) {

    int remove = 0;     //Variable to count the number of creatures removed 

    for(int i = getCurrentSize() - 1; i >= 0; --i ){ // Check if the level of the creature at index i is below the specified low_lvl
        if(low_lvl >= 0 && items_[i].getLevel() < low_lvl ){ // Also, ensure that low_lvl is non-negative
            exitCavern(items_[i]);   // If the condition is true, remove the creature at index i from the cavern
            remove++;
        }
    }
    return remove;
}

/**
    @param  : A reference to a string representing a creature Category with a value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"], or default value "ALL" if no category is given
    @post   : Removes all creatures from the Cavern whose category matches the given category. If no category is given, removes all creatures from the Cavern.
    @return : The number of creatures removed from the Cavern
              NOTE: no pre-processing of the input string necessary, only uppercase input will match. If the input string does not match one of the expected category values, do not remove any creatures.
*/
int Cavern::releaseCreaturesOfCategory(const std::string& category) {
    int release = 0;  // Variable to count the number of creatures removed

    for (int i = getCurrentSize() - 1; i >= 0; --i) {   // going through the creatures in the cavern want to know everyone in there 
        std::string creatureCategory = items_[i].getCategory();

        if (category == "ALL" || creatureCategory == category) {        //if the creature category is all or Checks if the category matches the given category or if no category is given
            
            exitCavern(items_[i]);  // Remove the creature from the cavern

            release++;  // Increment the count of removed creatures
        }
    }

    return release;

}

/**
  * @post    : Outputs a report of the creatures currently in the Cavern in the form:
              "UNKNOWN: [x]\nUNDEAD: [x]\nMYSTICAL: [x]\nALIEN: [x]\n\nAVERAGE LEVEL: [x]\nTAME:[x]%\n"
              Note that the average level should be rounded to the NEAREST integer, and the percentage of tame creatures in the Cavern should be rounded to 2 decimal places.

              Example output: 
              UNKNOWN: 1
              UNDEAD: 3
              MYSTICAL: 2
              ALIEN: 1

              AVERAGE LEVEL: 5
              TAME: 85.72%
*/
void Cavern::cavernReport() const{

    std::cout << "UNKNOWN: " << tallyCategory("UNKNOWN") << std::endl;
    std::cout << "UNDEAD: " << tallyCategory("UNDEAD") << std::endl;
    std::cout << "MYSTICAL: " << tallyCategory("MYSTICAL") << std::endl;
    std::cout << "ALIEN: " << tallyCategory("ALIEN") << std::endl;

    std::cout << "AVERAGE LEVEL: " << calculateAvgLevel() << std::endl;
    std::cout << "TAME: " << calculateTamePercentage() << "%" << std::endl << std::endl;
}