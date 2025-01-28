/*
CSCI235 Spring 2024
Project 7 - Binary Skill Tree
Jeremiah Gonzalez
May 6 2024
SkillTree.hpp declares the SkillTree class along with its private and public members
*/
#include "SkillTree.hpp"
#include "BinarySearchTree.hpp"
#include "BinaryNode.hpp"
#include <fstream>
#include <sstream>

/**
  * Default SkillTree Constructor
*/
SkillTree::SkillTree() {}

// Parameterized constructor for SkillTree
/**
 * @param: A const reference to string: the name of a csv file
 * @post: The SkillTree is populated with Skills from the csv file
 * The file format is as follows:
 * id,name,description,leveled
 * Ignore the first line. Each subsequent line represents a Skill to be added to the SkillTree.
*/
SkillTree::SkillTree(const std::string& fileName){
    
  std::ifstream fin(fileName);
  std::string line;
  std::getline(fin, line); //getting junk header
  std::string str_id, str_name, str_leveled, str_description;
  int id;
  bool leveled;

  while(std::getline(fin, line))
  {
    std::istringstream iss(line);
    std::getline(iss, str_id, ',');
    std::getline(iss, str_name, ',');
    std::getline(iss, str_description, ',');
    std::getline(iss, str_leveled, ',');
  

    std::istringstream(str_id) >> id;   //turning the strings into int
    std::istringstream(str_leveled) >> leveled; //turning string into a bool

    Skill new_Skill(id, str_name, str_description, leveled);    //creating a new skill object and add it to the SkillTree
    add(new_Skill);

    }
}
/**
 * @param: A const reference to int representing the id of the Skill to be found
 * @return: A pointer to the node containing the Skill with the given id, or nullptr if the Skill is not found
*/
std::shared_ptr<BinaryNode<Skill>> SkillTree::findSkill(const int& skill_id) const{
    std::shared_ptr<BinaryNode<Skill>> node = getRoot();
    while(node != nullptr){
        if(node -> getItem().id_ == skill_id){
            return node;
        }
        else if(node -> getItem().id_ > skill_id){
            node = node->getLeftChildPtr();
        }
        else 
            node = node->getRightChildPtr();
    }
        return nullptr;
}

/**
  * @param: A const reference to Skill 
  * @post: The Skill is added to the tree (in BST order as implemented in the base class) only if it was not already in the tree. Note that all comparisons are id-based as implemented by the Skill comparison operators.
  * @return: True if the Skill is successfully added to the SkillTree, false otherwise
  */
bool SkillTree::addSkill(const Skill& added_skill){
    if (contains(added_skill)) {
        return false; // Skill already exists in the tree
    } else {
        add(added_skill); // Add the skill to the tree using the function from Binary search Tree
        return true;
    }
}

/**
  * @param: A const reference to string: the name of a Skill
  * @return: True if the Skill is successfully removed from the SkillTree, false otherwise
*/
bool SkillTree::removeSkill(const std::string& remove_skill){

    bool is_successful = false;

    removeHelper(root_ptr_, remove_skill, is_successful);
    return is_successful;
}

void SkillTree::removeHelper(std::shared_ptr<BinaryNode<Skill>> current_node, const std::string& remove_skill, bool& success_removal) {
    if (current_node == nullptr) {
        success_removal = false; // Skill not found
    }
    if(current_node -> getItem().name_ == remove_skill){    // If the current node's item matches the skill to be removed, call the remove function 
        remove(current_node->getItem());
        success_removal = true; //removal was successful 
    }
    else{
        if(current_node ->getItem().name_ > remove_skill){
            removeHelper(current_node -> getLeftChildPtr(), remove_skill, success_removal);  // If the skill to be removed should be located in the left subtree
        }
        else{
            removeHelper(current_node -> getRightChildPtr(), remove_skill, success_removal);    //right subtree
        }
    }
}
/**
  * @post: Clears the tree
  */
