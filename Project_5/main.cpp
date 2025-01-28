/*
CSCI235 Spring 2024
Project 5 - Pantry struct 
Jeremiah Gonzalez
Mar 25 2024 
Pantry.hpp declares the Cavern class along with its private and public members
*/
#include "Pantry.hpp"
#include "LinkedList.hpp"
#include <iostream>


int main(){

Pantry pantry("debug.csv");


pantry.ingredientQuery("in1");
std::cout<<std::endl;

pantry.ingredientQuery("in2");
std::cout<<std::endl;

pantry.ingredientQuery("in3");
std::cout<<std::endl;

pantry.ingredientQuery("in4");
std::cout<<std::endl;

pantry.ingredientQuery("in5");
std::cout<<std::endl;

pantry.ingredientQuery("in6");
std::cout<<std::endl;

pantry.ingredientQuery("in7");
std::cout<<std::endl;

pantry.ingredientQuery("in8");
std::cout<<std::endl;

// Pantry test;
// test.addIngredient("sludge","blue",5,5,{});
// test.addIngredient("slu","blue",5,5,{});
// test.addIngredient("slud","blue",5,5,{});

// //std::cout << test.getLength() << std::endl;

// test.pantryList("CONTAINS");

// test.ingredientQuery("");













}