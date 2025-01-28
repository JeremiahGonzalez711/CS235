/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/16/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 2

Project 2 is creating the dragon class 
this part is to be hidden from the interface where we create private variables and public functions 
*/

#ifndef DRAGON_HPP_
#define DRAGON_HPP_

#include <iostream>
#include <string>
#include "Creature.hpp"     //inheartance 

class Dragon : public Creature{     //psuedo code from poject instructions //ih
    public:
        enum Element {NONE, FIRE, WATER, EARTH, AIR};

        Dragon(); //default constructor 

/**
  Parameterized constructor.
  @param      : The name of the Dragon (a reference to string)
  @param      : The category of the Dragon (a Category enum) with default value MYSTICAL
  @param      : The Dragon's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Dragon's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Dragon is tame, with default value False
  @param      : The element (an Element enum), with default value NONE if not provided
  @param      : The number of heads (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Dragon can fly, with default value False
  @post       : The private members are set to the values of the corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/

        Dragon(const std::string& name, Category c_category = MYSTICAL, int hitpoints = 1, int level = 1, bool tame = false, Element e_element = NONE, int heads = 1, bool flight = false);

        void setElement(const Element& e_element);      //setter method (to set the value of the element property)

        std::string getElement() const;        //getter method (used to retrieve the value to return as a string)

        bool setNumberOfHeads(const int& heads);         //setter method

        int getNumberOfHeads() const;       //getter method 

        void setFlight(const bool& flight);      //setter method

        bool getFlight() const;     //getter method 

        void display() const;

    private:
        Element affinity_;      //psuedo variables 
        int num_heads_;     //integer 
        bool can_fly_;      //can fly or not 

        std::string name_;      //variables used from Creature.hpp
        Category category_;
        int hitpoints_;
        int level_;
        bool is_tame_;        
};
#endif