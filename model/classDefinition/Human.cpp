//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/Human.h"
#include <iostream>
#include <QDebug>


void Human::move() {
    abscice = 100;
    intercept = 100;
}

Human::Human(double abscice, double intercept) {
    this->abscice = abscice;
    this->intercept = intercept;
}
// double Human::getAbscice(){
//     return this->abscice;
// }
// double Human::getIntercept(){
//     return this->abscice;
// }
// void Human::setAbscice(double abscice){
//     this->abscice = abscice;
// }
// void Human::setIntercept(double intercept){
//     this->intercept = intercept;
// }
Human::Human(){}
void Human::sayHello(){
    std::cout << "Hello world!" << std::endl;
}