/*
CSCI235 Spring 2024
Project 5 - Pantry struct 
Jeremiah Gonzalez
April 1 2024 
Pantry.hpp declares the Pantry class along with its private and public members
Creating a Param constructor and using recursion in two different circustances 
*/

#include "LinkedList.hpp"
#include "Pantry.hpp"
#include "Node.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

Pantry::Pantry() : LinkedList<Ingredient*> () { //Default Constructor
    
}

/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows:
        Name: A string
        Description: A string
        Quantity: A non negative integer
        Price: A non negative integer
        Recipe: A list of Ingredient titles of the form [NAME1] [NAME2];
        For example, to make this ingredient, you need (Ingredient 1 AND Ingredient 2)
        The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The recipe are separated by a semicolon and may be NONE.
        - The recipe may be in any order.
        - If any of the recipe are not in the list, they should be created as new ingredients with the following information:
            - Title: The name of the ingredient
            - Description: "UNKNOWN"
            - Quantity: 0
            - Recipe: An empty vector
        - However, if you eventually encounter a ingredient that matches one of the "UNKNOWN" ingredients while parsing the file, you should update all the ingredient details.
        
        For example, given a row in the file:
        Inferno_Espresso,An energizing elixir brewed with mystical flames providing resistance to caffeine crashes for a limited time.,1,50,Fiery_Bean Ember_Spice

        The order of the ingredients in the list:
        Fiery_Bean, Ember_Spice, Inferno_Espresso
        Hint: update as needed using addIngredient()
        
    @post: Each line of the input file corresponds to a ingredient to be added to the list. No duplicates are allowed.
    Hint: use std::ifstream and getline()
*/
Pantry::Pantry(const std::string& file){    //checking to see if file opens or not 

    std::ifstream read(file); //reads the file 

    if(!read.is_open()){
      std::cout << "Error: File can't be opened" << std::endl;  //file cant open 
    }

    std::string line;

    std::getline(read, line); //reading in the first line/ ignoring it

while(std::getline(read, line)){
    
    std::stringstream ssline(line);

    std::string name, description, quantity, price, recipe;

    std::vector <Ingredient*> recipe_vector; // empty vector

    std::getline(ssline, name, ',');
    std::getline(ssline, description, ',');
    std::getline(ssline, quantity, ',');
    std::getline(ssline, price, ',');
    std::getline(ssline, recipe, ';');

    int int_quantity = std::stoi(quantity);
    int int_price = std::stoi(price);


    std::istringstream recipe_stream(recipe);
    std::string temp_recipe = "";

        while (std::getline(recipe_stream, temp_recipe, ' ')) {
            if (temp_recipe != "NONE\r") {
                if (getPosOf(temp_recipe) != -1) { // if the position != -1, which means there is something inside the linked list
                Node<Ingredient*> *recipe_node = getPointerTo(getPosOf(temp_recipe)); // converts the int from getPosOf to a pointer
                recipe_vector.push_back(recipe_node -> getItem()); // pushes back the node's item (a recipe) into the empty vector into the linked list
              }
              else {    //default values
                Ingredient* default_pantry = new Ingredient; // creates a new object
                default_pantry -> name_ = name; // sets the quest title to the title stored in temp_depend
                default_pantry -> description_ = "UNKNOWN"; // sets the quest description to "UNKNOWN"
                default_pantry -> quantity_ = 0; // sets the quantity to 0
                default_pantry -> price_ = 0; // sets the price to 0
                default_pantry -> recipe_ = {}; // sets the recipe to a empty vector {}
                addIngredient(default_pantry); // adds the ingredient
                recipe_vector.push_back(default_pantry); // adds the deafult_pantry as a new pantry
            }
            if(contains(name)){
                recipe_vector.push_back(getEntry(getPosOf(name)));  //if the recipe exist put in the values already there 
            }
          }
        }
              addIngredient(name, description, int_quantity, int_price, recipe_vector); //add the containing values into each of their variables 
    }
}

