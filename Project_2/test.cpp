/*
Author: Jeremiah Gonzalez
Course: CSCI-235
Date: 2/18/2024
Instructor: Dr. Tiziana Ligorio
Assignment: Project 2

Project 1 is a program creating classes and useing them to name create and capture creatures, this part is the interface 
where we test the functions we made in the previous files 
*/

#include "Dragon.hpp"
#include "Creature.hpp"
#include "Ghoul.hpp"
#include "Mindflayer.hpp"

int main() {

    //Default
    Dragon Stardust;
    Stardust.display();

    //smog
    Dragon Smog("Smog");
    Smog.display();

    //Burny
    Dragon burny("Burny", Creature::UNDEAD, 100, 10, true, Dragon::FIRE, 1, true);
    burny.display();
    
    burny.setElement(Dragon::WATER);
    burny.setNumberOfHeads(2);
    burny.setNumberOfHeads(0);
    burny.setFlight(false);
    burny.display();
    
    //Default 
     Ghoul Lichking;    
     Lichking.display();
    
    //Homph
    Ghoul homph("Homph");
    homph.display();

    //Chomper
    Ghoul chomper("Chomper", Creature::ALIEN, 100, 10, true, 3, Ghoul::FLESHGORGER, true);
    chomper.display();

    chomper.setDecay(2);
    chomper.setDecay(-20);
    chomper.setFaction(Ghoul::SHADOWSTALKER);
    chomper.setTransformation(false);
    chomper.display();

    //Default
    Mindflayer Draxus;
    Draxus.display();

    //Big brain
    Mindflayer bigbrain("BIGBRAIN", Creature::MYSTICAL, 100, 10, true, {{Mindflayer::PSIONIC, 2}, {Mindflayer::TELEPATHIC, 1}, {Mindflayer::PSIONIC, 1}, {Mindflayer::ILLUSIONARY, 3}}, true, {Mindflayer::PSIONIC, Mindflayer::TELEPATHIC, Mindflayer::PSIONIC, Mindflayer::ILLUSIONARY} );
    bigbrain.display();
    
    return 0;
}  
