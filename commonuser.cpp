#include "users.h"

using namespace std;

struct user {
    char name[50];
    char password[100];
};

void CommonUser();
void delete_account(const string &loggedInUser);


//普通用户选择点菜/注销
void CommonUser() {
    int number;
    cout << "==========================================\n";
    cout << "Choose the operation you want to perform: \npress 1 to place an order\npress 2 to delete your account\npress 3 to back to login page\n";
    cout << "==========================================\n>>";
    number = getch();
    cout << char(number) << endl;
    if (number == '1') {
        dishbill();
    } else if (number == '2') {
        delete_account(name);
    } else if (number == '3') {
        main();
    } else {
        cout << "bad input :(\n";
        CommonUser();
    }
}


//注销账户函数
void delete_account(const string &loggedInUser) {
    char confirm;
    cout << "Are you sure to delete your account?(Y/n)\n>>" << endl;
    cin >> confirm;
    if (confirm == 'Y') {
        ifstream fin("user.txt");
        ofstream tempFile("temp.txt", ios::out);

        user c;
        bool found = false;

        while (fin >> c.name >> c.password) {
            if (c.name == loggedInUser) {
                found = true;
            } else {
                tempFile << c.name << " " << c.password << endl;
            }
        }

        fin.close();
        tempFile.close();

        // Remove the original file and rename the temporary file
        if (found) {
            remove("user.txt");
            rename("temp.txt", "user.txt");
            cout << "Account " << loggedInUser << " has been successfully logged out and deleted" << endl;
        } else {
            cout << "Account " << loggedInUser << " not found or unable to delete" << endl;
            remove("temp.txt"); // Delete the temporary file if the account was not found
        }
    } else if (confirm == 'n') {
        CommonUser();
    } else {
        cout << "bad input :(\n";
        CommonUser();
    }
}
