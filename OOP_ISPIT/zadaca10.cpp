//
// Created by aleks on 6/17/2025.
//
#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

//место за вашиот код

class NegativnaVrednost : exception {
public:
	NegativnaVrednost(){}

	void print() {
		cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
	}
};

class Oglas {
	string naslov;
	string category;
	string opis;
	float cena;
public:
	Oglas(string naslov = " ", string category = " ", string opis = " ", float cena = 0) {
		this->naslov = naslov;
		this->category = category;
		this->opis = opis;
		this->cena = cena;
	}

	float getCena() {
		return cena;
	}

	string getCategory() {
		return category;
	}

	bool operator > (Oglas &a ) {
		return cena > a.cena;
	}

	friend ostream& operator<<(ostream& out, Oglas o) {
		out<<o.naslov<<endl;
		out<<o.opis<<endl;
		out<<o.cena<<" evra"<<endl;
		out<<endl;
		return out;
	}
};

class Oglasnik {
	string imeoglasnik;
	Oglas* oglasi;
	int n;
public:
	Oglasnik(string imeoglasnik = " ", Oglas* oglasi = nullptr, int n = 0) {
		this->imeoglasnik = imeoglasnik;
		this->n = n;
		this->oglasi = new Oglas[n];
		for(int i = 0; i < n; i++) {
			this->oglasi[i] = oglasi[i];
		}
	}

	Oglasnik(const Oglasnik &o) {
		this->imeoglasnik = o.imeoglasnik;
		this->n = o.n;
		this->oglasi = new Oglas[o.n];
		for(int i = 0; i < o.n; i++) {
			this->oglasi[i] = o.oglasi[i];
		}
	}

	~Oglasnik() {
		delete[]this->oglasi;
	}

	Oglasnik& operator=(Oglasnik& o) {
		if (this != &o) {
			delete[]this->oglasi;
			this->imeoglasnik = o.imeoglasnik;
			this->n = o.n;
			this->oglasi = new Oglas[o.n];
			for(int i = 0; i < o.n; i++) {
				this->oglasi[i] = o.oglasi[i];
			}
		}
		return *this;
	}

	Oglasnik& operator+=(Oglas& o) {
		if(o.getCena() < 0) {
			throw NegativnaVrednost();
		}

		Oglas* temp = new Oglas[n + 1];
		for(int i = 0; i < n; i++) {
			temp[i] = oglasi[i];
		}
		temp[n] = o;
		n++;
		delete[]oglasi;
		oglasi = temp;

		return *this;
	}

	friend ostream& operator<<(ostream& out, Oglasnik &o) {
		out<<o.imeoglasnik<<endl;
		for(int i = 0; i < o.n; i++) {
			out<<o.oglasi[i];
		}
		return out;
	}

	void oglasiOdKategorija(const char *k) {
		for(int i = 0; i < n; i++) {
			if(oglasi[i].getCategory() == k) {
				cout<<oglasi[i];
			}
		}
	}

	void najniskaCena() {
		int naj = 0;
		for(int i = 0; i < n; i++) {
			if(oglasi[i].getCena() < oglasi[naj].getCena()) {
				naj = i;
			}
		}
		cout<<oglasi[naj];
	}

};


int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try {
        		ogl+=o;
        	} catch (NegativnaVrednost &e) {
        		e.print();
        	};
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try {
        		ogl+=o;
        	} catch (NegativnaVrednost &e) {
        		e.print();
        	};
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}