void SkillTree::clear(){
   removeNode(root_ptr_);
    root_ptr_ = nullptr; // Set the root pointer to nullptr after clearing
}

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
int SkillTree::calculateSkillPoints(const int& skill_id){

    int skill_Points = 0;    //variable to store the skill points

    std::shared_ptr<BinaryNode<Skill>> current = root_ptr_; //searching from the root

    while (current != nullptr) {     // Traverse the tree until the skill with the given id is found 

        skill_Points++;

        if (current->getItem().id_ == skill_id) {    //current node contains the skill with the given id, return the accumulated skill points
            return skill_Points;
        }
        if (skill_id < current->getItem().id_) {      // Move to the left child if the skill id is less than the current node's id
            current = current->getLeftChildPtr();
        }
        else {
            current = current->getRightChildPtr();  // Move to the right child if the skill id is greater than the current node's id
        }
    }
    return -1;
}


/**
  * @post: Balances the tree. Recall the definition of a balanced tree:
  * A tree is balanced if for any node, its left and right subtrees differ in height by no more than 1. * All paths from root of subtrees to leaf differ in length by at most 1
  * Hint: You may sort the elements and build the tree recursively using a divide and conquer approach      
  */
void SkillTree::balance(){
    std::vector<Skill> sorted_Skills;   //Collect all nodes in sorted order
    collect_Nodes_In_Order(root_ptr_, sorted_Skills);

    root_ptr_ = build_a_Balanced_Tree(sorted_Skills, 0, sorted_Skills.size() - 1);  //Rebuild the tree with the sorted nodes
}

void SkillTree::collect_Nodes_In_Order(std::shared_ptr<BinaryNode<Skill>> node, std::vector<Skill>& sorted_Skills) const {
    if (node == nullptr) {
        return; // Check if the current node is nullptr
    }
    collect_Nodes_In_Order(node->getLeftChildPtr(), sorted_Skills); // Traverse the left subtree in an in-order manner
    sorted_Skills.push_back(node->getItem());    // Add the item stored in the current node to the vector
    collect_Nodes_In_Order(node->getRightChildPtr(), sorted_Skills);
}

std::shared_ptr<BinaryNode<Skill>> SkillTree::build_a_Balanced_Tree(const std::vector<Skill>& sorted_Skills, int start_of_tree, int end_of_tree) {
    if (start_of_tree > end_of_tree) {
        return nullptr; // Check if the current node is nullptr
    }
    int middle_node = (start_of_tree + end_of_tree) / 2;    // Calculate the index of the middle element
    std::shared_ptr<BinaryNode<Skill>> newNode = std::make_shared<BinaryNode<Skill>>(sorted_Skills[middle_node]);    // Create a new shared pointer to a BinaryNode object with the skill at the middle index

    newNode->setLeftChildPtr(build_a_Balanced_Tree(sorted_Skills, start_of_tree, middle_node - 1));  // Recursively build the left subtree using elements before the middle index
    newNode->setRightChildPtr(build_a_Balanced_Tree(sorted_Skills, middle_node + 1, end_of_tree));

    return newNode;
}

/**
  * @post: prints the tree in preorder, in the format:
  [id_] [name_]\n
  [description_]\n 
  [leveled_]
  */
void SkillTree::preorderDisplay(){

    preorderDisplay_helper(getRoot());  //calling helper function 

  }

  void SkillTree::preorderDisplay_helper(std::shared_ptr<BinaryNode<Skill>> display_node){

    if (display_node == NULL)
        return;

    // First print data of node
    std::cout << display_node->getItem().id_ << " " << display_node->getItem().name_ << "\n";
    std::cout << display_node->getItem().description_ << "\n";
    std::cout << display_node->getItem().leveled_ << "\n";

    // Then recur on left subtree
    preorderDisplay_helper(display_node->getLeftChildPtr());

    // Now recur on right subtree
    preorderDisplay_helper(display_node->getRightChildPtr());
  }

