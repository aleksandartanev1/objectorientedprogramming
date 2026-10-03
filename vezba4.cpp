#include<iostream>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

void read (Date &d) {
    cin>>d.day>>d.month>>d.year;
}

void print (Date &d) {
    cout<<d.day<<"-"<<d.month<<"-"<<d.year<<endl;
}

void compare (Date &a , Date &b) {
    if (a.year > b.year) {
        cout<<"Prvata data e podocna"<<endl;
    }
    else if (a.month > b.month) {
        cout<<"Prvata data e podocna"<<endl;
    }
    else if (a.day > b.day) {
        cout<<"Prvata data e podocna"<<endl;
    }
    else if (a.month > b.month) {
    }
    else if (a.year<b.year) {
        cout<<"Vtorata data e podocna"<<endl;
    } else if (a.month<b.month) {
        cout<<"Vtorata data e podocna"<<endl;
    }
    else if (a.day < b.day) {
        cout<<"Vtorata data e podocna"<<endl;
    }
    else cout<<"Datite se isti" <<endl;
}
int main () {
    Date d1;
    Date d2;
    read(d1);
    read(d2);
    print(d1);
    print(d2);
    compare(d1,d2);
}