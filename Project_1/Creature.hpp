/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/8/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 1

Project 1 is a program creating classes and using them to name create and capture creatures, 
this part is to be hidden from the interface where we create private variables and public functions 
*/
#include <iostream>
#include <ctype.h>
#include <string>

#ifndef CREATURE_INTERFACE
#define CREATURE_INTERFACE

class Creature {    //creation of class

    public:

        enum Category {     //enum for the category of the creature
        UNKNOWN, 
        UNDEAD, 
        MYSTICAL, 
        ALIEN};

        Creature();     //default constructor 

        Creature(const std::string &name, Category c_category = UNKNOWN, int hitpoints = 1, int level = 1, bool tame = false); //default constructor 

        bool setName(const std::string& name);  //function 

        std::string getName() const;        //retrieve of an object of the class and returns the name of the object 

        void setCategory(const Category& n_category);       //function

        std::string getCategory() const;        //retrieves object and returns 

        bool setHitpoints (const int& hitpoints);       //function 

        int getHitpoints() const;       //get and returns 

        bool setLevel(const int& level);

        int getLevel() const;

        void setTame(const bool& tame);

        bool isTame() const;

        void display() const;   //intended to display the creature 

    /**
      private:
  - The name of the creature (a string in UPPERCASE)
  - The category of the creature (an enum)
  - The creature's hitpoints (an integer)
  - The creature's level (an integer)
  - A boolean flag indicating whether the creature is tame
    */


    private:

        std::string name_;      //making sure not to change the names this time! 

        Category category_;

        int hitpoints_;

        int level_;

        bool is_tame_;
        

};
#endif