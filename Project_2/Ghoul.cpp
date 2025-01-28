/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/17/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 2

Project 2 is a program creating classes and useing them to name create and capture Ghouls, this part is the interface 
where we use the private variables and public functions to for the user
*/

#include "Ghoul.hpp"

Ghoul::Ghoul() : Creature() {     //default constructor
    setCategory(UNDEAD);
    level_of_decay_ = 0;
    faction_ = NONE;

    can_transform_ = false;
}

Ghoul::Ghoul(const std::string& name, Category c_category, int hitpoints, int level, bool tame, int decay, Faction f_faction, bool transform):Creature(name, c_category, hitpoints, level, tame), level_of_decay_(decay), faction_(f_faction), can_transform_(transform) {
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

    for (int i = 0; i < name_.length(); i++) {
        name_[i] = toupper(name_[i]);
    }

    if (hitpoints <= 0) {
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

    is_tame_ = tame;

    switch(c_category) {
        case UNDEAD : category_ = UNDEAD; break;
        case MYSTICAL : category_ = MYSTICAL; break;
        case ALIEN : category_ = ALIEN; break;
        case UNKNOWN : category_ = UNKNOWN; break;
        default : category_ = UNKNOWN;
    }

    if (decay < 0) {
        level_of_decay_ = 0;
    }
    else 
    {
        level_of_decay_ = decay;
    }

    switch(f_faction) {
        case NONE : faction_ = NONE; break;
        case FLESHGORGER : faction_ = FLESHGORGER; break;
        case SHADOWSTALKER : faction_ = SHADOWSTALKER; break;
        case PLAGUEWEAVER : faction_ = PLAGUEWEAVER; break;
        default : faction_ = NONE;
    }

    can_transform_ = transform;

}

/**
  Setter for the level of decay.
  @param      : A reference to the level of decay (an integer)
  @pre        : The level of decay must be >= 0 (do nothing otherwise)
  @post       : The level of decay is set to the value of the parameter.
  @return     : true if the level of decay was set, false otherwise
*/
bool Ghoul::setDecay(const int& decay) {
    if (decay < 0) {
        return false;
    }
    else 
    {
        level_of_decay_ = decay;
        return true;
    }
}

/**
  Getter for the level of decay.
  @return     : The level of decay (an integer)
*/
int Ghoul::getDecay() const {
    return level_of_decay_;
}

/**
  Setter for the faction.
  @param      : A reference to the faction (a Faction enum)
  @post       : The faction is set to the value of the parameter.
*/
void Ghoul::setFaction(const Faction& f_faction) {
    switch(f_faction) {
        case NONE : faction_ = NONE; break;
        case FLESHGORGER : faction_ = FLESHGORGER; break;
        case SHADOWSTALKER : faction_ = SHADOWSTALKER; break;
        case PLAGUEWEAVER : faction_ = PLAGUEWEAVER; break;
        default : faction_ = NONE;
    }
}

/**
  Getter for the faction.
  @return     : The faction (a string representation of the Faction enum)
*/
std::string Ghoul::getFaction() const {
    std::string faction;
    switch(faction_) {
        case NONE : faction = "NONE"; break;
        case FLESHGORGER : faction = "FLESHGORGER"; break;
        case SHADOWSTALKER : faction = "SHADOWSTALKER"; break;
        case PLAGUEWEAVER : faction = "PLAGUEWEAVER"; break;
    }
    return faction;
}

/**
  Setter for the transformation.
  @param      : A reference to the transformation (a boolean)
  @post       : The transformation is set to the value of the parameter.
*/
void Ghoul::setTransformation(const bool& transform) {
    can_transform_ = transform;
}

/**
  Getter for the transformation.
  @return     : The transformation (a boolean)
*/
bool Ghoul::getTransformation() const {
    return can_transform_;
}

void Ghoul::display() const
{
    std::cout << "NAME: " << getName() << std::endl;
    std::cout << "CATEGORY: "<< getCategory() << std::endl; 
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    if(isTame() == 1){
         std::cout << "TAME: " << "TRUE" << std::endl;
    }
    else{
         std::cout << "TAME: " << "FALSE" << std::endl;
    }
    std::cout << "DECAY: " << getDecay() << std::endl;
    std::cout << "FACTION: " << getFaction() << std::endl;
    if(getTransformation() == 1){
        std::cout << "TRANSFORM: " << "TRUE" << std::endl;
    }
    else{
        std::cout << "TRANSFORM: " << "FALSE" << std::endl;
    }
}