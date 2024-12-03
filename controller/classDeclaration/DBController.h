//
// Created by wolverine on 12/2/24.
//

#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H
#include <iostream>
using namespace std;

/**
 * @class DBController
 */
class DBController {
    string DBName;
    string DBPassword;
public:
    void DBconnect();
    void DBdisconnect();
    void makeRequest();

};
#endif //DBCONTROLLER_H
