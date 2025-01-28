/*
CSCI235 Spring 2024
Project 4 - Cavern Class
Jeremiah Gonzalez
Mar 18 2024 
Dragon.cpp implements the constructors and private and public functions of the Dragon class
Where we are adding a display and eatMycoMorsel function 
*/

#include "Dragon.hpp"

Dragon::Dragon() : element_{NONE}, number_of_heads_{1}, flight_{false}
{
    setCategory(MYSTICAL); 
    
}


Dragon::Dragon(const std::string& name, Category category, int hitpoints, int level, bool tame, Element element, int number_of_heads, bool flight) : Creature(name, category, hitpoints, level, tame)
{
    element_ = element;
    if(!setNumberOfHeads(number_of_heads))
    {
        number_of_heads_ = 1;
    }
    flight_ = flight;
}

std::string Dragon::getElement() const
{
    switch(element_)
    {
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case EARTH:
            return "EARTH";
        case AIR:
            return "AIR";
        default:
            return "NONE";
    }
}

void Dragon::setElement(const Element& element)
{
    element_ = element;
}

int Dragon::getNumberOfHeads() const
{
    return number_of_heads_;
}

bool Dragon::setNumberOfHeads(const int& number_of_heads)
{
    if(number_of_heads > 0)
    {
        number_of_heads_ = number_of_heads;
        return true;
    }
    else
    {
        return false;
    }
}

bool Dragon::getFlight() const
{
    return flight_;
}

void Dragon::setFlight(const bool& flight)
{
    flight_ = flight;
}

/**
    @post     : displays Dragon data in the form:
    "DRAGON - [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [HITPOINTS]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]\n
    ELEMENT: [ELEMENT]\n
    HEADS: [NUMBER OF HEADS]\n
    IT [CAN/CANNOT] FLY\n"
    
    Example:
    DRAGON - JHIZARD
    CATEGORY: ALIEN
    HP: 7
    LVL: 5
    TAME: TRUE
    ELEMENT: FIRE
    HEADS: 3
    IT CAN FLY
*/

void Dragon::display() const{

    std::cout << "DRAGON - " << getName()
    << "\nCATEGORY: " << getCategory() 
    << "\nHP: " << getHitpoints() 
    << "\nLVL: " << getLevel() 
    << "\nTAME: " << (isTame() ? "TRUE" : "FALSE") 
    << "\nELEMENT: " << getElement() 
    << "\nHEADS: " << getNumberOfHeads() 
    << "\nIT " << (getFlight()  ? "CAN" : "CANNOT") << " FLY " << std::endl;

}

/**
    @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. 
              It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
              If the creature is an ALIEN, it consumes the mushroom and gains 1 additional hitpoint. Nothing else happens.
              If the creature is MYSTICAL, it consumes the mushroom and gains 1 additional hitpoint if it has FIRE or EARTH affinity (Either by cooking the mushroom first, or by being fungi-tolerant). Nothing else happens.
              But if it is MYSTICAL and has WATER, AIR, or no affinity, if it only has 1 hitpoint left, it doesn't want to risk it and leaves the Cavern. If it has more than 1 hitpoint, it loses 1 hitpoint and becomes untamed if it was tame. Nothing else happens.
    @return : true if the creature leaves the Cavern, false otherwise
*/

bool Dragon::eatMycoMorsel()  {
    if(getCategory() == "UNDEAD"){  //setting tame to be true if its false 
       if (isTame() == false){
        setTame(true);
       }
     setHitpoints(getHitpoints() + 1);    //giving it an extra hitpoint 
    }

    if (getCategory() == "ALIEN"){
        setHitpoints(getHitpoints() + 1); //gets 1 additional hit points
    }

    if(getCategory() == "MYSTICAL"){
        if(getElement() == "FIRE" || getElement() == "EARTH"){  //fire or earth they gain 1 hitpoint 
            setHitpoints(getHitpoints() + 1);
        }
    }
     if(getElement() == "WATER" || this->getElement() == "AIR" || this->getElement() == "NONE"){   //water or air other thngs happen 
        if(getHitpoints() == 1){
            return true;
        }
        if(getHitpoints() > 1){
            setHitpoints(getHitpoints() - 1);
            setTame(false); //chaning tame if it has 1 hitpoint 
        }
     }
            return false;
}