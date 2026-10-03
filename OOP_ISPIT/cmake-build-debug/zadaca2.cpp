// vashiot kod ovde

#include<iostream>
#include<cstring>

using namespace std;
class Vozac {
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool vet;

public:
    Vozac (char *ime = "", int vozrast = 0, int trki = 0, bool vet = 0) {
        strcpy(this->ime, ime);
        this->vozrast = vozrast;
        this->trki = trki;
        this->vet = vet;
    }

    friend ostream& operator<< (ostream& out, Vozac &o) {
        out<<o.ime<<endl;
        out<<o.vozrast<<endl;
        out<<o.trki<<endl;
        if (o.vet) {
            out<<"VETERAN"<<endl;
        }

        return out;
    }

    Vozac& operator=(const Vozac& other) {
        if (this != &other) {
            strcpy(this->ime, other.ime);
            this->vozrast = other.vozrast;
            this->trki = other.trki;
            this->vet = other.vet;
        }
        return *this;
    }


    virtual float zarabotuvacka() = 0;
    virtual float danok() = 0;
};

class Avtomobilist : public Vozac {
    float cena_avto;
public:
    Avtomobilist(char *ime = "", int vozrast = 0, int trki = 0, bool vet = 0, float cena_avto = 0) : Vozac(ime, vozrast, trki, vet) {
        this->cena_avto = cena_avto;
    }

    Avtomobilist& operator= (const Avtomobilist& other) {
        if (this != &other) {
            Vozac::operator=(other); // или рачно копирање
            this->cena_avto = other.cena_avto;
        }
        return *this;
    }



    float zarabotuvacka() override {
        return cena_avto / 5;
    }

    float danok() override {
        if (trki > 10) {
            return zarabotuvacka() * 0.15;
        } else return zarabotuvacka() * 0.1;
    }


};

class Motociklist : public Vozac {
    int mokjnost;
public:
    Motociklist(char *ime = "", int vozrast = 0, int trki = 0, bool vet = 0, int mokjnost = 0) : Vozac(ime, vozrast, trki, vet) {
        this->mokjnost = mokjnost;
    }

    Motociklist& operator= (const Motociklist& other) {
        if (this != &other) {
            Vozac::operator=(other); // или рачно копирање
            this->mokjnost = other.mokjnost;
        }
        return *this;
    }

    float zarabotuvacka() override {
        return mokjnost * 20;
    }

    float danok() override {
        if (vet) {
            return zarabotuvacka() * 0.25;
        } else return zarabotuvacka() * 0.2;
    }

};
int soIstaZarabotuvachka (Vozac **array, int n, Vozac *obj) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (array[i]->zarabotuvacka() == obj->zarabotuvacka()) {
            counter++;
        }
    }
    return counter;
}




int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}