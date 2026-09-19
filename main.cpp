#include<iostream>
#include "user.h"
#include "patient.h"
#include "visitor.h"
#include "admin.h"
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;


int main()
{
    srand(time(0));
    User user;
    user = loginmenu();
    string username = user.username;

    if(user.role == "visitor")
    {
        visitorSystem();
    }
    else if(user.role == "patient")
    {
        patientSystem(username);
    }
    else if(user.role == "admin")
    {
        adminSystem();
    }

    cin.ignore();
    cin.get();

    return 0;
}