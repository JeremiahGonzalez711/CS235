#include "Dragon.hpp"
#include "Ghoul.hpp"
#include "Mindflayer.hpp"
#include "Cavern.hpp"
#include <queue>
#include <stack>


int main(){

Cavern cavern("creatures.csv");

cavern.initializeUndeadStack();

cavern.setAttacks(cavern.getUndeadStack());
    std::cout << cavern.getUndeadStack().top()->getAttackQueue().size() << "\n";

std::cout << std::endl;

// while(!cavern.getUndeadStack().top()->getAttackQueue().empty()){
//     std::cout << cavern.getUndeadStack().top()->getAttackQueue().front().name_ << std::endl;
//     cavern.getUndeadStack().top()->getAttackQueue().pop();  
// }


// while(!cavern.getUndeadStack().empty()){
//     std::cout << cavern.getUndeadStack().top()->getAttackQueue().size() << "\n";
//     cavern.getUndeadStack().pop();
// }


// Attack cow;
// cow.name_ = "hi";
// cow.damage_.push_back(1);
// cow.damage_.push_back(2);
// cow.type_.push_back("UNDEAD");
// cow.type_.push_back("ALIEN");

// std::cout << cow.name_ << '\n';

// for(int i = 0; i < cow.damage_.size(); i++){
//     std::cout << cow.damage_[i]  << '\n';
// }
// for(int i = 0; i < cow.type_.size(); i++){
//     std::cout << cow.type_[i]  << '\n';
// }





// // Mindflayer mindflayer;

//Cavern cavern;

// Dragon dragon;
// dragon.setCategory(Creature::UNKNOWN);
// dragon.setElement(Dragon::FIRE);
// dragon.addAttack(3);

// dragon.getAttackQueue();




// // Ghoul ghoul;
// ghoul.setCategory(Creature::UNDEAD);
// ghoul.setFaction(Ghoul::SHADOWSTALKER);
// ghoul.addAttack(1);
// //ghoul.getAttackQueue();




// mindflayer.setCategory(Creature::UNDEAD);
// std::vector<Mindflayer::Projectile> v;
// Mindflayer::Projectile x;
// x.quantity_ = 5;
// x.type_ = Mindflayer::TELEPATHIC;
// v.push_back(x);
// mindflayer.setProjectiles(v);

// std::vector<Mindflayer::Variant> temp;
// Mindflayer::Variant affin;
// affin = Mindflayer::PSIONIC;
// mindflayer.addAttack(2);
// mindflayer.getAttackQueue();



// // dragon.getAttackQueue().front().name_;
// // dragon.getAttackQueue().front().type_;
// // dragon.getAttackQueue().front().damage_;


// std::cout << dragon.getAttackQueue().front().name_ << std::endl;
// std::cout << dragon.getAttackQueue().front().damage_ << std::endl;
// std::cout << dragon.getAttackQueue().front().type_ << std::endl;




 // std::cout << attack_queue_.front().name_ << std::endl;           //for testing add attack 
    // for(int i = 0; i < attack_queue_.front().damage_.size(); i++){
    //     std::cout << attack_queue_.front().damage_[i] << std::endl;
    // }
    // for(int i = 0; i < attack_queue_.front().type_.size(); i++){
    //     std::cout << attack_queue_.front().type_[i] << std::endl;
    // }


return 0;

}