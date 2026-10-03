//
// Created by aleks on 6/17/2025.
//
#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код

class Delo {
    string name;
    int godina;
    string country;
public:
    Delo(string name = " ", int godina = 0, string country = " ") {
        this->name = name;
        this->godina = godina;
        this->country = country;
    }
    string getIme() {return name;}
    string getCountry() {return country;}
    int getGodina() {return godina;}

    void setName(string n) {name = n;};
    void setCountry(string c) {country = c;};
    void setGodina(int g) {godina = g;};

    bool operator==(const Delo &a) const {return name == a.name;};

};

class Pretstava {
protected:
    Delo delo;
    int karti;
    string date;
public:
    Pretstava(Delo delo, int karti = 0, string date = " ") {
        this->delo = delo;
        this->date = date;
        this->karti = karti;
    }

    Delo getDelo() {
        return delo;
    }

    int getKarti() {
        return karti;
    }

    virtual int cena() {
        int price = 0;
        if(delo.getGodina() >= 1901 && delo.getGodina() <= 2100) {
            price+=50;
        } else if(delo.getGodina() >= 1801 && delo.getGodina() <= 1900) {
            price+=75;
        } else if(delo.getGodina() < 1801) {
            price+=100;
        }

        if (delo.getCountry() == "Italija") {
            price+=100;
        } else if (delo.getCountry() == "Rusija") {
            price+=150;
        } else price+=80;


        return price;
    }
};

class Opera : public Pretstava {
public:
    Opera(Delo delo, int karti = 0, string date = " ") : Pretstava(delo, karti, date) {

    }

    int cena() override {
        int price = 0;
        if(delo.getGodina() >= 1901 && delo.getGodina() <= 2100) {
            price+=50;
        } else if(delo.getGodina() >= 1801 && delo.getGodina() <= 1900) {
            price+=75;
        } else if(delo.getGodina() < 1801) {
            price+=100;
        }

        if (delo.getCountry() == "Italija") {
            price+=100;
        } else if (delo.getCountry() == "Rusija") {
            price+=150;
        } else price+=80;


        return price;
    }


};

class Balet : public Pretstava {
    static int atribut;
public:
    Balet(Delo delo, int karti = 0, string date = " ") : Pretstava(delo, karti, date) {
;
    }

    static void setCenaBalet(const int m) {
        atribut = m;
    }

    int cena() override {
        int price = 0;
        if(delo.getGodina() >= 1901 && delo.getGodina() <= 2100) {
            price+=50;
        } else if(delo.getGodina() >= 1801 && delo.getGodina() <= 1900) {
            price+=75;
        } else if(delo.getGodina() < 1801) {
            price+=100;
        }

        if (delo.getCountry() == "Italija") {
            price+=100;
        } else if (delo.getCountry() == "Rusija") {
            price+=150;
        } else price+=80;

        price+=atribut;

        return price;
    }

};

int Balet::atribut = 150;

int prihod (Pretstava** p, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
      sum+=  p[i]->cena() * p[i]->getKarti();
    }

    return sum;
};

int brojPretstaviNaDelo(Pretstava **p, int n, Delo d) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(p[i]->getDelo() == d) {
            sum++;
        }
    }
    return sum;
}





//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
