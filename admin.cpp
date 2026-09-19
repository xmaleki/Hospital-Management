#include <iostream>
#include <string>
#include <fstream>
#include "admin.h"
#include "user.h"

using namespace std;

void adminSystem()
{
    int choice;
    while(true)
    {
        cout<<"=========== ADMIN PANEL ==========="<<endl;
        cout<<"1. View Bastari Patients"<<endl;
        cout<<"2. View Tarkhis Patients"<<endl;
        cout<<"3. Add Patient to Batari List"<<endl;
        cout<<"4. Add Patient to Tarkhis List"<<endl;
        cout<<"5. Quit"<<endl;
        cout<<"Select: ";
        cin>>choice;

        switch (choice)
        {
        case 1:
            showList("bastari.txt", "Bastari List");
            break;
        case 2:
            showList("tarkhis.txt", "Tarkhis List");
            break;
        case 3:
            addToList("bastari.txt");
            break;
        case 4:
            addToList("tarkhis.txt");
            break;
        case 5:
            return;


        default:
            cout<<"Invalid choice!"<<endl;
        }
    }

}



void showList(string filename, string title)
{
    cout<<"=========="<<title<<"=========="<<endl;
    ifstream file(filename);
    string name;
    int count = 0;

    if(!file || file.peek() == EOF)
    {
        cout<<"List is empty."<<endl;
    }
    else
    {
        while(getline(file, name))
        {
            if(!name.empty())
            {
                cout<<count<<". "<<name<<endl;
            }
        }
    }
    
    file.close();
}


void addToList(string filename)
{
    string name;
    cout<<"Enter the username to add: ";
    cin>>name;
    name = lowercase(name);

    ofstream file(filename, ios::app);
    if(file)
    {
        file<<name<<endl;
        cout<<"[OK] "<<name<<" added to "<<filename<<endl;
        file.close(); 
    }
}






