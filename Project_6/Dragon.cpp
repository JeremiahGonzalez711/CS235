/*
CSCI235 Spring 2024
Project 6 - Creature Training! 
Jeremiah Gonzalez
April 16 2024
Dragon.cpp implements the constructors and private and public functions of the Dragon class
*/

#include "Dragon.hpp"
#include <queue>
#include <stack>

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


void Dragon::display() const
{
    std::cout << "DRAGON - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "ELEMENT: " << getElement() << std::endl;
    std::cout << "HEADS: " << getNumberOfHeads() << std::endl;
    std::cout << "IT " << (getFlight() ? "CAN" : "CANNOT") << " FLY" << std::endl;
}



bool Dragon::eatMycoMorsel()
{
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "ALIEN")
    {
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "MYSTICAL")
    {
        if(getElement() == "FIRE" || getElement() == "EARTH")
        {
            setHitpoints(getHitpoints() + 1);
            return false;
        }
        else if(getHitpoints() == 1)
        {
            return true;
        }
        else
        {
            setHitpoints(getHitpoints() - 1);
            setTame(false);
            return false;
        }
    }
    else
    {
        return false;
    }
}

/**
  * @param: A const reference to int corresponding to the attack to be added to the attack queue.
  * @post: Adds an attack to the attack queue based on the int parameter.
  * Here are the attacks for the Dragon:
  
* 1: Attack name: BITE
*      if ALIEN: 4 PHYSICAL
*      if MYSTICAL: 2 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 2 PHYSICAL, 1 POISON
*      if UNKNOWN: 2 PHYSICAL

* 2: Attack name: STOMP
*      if ALIEN: 2 PHYSICAL
*      if MYSTICAL: 1 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 1 PHYSICAL, 1 POISON
*      if UNKNOWN: 1 PHYSICAL

* 3: Attack name: [ELEMENTAL BREATH/BAD BREATH], where the name is ELEMENTAL BREATH if the Dragon has an elemental affinity, otherwise it is BAD BREATH
*      if ALIEN: 6 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if MYSTICAL: 3 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if UNDEAD: 3 [POISON/FIRE/WATER/EARTH/AIR], 1 POISON. The damage types and amount are added to the vector as two separate entries, even if both entries are POISON type.
*      if UNKNOWN: 3 [POISON/FIRE/WATER/EARTH/AIR] where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON  
*/
void Dragon::addAttack(const int& attack_add){

    Attack temp_variables;

    if(attack_add == 1){
        temp_variables.name_ = "BITE";
        if(getCategory() == "ALIEN"){
            temp_variables.damage_.push_back(4);
            temp_variables.type_.push_back("PHYSICAL");
        }
        if(getCategory() == "MYSTICAL"){
            temp_variables.damage_.push_back(2);
            temp_variables.type_.push_back("PHYSICAL");
        if(getElement() == "FIRE" || getElement() == "AIR" || getElement() == "WATER" || getElement() == "EARTH"){  //checking for elements individually 
                temp_variables.damage_.push_back(1);    //adds extra 1 damage 
                temp_variables.type_.push_back(getElement());
            }
        }
        if(getCategory() == "UNDEAD"){
            temp_variables.damage_.push_back(2);
            temp_variables.type_.push_back("PHYSICAL");    //2 for physical 
            temp_variables.damage_.push_back(1);
            temp_variables.type_.push_back("POISON");      //1 for posion 
        }
        if(getCategory() == "UNKNOWN"){
            temp_variables.damage_.push_back(2);
            temp_variables.type_.push_back("PHYSICAL");
        }
        Creature::addAttack(temp_variables);
    }

    else if(attack_add == 2){
        temp_variables.name_ = "STOMP";
        if(getCategory() == "ALIEN"){
            temp_variables.damage_.push_back(2);
            temp_variables.type_.push_back("PHYSICAL");
        }
        if(getCategory() == "MYSTICAL"){
            temp_variables.damage_.push_back(1);
            temp_variables.type_.push_back("PHYSICAL");
        if(getElement() == "FIRE" || getElement() == "AIR" || getElement() == "WATER" || getElement() == "EARTH"){
                temp_variables.damage_.push_back(1);    //adds extra 1 damage 
                temp_variables.type_.push_back(getElement());
            }
        }
        if(getCategory() == "UNDEAD"){
            temp_variables.damage_.push_back(1);
            temp_variables.type_.push_back("PHYSICAL");    //1 for physical 
            temp_variables.damage_.push_back(1);
            temp_variables.type_.push_back("POISON");      //1 for posion 
        }
        if(getCategory() == "UNKNOWN"){
            temp_variables.damage_.push_back(1);
            temp_variables.type_.push_back("PHYSICAL");
        }
        Creature::addAttack(temp_variables);
    }

    else if(attack_add == 3){
        if(getElement() == "NONE"){
            temp_variables.name_ = "BAD BREATH";
        }
        else{
            temp_variables.name_ = "ELEMENTAL BREATH";
        }

        if(getCategory() == "ALIEN"){
            if(getElement() == "FIRE" || getElement() == "AIR" || getElement() == "WATER" || getElement() == "EARTH" || getElement() == "POISON"){
                temp_variables.damage_.push_back(6);
                temp_variables.type_.push_back(getElement());
            }
            else{
                temp_variables.type_.push_back("POISON"); 
                temp_variables.damage_.push_back(6);
            }
        }
        if(getCategory() == "MYSTICAL"){
            if(getElement() == "FIRE" || getElement() == "AIR" || getElement() == "WATER" || getElement() == "EARTH" || getElement() == "POISON"){
                temp_variables.damage_.push_back(3);
                temp_variables.type_.push_back(getElement());
            }
            else{
                temp_variables.type_.push_back("POISON"); 
                temp_variables.damage_.push_back(3);
            }
        }
        if(getCategory() == "UNDEAD"){
            if(getElement() == "FIRE" || getElement() == "AIR" || getElement() == "WATER" || getElement() == "EARTH" || getElement() == "POISON"){
                temp_variables.damage_.push_back(3);
                temp_variables.type_.push_back(getElement());
                temp_variables.damage_.push_back(1);
                temp_variables.type_.push_back("POISON");
            }
            else{
                temp_variables.type_.push_back("POISON"); 
                temp_variables.damage_.push_back(3);

                temp_variables.damage_.push_back(1);
                temp_variables.type_.push_back("POISON");
            }
        }
        if(getCategory() == "UNKNOWN"){
            if(getElement() == "FIRE" || getElement() == "AIR" || getElement() == "WATER" || getElement() == "EARTH" || getElement() == "POISON"){
                temp_variables.damage_.push_back(3);
                temp_variables.type_.push_back(getElement());
            }
            else{
                temp_variables.type_.push_back("POISON"); //default aka none is POSION 
                temp_variables.damage_.push_back(3);
            }
        }
        Creature::addAttack(temp_variables);
    }
}

/**
  * @post: Displays available attacks and promps the user to enter 2 numbers in the range [1,3]
  *        Print in the following form:
  *        [DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n
  */
void Dragon::displayAttacks() const{
      std::cout << "[DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n";
}               