/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/18/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 2

Project 2 is a program creating classes and useing them to name create and capture Mindflayers, this part is the interface 
where we use the private variables and public functions to for the user
*/

#include "Mindflayer.hpp"
#include <vector>
#include <iostream>

Mindflayer::Mindflayer() {      //default constructor 
    setCategory(ALIEN);

    summoning_ = false;
}

Mindflayer::Mindflayer(const std::string& name, Category c_category, int hitpoints, int level, bool tame, std::vector<Projectile> projectile, bool summon, std::vector<Variant> affinity) : Creature(name, c_category, hitpoints, level, tame), projectiles_(projectile), affinities_(affinity), summoning_(summon) {

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
        };

    projectiles_ = projectile;

    affinities_ = affinity;

    summoning_ = summon;

    for (int i = 0; i < projectiles_.size(); i++) {
        for (int j = i + 1; j < projectiles_.size(); j++) {
            if (projectiles_[j].type_ < projectiles_[i].type_) {
                std::swap(projectiles_[j], projectiles_[i]);
            }
        }
    }

    for (int p = 0; p < projectiles_.size();) {
        if(projectiles_[p].quantity_ <= 0) {
            projectiles_.erase(projectiles_.begin() + p);
        }
        else 
        {
            p++;
        }
    }

    for (int q = 1; q < projectiles_.size(); q++) {
        if (projectiles_[q].type_ == projectiles_[q - 1].type_) {
            projectiles_[q].quantity_ = projectiles_[q].quantity_ + projectiles_[q - 1].quantity_;
            projectiles_.erase(projectiles_.begin() + (q - 1));
            q--;
        }
    }

    for (int z = 0; z < affinities_.size(); z++) {
        for (int x = z + 1; x < affinities_.size(); x++) {
            if (affinities_[x] < affinities_[z]) {
                std::swap(affinities_[x], affinities_[z]);
            } 
        }
    }

    for (int t = 1; t < affinities_.size(); t++) {
        if(affinities_[t] == affinities_[t - 1]) {
            affinities_.erase(affinities_.begin() + (t - 1));
            t--;
        }
    }

}

/**
  Setter for the projectiles.
  @param      : A reference to the projectiles (a vector of Projectile structs)
  @post       : The projectiles are set to the value of the parameter. There should not be any duplicate projectiles in Mindflayer's projectiles vector.
        : For example, if the vector in the given parameter contains the following Projectiles: {{PSIONIC, 2}, {TELEPATHIC, 1}, {PSIONIC, 1}, {ILLUSIONARY, 3}}, 
        : the projectiles vector should be set to contain the following Projectiles: {{PSIONIC, 3}, {TELEPATHIC, 1}, {ILLUSIONARY, 3}}.
        : If the quantity of a projectile is 0 or negative, it should not be added to the projectiles vector. 
        : Note the order of the projectiles in the vector.
*/
void Mindflayer::setProjectiles(const std::vector<Projectile>& projectile) {
     std::vector<Mindflayer::Projectile> P_object = {};  //Creating a empty vector and story values into it as long as its greater than 0 

for (int i = 0; i < projectile.size(); i++){        //storing values into empty vector 
    if(projectile[i].quantity_ > 0){
        P_object.push_back(projectile[i]);
    }
}

for (int i = 0; i < P_object.size(); i++)   //nested for loop
        for (int j = i + 1; j < P_object.size(); j++) {
            if (P_object[i].type_ = P_object[j].type_) {
                if (P_object[j].quantity_ > 0){
                    P_object[i].quantity_ += projectile[j].quantity_;       //adding to quantity
                    P_object.erase(P_object.begin() + j);
                    j--;
                }
            }
        }
        projectiles_ = P_object;
}

/**
  Getter for the projectiles.
  @return     : The projectiles (a vector of Projectile structs)
*/
std::vector<Mindflayer::Projectile> Mindflayer::getProjectiles() const {
    return projectiles_;
}

/**
  Setter for the summoning.
  @param      : A reference to the summoning (a boolean)
  @post       : The summoning is set to the value of the parameter.
*/
void Mindflayer::setSummoning(const bool& summon) {
    summoning_ = summon;
}

/**
  Getter for the summoning.
  @return     : The summoning (a boolean)
*/
bool Mindflayer::getSummoning() const {
    return summoning_;
}

/**
  Setter for the affinities.
  @param      : A reference to the affinities (a vector of Variant enums)
  @post       : The affinities are set to the value of the parameter.
        : There should not be any duplicate affinities in Mindflayer's affinities vector. 
        : For example, if the vector in the given parameter contains the following affinities: {PSIONIC, TELEPATHIC, PSIONIC, ILLUSIONARY}, 
        : the affinities vector should be set to contain the following affinities: {PSIONIC, TELEPATHIC, ILLUSIONARY}.
        : Note the order of the affinities in the vector.
*/
void Mindflayer::setAffinities(const std::vector<Mindflayer::Variant>& affinity) {
     std::vector<Mindflayer::Variant> P_object = {};

     for(int i = 0; i < affinity.size(); i++)
    {
        P_object.push_back(affinity[i]);
    }

    for(int i = 0; i < P_object.size(); i++)
    {
        for(int j = i + 1; j < P_object.size(); j++) 
        {
            if(P_object[i] == P_object[j])
            {
                P_object.erase(P_object.begin() + j);
                j--;
            }
        }    
   }   
    affinities_ = P_object;
}

/**
  Getter for the affinities.
  @return     : The affinities (a vector of Variant enums)
*/
std::vector<Mindflayer::Variant> Mindflayer::getAffinities() const {
    return affinities_;
}

/**
  @param       : A reference to the Variant 
  @return      : The string representation of the variant
*/
std::string Mindflayer::variantToString(const Variant& v_variant) const{
    std::string v;
    switch(v_variant) {
         case PSIONIC:
        return "PISIONIC";
        case TELEPATHIC:
        return "TELEPATHIC";
        case ILLUSIONARY:
        return "ILLUSIONARY";
         default:
        return "NONE";
    }
    return v;
}

void Mindflayer::display() const
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
     if(getSummoning() == 1){
        std::cout << "SUMMONING: " <<  "TRUE" << std::endl;
    }
    else{
        std::cout << "SUMMONING: " << "FALSE" << std::endl;
    }
    for(int i = 0; i < projectiles_.size(); i++) {
        std::cout << variantToString(projectiles_[i].type_) << ": " << projectiles_[i].quantity_ << std::endl;
    }
    if(affinities_.size() > 0){
    std::cout << "AFFINITIES: " << std::endl;
    }
     for (int i = 0; i < affinities_.size(); i++) {  
        std::cout << variantToString(affinities_[i]) << std::endl;
    }
}