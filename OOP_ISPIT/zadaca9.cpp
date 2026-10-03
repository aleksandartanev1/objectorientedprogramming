//
// Created by aleks on 6/18/2025.
//

#include<iostream>
#include<cstring>

using namespace std;

class LoshaGodinaException : exception {
public:
	LoshaGodinaException() {}
	void print() {
		cout<<"Ne moze da se vnese dadeniot trud"<<endl;
	}
};

class Trud {
	char znak; // C konfrenci J spisanie
	int godina;
public:
	Trud(char znak = 'C', int godina = 0) {
		this->znak = znak;
		this->godina = godina;
	}

	char getZnak() {
		return znak;
	}

	int getTrudGod() {
		return godina;
	}

	friend istream& operator>>(istream& in, Trud& t) {
		in>>t.znak>>t.godina;
		return in;
	}
};

class Student {
protected:
	string ime;
	int indeks;
	int godupis;
	int *ocenki;
	int brojocenki;
public:
	Student(string ime = " ", int indeks = 0, int godupis = 0, int *ocenki = nullptr, int brojocenki = 0) {
		this->ime = ime;
		this->indeks = indeks;
		this->godupis = godupis;
		this->brojocenki = brojocenki;
		this->ocenki = new int[brojocenki];
		for(int i = 0; i < brojocenki; i++) {
			this->ocenki[i] = ocenki[i];
		}
	}

	int getIndex() {
		return indeks;
	}

	Student& operator=(const Student& other) {
		if(this != &other) {
			delete[]this->ocenki;
			this->ime = other.ime;
			this->indeks = other.indeks;
			this->godupis = other.godupis;
			this->brojocenki = other.brojocenki;
			this->ocenki = new int[other.brojocenki];
			for(int i = 0; i < other.brojocenki; i++) {
				this->ocenki[i] = other.ocenki[i];
			}
		}
	}

	Student(const Student& other) {
		this->ime = other.ime;
		this->indeks = other.indeks;
		this->godupis = other.godupis;
		this->brojocenki = other.brojocenki;
		this->ocenki = new int[other.brojocenki];
		for(int i = 0; i < other.brojocenki; i++) {
			this->ocenki[i] = other.ocenki[i];
		}
	}

	~Student() {
		delete[]this->ocenki;
	}

	virtual float rang() {
		float sum = 0;
		for(int i = 0; i < brojocenki; i++) {
			sum+=ocenki[i];
		}

		return sum / brojocenki;
	}

	friend ostream& operator<<(ostream& out, Student &s) {
		out<<s.indeks<<" "<<s.ime<<" "<<s.godupis<<" "<<s.rang()<<endl;
		return out;
	}
};

class PhDStudent : public Student {
	Trud* trudovi;
	int brojnatrudovi;
public:
	PhDStudent(string ime = " ", int indeks = 0, int godupis = 0, int *ocenki = nullptr, int brojocenki = 0, Trud* trudovi = nullptr, int brojnatrudovi = 0) : Student(ime, indeks, godupis, ocenki, brojocenki) {
		this->brojnatrudovi = brojnatrudovi;
		this->trudovi = new Trud[brojnatrudovi];
		for(int i = 0; i < brojnatrudovi; i++) {
			this->trudovi[i] = trudovi[i];
		}
	}

	PhDStudent& operator=(const PhDStudent& other) {
		if(this != &other) {
			delete[]this->trudovi;
			Student::operator=(other);
			this->brojnatrudovi = other.brojnatrudovi;
			this->trudovi = new Trud[other.brojnatrudovi];
			for(int i = 0; i < other.brojnatrudovi; i++) {
				this->trudovi[i] = other.trudovi[i];

			}
		}
		return *this;
	}

	PhDStudent(const PhDStudent& other) {
		Student::operator=(other);
		this->brojnatrudovi = other.brojnatrudovi;
		this->trudovi = new Trud[other.brojnatrudovi];
		for(int i = 0; i < other.brojnatrudovi; i++) {
			this->trudovi[i] = other.trudovi[i];
		}
	}

	~PhDStudent() {
		delete[]this->trudovi;
	}

	float rang() override {
		float suma = Student::rang();
		for(int i = 0; i < brojnatrudovi; i++) {
			if(trudovi[i].getZnak() == 'C' || trudovi[i].getZnak() == 'c') {
				suma+=1;
			} else if (trudovi[i].getZnak() == 'J' || trudovi[i].getZnak() == 'j') {
				suma+=3;
			}
		}

		return suma;
	}

	PhDStudent& operator+=(Trud o) {
		if(o.getTrudGod() > godupis) {
			throw LoshaGodinaException();
		}

		Trud* temp = new Trud[brojnatrudovi + 1];
		for(int i = 0; i < brojnatrudovi; i++) {
			temp[i] = trudovi[i];
		}

		temp[brojnatrudovi] = o;
		brojnatrudovi++;
		delete[]trudovi;
		trudovi = temp;

		return *this;
	}


};

int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=



		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2

		for (int i = 0; i < m; i++) {
			if (niza[i]->getIndex() == indeks) {
				PhDStudent *temp = dynamic_cast<PhDStudent *>(niza[i]);
				if (temp) {
					try {
						*temp += t;
					} catch (LoshaGodinaException &e) {
						e.print();
					}
				} else {
					cout << "Ne postoi PhD student so indeks " << indeks << endl;
				}
			}
		}

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}