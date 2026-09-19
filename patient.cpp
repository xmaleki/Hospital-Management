#include<iostream>
#include<string>
#include "patient.h"
#include "emergency.h"
#include "patient.h"
#include "pediatrics.h"
#include "psychic.h"
#include "user.h"
#include <fstream>

using namespace std;


void patientSystem(string username)
{
    if(!patientexists(username))
    {
        createpatient(username);
    }
    else
    {
        cout<<"\n--- Welcome Back! Your medical history was found. ---\n";

        bool hasBMI = false, hasAnxiety = false, hasDepression = false, hasStress = false, hasDrugs = false;
        bool hasAge = false, hasWeight = false, hasHeight = false, hasSymptoms = false;

        string filename = username + ".txt";
        ifstream file(filename);
        string line;

        while(getline(file, line))
        {
            if(line.find("bmi=") != string::npos)
                hasBMI = true;
            if(line.find("age=") != string::npos)
                hasAge = true;
            if(line.find("weight=") != string::npos)
                hasWeight = true;
            if(line.find("height=") != string::npos)
                hasHeight = true;
            if(line.find("symptoms=") != string::npos)
                hasSymptoms = true;
            if(line.find("drugs=") != string::npos)
                hasDrugs = true;
            if(line.find("stresslevel=") != string::npos)
                hasStress = true;
            if(line.find("depressionlevel=") != string::npos)
                hasDepression = true;
            if(line.find("anxietylevel=") != string::npos)
                hasAnxiety = true;
        }
        file.close();

        ofstream file1(username + ".txt", ios::app);

        if(hasDrugs)
        {
            string newdrugs, answer;
            cout<<"--------> Do you want to update your drugs? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                cout<<"Enter new drugs: ";
                cin>>newdrugs;
                file1<<"drugs="<<newdrugs<<endl;
            }
        }


        if(hasSymptoms)
        {
            string newsymptoms, answer;
            cout<<"--------> Do you want to update your symptoms? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                cout<<"Enter new symptoms: ";
                cin>>newsymptoms;
                file1<<"symptoms="<<newsymptoms<<endl;
            }
        }


        if(hasAge)
        {
            int newage;
            string answer;
            cout<<"--------> Do you want to update your age? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                cout<<"Enter new age: ";
                cin>>newage;
                file1<<"age="<<newage<<endl;
            }
        }

        
        if(hasWeight)
        {
            int weight;
            string answer;
            cout<<"--------> Do you want to update your weight? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                cout<<"Enter new weight: ";
                cin>>weight;
                file1<<"weight="<<weight<<endl;
            }
        }


        if(hasHeight)
        {
            int height;
            string answer;
            cout<<"--------> Do you want to update your height? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                cout<<"Enter new height: ";
                cin>>height;
                file1<<"height="<<height<<endl;
            }
        }


        if(hasBMI)
        {
            string answer;
            cout<<"--------> Do you want to calculate BMI again? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                bmi(username);
            }
        }

        
        if(hasAnxiety)
        {
            string answer;
            cout<<"--------> Do you want to answer anxiety question again? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                anxiety(username);
            }
        }

        if(hasDepression)
        {
            string answer;
            cout<<"--------> Do you want to answer depression question again? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                depression(username);
            }
        }

        if(hasStress)
        {
            string answer;
            cout<<"--------> Do you want to answer stress question again? ";
            cin>>answer;
            answer = lowercase(answer);
            if(answer == "yes")
            {
                stress(username);
            }
        }

    }



    string departments = choosedepartment(username);

    if(departments.find("emergency") != string::npos)
    {
        emergencySystem(username);
    }

    if(departments.find("children") != string::npos)
    {
        pediatricsSystem(username);
    }

    if(departments.find("mental") != string::npos)
    {
        psychicSystem(username);
    }
}





bool patientexists(string username)
{
    string filename = username + ".txt";
    ifstream file(filename);

    if(file)
    {
        file.close();
        return true;
    }
    
    return false;
}

void createpatient(string username)
{
    string gender, age, weight, height, nationalnumber, symptoms, drugs;

    cout<<endl<<"Please enter patient information"<<endl;
    cout<<"=========== Personal Information ==========="<<endl;
    cout<<"Gender: ";
    cin>>gender;
    gender = lowercase(gender);
    cout<<"Age: ";
    cin>>age;
    age = lowercase(age);
    cout<<"Weight (kg): ";
    cin>>weight;
    weight = lowercase(weight);
    cout<<"Height (cm): ";
    cin>>height;
    height = lowercase(height);
    cout<<endl<<"=========== Identification Information ==========="<<endl;
    cout<<"National Number: ";
    cin>>nationalnumber;
    nationalnumber = lowercase(nationalnumber);
    cin.ignore();
    cout<<endl<<"=========== Medical Information ==========="<<endl;
    cout<<"Symptoms (comma separated): ";
    getline(cin, symptoms);
    symptoms = lowercase(symptoms);
    cout<<"Prescription Drugs: ";
    getline(cin, drugs);
    drugs = lowercase(drugs);

    string filename = username + ".txt";
    ofstream file(filename);

    file<<"gender="<<gender<<endl;
    file<<"age="<<age<<endl;
    file<<"weight="<<weight<<endl;
    file<<"height="<<height<<endl;
    file<<"nationalnumber="<<nationalnumber<<endl;
    file<<"symptoms="<<symptoms<<endl;
    file<<"drugs="<<drugs<<endl;

    file.close();
}


string getvalue(string username, string key)
{
    string filename = username + ".txt";
    ifstream file(filename);

    if(!file)
        return "";
    
    string line;
    string lastvalue = "";

    while(getline(file, line))
    {
        int pos = line.find('=');
        if(pos == string::npos)
            continue;

        string fileKey = line.substr(0,pos);
        string value = line.substr(pos + 1);
        
        if(key == fileKey)
        {
            lastvalue = value;
        }
    }

    file.close();
    return lastvalue;

}

string choosedepartment(string username)
{
    string agestr = getvalue(username,"age");
    string symptoms = getvalue(username, "symptoms");
    string result = "";

    //if(agestr == "") return "";
    int age = stoi(agestr);

    if(symptoms.find("khonrizi shadid") != string::npos ||
       symptoms.find("tab shadid") != string::npos ||
       symptoms.find("zarbe maghzi") != string::npos ||
       symptoms.find("ghat ozve") != string::npos ||
       symptoms.find("tasadof") != string::npos ||
       symptoms.find("sokhtegi") != string::npos ||
       symptoms.find("khafegi") != string::npos ||
       symptoms.find("hamle ghlabi") != string::npos)
    {
        result += "emergency";
    }

    if(age < 18)
        result += ",children";

    if(symptoms.find("stress") != string::npos ||
       symptoms.find("ezterab") != string::npos)
       result += ",mental";

    return result;

}