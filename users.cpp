#include "users.h"
#include "md5.h"

using namespace std;
int f1 = 0; //0登陆未成功，1普通用户，2为Admin账户

struct user {
    char name[50];
    char password[100];
};

string name; //用户名变量，设置为全局变量

void homepage();
void login();
void regist();


//首页
void homepage() {
    int input;
    cout << "==========================================" << endl;
    cout << "|Welcome to the order system by MiguoQAQ!|" << endl;
    cout << "| log in:   press \"1\"                    |" << endl;
    cout << "| register: press \"2\"                    |" << endl;
    cout << "==========================================\n>>";
    // Get the user input
    input = getch();
    cout << char(input) << endl;

    if (input == '1') {
        login();
    } else if (input == '2') {
        regist();
    } else {
        cout << "bad input :(\n";
        homepage();
    }
    return;
}


//登陆
void login() {
    char *password = new char[100];
    cout << "username:\n>>";
    cin >> name;
    cout << "password:\n>>";
    char test;
    int  i = 0;
    while ((test = getch()) != '\r') //实现输入密码显示*，同时退回也会减去*
    {
        if (test == 8) {
            if (i > 0) {
                cout << test << " " << test;
                password[i--] = '\0';
            }
        } else {
            if (i < 20)
                cout << "*";
            password[i] = test;
            i++;
        }
    }
    password[i] = '\0';
    ifstream fin("user.dat", ios::binary);
    if (!fin) {
        cout << "Error opening file\n";
        return;
    }

    user   c;
    string passwordmd5 = md5(password);
    char  *st1         = const_cast<char *>(passwordmd5.c_str());
    while (fin >> c.name >> c.password) {
        if (strcmp(c.name, "Admin") == 0 && strcmp(c.password, st1) == 0) {
            f1 = 2; //设置flag为管理员用户
            return;
        } else if (strcmp(c.name, name.c_str()) == 0 && strcmp(c.password, st1) == 0) {
            system("cls");
            cout << "\n==========================================\n";
            cout << "Welcome," << name.c_str() << "!" << endl;
            f1 = 1; //设置flag为普通用户
            return;
        }
    }
    if (f1 == 0) {
        cout << "\nWrong username or password\n";
        login();
    }
}


//注册函数
void regist() {
    char    *password = new char[100]; //分配20个字节，然后返回首地址给password,即password可以看做一个20字节的字符数组，即字符串
    user     c;
    ifstream fin; //声明 ifstream 对象
    fin.open("user.dat", ios::binary | ios::in); //用户文件
    cout << "please input your username:";
    cin >> name;
    while (fin >> c.name >> c.password) {
        if (c.name == name) { //判断已注册用户名
            cout << "this username has been registered" << endl;
            fin.close();
            regist();
            return;
        }
    }
    char test;
    int  i = 0;
    cout << "please input your password:";
    while ((test = getch()) != '\r') {
        if (test == 8) //ASCII码8为退格
        {
            if (i > 0) {
                cout << test << " " << test;
                password[i--] = '\0';
            }
        } else {
            if (i < 100) {
                cout << "*";
                password[i] = test;
                i++;
            }
        }
    }
    password[i] = '\0';
    cout << "\nplease input your password again:";
    char *password2 = new char[100];
    i               = 0;
    while ((test = getch()) != '\r') {
        if (test == 8) {
            if (i > 0) {
                cout << test << " " << test;
                password2[i--] = '\0';
            }
        } else {
            if (i < 100) {
                cout << "*";
                password2[i] = test;
                i++;
            }
        }
        password2[i] = '\0';
    }
    if (strcmp(password, password2) != 0) { //判断两次输入的密码是否一致
        cout << "\nPassword entered incorrectly twice\n";
        fin.close();
        regist();
    } else {
        cout << "\nregistration success\n";
        fin.close();
        ofstream fout;
        fout.open("user.dat", ios::binary | ios_base::app | ios_base::out);
        fout << name << " " << md5(password) << endl;
        fout.close(); //关闭文件连接
        delete[] password;
        delete[] password2;
        cout << "Return to login interface\n";
        homepage();
    }
}