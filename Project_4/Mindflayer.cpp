/*
CSCI235 Spring 2024
Project 4 - Cavern Class
Jeremiah Gonzalez
Mar 18 2024 
Mindflayer.cpp implements the constructors and private and public functions of the Mindflayer class
Where we are adding a display and eatMycoMorsel function 
*/

#include "Mindflayer.hpp"

Mindflayer::Mindflayer() : affinities_{}, summoning_{false}, projectiles_{}
{
    setCategory(ALIEN);
}

Mindflayer::Mindflayer(const std::string& name, Category category, int hitpoints, int level, bool tame, std::vector<Projectile> projectiles, bool summoning, std::vector<Variant> affinities) : Creature(name, category, hitpoints, level, tame)
{
    setProjectiles(projectiles);
    summoning_ = summoning;
    setAffinities(affinities);
}

std::vector<Mindflayer::Projectile> Mindflayer::getProjectiles() const
{
    return projectiles_;
}

void Mindflayer::setProjectiles(const std::vector<Projectile>& projectiles)
{
    std::vector<Projectile> temp;
    for(int i = 0; i < projectiles.size(); i++)
    {
        bool found = false;
        for(int j = 0; j < temp.size(); j++)
        {
            if(projectiles[i].type_ == temp[j].type_)
            {
                if(projectiles[i].quantity_ > 0)
                {
                    temp[j].quantity_ += projectiles[i].quantity_;
                    found = true;
                }
            }
        }
        if(!found)
        {
            if(projectiles[i].quantity_ > 0)
            {
                temp.push_back(projectiles[i]);
            }
        }
    }
    projectiles_ = temp;
}

void Mindflayer::setSummoning(const bool& summoning)
{
    summoning_ = summoning;
}

bool Mindflayer::getSummoning() const
{
    return summoning_;
}

std::vector<Mindflayer::Variant> Mindflayer::getAffinities() const
{
    return affinities_;
}

void Mindflayer::setAffinities(const std::vector<Variant>& affinities)
{
    std::vector<Variant> temp;
    for(int i = 0; i < affinities.size(); i++)
    {
        bool found = false;
        for(int j = 0; j < temp.size(); j++)
        {
            if(affinities[i] == temp[j])
            {
                found = true;
            }
        }
        if(!found)
        {
            temp.push_back(affinities[i]);
        }
    }
    affinities_ = temp;
}

std::string Mindflayer::variantToString(const Variant& variant) const
{
    switch(variant)
    {
        case PSIONIC:
            return "PSIONIC";
        case TELEPATHIC:
            return "TELEPATHIC";
        case ILLUSIONARY:
            return "ILLUSIONARY";
        default:
            return "NONE";
    }
}

/**
    @post     : displays Mindflayer data in the form:
    "MINDFLAYER - [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [HITPOINTS]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]\n
    SUMMONING: [SUMMONING]\n
    [PROJECTILE TYPE 1]: [QUANTITY 1]\n
    [PROJECTILE TYPE 2]: [QUANTITY 2]\n
    AFFINITIES: \n
    [AFFINITY 1]\n
    [AFFINITY 2]\n"

    NOTE: For the Projectiles, print out the type and quantity of each projectile in the format: 
    [TYPE]: [QUANTITY] for each projectile in the vector, where the type is the string equivalent of the Variant (eg. "PSIONIC"/"TELEPATHIC"/"ILLUSIONARY"). If there are no projectiles, don't print anything. 

    For the Affinities, print out each affinity in the format: [AFFINITY 1]\n[AFFINITY 2]\n for each Affinity in the vector, where the Affinity is the string equivalent of the Variant (eg. "PSIONIC"/"TELEPATHIC"/"ILLUSIONARY"). If there are no affinities, don't print anything, including the label "AFFINITIES:". 
    
    Example:
    MINDFLAYER - JHOCTOPUS
    CATEGORY: UNDEAD
    HP: 3
    LVL: 6
    TAME: TRUE
    SUMMONING: TRUE
    PSIONIC: 2
    TELEPATHIC: 11
    AFFINITIES: 
    PSIONIC
    ILLUSIONARY
*/
void Mindflayer::display() const{

    std::cout << "MINDFLAYER - " << getName()
    << "\nCATEGORY: " << getCategory()
    << "\nHP: " << getHitpoints()
    << "\nLVL: " << getLevel() 
    << "\nTAME: " << (isTame() ? "TRUE" : "FALSE")
    << "\nSUMMONING: " << (getSummoning() ? "TRUE" : "FALSE") << std::endl;
    
    for(int i = 0; i < projectiles_.size(); i++){    //going through the projectiles for displaying
        std::cout << variantToString(projectiles_[i].type_) << ": " << projectiles_[i].quantity_ << std::endl;
    }
    
    if(affinities_.size() > 0){     //going through affinities for displaying
        std::cout << "AFFINITIES: " <<std::endl;
    }
    for(int i = 0; i < affinities_.size(); i++){
        std::cout << variantToString(affinities_[i]) << std::endl;
    }
}

