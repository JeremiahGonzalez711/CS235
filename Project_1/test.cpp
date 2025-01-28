/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/8/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 1

Project 1 is a program creating classes and useing them to name create and capture creatures, this part is the interface 
where we test the functions we made in the previous files 
*/

#include "Creature.hpp"

int main(){

    //test 2.1
    Creature Stardustdragon;

    Stardustdragon.setLevel(5);

    Stardustdragon.setHitpoints(10);

    Stardustdragon.setTame(true);

    Stardustdragon.display();

    //test2.2

    Creature Wormy("Wormy", Creature::MYSTICAL, 3, 2);
    Wormy.setTame(true);

    Wormy.display();
    return 0;
}