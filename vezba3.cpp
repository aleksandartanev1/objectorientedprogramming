/*programa sho vrakja drzavi i detali za niv */
#include <iostream>
#include<cstring>
using namespace std;

struct grad {
    string imegrad;
    int ziteli;

};

struct drzava {

    string ime;
    string predsedatel;
    int ziteli;
    grad glaven;

    void print () {
        cout<<ime<<endl;
        cout<<predsedatel<<endl;
        cout<<ziteli<<endl;
        cout<<glaven.imegrad<<endl;
        cout<<glaven.ziteli<<endl;
    }
};

void out(drzava &d) {
    cout<<d.ime<<endl;
    cout<<d.predsedatel<<endl;
    cout<<d.ziteli<<endl;
    cout<<d.glaven.imegrad<<endl;
    cout<<d.glaven.ziteli<<endl;
}

void read (int n, drzava c[]) {
    for (int i = 0; i < n; i++) {
        cin>>c[i].ime;
        cin>>c[i].predsedatel;
        cin>>c[i].glaven.imegrad;
        cin>>c[i].glaven.ziteli;
        cin>>c[i].ziteli;
    }
};

    void maxCapitalPopulation(int n, drzava c[]) {
    drzava max = c[0];
    for (int i = 1; i < n; ++i) {
        if (c[i].glaven.ziteli > max.glaven.ziteli) {
            max = c[i];
        }
    }

    cout << max.predsedatel << endl;

}

int main () {

    drzava countries[100];
    int n;
    cin >> n;
    read(n, countries);

    for (int i = 0; i < n; ++i) {
        //print(countries[i]);
        countries[i].print();
    }

    maxCapitalPopulation(n, countries);

}
