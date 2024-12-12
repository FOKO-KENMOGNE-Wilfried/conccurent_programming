#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "IngredientQuantite.h"
#include "IngredientEnum.h"
#include "Recette.h"

class RecipeBook {

public:
    static std::string getIngredientName(IngredientsEnum ingredientEnum);
    static std::vector<IngredientQuantite> getIngredientEnums(Recette recette);
};

#endif