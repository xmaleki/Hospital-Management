#include<iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include "emergency.h"
#include "patient.h"
#include "user.h"
#include <string>
#include <fstream>

using namespace std;



void emergencySystem(string username)
{
    
    string filepath = username + ".txt";
    ofstream file(filepath, ios::app);
    
    int EyeResponse = rand() % 6;
    int VerbalResponse = rand() % 6;
    int MotorResponse = rand() % 6;

    file<<"EyeResponse="<<EyeResponse<<endl;
    file<<"VerbalResponse="<<VerbalResponse<<endl;
    file<<"MotorResponse="<<MotorResponse<<endl;

    file.close();


    cout<<endl<<"==============================================="<<endl;
    cout<<"               EMERGENCY DEPARTMENT            ";
    cout<<endl<<"==============================================="<<endl;
    
    calculatebloodpressure(username);

    checkdruginteraction(username);

    determinebloodgroup(username);

    calculateGCS(username);

}



void calculatebloodpressure(string username)
{
    cout<<"======== Blood Pressure Calculation ========"<<endl;

    string weightstr = getvalue(username, "weight");
    if(weightstr == "")
    {
        cout<<"Weight not found in file.";
        return;
    }

    int weight = stoi(weightstr);

    int option;

    cout<<"Daily salt consumption:"<<endl;
    cout<<"1. Rarely (0 mg)"<<endl;
    cout<<"2. Sometimes (2 mg)"<<endl;
    cout<<"3. A lot (5 mg)"<<endl;
    cout<<"Select option (1-3): ";
    cin>>option;


    while(option <= 0 || option > 3)
    {
        cout<<"Invalid option. Enter again: ";
        cin>>option;
    }

    int SBP = weight + 40 + option;
    
    cout<<"Systolic Blood Pressure (SBP): "<<SBP<<endl;

    ofstream file(username + ".txt", ios::app);
    file<<"SBP="<<SBP<<endl;

    file.close();
}


void checkdruginteraction(string username)
{
    string mosaken;
    bool boolmosaken = false;

    cout<<"Do you take Mosaken? (yes/no): ";
    cin>>mosaken;
    mosaken = lowercase(mosaken);

    if(mosaken == "yes")
    {
        boolmosaken = true;
    } 

    cout<<endl<<"====== Drug Interaction Check ======"<<endl;
    
    string drugs = getvalue(username, "drugs");

    if((drugs.find("warfarin") != string::npos) && boolmosaken)
    {
        cout<<"Warning: Drug interaction detected (warfarin & mosaken)."<<endl;
        ofstream file(username + ".txt", ios::app);
        file<<"DrugInteraction=Yes"<<endl;
        file.close();
    }
    else
    {
        cout<<"No drug interaction detected."<<endl;
        ofstream file(username + ".txt", ios::app);
        file<<"DrugInteraction=No"<<endl;
        file.close();
    }

}



