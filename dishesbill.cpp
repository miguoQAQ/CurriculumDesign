#include "users.h"

using namespace std;

void writeOrder(const map<string, int> &order, const vector<Dish> &dishes);
double findDishPrice(const string &dishName, const vector<Dish> &dishes);
void displayDishesPerLine(const string &filename);
void dishbill();

// 读取菜品信息
vector<Dish> readDishes(const string &filename) {
    ifstream     file(filename);
    vector<Dish> dishes;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string       name, category;
            double       price;
            if (getline(ss, name, ',') && getline(ss, category, ',') && ss >> price) {
                Dish dish = {name, category, price};
                dishes.push_back(dish);
            }
        }

        file.close();
    } else {
        cerr << "Error: Unable to open file" << endl;
    }

    return dishes;
}

// 写入用户订单到文件
void writeOrder(const map<string, int> &order, const vector<Dish> &dishes) {
    ofstream file(name + ".txt");
    if (file.is_open()) {
        file << "Username: " << name << "\n";
        file << "Order time: " << time(0) << "\n";
        double total = 0.0;
        for (auto &entry : order) {
            file << entry.first << " x" << entry.second << " Price: " << entry.second * findDishPrice(entry.first, dishes) << "\n";
            total += entry.second * findDishPrice(entry.first, dishes);
        }
        file << "Total price: " << total << "\n";
        file.close();
    } else {
        cerr << "Error: Unable to create order file" << endl;
    }
}

// 查找菜品价格
double findDishPrice(const string &dishName, const vector<Dish> &dishes) {
    for (const auto &dish : dishes) {
        if (dish.name == dishName) {
            return dish.price;
        }
    }
    return 0.0; // 若未找到则返回0
}

//输出全部菜品
void displayDishesPerLine(const string &filename) {
    ifstream file(filename);
    string   line;

    if (file.is_open()) {
        cout << "Dishes Information per line:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    } else {
        cerr << "Error: Unable to open file" << endl;
    }
}

//生成订单账单
void dishbill() {
    vector<Dish> dishes = readDishes("dishes.txt");

    // 用户点单
    map<string, int> order;
    string           dishName, ss;
    int              quantity;

    cout << "==========================================" << endl;
    displayDishesPerLine("dishes.txt");
    cout << "==========================================" << endl;
    bool ordering = true;
    while (ordering) {
        cout << "Enter dish name(or # to finish): ";
        getline(cin, ss); //吸收缓冲区的\n
        getline(cin, dishName);
        if (dishName == "#") {
            ordering = false;
            continue;
        }
        cout << "Enter dish quantity: ";
        cin >> quantity;
        order[dishName] += quantity;
    }

    // 将点单写入文件
    writeOrder(order, dishes);

    // 显示订单内容
    cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Your order:" << endl;
    double totalCost = 0.0;
    for (auto &entry : order) {
        double cost = entry.second * findDishPrice(entry.first, dishes);
        totalCost += cost;
        cout << entry.first << " x" << entry.second << " Cost: " << cost << endl;
    }

    // 显示总价
    cout << "Total cost: " << totalCost << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
    CommonUser();
    return;
}