//
// Created by darkwall on 12/2/24.
//

#ifndef WASHINGMACHINE_H
#define WASHINGMACHINE_H
using namespace std;

/**
 * @class WashingMachine
 */
class WashingMachine {
public:
    double abscice;
    double intercept;
    /**
     * @brief
     *
     * @param towels_number
     * @param wash_towels
     */
    WashingMachine(double abscise, double intercept /*, int towels_number, int wash_towels */)
        :// : towelsNumber(towels_number),
        //   washTowels(wash_towels),
          intercept(intercept), abscice(abscise) {
    }

    int getTowelsNumber();
    void setTowelsNumber(int towels_number);
    WashingMachine();
    // ~WashingMachine();
private:
    int towelsNumber;
    int washTowels;

};
#endif //WASHINGMACHINE_H
