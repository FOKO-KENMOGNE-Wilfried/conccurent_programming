//
// Created by darkwall on 12/2/24.
//

#ifndef RECIPE_H
#define RECIPE_H

#include <iostream>
#include <utility>
#include <vector>

#include "UstensilModel.h"
#include "../../enum/RecipeBook.h"

using namespace std;

/**
 * @class Recipe
 *
 * @brief this class has the differents dishes of the card
 */
class Recipe {
public:
    /**
     *@brief the constructor of the class Recipe
     *
     * @param name
     * @param type
     * @param cooking_time
     * @param is_makable
     * @param ingredients_list
     * @param cooking_ustensils_list
     * @param eating_ustensil
     */

    Recipe(Recette recette);
    // ~Recipe();
    /**
     * @brief to change the feasibility of a dishes if it isn't feasible anymore
     */
    void toogleIsMakable();
    std::vector<IngredientQuantite> getRecipeSpecification();
private:
    string name;
    string type;
    int cookingTime;
    bool isMakable;
    vector<string*> ingredientsList;
    vector<UstensilModel*> cookingUstensilsList;
    vector<UstensilModel*> eatingUstensil;
    std::vector<IngredientQuantite> recipe;
};

#endif //RECIPE_H
