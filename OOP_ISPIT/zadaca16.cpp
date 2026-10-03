// вашиот код треба да биде тука
#include<iostream>
#include<cstring>

using namespace std;

class Transport {
protected:
    string destination;
    int price;
    int distance;
public:
    Transport(string destination = " ", int price = 0, int distance = 0) {
        this->destination = destination;
        this->price = price;
        this->distance = distance;
    }

    virtual int cenaTransport() = 0;
    virtual int getDistance() = 0;

    string getDestination() {
        return destination;
    }

    friend ostream& operator<<(ostream& out, Transport& o) {
        out<<o.destination<<" "<<o.distance<<" "<<o.price<<endl;
        return out;
    }
};

class AvtomobilTransport : public Transport {
    bool sofer;
public:
    AvtomobilTransport(string destination = " ", int price = 0, int distance = 0, bool sofer = 0) {
        this->destination = destination;
        this->price = price;
        this->distance = distance;
        this->sofer = sofer;
    }
    string getDestination() {
        return destination;
    }
    int getDistance() override {
        return distance;
    }

    int cenaTransport() override {
        int cena = price;
        if(sofer) {
            cena += price * 0.2;
        }

        return cena;
    }

    bool operator< (AvtomobilTransport &p) {
        return getDistance() < p.getDistance();
    }
};

class KombeTransport : public Transport {
    int people;
public:
    KombeTransport(string destination = " ", int price = 0, int distance = 0, int people = 0) {
        this->destination = destination;
        this->price = price;
        this->distance = distance;
        this->people = people;
    }
    int getDistance() override {
        return distance;
    }
    string getDestination() {
        return destination;
    }



    int cenaTransport() override {
        int cena = price;

        cena -= 200 * people;

        return cena;
    }

    bool operator< (KombeTransport &p) {
        return getDistance() < p.getDistance();
    }
};

void pecatiPoloshiPonudi(Transport** ponudi, int n, AvtomobilTransport nov) {

    for(int i = 0; i < n - 1; i++) {
        if(ponudi[i]->getDistance() > ponudi[i + 1]->getDistance()) {
            swap(ponudi[i], ponudi[i + 1]);
        }
    }

    for(int i = 0; i < n; i++) {
        if(ponudi[i]->cenaTransport() > nov.cenaTransport()) {
            cout<<ponudi[i]->getDestination()<<" "<<ponudi[i]->getDistance()<<" "<<ponudi[i]->cenaTransport()<<endl;
        }
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
