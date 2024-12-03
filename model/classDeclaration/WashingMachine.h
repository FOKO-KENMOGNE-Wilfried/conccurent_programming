//
// Created by wolverine on 12/2/24.
//

#ifndef WASHINGMACHINE_H
#define WASHINGMACHINE_H
using namespace std;

/**
 * @class WashingMachine
 */
class WashingMachine {
public:
    /**
     * @brief
     *
     * @param towels_number
     * @param wash_towels
     */
    WashingMachine(int towels_number, int wash_towels)
        : towelsNumber(towels_number),
          washTowels(wash_towels) {
    }

    int getTowelsNumber();
    void setTowelsNumber(int towels_number);

private:
    int towelsNumber;
    int washTowels;

};
#endif //WASHINGMACHINE_H
