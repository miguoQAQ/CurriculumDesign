#include "users.h"

using namespace std;

void DishList::loadFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string name, category, priceStr;
        double price;
        size_t pos1, pos2;

        pos1 = line.find(',');
        if (pos1 != string::npos) {
            name = line.substr(0, pos1);
            pos2 = line.find(',', pos1 + 1);
            if (pos2 != string::npos) {
                category = line.substr(pos1 + 1, pos2 - pos1 - 1);
                priceStr = line.substr(pos2 + 1);
                price    = stod(priceStr);
                addDish(name, category, price);
            }
        }
    }
    file.close();
}

void DishList::saveToFile(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    Dish *current = head;
    while (current != nullptr) {
        file << current->name << "," << current->category << "," << current->price << endl;
        current = current->next;
    }
    file.close();
    cout << "Data saved to file successfully." << endl;
}


void DishList::addDish(string name, string category, double price) {
    Dish *newDish = new Dish{name, category, price, nullptr};

    if (head == nullptr) {
        head = newDish;
    } else {
        Dish *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newDish;
    }
}

void DishList::deleteDish(string name) {
    Dish *current  = head;
    Dish *previous = nullptr;

    while (current != nullptr && current->name != name) {
        previous = current;
        current  = current->next;
    }

    if (current == nullptr) {
        cout << "Dish not found." << endl;
        return;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
    cout << "Dish deleted successfully." << endl;
}

void DishList::updateDish(string name, string newCategory, double newPrice) {
    Dish *current = head;

    while (current != nullptr && current->name != name) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Dish not found." << endl;
        return;
    }

    current->category = newCategory;
    current->price    = newPrice;
    cout << "Dish updated successfully." << endl;
}

void DishList::searchDish(const string &keyword, const string &searchType) {
    Dish *current = head;
    
    if (searchType == "1") {
        while (current != nullptr) {
            if (current->name.find(keyword) != string::npos) {
                cout << "Name: " << current->name << ", Category: " << current->category << ", Price: " << current->price << endl;
            }
            current = current->next;
        }
    } else if (searchType == "2") {
        while (current != nullptr) {
            if (current->category.find(keyword) != string::npos) {
                cout << "Name: " << current->name << ", Category: " << current->category << ", Price: " << current->price << endl;
            }
            current = current->next;
        }
    } else {
        cout << "Invalid search type. Please use '1' or '2'." << endl;
    }
}

void DishList::displayDishes() {
    Dish *current = head;
    cout << "Dish List:" << endl;
    while (current != nullptr) {
        cout << "Name: " << current->name << ", Category: " << current->category << ", Price: " << current->price << endl;
        current = current->next;
    }
}


DishList::~DishList() {
    Dish *current = head;
    Dish *next    = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}