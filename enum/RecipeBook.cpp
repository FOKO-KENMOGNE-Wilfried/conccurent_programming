#include <iostream>
#include <vector>
#include <stdexcept>

#include "RecipeBook.h"

std::string RecipeBook::getIngredientName(IngredientsEnum ingredientEnum) {
        switch (ingredientEnum) {
            case IngredientsEnum::Tomate: return "Tomate";
            case IngredientsEnum::Oignon: return "Oignon";
            case IngredientsEnum::Piment: return "Piment";
            case IngredientsEnum::Sel: return "Sel";
            case IngredientsEnum::Poivre: return "Poivre";
            case IngredientsEnum::Huile: return "Huile";
            case IngredientsEnum::Ail: return "Ail";
            case IngredientsEnum::Gingembre: return "Gingembre";
            case IngredientsEnum::Curcuma: return "Curcuma";
            case IngredientsEnum::Cannelle: return "Cannelle";
            case IngredientsEnum::Paprika: return "Paprika";
            case IngredientsEnum::Basilic: return "Basilic";
            case IngredientsEnum::Romarin: return "Romarin";
            case IngredientsEnum::Thym: return "Thym";
            case IngredientsEnum::Safran: return "Safran";
            case IngredientsEnum::Menthe: return "Menthe";
            case IngredientsEnum::Persil: return "Persil";
            case IngredientsEnum::Coriandre: return "Coriandre";
            case IngredientsEnum::Origan: return "Origan";
            case IngredientsEnum::LaitueRomaine: return "LaitueRomaine";
            case IngredientsEnum::Carotte: return "Carotte";
            case IngredientsEnum::PouletGrille: return "PouletGrille";
            case IngredientsEnum::BoeufHache: return "BoeufHache";
            case IngredientsEnum::ChocolatNoir: return "ChocolatNoir";
            case IngredientsEnum::HaricotsRouges: return "HaricotsRouges";
            case IngredientsEnum::PommeDeTerre: return "PommeDeTerre";
            case IngredientsEnum::Poireau: return "Poireau";
            case IngredientsEnum::Sucre: return "Sucre";
            case IngredientsEnum::celeri: return "celeri";
            case IngredientsEnum::Farine: return "Farine";
            case IngredientsEnum::Celeri: return "Celeri";
            case IngredientsEnum::Croutons: return "Croutons";
            case IngredientsEnum::Parmesan: return "Parmesan";
            case IngredientsEnum::SauceCesar: return "SauceCesar";
            case IngredientsEnum::Oeufs: return "Oeufs";
            case IngredientsEnum::PoudreDAmande: return "PoudreDAmande";
            case IngredientsEnum::LevureChimique: return "LevureChimique";
            case IngredientsEnum::Beurre: return "Beurre";
            case IngredientsEnum::Cumin: return "Cumin";
            case IngredientsEnum::HerbesDeProvence: return "HerbesDeProvence";
            default: throw std::invalid_argument("Ingredient not foung");
        }
}
    std::vector<IngredientQuantite>  RecipeBook::getIngredientEnums(Recette recette) {
        switch (recette) {
            case Recette::SauceTomate:
                return {
                    {IngredientsEnum::Tomate, 10},
                    {IngredientsEnum::Oignon, 1},
                    {IngredientsEnum::Sel, 5},
                    {IngredientsEnum::Poivre, 2},
                    {IngredientsEnum::Huile, 15},
                    {IngredientsEnum::Basilic, 5}
                };
            case Recette::PoissonGrille:
                return {
                    {IngredientsEnum::Ail, 10},
                    {IngredientsEnum::Gingembre, 10},
                    {IngredientsEnum::Sel, 5},
                    {IngredientsEnum::Poivre, 2},
                    {IngredientsEnum::Huile, 20},
                    {IngredientsEnum::Thym, 2}
                };
            case Recette::PouletFrit:
                return {
                    {IngredientsEnum::Ail, 10},
                    {IngredientsEnum::Gingembre, 10},
                    {IngredientsEnum::Sel, 5},
                    {IngredientsEnum::Poivre, 2},
                    {IngredientsEnum::Huile, 50},
                    {IngredientsEnum::Paprika, 5},
                    {IngredientsEnum::Cannelle, 2}
                };
            case Recette::RizPilaf:
                return {
                    {IngredientsEnum::Tomate, 6},
                    {IngredientsEnum::Oignon, 1},
                    {IngredientsEnum::Ail, 10},
                    {IngredientsEnum::Sel, 5},
                    {IngredientsEnum::Poivre, 2},
                    {IngredientsEnum::Huile, 15},
                    {IngredientsEnum::Curcuma, 3}
                };
            case Recette::CurryLegumes:
                return {
                    {IngredientsEnum::Tomate, 10},
                    {IngredientsEnum::Oignon, 1},
                    {IngredientsEnum::Piment, 1},
                    {IngredientsEnum::Sel, 5},
                    {IngredientsEnum::Poivre, 2},
                    {IngredientsEnum::Huile, 20},
                    {IngredientsEnum::Ail, 10},
                    {IngredientsEnum::Gingembre, 10},
                    {IngredientsEnum::Curcuma, 3},
                    {IngredientsEnum::Paprika, 3}
                };
            case Recette::SpaghettiBolognese:
                return {
                    {IngredientsEnum::Tomate, 20},
                    {IngredientsEnum::Oignon, 1},
                    {IngredientsEnum::Carotte, 1},
                    {IngredientsEnum::Ail, 10},
                    {IngredientsEnum::Huile, 20},
                    {IngredientsEnum::Sel, 5},
                    {IngredientsEnum::Poivre, 2},
                    {IngredientsEnum::Basilic, 5},
                    {IngredientsEnum::Origan, 5}
                };
            case Recette::SaladeCesar:
                return {
                    {IngredientsEnum::LaitueRomaine, 1},
                    {IngredientsEnum::PouletGrille, 1},
                    {IngredientsEnum::Croutons, 50},
                    {IngredientsEnum::Parmesan, 30},
                    {IngredientsEnum::SauceCesar, 50}
                };
            case Recette::ChiliConCarne:
                return {
                    {IngredientsEnum::BoeufHache, 2},
                    {IngredientsEnum::HaricotsRouges, 1},
                    {IngredientsEnum::Tomate, 20},
                    {IngredientsEnum::Oignon, 1},
                    {IngredientsEnum::Piment, 1},
                    {IngredientsEnum::Ail, 10},
                    {IngredientsEnum::Huile, 20},
                    {IngredientsEnum::Sel, 5},
                    {IngredientsEnum::Poivre, 2},
                    {IngredientsEnum::Paprika, 5},
                    {IngredientsEnum::Cumin, 5}
                };
            case Recette::SoupeLegumes:
                return {
                    {IngredientsEnum::Carotte, 2},
                    {IngredientsEnum::PommeDeTerre, 2},
                    {IngredientsEnum::Poireau, 1},
                    {IngredientsEnum::Celeri, 1},
                    {IngredientsEnum::Tomate, 10},
                    {IngredientsEnum::Ail, 10},
                    {IngredientsEnum::Oignon, 1},
                    {IngredientsEnum::Huile, 15},
                    {IngredientsEnum::Sel, 5},
                    {IngredientsEnum::Poivre, 2},
                    {IngredientsEnum::HerbesDeProvence, 5}
                };
            case Recette::GateauChocolat:
                return {
                    {IngredientsEnum::ChocolatNoir, 10},
                    {IngredientsEnum::Beurre, 1},
                    {IngredientsEnum::Sucre, 4},
                    {IngredientsEnum::Farine, 2},
                    {IngredientsEnum::Oeufs, 4},
                    {IngredientsEnum::PoudreDAmande, 2},
                    {IngredientsEnum::LevureChimique, 5}
                };
            default:
                return {};
        }
    }