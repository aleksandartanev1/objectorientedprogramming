#include<iostream>
using namespace std;

class example {
private:
    int a;
    int b;

public:
    example () { //default contstructor
        cout<<"Default constructor is called"<<endl;
        a = 0;
        b = 0;
    }

    example (int _a, int _b) { // constructor
        cout<<"Constructor with arguments is called"<<endl;
        a = _a;
        b = _b;
    }
    ~example() {
        cout<<"Object is destroyed"<<endl;
    }
};

int main () {
    example e(10,10);
    cout<<endl;
    example r;
}