void determinebloodgroup(string username)
{
    string FatherBloodGroup, MotherBloodGroup, ChildBloodGroup;
    char FatherRh, MotherRh, ChildRh;
    

    cout<<endl<<"======== Blood Group Determination ========"<<endl;
    cout<<"Father ABO (A, B, AB, O): ";
    cin>>FatherBloodGroup;

    cout<<"Mother ABO (A, B, AB, O): ";
    cin>>MotherBloodGroup;

    cout<<"Father Rh (+ , -): ";
    cin>>FatherRh;

    cout<<"Mother Rh (+ , -): ";
    cin>>MotherRh;

    if( (FatherBloodGroup == "AB" || MotherBloodGroup == "AB") &&
        !(FatherBloodGroup == "AB" && MotherBloodGroup == "AB") &&
        !(FatherBloodGroup == "O" || MotherBloodGroup == "O") )
        {
            int r = rand() % 3;

            if(r == 0)
                ChildBloodGroup = "A";
            else if(r == 1)
                ChildBloodGroup = "B";
            else
                ChildBloodGroup = "AB";
        }

    else if(FatherBloodGroup == "AB" && MotherBloodGroup == "AB")
    {
        ChildBloodGroup = "AB";
    }
    else if(FatherBloodGroup == "O" && MotherBloodGroup != "O") 
    {
        ChildBloodGroup = MotherBloodGroup;
    }
    else if(FatherBloodGroup != "O" && MotherBloodGroup == "O")
    {
        ChildBloodGroup = FatherBloodGroup;
    }
    else if(FatherBloodGroup == "O" && MotherBloodGroup == "O")
    {
        ChildBloodGroup = "O";
    }
    else if( (FatherBloodGroup == "A" || MotherBloodGroup == "A") &&
        !(FatherBloodGroup == "A" && MotherBloodGroup == "A") )
    {
            ChildBloodGroup = (rand() % 2 == 0) ? "A" : "B";
    }
    else if( (FatherBloodGroup == "B" || MotherBloodGroup == "B") &&
        !(FatherBloodGroup == "B" && MotherBloodGroup == "B") )
    {
            ChildBloodGroup = (rand() % 2 == 0) ? "A" : "B";
    }
    else if(FatherBloodGroup == "A" && MotherBloodGroup == "A")
    {
        ChildBloodGroup = "A";
    }
    else if(FatherBloodGroup == "B" && MotherBloodGroup == "B")
    {
        ChildBloodGroup = "B";
    }
    
    if(FatherRh == '-' && MotherRh == '-')
    {
        ChildRh = '-';
    }
    else
    {
        ChildRh = (rand() % 2 == 0) ? '-' : '+';
    }

    string finalGroup = ChildBloodGroup + ChildRh;
    ofstream file(username + ".txt", ios::app);
    file<<"BloodGroup="<<finalGroup<<endl;
    file.close();




    string answer;
    cout<<"Do you want to donate blood? (Yes/No) ";
    cin>>answer;
    answer = lowercase(answer);
    if(answer == "yes")
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        ofstream file1("blood_bank.txt", ios::app);
        file1<<username<<"|"<<finalGroup<<"|"<<asctime(ltm);
        file1.close();

        increasebankinventory(finalGroup);   
    }
    else
        return;

    
}



