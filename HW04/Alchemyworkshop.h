#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients;

    PotionRecipe(const std::string& name,
        const std::vector<std::string>& ingredients);
};

class AlchemyWorkshop {
public:
    static const int MAX_STOCK = 3;

private:
    std::vector<PotionRecipe>  recipes;
    std::map<std::string, int> inventory;

    const PotionRecipe* findRecipeByName(const std::string& name) const;

public:
    void addRecipe(const std::string& name,
        const std::vector<std::string>& ingredients);
    void displayAllRecipes() const;

    void searchByPotionName(const std::string& name) const;
    void searchByIngredient(const std::string& ingredient) const;

    void displayInventory() const;
    void dispensePotion(const std::string& query);
    void returnPotion(const std::string& potionName);
};