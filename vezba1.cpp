#include <iostream>

using namespace std;

struct dae {
    int godina;
    int mesec;
    int den;
};
void print (dae &d) {
    cout<<d.godina<<" "<<d.mesec<<" "<<d.den<<endl;
}
void citaj (dae &d) {
    cin>>d.godina>>d.mesec>>d.den;
}

int main() {
    dae d1;
    citaj (d1);
    print(d1);
}