void calculateGCS(string username)
{
    cout<<endl<<"============= GCS Calculation =============";
    
    string eyeStr = getvalue(username, "EyeResponse");
    string verbalStr = getvalue(username, "VerbalResponse");
    string motorStr = getvalue(username, "MotorResponse");

    if(eyeStr == "" || verbalStr == "" || motorStr == "")
    {
        cout<<"Error reading GCS parameters from file.";
        return;
    }

    int E = stoi(eyeStr);
    int V = stoi(verbalStr);
    int M = stoi(motorStr);

    int GCS = E + V + M;

    if(GCS>=3 && GCS<=8)
    {
        cout<<endl<<"Possibility of coma: very bad situation!";
    }
    else if(GCS>=9 && GCS<=12)
    {
        cout<<endl<<"Medium damage: The patient needs care.";
    }
    else if(GCS>=13 && GCS<=15)
    {
        cout<<endl<<"Good consciousness, patient's condition is stable.";
    }

    string symptoms = getvalue(username, "symptoms");

    if(GCS<13 || (!symptoms.empty() && (symptoms.find("khonrizi shadid") != string::npos || 
    symptoms.find("zarbe maghzi") != string::npos ||
    symptoms.find("ghat ozve") != string::npos ||
    symptoms.find("tasadof") != string::npos ||
    symptoms.find("khafegi") != string::npos)))
    {
        ofstream file1(username + ".txt", ios::app);
        file1<<"patientstatus=bastari"<<endl;
        file1.close();

        ofstream file2("bastari.txt", ios::app);
        file2<<username<<endl;
        file2.close();
    }
    else
    {
        ofstream file3(username + ".txt", ios::app);
        file3<<"patientstatus=tarkhis"<<endl;
        file3.close();

        ofstream file4("tarkhis.txt", ios::app);
        file4<<username<<endl;
        file4.close();
    }



    string patientgroup = getvalue(username, "BloodGroup");

    if((symptoms.find("ghat ozve") != string::npos) || (symptoms.find("tasadof") != string::npos))
    {
        cout<<endl<<"============== Blood Donation =============="<<endl;
        int inventory[8];
        string names[8] = {"AB+", "AB-", "B+", "B-", "A+", "A-", "O+", "O-"};
        
        ifstream infile("bank_inventory.txt");
        for(int i = 0; i < 8; i++)
            infile >> inventory[i];
        infile.close();

        int compatiblegroup[8];
        int count = 0;


        for(int i = 0; i < 8; i++)
        {
            string donor = names[i];
            bool match = false;

            if(patientgroup == "AB+")
                match = true;
            else if(patientgroup == "AB-")
            {
                if(donor == "AB-" || donor == "B-" || donor == "A-" || donor == "O-")
                    match = true;
            }
            else if(patientgroup == "B+")
            {
                if(donor == "B+" || donor == "B-" || donor == "O+" || donor == "O-")
                    match = true;
            }
            else if(patientgroup == "B-")
            {
                if(donor == "B-" || donor == "O-")
                    match = true;
            }
            else if(patientgroup == "A+")
            {
                if(donor == "A+" || donor == "A-" || donor == "O+" || donor == "O-")
                    match = true;
            }
            else if(patientgroup == "A-")
            {
                if(donor == "A-" || donor == "O-")
                    match = true;
            }
            else if(patientgroup == "O+")
            {
                if(donor == "O+" || donor == "O-")
                    match = true;
            }
            else if(patientgroup == "O-")
            {
                if(donor == "O-")
                    match = true;
            }


            if(match && inventory[i]>0)
            {
                compatiblegroup[count] = i;
                count++;
            }
        }


        if(count>0)
        {
            srand(time(0));
            int randomindex = compatiblegroup[rand() % count];
            inventory[randomindex]--;

            ofstream outfile("bank_inventory.txt");
            for(int i = 0; i < 8; i++)
            {
                outfile << inventory[i] <<endl;
            }
            outfile.close();

            cout<<"[OK]: Used 1 unit of "<<names[randomindex]<<" for patient."<<endl;
            cout<<"==============---------------=============="<<endl;
        }
        else
        {
            cout<<"[ERROR]: No compatible blood found for " << patientgroup<< "!"<<endl;
        }
    }

}




void increasebankinventory(string finalgroup)
{
    checkbloodbankfile();

    int inventory[8];

    ifstream infilein("bank_inventory.txt");
    for(int i = 0; i < 8; i++)
    {
        infilein >> inventory[i];
    }

    infilein.close();

    
    int index = -1;
    
    if(finalgroup == "AB+")
        index = 0;
    else if (finalgroup == "AB-") 
        index = 1;
    else if (finalgroup == "B+")
        index = 2;
    else if (finalgroup == "B-")
        index = 3;
    else if (finalgroup == "A+")
        index = 4;
    else if (finalgroup == "A-")
        index = 5;
    else if (finalgroup == "O+")
        index = 6;
    else if (finalgroup == "O-")
        index = 7;

    if(index != -1)
    {
        inventory[index]++;

        ofstream invfileout("bank_inventory.txt");
        for(int i = 0; i < 8; i++)
        {
            invfileout<<inventory[i]<<endl;
        }
        invfileout.close();
        cout<<"blood bank inventory updated!"<<endl;
    }
}






void checkbloodbankfile()
{
    ifstream checkfile("bank_inventory.txt");
    if(!checkfile)
    {
        ofstream outfile("bank_inventory.txt");
        for(int i = 0; i < 8; i++)
        {
            outfile<<"0"<<endl;
        }
        outfile.close();
    }
    else
    {
        checkfile.close();
    }
}



















