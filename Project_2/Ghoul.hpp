/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/17/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 2

Project 2 is creating the Ghoul class 
this part is to be hidden from the interface where we create private variables and public functions 
*/
#ifndef GHOUL_HPP_
#define GHOUL_HPP_

#include <iostream>
#include <string>
#include "Creature.hpp"

class Ghoul : public Creature {
    public:
        enum Faction {NONE, FLESHGORGER, SHADOWSTALKER, PLAGUEWEAVER};

        Ghoul();    //default constructor

/**
  Parameterized constructor.
  @param      : The name of the Ghoul (a reference to string)
  @param      : The category of the Ghoul (a Category enum) with default value UNDEAD
  @param      : The Ghoul's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Ghoul's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Ghoul is tame, with default value False
  @param      : The level of decay (an integer), with default value 0 if not provided, or if the value provided is negative
  @param      : The faction (a Faction enum), with default value NONE if not provided
  @param      : A flag indicating whether the Ghoul can transform, with default value False
  @post       : The private members are set to the values of the corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/

        Ghoul(const std::string& name, Category c_category = UNDEAD, int hitpoints = 1, int level = 1, bool tame = false, int decay = 0, Faction f_faction = NONE, bool transform = false);

        bool setDecay(const int& decay);        //setter method

        int getDecay() const;       //getter method

        void setFaction(const Faction& f_faction);      //setter method

        std::string getFaction() const;     //getter method

        void setTransformation(const bool& transfom);       //setter method

        bool getTransformation() const;     //getter method

        void display() const;

    private:
        int level_of_decay_;        //psuedo variables 
        Faction faction_;
        bool can_transform_;

        std::string name_;      //variables used from Creature.hpp
        Category category_;
        int hitpoints_;
        int level_;
        bool is_tame_;
};
#endif
