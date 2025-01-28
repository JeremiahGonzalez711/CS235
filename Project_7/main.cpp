/*
CSCI235 Spring 2024
Project 7 - Binary Skill Tree
Jeremiah Gonzalez
May 6 2024
SkillTree.hpp declares the SkillTree class along with its private and public members
*/
#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include "SkillTree.hpp"

int main()
 {
    
    // Testing SkillTree Class
    SkillTree tree;

    // Add some skills to the tree
    tree.addSkill(Skill(1, "Skill1", "Description1", true));
    tree.addSkill(Skill(2, "Skill2", "Description2", false));
    tree.addSkill(Skill(3, "Skill3", "Description3", true));
    tree.addSkill(Skill(4, "Skill4", "Description4", false));
    tree.addSkill(Skill(5, "Skill5", "Description5", true));

    // Remove a skill that exists in the tree
    // std::cout << "Removing Skill2... ";
    // if (tree.removeSkill("Skill2")) {
    //     std::cout << "Successful!" << std::endl;
    // } else {
    //     std::cout << "Failed!" << std::endl;
    // }

     // Print the tree before balancing
    // std::cout << "Tree before balancing:\n";
    // tree.preorderDisplay();

    // // Balance the tree
    // tree.balance();

    // // Print the tree after balancing
    // std::cout << "\nTree after balancing:\n";
    // tree.preorderDisplay();


    // // Remove a skill that doesn't exist in the tree
    // std::cout << "Removing Skill5... ";
    // if (tree.removeSkill("Skill5")) {
    //     std::cout << "Successful!" << std::endl;
    // } else {
    //     std::cout << "Failed!" << std::endl;
    // }


     // Print the remaining skills in the tree
    // std::cout << "Remaining skills in the tree:" << std::endl;
    // tree.preorderDisplay();


    // Calculate skill points for some skill ids
    int skillId1 = 8;
    int skillPoints1 = tree.calculateSkillPoints(skillId1);
    std::cout << "Skill points needed to level up skill with id " << skillId1 << ": " << skillPoints1 << std::endl;

    int skillId2 = 3;
    int skillPoints2 = tree.calculateSkillPoints(skillId2);
    std::cout << "Skill points needed to level up skill with id " << skillId2 << ": " << skillPoints2 << std::endl;

    int skillId3 = 11; // Assuming skill id 11 does not exist
    int skillPoints3 = tree.calculateSkillPoints(skillId3);
    if (skillPoints3 == -1) {
        std::cout << "Skill with id " << skillId3 << " not found in the tree" << std::endl;
    }


     return 0;
}