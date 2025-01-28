/*
CSCI235 Spring 2024
Project 4 - Cavern Class
Jeremiah Gonzalez
Mar 18 2024 
Ghoul.cpp implements the constructors and private and public functions of the Ghoul class
Where we are adding a display and eatMycoMorsel function 
*/

#include "Ghoul.hpp"

Ghoul::Ghoul() :  decay_{0}, faction_{NONE}, transformation_{false}
{
    setCategory(UNDEAD); 
}

Ghoul::Ghoul(const std::string& name, Category category, int hitpoints, int level, bool tame, int decay, Faction faction, bool transformation) : Creature(name, category, hitpoints, level, tame)
{
    if(!setDecay(decay))
    {
        decay_ = 0;
    }
    faction_ = faction;
    transformation_ = transformation;
}

int Ghoul::getDecay() const
{
    return decay_;
}

bool Ghoul::setDecay(const int& decay)
{
    if(decay >= 0)
    {
        decay_ = decay;
        return true;
    }
    else
    {
        return false;
    }
}

std::string Ghoul::getFaction() const
{
    switch(faction_)
    {
        case FLESHGORGER:
            return "FLESHGORGER";
        case SHADOWSTALKER:
            return "SHADOWSTALKER";
        case PLAGUEWEAVER:
            return "PLAGUEWEAVER";
        default:
            return "NONE";
    }
}

void Ghoul::setFaction(const Faction& faction)
{
    faction_ = faction;
}

bool Ghoul::getTransformation() const
{
    return transformation_;
}

void Ghoul::setTransformation(const bool& transformation)
{
    transformation_ = transformation;
}


/**
    @post     : displays Ghoul data in the form:
    GHOUL - [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [HITPOINTS]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]\n
    DECAY: [DECAY]\n
    FACTION: [FACTION]\n
    IT [CAN/CANNOT] TRANSFORM\n"
    
    Example:
    GHOUL - JHRAT
    CATEGORY: MYSTICAL
    HP: 4
    LVL: 8
    TAME: TRUE
    DECAY: 3
    FACTION: FLESHGORGER
    IT CAN TRANSFORM
    
 */
void Ghoul::display() const{

    std::cout << "GHOUL - " << getName()
    << "\nCATEGORY: " << getCategory()
    << "\nHP: " << getHitpoints() 
    << "\nLVL: " << getLevel() 
    << "\nTAME: " << (isTame() ? "TRUE" : "FALSE")
    << "\nDECAY: " << getDecay()
    << "\nFACTION: " << getFaction()
    << "\nIT " << (getTransformation() ? "CAN" : "CANNOT") << " TRANSFORM " << std::endl;
    }

   /**
    @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
              If the creature is of Faction FLESHGORGER, it becomes so offended by being offered a mushroom that it becomes untamed if it was tame. If it was already untamed, it leaves the Cavern. Nothing else happens.
              If the creature was of Faction SHADOWSTALKER, if it was untame, it hides from the mushroom and nothing happens. If it was tame, it eats the mushroom and loses 1 hitpoint, unless it only had 1 hitpoint left in which case it stays at 1 hitpoint but becomes untame. Nothing else happens.
    @return   : true if the creature leaves the Cavern, false otherwise
    */

    bool Ghoul::eatMycoMorsel(){

    if(getCategory() == "UNDEAD"){  //setting tame to be true if its false 
       if (isTame() == false){
            setTame(true);
       }
        setHitpoints(getHitpoints() + 1); //giving it an extra hitpoint nothing else happens 
        return false;
    }

    if(getFaction() == "FLESHGORGER"){  //if tame it becomes untamed 
        if(isTame() == true){
            setTame(false);
            return false;
        }
        else if(isTame() == false){     //if untamed it leaves the cavern 
            return true;
        }
    }
    if(getFaction() == "SHADOWSTALKER"){    //if it has 1 hitpoint it becomes untamed 
        if(isTame() == true){
            if(getHitpoints() == 1){
                setTame(false);
            }
            else setHitpoints(getHitpoints() - 1);  //if tamed it looses 1 hitpoint
        }
     }
        return false;
    }
        

