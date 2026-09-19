#ifndef USER_H
#define USER_H
#include<string>
using namespace std;
struct User
{
    string username;
    string role;
};

string lowercase(string);
bool validpassword(string);
bool userexist(string, string);
bool usernamecheck(string);
string getpassword(string, string);
void saveuser(string, string, string);
string rolemenu();
void login(string, string);
string signup(string);
User loginmenu();



#endif