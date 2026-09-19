#include <iostream>
#include <ctime>
#include <fstream>
#include "visitor.h"
#include "user.h"

using namespace std;

void visitorSystem()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int hour = ltm->tm_hour;

    if(hour >= 9 && hour <= 18)
    {
        visitPatient();
        cin.ignore();
        cin.get();
    }
    else 
    {
        cout<< "Visiting hours are 9:00 to 18:00. Access denied."<<endl;
    }
}

void visitPatient()
{
    string patientName;
    cout<<"\n--- Welcome to the Visitor Portal ---"<<endl;
    cout<<"Enter the Username of the patient you want to visit: ";
    cin>>patientName;
    patientName = lowercase(patientName);


    ifstream file("bastari.txt");
    
    if(!file)
    {
        cout<<"No patient exist.";
        return;
    }

    string line;
    bool found = false;

    while(getline(file, line))
    {
        if(lowercase(line) == patientName)
        {
            found = true;
            break;
        }
    }
    file.close();

    if(found)
    {
        cout<<"\n Access Granted. You may visit "<< patientName << "." << endl;
    } else {
        cout<<"\n Access Denied. This patient is not in the Bastari list."<< endl;
    }

}



















