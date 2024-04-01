#ifndef USERS_H
#define USERS_H


#include <conio.h>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

//定义Dish结构体
struct Dish {
    string name;
    string category;
    double price;
    Dish  *next;
};

//声明DishList类
class DishList {
private:
    Dish *head;

public:
    DishList()
        : head(nullptr) {
    }
    void loadFromFile(const string &filename);
    void saveToFile(const string &filename);
    void addDish(string name, string category, double price);
    void deleteDish(string name);
    void updateDish(string name, string newCategory, double newPrice);
    void searchDish(const string &keyword, const string &searchType);
    void displayDishes();
    ~DishList();
};

extern int    f1;
extern string name;
int           main();
void          homepage();
void          regist();
void          login();

void CommonUser();
void delete_account(const string &name);

void changedishes();
void adminchoose();

void   dishbill();
void   displayDishesPerLine(const std::string &filename);
double findDishPrice(const std::string &dishName, const std::vector<Dish> &dishes);
void   writeOrder(const std::map<std::string, int> &order, const std::vector<Dish> &dishes);

#endif