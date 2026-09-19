#include<iostream>
#include<string>
#include"pediatrics.h"
#include"patient.h"
#include "patient.h"
#include <fstream>


void pediatricsSystem(string username)
{
    cout<<endl<<"==============================================="<<endl;
    cout<<"             PEDIATRICS DEPARTMENT             ";
    cout<<endl<<"==============================================="<<endl;
    
    bmi(username);
}



void bmi(string username)
{
    string heightstr = getvalue(username, "height");
    string weightstr = getvalue(username, "weight");
    
    double height = stod(heightstr) / 100.0;
    double weight = stod(weightstr);
    double bmi = weight / (height*height);

    ofstream file(username + ".txt", ios::app);
    if(file)
    {
        file<<"bmi="<<bmi<<endl;
        file.close();
    }

    cout<<endl<<"Your BMI is : "<<bmi<<endl;
    
}