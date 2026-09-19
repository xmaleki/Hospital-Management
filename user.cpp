#include "user.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>


using namespace std;



string lowercase(string input)
{
    for(int i = 0; i < input.length(); i++)
    {
        input[i] = tolower(input[i]);
    }

    return input;
}

bool validpassword(string password)
{
    if(password.length() < 8)
        return false;

    bool upper = false;
    bool lower = false;
    bool digit = false;
    
    for(int i = 0; i < password.length(); i++)
    {
        if(isupper(password[i]))
            upper = true;
        if(islower(password[i]))
            lower = true;
        if(isdigit(password[i]))
            digit = true;
    }

    return upper && lower && digit;

}


bool userexist(string username, string role)
{
    ifstream file("users.txt");

    if(!file)
        return false;

    string line;

    while(getline(file, line))
    {
        int FirstLoc = line.find('|');
        int SecondLoc = line.find('|', FirstLoc + 1);
        string Fileusername, FileRole;


        Fileusername = line.substr(0,FirstLoc);
        FileRole = line.substr(SecondLoc + 1);

        if(username == Fileusername && role == FileRole)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;

}








bool usernamecheck(string username)
{
    ifstream file("users.txt");
    if(!file)
        return false;

    string line;

    while(getline(file, line))
    {
        int FirstLoc = line.find('|');
        string Fileusername;

        Fileusername = line.substr(0,FirstLoc);

        if(username == Fileusername)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}








string getpassword(string username, string role)
{
    ifstream file("users.txt");

    if(!file)
        return "";

    string line;

    while(getline(file, line))
    {
        int FirstLoc = line.find('|');
        int SecondLoc = line.find('|', FirstLoc + 1);

        string FileUsername = line.substr(0, FirstLoc);
        string FilePassword = line.substr(FirstLoc + 1, SecondLoc - FirstLoc - 1);
        string FileRole = line.substr(SecondLoc + 1);

        if(username == FileUsername && role == FileRole)
        {
            file.close();
            return FilePassword;
        }
    }

    file.close();
    return "";

}


void saveuser(string username, string password, string role)
{
    ofstream file("users.txt", ios::app);
    file<<username <<"|" <<password <<"|" <<role <<endl;
    file.close();

}



string rolemenu()
{
    string input;

    while(true)
    {      
        cout<<"1.Admin"<<endl;
        cout<<"2.Patient"<<endl;
        cout<<"3.Visitor"<<endl;
        cout<<"Select User Type: "; 
        cin>>input;
        
        if(input == "1")
            return "admin";
        
        if(input == "2")
            return "patient";

        if(input == "3")
            return "visitor";

        cout<<"Invalid input. Try again!"<<endl;

    }

}


void login(string username,string role)
{
    string password = getpassword(username, role);

    if(password == "")
    {
        cout<<"Error!";
    }

    string inputpassword;

    while(true)
    {
        cout<<"Enter Password: ";
        cin>>inputpassword;

        if(inputpassword == password)
        {
            cout<<"Login successful."<<endl;
            return;
        }

        cout<<"\nIncorrect password. Try again.";
    }

}


string signup(string role)
{
    string username;
    string password;


    cout<<"Sign Up"<<endl;

    while(true)
    {
        cout<<"Enter Username: ";
        cin>>username;
        username = lowercase(username);
        while(true)
        {
            if(usernamecheck(username))
            {
                cout<<"This username already exist!"<<endl<<"Enter Username: ";
                cin>>username;
                username = lowercase(username);
            }
            else
                break;
        }

        if(userexist(username, role))
        {
            cout<<"The user already registered."<<endl;
        }
        else
            break;
    }
    

    while(true)
    {
        cout<<"Enter password: ";
        cin>>password;

        if(validpassword(password))
            break;

        cout<<"Invalid password.\n";
        cout<<"Password must contain:\n";
        cout<<"- At least 8 characters\n";
        cout<<"- One uppercase letter\n";
        cout<<"- One lowercase letter\n";
        cout<<"- One digit\n";
    }

    saveuser(username, password, role);
    cout<<"Registration successful.\n";
    return username;
}


User loginmenu()
{
    string username;
    string role = rolemenu();
    cout<<"Username: ";
    cin>>username;
    username = lowercase(username);

    if(userexist(username, role))
    {
        login(username, role);
    }
    else
    {
        username = signup(role);
        username = lowercase(username);
        cout<<"Please login now.\n";
        login(username, role);
    }

    User u;
    u.username = username;
    u.role = role;

    return u;
}






















