#include "../classDeclaration/WashingMachine.h"
//
// Created by darkwall on 12/2/24.
//
int WashingMachine::getTowelsNumber() {
    return towelsNumber;
}
void WashingMachine::setTowelsNumber(int towels_number) {
    this->towelsNumber = towels_number;
}

WashingMachine::WashingMachine(){}
