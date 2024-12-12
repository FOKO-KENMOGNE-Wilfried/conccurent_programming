//
// Created by darkwall on 12/2/24.
//
#include "../classDeclaration/Recipe.h"

void Recipe::toogleIsMakable() {
    this->isMakable = !this->isMakable;
}

Recipe::Recipe(Recette recette){
    this->recipe = RecipeBook::getIngredientEnums(recette);
}

std::vector<IngredientQuantite> Recipe::getRecipeSpecification(){
    return this->recipe;
}