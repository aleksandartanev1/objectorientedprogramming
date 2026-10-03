#include<iostream>
#include<cstring>
using namespace std;

class team {
private:
    char name[50];
    char city[50];
    int foundingyear;

public:
    team (char *_name = "name", char *_city = "city", int _foundingyear = 999) {
        strcpy(name, _name);
        strcpy(city, _city);
        foundingyear = _foundingyear;
    }

    void print() {
        cout<<"Team: "<<name<<" - "<<city<<" ("<<foundingyear<<")"<<endl;
    }

    team (const team &other) {
        cout<<"COPY TEAM"<<endl;
        strcpy(name, other.name);
        strcpy(city, other.city);
        foundingyear = other.foundingyear;
    }

    ~team()  {};


    };

class match {
private:
    team home;
    team away;
    int homegoals;
    int awaygoals;

public:
    match (team _home, team _away, int _homegoals, int _awaygoals) {

        home = _home;
        away = _away;
        homegoals = _homegoals;
        awaygoals = _awaygoals;
    }

    void print () {
        cout<<"Match between: "<<endl;
        home.print();
        cout<<" & "<<endl;
        away.print();
        cout<<"Result - "<<homegoals<<" : "<<awaygoals<<endl;

    }

    match (const match &other) {
        cout<<"COPY MATCH"<<endl;
        home = other.home;
        away = other.away;
        homegoals = other.homegoals;
        awaygoals = other.awaygoals;
    }
};

int main () {
    team home("fc barcelona","barcelona",1920);
    team away("real madrid", "madrid", 1920);
    match copa(home,away,2,5);
    copa.print();


}