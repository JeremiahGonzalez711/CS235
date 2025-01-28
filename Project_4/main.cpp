//#include "ArrayBag.hpp"
#include "Cavern.hpp"
#include "Creature.hpp"
#include "Dragon.hpp"
#include "Ghoul.hpp"
#include "Mindflayer.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

int main(){


Cavern cavern("creatures.csv");
cavern.displayCreatures();




       /*
       //Testing with subclasses display() and eatMycoMorsel
       std::cout << "This is Dragon Display and eatMycoMorsel" << std::endl;
       Dragon JHIZARD = Dragon();
       JHIZARD.setName("JHIZARD");
       JHIZARD.setCategory(Creature::Category::ALIEN);
       JHIZARD.setHitpoints(7);
       JHIZARD.setLevel(5);
       JHIZARD.setTame(true);
       JHIZARD.setElement(Dragon::Element::FIRE);
       JHIZARD.setNumberOfHeads(3);
       JHIZARD.setFlight(true);
       JHIZARD.display();
       JHIZARD.eatMycoMorsel();
       std::cout << JHIZARD.getHitpoints() << std::endl << std::endl;

       std::cout << std::endl;
       std::cout << std::endl;

       //Testing with subclasses display() and eatMycoMorsel
       std::cout <<"This is a Ghoul Display and eatMycoMorsel" << std::endl;
       Ghoul JHRAT = Ghoul();
       JHRAT.setName("JHRAT");
       JHRAT.setCategory(Creature::Category::MYSTICAL);
       JHRAT.setHitpoints(4);
       JHRAT.setLevel(8);
       JHRAT.setTame(true);
       JHRAT.setDecay(3);
       JHRAT.setFaction(Ghoul::Faction::FLESHGORGER);
       JHRAT.setTransformation(true);
       JHRAT.display();
       JHRAT.eatMycoMorsel();
       
       std::cout << std::endl;
       std::cout << std::endl;

       //Testing with subclasses display() and eatMycoMorsel
       std::cout <<"This is a MindfFlayer Display and eatMycoMorsel" << std::endl;
       Mindflayer JHOCTOPUS = Mindflayer();
       JHOCTOPUS.setName("JHOCTOPUS");
       JHOCTOPUS.setCategory(Creature::Category::UNDEAD);
       JHOCTOPUS.setHitpoints(3);
       JHOCTOPUS.setLevel(6);
       JHOCTOPUS.setTame(true);
       JHOCTOPUS.setSummoning(true);
       //JHOCTOPUS.
       //JHOCTOPUS
       //JHOCTOPUS
       //JHOCTOPUS
       //JHOCTOPUS
       JHOCTOPUS.display();
       */
}