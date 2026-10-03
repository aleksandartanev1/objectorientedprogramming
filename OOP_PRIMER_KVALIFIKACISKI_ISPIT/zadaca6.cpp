//
// Created by aleks on 5/20/2025.
//
#include <iostream>

using namespace std;

class Project {
protected:
    string name;
    int duration;
public:
    Project(string name = "Project1", int duration = 2) : name(name), duration(duration) {}

    ~Project() {}

    void showInfo() {
        cout << name << " " << duration << " " ;
    }
};

class TeamProject : public  Project {
    int teamsize;
public:
    TeamProject(string name = "Project1", int duration = 2, int teamsize = 5) : Project(name, duration) {
        if (teamsize <= 0 || teamsize > 10) {
            this->teamsize = 5;
        } else this->teamsize = teamsize;
        this->name = name;
        this->duration = duration;
    }

    int calculateTotalTeamHours() {
        return duration + teamsize * 160;
    }

    void showInfo() {
        Project::showInfo();
        cout<<teamsize<<endl;
    }
};


TeamProject *createTeamProjects(int n) {
    TeamProject *teamProjects = new TeamProject[n];
    string name;
    int duration, teamSize;
    for (int i = 0; i < n; i++) {
        cin >> name >> duration >> teamSize;
        teamProjects[i] = TeamProject(name, duration, teamSize);
    }
    return teamProjects;
}


int main() {
    int testCase;
    cin >> testCase;

    switch (testCase) {
        case 1 : {
            TeamProject teamProject;
            teamProject.showInfo();
            break;
        }
        case 2 : {
            TeamProject teamProject("CS101", 5, 3);
            teamProject.showInfo();
            TeamProject teamProject1("CS102", 7, 2);
            teamProject1.showInfo();
            break;
        }
        case 3 : {
            TeamProject teamProject("CS101", 5, 13);
            teamProject.showInfo();
            TeamProject teamProject1("CS102", 7, 0);
            teamProject1.showInfo();
            break;
        }
        case 4: {
            TeamProject teamProject("CS101", 4, 1);
            cout << teamProject.calculateTotalTeamHours();
            break;
        }
        case 5: {
            int n;
            cin >> n;
            TeamProject *teamProjects = createTeamProjects(n);
            for (int i = 0; i < n; i++) {
                teamProjects[i].showInfo();
            }
            delete [] teamProjects;
            break;
        }
        default: {
            int n;
            cin >> n;
            TeamProject *teamProjects = createTeamProjects(n);
            for (int i = 0; i < n; i++) {
                teamProjects[i].showInfo();
            }
            for (int i = 0; i < n; i++) {
                cout << teamProjects[i].calculateTotalTeamHours() << endl;
            }
            delete [] teamProjects;
            break;
        }
    }
}

