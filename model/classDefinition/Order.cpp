//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/Order.h"


void Order::CreateCutlery() {
    // TODO add a method to create the differents cutlery on demand
}

std::vector<Recipe*> Order::getOrderRecipes(){
    return this->orderRecipes;
}

Order::Order(){}

Order::~Order(){}