/**
        Destructor
        @post: Explicitly deletes every dynamically allocated Ingredient object
*/
Pantry::~Pantry() {
    clear();
}

/**
    @param: A const string reference to a ingredient name
    @return: The integer position of the given ingredient if it is in the Pantry, -1 if not found.
*/  
int Pantry::getPosOf(const std::string& ingredient_name) const{
    Node<Ingredient*>* new_node = getHeadNode();    //making a new pointer to the head pointer 
    int position = 0;

    while(new_node != nullptr){
        if(new_node -> getItem() -> name_ == ingredient_name){  //seeing if the name = to the ingredient name inputted 
            return position;
        }
            position++;
            new_node = new_node -> getNext();   //setting the currnt node to the next one (sorted list)
        }
    
    return -1;  //returning -1 if the pantry isnt in the linked list 
}

/**
    @param: A const string reference to a ingredient name
    @return: True if the ingredient information is already in the Pantry
*/
bool Pantry::contains(const std::string& ingredient_name) const{
    return getPosOf(ingredient_name) != -1;
}

/**
    @param:  A pointer to an Ingredient object
    @post:  Inserts the given ingredient pointer into the Pantry, unless an ingredient of the same name is already in the pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully, false otherwise.
*/
bool Pantry::addIngredient(Ingredient* add){
     if(contains(add ->name_) && getPointerTo(getPosOf(add->name_)) -> getItem() -> description_ != "UNKNOWN"){
        return false;
    }
    else if(contains(add->name_) && getPointerTo(getPosOf(add->name_)) -> getItem() -> description_ == "UNKNOWN"){  //updating Ingredient values 
        getPointerTo(getPosOf(add->name_)) -> getItem()  -> name_ = add -> name_;
        getPointerTo(getPosOf(add->name_)) -> getItem()  -> description_ = add -> description_;
        getPointerTo(getPosOf(add->name_)) -> getItem()  -> quantity_  = add -> quantity_;
        getPointerTo(getPosOf(add->name_)) -> getItem()  -> price_ = add -> price_;
        getPointerTo(getPosOf(add->name_)) -> getItem()  -> recipe_ = add -> recipe_;
        return true;
    }
    else {
       insert(getLength(), add); //Ingredient doesnt exist so I add it to the pantry 
       return true;
    }   
}

/**
    @param: A const string reference representing a ingredient name
    @param: A const string reference representing ingredient description
    @param: A const int reference representing the ingredient's quantity
    @param: A const int reference representing the ingredient's price
    @param: A const reference to a vector holding Ingredient pointers representing the ingredient's recipe
    @post:  Creates a new Ingredient object and inserts a pointer to it into the Pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully
*/
bool Pantry::addIngredient(const std::string& name, const std::string& ingredient_description, const int& ingredient_quantity, const int& ingredient_price, const std::vector<Ingredient*>& recipe){
    Ingredient* ingredient = new Ingredient(name, ingredient_description, ingredient_quantity, ingredient_price, recipe);   //Creating a new ingredient 
    return addIngredient(ingredient);
    }

/**
    @param:  A Ingredient pointer
    @return: A boolean indicating if all the given ingredient can be created (all of the ingredients in its recipe can be created, or if you have enough of each ingredient in its recipe to create it)
*/
bool Pantry::canCreate(Ingredient* can_create_ingredient) const{  //checks if the recipe is empty 
    if(can_create_ingredient -> recipe_.empty()){
        return false;
    }
    for(Ingredient* Ingredient_rec : can_create_ingredient -> recipe_){ //Iterate trhough each ingredient in the recipe
        int recipe_Position = getPosOf(Ingredient_rec -> name_);    //gets position of the current ingredient in the pantry 
        if(recipe_Position == -1){
            return false;
        }
    Ingredient* Entry_of_Ingredient = getEntry(recipe_Position);    //entry of the ingredient from the pantry 
    if(Entry_of_Ingredient -> quantity_ == 0 && !canCreate(Entry_of_Ingredient)){   //recursion 
        return false;
        }
    }
        return true;    //everything is found return true 
}

