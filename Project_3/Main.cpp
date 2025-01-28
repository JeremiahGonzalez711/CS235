/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 3/1/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 3

*/
#include <iostream>
#include "ArrayBag.hpp"
#include "Creature.hpp"
#include "Cavern.hpp"

int main(){
    //array bag for creature 
    ArrayBag<Creature> creatureBag;

    //creating cavern object 
    Cavern cavern;

    Creature creature1("Dragon", Creature::Category::ALIEN, 20, 3, true);
    Creature creature2("Goblin", Creature::Category::UNDEAD, 5, 6, false);
    Creature creature3("Orc", Creature::Category::UNKNOWN, 8, 3, true);

    std::cout << std::endl;


    cavern.enterCavern(creature1);  //true 
    cavern.enterCavern(creature2);  //false 
    cavern.enterCavern(creature3);  //true 
    
    
    cavern.cavernReport();


   
    //std::cout << "Total creatures in the cavern: " << cavern.tallyCategory() << "\n";
    //std::cout << "Total levels in the cavern: " << cavern.getLevelSum() << "\n";
    //std::cout << "Total tame creatures: " << cavern.getTameCount() << "\n";
    


    return 0;
}