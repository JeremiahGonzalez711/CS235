/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/16/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 2

Project 2 is a program creating classes and useing them to name create and capture Dragons, this part is the interface 
where we use the private variables and public functions to for the user
*/

#include <iostream>
#include "Dragon.hpp"

Dragon::Dragon() : Creature() { //default constructor 
   setCategory(MYSTICAL);
   setElement(NONE);
   setNumberOfHeads(1);
   can_fly_ = false;
}

Dragon::Dragon(const std::string& name, Category c_category, int hitpoints, int level, bool tame, Element e_element, int heads, bool flight)
    : Creature(name, c_category, hitpoints, level, tame), affinity_(e_element), num_heads_(heads), can_fly_(flight) {
    for (int c = 0; c < name.length(); c++) {
        if (!isalpha(name[c])) {
            name_ = "NAMELESS";
            break;
        }
        else 
        {
            name_ = name;
        } 
    }

    for (int i = 0; i < name_.length(); i++) {      //Toupper convers lowercase to uppercase ones
        name_[i] = toupper(name_[i]);
    }

    if (hitpoints <= 0) {       //Ensure hitpoints are atleast 1
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

    is_tame_ = tame;        //set is_tame_ based on the provided boolean value

    switch(c_category) {        //set category on the provided enum value (c_category)
        case UNDEAD : category_ = UNDEAD; break;
        case MYSTICAL : category_ = MYSTICAL; break;
        case ALIEN : category_ = ALIEN; break;
        case UNKNOWN : category_ = UNKNOWN; break;
        default : category_ = UNKNOWN;
    }

    switch(e_element) {
        case NONE : affinity_ = NONE; break;
        case FIRE : affinity_ = FIRE; break;
        case WATER : affinity_ = WATER; break;
        case EARTH : affinity_ = EARTH; break;
        case AIR : affinity_ = AIR; break;
        default : affinity_ = NONE;
    }

    if (heads <= 0) {
        num_heads_ = 1;
    }
    else 
    {
        num_heads_ = heads;
    }

    can_fly_ = flight;

}

/**
  Setter for the element.
  @param      : A reference to the element (an Element enum)
  @post       : The element is set to the value of the parameter.
*/
void Dragon::setElement(const Element& e_element) {
    switch(e_element) {
        case NONE : affinity_ = NONE; break;
        case FIRE : affinity_ = FIRE; break;
        case WATER : affinity_ = WATER; break;
        case EARTH : affinity_ = EARTH; break;
        case AIR : affinity_ = AIR; break;
        default : affinity_ = NONE;
    }
}

/**
  Getter for the element.
  @return     : The element (a string representation of the Element enum)
*/
std::string Dragon::getElement() const {
    std::string element;
    switch(affinity_) {
        case NONE : element = "NONE"; break;
        case FIRE : element = "FIRE"; break;
        case WATER : element = "WATER"; break;
        case EARTH : element = "EARTH"; break;
        case AIR : element = "AIR"; break;
    }
    return element;
}

/**
  Getter for the number of heads.
  @return     : The number of heads (an integer)
*/
int Dragon::getNumberOfHeads() const {
    return num_heads_;
}

/**
  Setter for the number of heads.
  @param      : A reference to the number of heads (an integer)
  @pre        : The number of heads is > 0. Do nothing for invalid values.
  @post       : The number of heads is set to the value of the parameter.
  @return     : True if the number of heads is set, false otherwise.
*/
bool Dragon::setNumberOfHeads(const int& heads) {
    if (heads <= 0) {
        return false;
    }
    else 
    {
        num_heads_ = heads;
        return num_heads_;
    }
}

/**
  Setter for the flight flag.
  @param      : A reference to the flight flag (a boolean)
  @post       : The flight flag is set to the value of the parameter.
*/
void Dragon::setFlight(const bool& flight) {
    can_fly_ = flight;
}

/**
  Getter for the flight flag.
  @return     : The flight flag (a boolean)
*/
bool Dragon::getFlight() const {
    return can_fly_;
}
 void Dragon::display() const
{
    std::cout << "NAME: " << getName() << std::endl;
    std::cout << "CATEGORY: "<< getCategory() << std::endl; 
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    if(isTame()){
         std::cout << "TAME: " << "TRUE" << std::endl;
    }
    else{
         std::cout << "TAME: " << "FALSE" << std::endl;
    }
    std::cout << "ELEMENT: " << getElement() << std::endl;
    std::cout << "HEADS: " << getNumberOfHeads() << std::endl;
    if(getFlight()){
        std::cout << "FLIGHT: " << "TRUE" << std::endl;
    }
    else{
        std::cout << "FLIGHT: " << "FALSE" << std::endl;
    }
}