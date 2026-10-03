//
// Created by aleks on 6/16/2025.
//
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

class StudentFailedException : exception {
    string indeks;
public:
    StudentFailedException(string indeks) {
        this->indeks = indeks;
    }

    void print() {
        cout<<"Student with id "<<indeks<<" failed the course"<<endl;
    }
};

class Student {
protected:
    string indeks;
    string ime;
    string prezime;
    int poeni;
public:
    Student(string indeks = " ", string ime = " ", string prezime = " ", int poeni = 0) {
        this->indeks = indeks;
        this->ime = ime;
        this->prezime = prezime;
        this->poeni = poeni;
    }

    int grade() {
        if (poeni < 50) {
            return 5;
        } else if (poeni >= 50 && poeni <= 59) {
            return 6;
        } else if (poeni >= 60 && poeni <= 69) {
            return 7;
        } else if (poeni >= 70 && poeni <= 79) {
            return 8;
        } else if (poeni >= 80 && poeni <= 89) {
            return 9;
        }  else if (poeni >= 90 && poeni <= 100) {
            return 10;
        }
    }

    string getID() {
        return indeks;
    }

    friend ostream& operator<<(ostream& out, Student &s) {
        out<<s.indeks<<" "<<s.ime<<" "<<s.prezime<<" "<<s.poeni<<" Grade: "<<s.grade()<<endl;
        return out;
    }
};

class Results {
    Student* students;
    int n;
public:
    Results(Student* students = nullptr, int n = 0) {
        this->n = n;
        this->students = new Student[n];
        for(int i = 0; i < n; i++) {
            this->students[i] = students[i];
        }
    }

    ~Results() {
        delete[]this->students;
    }

    Results& operator=(const Results& o) {
        if (this != &o) {
            delete[]this->students;
            this->n = o.n;
            this->students = new Student[o.n];
            for(int i = 0; i < o.n; i++) {
                this->students[i] = o.students[i];
            }
        }
        return *this;
    }

    int getN() {
        return n;
    }

    Results(const Results &o) {
        this->n = o.n;
        this->students = new Student[o.n];
        for(int i = 0; i < o.n; i++) {
            this->students[i] = o.students[i];
        }
    }

    Results& operator+=(Student &s) {

        if (s.grade() == 5) {
            throw StudentFailedException(s.getID());
        }
        Student* temp = new Student[n + 1];

        for(int i = 0; i < n; i++) {
            temp[i] = students[i];
        }

        temp[n] = s;
        n++;
        delete[]students;
        students = temp;

        return *this;
    }

    friend ostream& operator<<(ostream& out, Results &r) {
        for(int i = 0; i < r.n; i++) {
            out<<r.students[i];
        }
        return out;
    }

    Results withGrade(int grade) {
        int count = 0;
        Student* temp;
        temp = new Student[n];
        for(int i = 0; i < n; i++) {
            if(students[i].grade() == grade) {
                temp[count] = students[i];
                count++;
            }
        }
        return {temp, count};
    }

};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();

    Results results;
    //TODO your code here
    //TODO Read the students from the file and add them in `results`

    ifstream fin("input.txt");
    string id;
    while (fin >> id) {
        if (id == "----") {
            break;
        }
        string name;
        string surname;
        int pts;
        fin >> name;
        fin >> surname;
        fin >> pts;
        Student s = Student(id,name,surname,pts);

        try {
            results += s;
        } catch (StudentFailedException(&a)) {
            a.print();
        }

    }
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line
    ofstream out("output1.txt");
    out<<results;
    out.close();
    Results temp;

        temp = results.withGrade(grade);

    ofstream out2("output2.txt");
    if (temp.getN() == 0) {
        out2<<"None"<<endl;
    }
    else {
        out2 << temp;
    }
    out2.close();
    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");


    return 0;
}