/**
    @post: 
    If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.

    If the creature is MYSTICAL, if it can summon a Thoughtspawn, it gives the mushroom to the Thoughtspawn instead. If it cannot summon a Thoughtspawn and is tame, it eats the mushroom to be polite. If it only had 1 hitpoint left, it remains at 1 hitpoint and becomes untame, else it loses 1 hitpoint. If it cannot summon a Thoughtspawn and is untame, it decides it doesn't have to deal with this and it leaves the Cavern. Nothing else happens.

    If the creature is an ALIEN, if it has Telepathic affinity, it convinces Selfa Ensert to eat the mushroom instead, and gains 1 hitpoint from laughing at their resulting illness (as laughter is the best medicine).

    If it is an ALIEN and does not have Telepathic affinity, but has a Telepathic projectile, it uses one of such projectile to achieve the same effect. (Remember to remove the projectile from the vector if it only had 1 left)

    If it is an ALIEN and does not have Telepathic affinity or a Telepathic projectile, it eats the mushroom and gains 2 hitpoints. As it turns out, the mushroom was good for it. It becomes tame if it was not already. Nothing else happens.

    @return   : true if the creature leaves the Cavern, false otherwise
*/

bool Mindflayer::eatMycoMorsel(){

    if(getCategory() == "UNDEAD"){  //setting tame to be true if its false 
       if (isTame() == false){
        setTame(true);
       }
        setHitpoints(getHitpoints() + 1);      //giving it an extra hitpoint nothing else happens 
        return false;   //ends for otherwise
    }

    if(getCategory() == "MYSTICAL"){    
        if(getSummoning() == false && isTame() == true){   //cant summon but is tamed it eats mushroom, if it has 1 hit point it becomes untamed but if it has more than 1 is just looses 1 hitpoint 
           if(getHitpoints() == 1){
                setTame(false);
                return false;
            }
            else setHitpoints(getHitpoints() - 1);
                return false;
            }
        if(getSummoning() == false && isTame() == false){       //cant summon and isn't tamed it leaves the cavern 
                return true;    //leaves cavern 
        }
      } 

    if(getCategory() == "ALIEN"){     

        bool affrin;        //inatializing new variables 
        bool project;
                                                      
        for( int i = 0; i < affinities_.size(); i++){   //Alien and has TELEPATHIC it makes you eats the mushroom and gains a hitpoint 
            if(affinities_[i] == TELEPATHIC) {                                            
                affrin = true;                               
            }
        }

        for(int i = 0; i < projectiles_.size(); i++){
            if(projectiles_[i].type_ == TELEPATHIC){        //.type_ is what makes it different from thr affinities vector 
                if(projectiles_[i].quantity_ == 1){
                    projectiles_.erase(projectiles_.begin()+ i); //going to through to i element 
                }
                else (projectiles_[i].quantity_ -= 1); 
                    project = true;
            }
        }
    
        if(!affrin && !project){
            if (isTame() == false){
                setTame(true);
        }
            setHitpoints(getHitpoints() + 2);      //giving it an two extra hitpoint nothing else happens 
            return false;
        }
        else {
             setHitpoints(getHitpoints() + 1); 
             return false;
        }
     }
             return false;
}