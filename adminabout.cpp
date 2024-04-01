#include "users.h"

using namespace std;

void adminchoose();
void changedishes();

// 管理员用户选择修改菜品
void adminchoose()
{
    int number;
    cout << "\n===============================\n";
    cout << "|How are you today?           |\n|press 1 to change dishes     |\n|press 2 to back to login page|" << endl;
    cout << "===============================\n";
    number = getch();
    cout << char(number) << endl;
    if (number == '1')
    {
        changedishes();
    }
    else if (number == '2')
    {
        main();
    }
    else
    {
        cout << "bad input :(\n";
        adminchoose();
    }
}

// 修改菜品目录
void changedishes()
{
    DishList dishList;
    dishList.loadFromFile("dishes.txt");

    while (true)
    {
        cout << "========================" << endl;
        cout << "|Menu:                 |" << endl;
        cout << "|1. Display all dishes |" << endl;
        cout << "|2. Add a new dish     |" << endl;
        cout << "|3. Delete a dish      |" << endl;
        cout << "|4. Update a dish      |" << endl;
        cout << "|5. Search for a dish  |" << endl;
        cout << "|6. Save and exit      |" << endl;
        cout << "========================" << endl;

        int choice;
        cout << ">>";
        cin >> choice;

        if (choice == 1)
        {
            // 显示全部菜品
            dishList.displayDishes();
        }
        else if (choice == 2)
        {
            // 添加菜品
            string name, category, ss;
            double price;
            cout << "Enter dish name: " << endl;
            getline(cin, ss); // 吸收缓冲区的\n
            getline(cin, name);
            cout << "Enter dish category: " << endl;
            cin >> category;
            cout << "Enter dish price: " << endl;
            cin >> price;
            dishList.addDish(name, category, price);
        }
        else if (choice == 3)
        {
            // 删除菜品
            string name;
            cout << "Enter the name of the dish to delete: " << endl;
            cin >> name;
            dishList.deleteDish(name);
        }
        else if (choice == 4)
        {
            // 修改菜品信息，不修改菜品名
            string name, newCategory;
            double newPrice;
            cout << "Enter the name of the dish to update: " << endl;
            cin >> name;
            cout << "Enter new category: " << endl;
            cin >> newCategory;
            cout << "Enter new price: " << endl;
            cin >> newPrice;
            dishList.updateDish(name, newCategory, newPrice);
        }
        else if (choice == 5)
        {
            // 按照关键词查找（本质上是子串查找）
            string keyword, category;
            cout << "Enter keyword to search: " << endl;
            cin >> keyword;
            cout << "Enter search type: " << endl;
            cout << "Press 1 to search in name" << endl;
            cout << "Press 2 to search in category" << endl;
            cin >> category;
            dishList.searchDish(keyword, category);
        }
        else if (choice == 6)
        {
            // 保存并退出
            dishList.saveToFile("dishes.txt");
            adminchoose();
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            changedishes();
        }
    }
}