/**
    @param: A Ingredient pointer
    @post: Prints the ingredient name, quantity, and description.
    The output should be of the form:
    [Ingredient Name]: [Quantity]\n
    [Ingredient Description]\n
    Price: [Price]\n
    Recipe:\n
    [Ingredient0] [Ingredient1]\n


    If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
*/
void Pantry::printIngredient(Ingredient* print_ingredient) const{
    
    std::cout 
    <<print_ingredient -> name_ << ": " << print_ingredient -> quantity_ << "\n" //name and quantity
    <<print_ingredient -> description_ << "\n"
    << "Price: " << print_ingredient -> price_ << "\n"
    << "Recipe: " << "\n";
    if(print_ingredient -> recipe_.empty()){
        std::cout << "NONE\n\n";
    }
    if((print_ingredient -> recipe_).size() > 0){   //if the recipe exist print out 
        for(int i = 0; i < (print_ingredient -> recipe_).size(); i++){
            std::cout << print_ingredient -> recipe_[i] -> name_ << " ";  //printing out the Ingredient (accessing the vector to get the position of name than the position of ingredient name)
          
        }
        std::cout << "\n";
    }
}

/**
    @param: A const string reference to a ingredient name
    @post:  Prints a list of ingredients that must be created before the given ingredient can be created (missing ingredients for its recipe, where you have 0 of the needed ingredient).
            If the ingredient is already in the pantry, print "In the pantry([quantity])\n"
            If there are no instances of the ingredient, if it cannot be crafted because of insufficient ingredients, print "[Ingredient Name](0)\nMISSING INGREDIENTS"
            If it can be crafted, recursively print the ingredients that need to be used (if there are instances of them) or created (if there are no instances of them) in the order that the ingredients appear in the recipe, joined by "<-".
            If the ingredient has no recipe, print "UNCRAFTABLE\n" at the end of the function.

            Below are some of the expected forms. "Scenario: [scenario] is not part of the output. It is just to help you understand the expected output.":

            Scenario: The Ingredient does not exist in the list
            Query: [Ingredient Name]
            No such ingredient

            Scenario: The Ingredient exists in the list, and there are >0 instances of it
            Query: [Ingredient Name]
            In the pantry ([Quantity])

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that is already in the pantry
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](1)

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that has to be crafted
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](C) <- [Ingredient Name2](3)
            
            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and there are multiple ingredients that have to be crafted (each row represents a different ingredient inå the original recipe)
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](C) <- [Ingredient Name2](3)
            [Ingredient Name3](C) <- [Ingredient Name4](C) <- [Ingredient Name5] (3)

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is not craftable (it has no recipe)
            Query: [Ingredient Name0]
            UNCRAFTABLE

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it has a recipe, but you do not have enough of the ingredients to craft it
            Query: [Ingredient Name0]
            [Ingredient Name0](0)
            MISSING INGREDIENTS
    
        HINT: Use canCreate() to determine if the ingredient can be created.
    */
    void Pantry::ingredientQuery(const std::string &ingredient_query) const {
        std::cout << "Query: " << ingredient_query << "\n"; //print out Query and int naum

        int temp_position = getPosOf(ingredient_query);

        if (!contains(ingredient_query)) {   //ingredient doesnt exist 
            std::cout << "No such ingredient" << "\n";
         }   
        Ingredient* ingredient = getEntry(temp_position);

        if (temp_position != -1 && ingredient -> quantity_ > 0) {   //Ingredient exists in the list, and there are >0 instances of it
            std::cout << "In the pantry (" << ingredient -> quantity_ << ")" << "\n";
                if (!canCreate(ingredient)) {
                    std::cout << "UNCRAFTABLE" << "\n";
                    return;
            }   
        }
        if (temp_position != -1 && ingredient -> recipe_.empty()) {
                std::cout << "UNCRAFTABLE" << "\n";
                return;
        }

        if (temp_position != -1 && ingredient -> quantity_ == 0 && !ingredient -> recipe_.empty()) { //Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that is already in the pantry
            if (canCreate(ingredient)) {
                std::cout << ingredient -> name_ << "(C)" << "\n";
                for (int i = 0; i < ingredient -> recipe_.size(); i++) {
                    if (ingredient -> recipe_[i] -> quantity_ == 0 && !canCreate(ingredient -> recipe_[i])) {
                        std::cout << "MISSING INGREDIENT" << "\n";
                    } else {
                        ingredientQuery_Helper(ingredient -> recipe_[i]);
                    }
                }
            } else {
                std::cout << ingredient -> name_ << "(0)" << "\n";  //else The ingredients are missing 
                std::cout << "MISSING INGREDIENT" << "\n";
            } 
        }
};

    //helper function (recursion)
    void Pantry::ingredientQuery_Helper(Ingredient* ingredient_helper) const {
        if (ingredient_helper -> quantity_ > 0) {
            std::cout << ingredient_helper -> name_ << "(" << ingredient_helper -> quantity_ << ")" << "\n";
                return;
    } else if (ingredient_helper -> quantity_ == 0 && canCreate(ingredient_helper)) {
        std::cout << ingredient_helper -> name_ << "(C) <-";
        for (int i = 0; i < ingredient_helper -> recipe_.size(); i++) {
            ingredientQuery_Helper(ingredient_helper -> recipe_[i]);
        }
    }
};

    /**
    @return: An integer sum of the price of all the ingredients currently in the list.
    Note: This should only include price values from ingredients that you have 1 or more of. Do not consider ingredients that you have 0 of, even if you have the ingredients to make them.
    */
    int Pantry::calculatePantryValue() const{

        int Pantry_value = 0;

        for(int i = 0; i < getLength(); i++){   //iterates through each ingredient in the pantry
            Ingredient* ingredient_entry = getEntry(i); //retrieves the ingredient at index i in the pantry
            Pantry_value += ingredient_entry -> price_ * ingredient_entry -> quantity_;  //calcuating the total pantry value (value is added to the Pantry_value variable, which accumulates the total value of the pantry)
        }
            return Pantry_value;
    }

    /**
    @param: A const string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every ingredient in the list.
        With filter "CONTAINS":   Only print out the ingredients with >0 instances in the list.
        With filter "MISSING": Only print out the ingredients with 0 instances in the list.
        With filter "CRAFTABLE":  Only print out the ingredients where you have all the ingredients to craft them.
        If an invalid filter is passed, print "INVALID FILTER\n"
        Printing ingredients should be of the form:

        [Ingredient name]: [Quantity]
        [Ingredient description]\n
        Price: [price]\n
        Recipe:\n
        [Ingredient0] [Ingredient1]\n\n

        If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
    */
    void Pantry::pantryList(const std::string& filter) const{
        
        Node<Ingredient*>* new_node = getHeadNode();
            
        while(new_node != nullptr){ //while the new node is not empty print all of the ingredients in the list 

             if(filter == "NONE"){
                printIngredient(new_node -> getItem());
             }
            else if(filter == "CONTAINS"){
                if(new_node -> getItem() -> quantity_ > 0) {
                    printIngredient(new_node -> getItem());
                }
             }
            else if(filter == "MISSING"){
                if(new_node -> getItem() -> quantity_ == 0) {
                    printIngredient(new_node -> getItem());
                }
             }
            else if(filter == "CRAFTABLE"){
                if(canCreate(new_node -> getItem() )){
                    printIngredient(new_node -> getItem());
                }
             }
            else {
                std::cout << "INVALID FILTER\n";
             }
                new_node = new_node -> getNext();
            }
     }

