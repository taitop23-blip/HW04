// Main.cpp

#include "AlchemyWorkshop.h"

static void printMenu() {
    std::cout << "\n⚗️  연금술 공방 관리 시스템\n"
        << "──────────────────────────\n"
        << " 1. 레시피 추가\n"
        << " 2. 모든 레시피 출력\n"
        << " 3. 물약 이름으로 검색\n"
        << " 4. 재료 이름으로 검색\n"
        << " 5. 창고 재고 확인\n"
        << " 6. 물약 지급\n"
        << " 7. 공병 반환\n"
        << " 0. 종료\n"
        << "선택: ";
}

int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        printMenu();

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << ">> 잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            std::vector<std::string> ingredientsInput;
            std::string ingredient;
            std::cout << "재료를 입력하세요 (완료 시 '끝' 입력)\n";
            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);
                if (ingredient == "끝") break;
                if (!ingredient.empty()) ingredientsInput.push_back(ingredient);
            }

            if (!ingredientsInput.empty()) {
                myWorkshop.addRecipe(name, ingredientsInput);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::string name;
            std::cout << "검색할 물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            myWorkshop.searchByPotionName(name);

        }
        else if (choice == 4) {
            std::string ingredient;
            std::cout << "검색할 재료 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, ingredient);
            myWorkshop.searchByIngredient(ingredient);

        }
        else if (choice == 5) {
            myWorkshop.displayInventory();

        }
        else if (choice == 6) {
            std::string query;
            std::cout << "지급할 물약 이름 또는 재료 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, query);
            myWorkshop.dispensePotion(query);

        }
        else if (choice == 7) {
            std::string name;
            std::cout << "반환할 물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            myWorkshop.returnPotion(name);

        }
        else if (choice == 0) {
            std::cout << "공방 문을 닫습니다... 안녕히 가세요!" << std::endl;
            break;

        }
        else {
            std::cout << ">> 잘못된 선택입니다. 다시 시도해주세요." << std::endl;
        }
    }

    return 0;
}