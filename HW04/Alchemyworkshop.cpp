#include "AlchemyWorkshop.h"

PotionRecipe::PotionRecipe(const std::string& name,
    const std::vector<std::string>& ingredients)
    : potionName(name), ingredients(ingredients) {
}

const PotionRecipe* AlchemyWorkshop::findRecipeByName(const std::string& name) const {
    for (const auto& recipe : recipes) {
        if (recipe.potionName == name) return &recipe;
    }
    return nullptr;
}

void AlchemyWorkshop::addRecipe(const std::string& name,
    const std::vector<std::string>& ingredients) {
    if (findRecipeByName(name)) {
        std::cout << ">> 이미 존재하는 레시피입니다: " << name << std::endl;
        return;
    }
    recipes.push_back(PotionRecipe(name, ingredients));
    inventory[name] = MAX_STOCK;
    std::cout << ">> 새로운 레시피 '" << name
        << "'이(가) 추가되었습니다. (초기 재고: " << MAX_STOCK << "개)" << std::endl;
}

void AlchemyWorkshop::displayAllRecipes() const {
    if (recipes.empty()) {
        std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
        return;
    }
    std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
    for (const auto& recipe : recipes) {
        std::cout << "- 물약 이름: " << recipe.potionName << std::endl;
        std::cout << "  > 필요 재료: ";
        for (size_t j = 0; j < recipe.ingredients.size(); ++j) {
            std::cout << recipe.ingredients[j];
            if (j < recipe.ingredients.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------\n";
}

void AlchemyWorkshop::searchByPotionName(const std::string& name) const {
    const PotionRecipe* recipe = findRecipeByName(name);
    if (!recipe) {
        std::cout << ">> '" << name << "' 이름의 레시피를 찾을 수 없습니다." << std::endl;
        return;
    }
    std::cout << "\n--- [ 검색 결과: 물약 이름 ] ---" << std::endl;
    std::cout << "- 물약 이름: " << recipe->potionName << std::endl;
    std::cout << "  > 필요 재료: ";
    for (size_t j = 0; j < recipe->ingredients.size(); ++j) {
        std::cout << recipe->ingredients[j];
        if (j < recipe->ingredients.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "--------------------------------\n";
}

void AlchemyWorkshop::searchByIngredient(const std::string& ingredient) const {
    std::vector<const PotionRecipe*> results;
    for (const auto& recipe : recipes) {
        for (const auto& ing : recipe.ingredients) {
            if (ing == ingredient) {
                results.push_back(&recipe);
                break;
            }
        }
    }
    if (results.empty()) {
        std::cout << ">> '" << ingredient << "' 재료가 포함된 레시피를 찾을 수 없습니다." << std::endl;
        return;
    }
    std::cout << "\n--- [ 검색 결과: 재료 '" << ingredient << "' ] ---" << std::endl;
    for (const auto* recipe : results) {
        std::cout << "- 물약 이름: " << recipe->potionName << std::endl;
        std::cout << "  > 필요 재료: ";
        for (size_t j = 0; j < recipe->ingredients.size(); ++j) {
            std::cout << recipe->ingredients[j];
            if (j < recipe->ingredients.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------------\n";
}

void AlchemyWorkshop::displayInventory() const {
    if (inventory.empty()) {
        std::cout << "창고가 비어 있습니다." << std::endl;
        return;
    }
    std::cout << "\n--- [ 창고 재고 현황 ] ---" << std::endl;
    for (const auto& pair : inventory) {
        std::cout << "- " << pair.first << " : " << pair.second << "개" << std::endl;
    }
    std::cout << "--------------------------\n";
}

void AlchemyWorkshop::dispensePotion(const std::string& query) {
    std::vector<std::string> candidates;
    for (const auto& recipe : recipes) {
        if (recipe.potionName == query) {
            candidates.push_back(recipe.potionName);
            continue;
        }
        for (const auto& ing : recipe.ingredients) {
            if (ing == query) {
                candidates.push_back(recipe.potionName);
                break;
            }
        }
    }
    if (candidates.empty()) {
        std::cout << ">> '" << query << "'에 해당하는 물약을 찾을 수 없습니다." << std::endl;
        return;
    }
    std::string targetName;
    if (candidates.size() == 1) {
        targetName = candidates[0];
    }
    else {
        std::cout << "\n여러 물약이 검색되었습니다. 지급할 물약을 선택하세요:" << std::endl;
        for (size_t i = 0; i < candidates.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << candidates[i] << std::endl;
        }
        std::cout << "선택 (번호 입력): ";
        int sel;
        std::cin >> sel;
        if (std::cin.fail() || sel < 1 || sel > static_cast<int>(candidates.size())) {
            std::cout << ">> 잘못된 선택입니다." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }
        targetName = candidates[sel - 1];
    }
    int& stock = inventory[targetName];
    if (stock <= 0) {
        std::cout << ">> '" << targetName << "' 의 재고가 없습니다. 지급할 수 없습니다." << std::endl;
        return;
    }
    --stock;
    std::cout << ">> '" << targetName << "'을(를) 모험가에게 지급했습니다. (남은 재고: "
        << stock << "개)" << std::endl;
}

void AlchemyWorkshop::returnPotion(const std::string& potionName) {
    if (!findRecipeByName(potionName)) {
        std::cout << ">> '" << potionName << "' 은(는) 등록되지 않은 물약입니다." << std::endl;
        return;
    }
    int& stock = inventory[potionName];
    if (stock >= MAX_STOCK) {
        std::cout << ">> '" << potionName << "' 창고가 이미 최대(" << MAX_STOCK
            << "개)입니다. 반환이 불가합니다." << std::endl;
        return;
    }
    ++stock;
    std::cout << ">> '" << potionName << "' 공병을 반환받았습니다. (현재 재고: "
        << stock << "개)" << std::endl;
}