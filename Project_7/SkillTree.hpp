/*
CSCI235 Spring 2024
Project 7 - Binary Skill Tree
Jeremiah Gonzalez
May 6 2024
SkillTree.hpp declares the Skill Struct and SkillTree class along with its private and public members
*/
#ifndef SKILLTREE_HPP
#define SKILLTREE_HPP
#include "BinarySearchTree.hpp"
#include "BinaryNode.hpp"
#include <string>


struct Skill
{
    int id_;
    std::string name_;
    std::string description_;
    bool leveled_;

// Default constructor
Skill() : id_(0), name_(""), description_(""), leveled_(false){}

// Parameterized constructor for Skill
/**
 * @param id: The unique identifier for the Skill
 * @param name: The name of the Skill
 * @param description: The description of the Skill
 * @param leveled: Whether or not the Skill is leveled up
*/
Skill(const int& id, const std::string& name, const std::string& description, bool leveled) : id_{id}, name_{name}, description_{description}, leveled_{leveled} {}

/**
  * @param: A const reference to Skill 
  * @return: True if the id_ of the Skill is equal to that of the argument, false otherwise
  */
bool operator==(const Skill& id_equal) const{
    return this->id_ == id_equal.id_;   //id_ refers to the id_ member variable of the Skill object passed as an argument
}                                      

/**
  * @param: A const reference to Skill 
  * @return: True if the id_ of the Skill is less than that of the argument, false otherwise
  */
bool operator<(const Skill& id_less) const{
    return this->id_ < id_less.id_;
}

/**
  * @param: A const reference to Skill 
  * @return: True if the id_ of the Skill is greater than that of the argument, false otherwise
  */
bool operator>(const Skill& id_greater) const{
    return this->id_ > id_greater.id_;
}
};

class SkillTree : public BinarySearchTree<Skill>{      //SkillTree class as a subclass of BinarySearchTree that stores Skills

public:
// Default constructor
SkillTree();

// Parameterized constructor for SkillTree
/**
 * @param: A const reference to string: the name of a csv file
 * @post: The SkillTree is populated with Skills from the csv file
 * The file format is as follows:
 * id,name,description,leveled
 * Ignore the first line. Each subsequent line represents a Skill to be added to the SkillTree.
*/
SkillTree(const std::string& fileName);

/**
 * @param: A const reference to int representing the id of the Skill to be found
 * @return: A pointer to the node containing the Skill with the given id, or nullptr if the Skill is not found
*/
std::shared_ptr<BinaryNode<Skill>> findSkill(const int& skill_id) const;

/**
  * @param: A const reference to Skill 
  * @post: The Skill is added to the tree (in BST order as implemented in the base class) only if it was not already in the tree. Note that all comparisons are id-based as implemented by the Skill comparison operators.
  * @return: True if the Skill is successfully added to the SkillTree, false otherwise
  */
bool addSkill(const Skill& added_skill);

/**
  * @param: A const reference to string: the name of a Skill
  * @return: True if the Skill is successfully removed from the SkillTree, false otherwise
*/
bool removeSkill(const std::string& remove_skill);

void removeHelper(std::shared_ptr<BinaryNode<Skill>> current_node, const std::string& remove_skill, bool& success_removal);

/**
  * @post: Clears the tree
*/
void clear();

/**
  * @param: A const reference to int representing the id of a Skill
    * Note: For a Skill to be leveled up, its parent Skill must also be leveled up, thus the Skill points are the number of Skills that must be leveled up before and including the Skill with the given id.
  * @return: an integer: the number of skill points needed to level up the Skill with the given id, starting from the root (i.e. the number of nodes from root to the given Skill).
  * Include the Skill with the given id in the count. For example, if the tree contains the following Skills (represented by their ids):
  *   5
  *  / \
  * 1   8
  * and the function parameter queries for id 8, the function should return 2.
  * Disregard the leveled_ field of the existing Skills in the tree.
  * If the Skill with the given id is not found, return -1.
*/
int calculateSkillPoints(const int& skill_id);

/**
  * @post: Balances the tree. Recall the definition of a balanced tree:
  * A tree is balanced if for any node, its left and right subtrees differ in height by no more than 1. * All paths from root of subtrees to leaf differ in length by at most 1
  * Hint: You may sort the elements and build the tree recursively using a divide and conquer approach      
*/
void balance();

void collect_Nodes_In_Order(std::shared_ptr<BinaryNode<Skill>> node, std::vector<Skill>& sortedSkills) const;

std::shared_ptr<BinaryNode<Skill>> build_a_Balanced_Tree(const std::vector<Skill>& sortedSkills, int start, int end);

/**
  * @post: prints the tree in preorder, in the format:
  [id_] [name_]\n
  [description_]\n 
  [leveled_]
  */
void preorderDisplay();

void preorderDisplay_helper(std::shared_ptr<BinaryNode<Skill>> display_node);

};



#endif
