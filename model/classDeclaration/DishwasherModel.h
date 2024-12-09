//
// Created by darkwall on 12/2/24.
//

#ifndef DISHWASHERMODEL_H
#define DISHWASHERMODEL_H
using namespace std;

/**
 * @class DishwasherModel
 */
class DishwasherModel {
public:
    double abscice;
    double intercept;
    /**
     * @brief
     *
     * @param plates_number
     * @param glasses_number
     * @param cutlery_number
     */
    DishwasherModel(double abscise, double intercept /*, int plates_number, int glasses_number, int cutlery_number*/)
    :   //   platesNumber(plates_number),
        //   glassesNumber(glasses_number),
        //   cutleryNumber(cutlery_number), 
          intercept(intercept), abscice(abscise) {
    }
    // ~DishwasherModel();
    void releaseDishes();
    int getPlatesNumber();
    int getGlassesNumber();
    int getCutleryNumber();
    void setCutleryNumber(int cutlery_number);
    void setGlassesNumber(int glasses_number);
    void setPlatesNumber(int plates_number);

private:
    int platesNumber;
    int glassesNumber;
    int cutleryNumber;

};
#endif //DISHWASHERMODEL_H
