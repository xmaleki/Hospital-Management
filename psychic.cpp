#include<iostream>
#include<string>
#include "psychic.h"
#include "patient.h"
#include <fstream>

using namespace std;


void psychicSystem(string username)
{
    cout<<endl<<"==============================================="<<endl;
    cout<<"             PSYCHIC DEPARTMENT                ";
    cout<<endl<<"==============================================="<<endl;
    cout<<"Please give each question a score between 1 and 4:"<<endl;

    anxiety(username);

    depression(username);
    
    stress(username);

}



void anxiety(string username)
{
    int score[3] = {0};
    int result = 0;
    string questions[3] = {"1. man bish az had darbare masael rozmare negaran mishavam: ",
                           "2. agar kasi az man narahat bashad kheili barayam mohem ast: ",
                           "3. hengam sohbat ba gharibeha ehsas ezterab mikonam: "};
    cout<<endl<<"======= Anxiety Questions ======="<<endl;

    for(int i = 0; i < 3; i++)
    {
        cout<<questions[i];
        cin>>score[i];
        while(true)
        {
            if(score[i] > 4 || score[i] <= 0)
            {
                cout<<"Invalid answer. enter (1-4): ";
                cout<<endl<<questions[i];
                cin>>score[i];
            }
            else
                break;
        }
    }
    
    for(int i = 0; i < 3; i++)
    {
        result += score[i];
    }

    result = result * 3;

    string anxietylevel = "";

    if(result >= 9 && result <= 18)
    {
        anxietylevel = "low";
    }
    else if (result >= 21 && result <= 27)
    {
        anxietylevel = "medium";
    }
    else if(result >= 30 && result <= 36)
    {
        anxietylevel = "high";
    }
    

    ofstream file(username + ".txt", ios::app);
    file<<"totalanxietyscore="<<result<<endl;
    file<<"anxietylevel="<<anxietylevel<<endl;
    file.close();

}



void depression(string username)
{
    int score[4] = {0};
    int result = 0;
    string questions[4] = {"1. ehsas gonah ya bi arzeshi daram: ",
                           "2. aghlab ghamgin ya afsorde hastam: ",
                           "3. nesbat be ayande naomid ya moradad hastam: ",
                           "4. bish az had khodam ra sarzanesh mikonam: "};
    cout<<endl<<"======= Depression Questions ======="<<endl;

    for(int i = 0; i < 4; i++)
    {
        cout<<questions[i];
        cin>>score[i];
        while(true)
        {
            if(score[i] > 4 || score[i] <= 0)
            {
                cout<<"Invalid answer. enter (1-4): ";
                cout<<endl<<questions[i];
                cin>>score[i];
            }
            else
                break;
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        result += score[i];
    }

    result = result * 4;

    string depressionlevel = "";

    if(result >= 16 && result <= 32)
    {
        depressionlevel = "low";
    }
    else if (result >= 36 && result <= 48)
    {
        depressionlevel = "medium";
    }
    else if(result >= 52 && result <= 64)
    {
        depressionlevel = "high";
    }


    ofstream file(username + ".txt", ios::app);
    file<<"totaldepressionscore="<<result<<endl;
    file<<"depressionlevel="<<depressionlevel<<endl;
    file.close();

}




void stress(string username)
{
    int score[2] = {0};
    int result = 0;
    string questions[2] = {"1. dar sharayet sakhat ehsas mikonam kontorol oza ra az dast midaham: ",
                           "2. nemitavanam be rahati az afkar stress za fasele begiram: "};
    cout<<endl<<"======= Stress Questions ======="<<endl;

    for(int i = 0; i < 2; i++)
    {
        cout<<questions[i];
        cin>>score[i];
        while(true)
        {
            if(score[i] > 4 || score[i] <= 0)
            {
                cout<<"Invalid answer. enter (1-4): ";
                cout<<endl<<questions[i];
                cin>>score[i];
            }
            else
                break;
        }
    }
    
    for(int i = 0; i < 2; i++)
    {
        result += score[i];
    }

    result = result * 2;

    string stresslevel = "";

    if(result >= 4 && result <= 8)
    {
        stresslevel = "low";
    }
    else if (result >= 10 && result <= 12)
    {
        stresslevel = "medium";
    }
    else if(result >= 14 && result <= 16)
    {
        stresslevel = "high";
    }


    ofstream file(username + ".txt", ios::app);
    file<<"totalstressscore="<<result<<endl;
    file<<"stresslevel="<<stresslevel<<endl;
    file.close();

}
