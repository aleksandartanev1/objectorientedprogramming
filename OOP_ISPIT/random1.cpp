//
// Created by aleks on 6/17/2025.
//
// Опис на задачата
//
// Да се дефинира класа BankAccount во која се чуваат информации за банкарска сметка:
// - број на сметка (string)
// - име на сопственик (string)
// - тип на сметка (string)
// - салдо (int)
//
// За класата BankAccount да се дефинираат:
// 1. Потребни конструктори
// 2. Методи set() и get() за сите атрибути
// 3. Оператор >> за вчитување од stream
// 4. Оператор << за печатење во stream
// 5. Префиксен ++ за зголемување на салдото за 100
// 6. Постфикс -- за намалување на салдото за 100
// 7. Оператор += кој додава на салдото одреден број (int)
// 8. Метод void print(ofstream& out) – печати ја целата информација за сметката во подадениот ofstream
//
// Да се дефинира класа Bank која чува листа на сметки (динамички алоцирана низа на објекти BankAccount и број на сметки).
//
// За класата Bank да се имплементираат:
// 1. Потребни конструктори и деструктор
// 2. Оператор += за додавање BankAccount во банката
// 3. Оператор [] кој враќа референца кон BankAccount со даден број на сметка; ако не постои, да фрли AccountNotFoundException
// 4. Оператор << за печатење на сите сметки во банката
// 5. Метод Bank notOfType(string type) – враќа нов објект Bank во кој се вклучени сите сметки чиј тип не е type
//
// Главни барања (main)
//
// 1. Од стандардниот влез се читаат линии во формат:
//    <бројСметка> <имеСопственик> <типСметка> <салдо>
//    Се чита додека не се внесе ----; сите линии се запишуваат во input.txt.
// 2. Во main() да се отвори input.txt и со operator>> да се вчитаат сите BankAccount и да се додаваат во објектот bank (со operator+=).
// 3. По вчитувањето, од стандардниот влез да се прочитаат два стринга:
//    - searchNumber – број на сметка за пребарување
//    - filterType – тип на сметка за филтрирање (notOfType)
// 4. Во фајлот output1.txt да се испишат сите сметки (со operator<< на Bank).
// 5. Во фајлот output2.txt:
//    - Пребарај bank[searchNumber]: ако постои, повикај print(ofstream&) за таа сметка; ако не постои, фрли и фати AccountNotFoundException и запиши:
//      No account with number <searchNumber> found.
//    - Потоа повикај bank.notOfType(filterType) и со operator<< запиши ги сите преостанати сметки.
// 6. На крај, програмата да отпечати на екран:
//    All accounts:
//    <содржина на output1.txt>
//    Search result for account <searchNumber>:
//    <содржина на output2.txt>
//
// Starter Main Code:

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class AccountNotFoundException : exception {
    string broj;
public:
    AccountNotFoundException(string broj) {
        this->broj = broj;
    }

    void print() {
        cout<<"The account with number: "<<broj<<" was not found"<<endl;
    }
};

class BankAccount {
    string broj;
    string ime;
    string type;
    int saldo;
public:
    BankAccount(string broj = " ", string ime = " ", string type = " ", int saldo = 0) {
        this->broj = broj;
        this->ime = ime;
        this->type = type;
        this->saldo = saldo;
    }

    string getBroj() {
        return broj;
    }
    string getIme() {
        return ime;
    }
    string getType() {
        return type;
    }
    int getSaldo() {
        return saldo;
    }

    void setBroj(string b) {
        broj = b;
    }
    void setIme(string b) {
        ime = b;
    }
    void setType(string b) {
        type = b;
    }
    void setSaldo(int b) {
        saldo = b;
    }


    friend istream& operator>>(istream& in, BankAccount& b) {
        in>>b.broj;
        in>>b.ime;
        in>>b.type;
        in>>b.saldo;
        in.ignore();
        return in;
    }

    friend ostream& operator<<(ostream& out, BankAccount& b) {
        out<<"Sopstvenik: "<<b.ime<<" Type: "<<b.type<<"- - - Saldo: "<<b.saldo<<"$"<<endl;
        return out;
    }

    void operator--() {
        saldo-=100;
    }

    void operator++() {
        saldo+=100;
    }

    void operator--(int) {
        saldo-=100;
    }

    void operator++(int) {
        saldo+=100;
    }

    BankAccount& operator+=(int b) {
        saldo+=b;
        return *this;
    }

    void print(ofstream& out) {
        out<<"Sopstvenik: "<<ime<<" Type: "<<type<<"- - - Saldo: "<<saldo<<"$"<<endl;
    }
};

class Bank {
    BankAccount* accounts;
    int n;
public:
    Bank() {
        accounts = nullptr;
        n = 0;
    }

    Bank(BankAccount* accounts, int n) {
        this->n = n;
        this->accounts = new BankAccount[n];
        for(int i = 0; i < n; i++) {
            this->accounts[i] = accounts[i];
        }
    }

    Bank(const Bank &o) {
        this->n = o.n;
        accounts = new BankAccount[o.n];
        for(int i = 0; i < n; i++) {
            this->accounts[i] = o.accounts[i];
        }
    }

    Bank& operator=(const Bank& o) {
        if(this != &o) {
            delete[]this->accounts;
            this->n = o.n;
            this->accounts = new BankAccount[o.n];
            for(int i = 0; i < o.n; i++) {
                this->accounts[i] = o.accounts[i];
            }
        }
        return *this;
    }

    ~Bank() {
        delete[]this->accounts;
    }

    Bank& operator+=(BankAccount &b) {
        BankAccount* temp = new BankAccount[n + 1];
        for(int i = 0; i < n; i++) {
            temp[i] = accounts[i];
        }
        temp[n] = b;
        n++;
        delete[]accounts;
        accounts = temp;

        return *this;
    }

    BankAccount& operator[](string b) {
        for(int i = 0; i < n; i++) {
            if(accounts[i].getBroj() == b) {
                return accounts[i];
            }
        }

        throw AccountNotFoundException(b);
    }

    friend ostream& operator<<(ostream& out, Bank& b) {
        for(int i = 0; i < b.n; i++) {
            out<<b.accounts[i];
        }
        return out;
    }

    Bank notOfType(string type) {
        BankAccount* temp = new BankAccount[n];
        int index = 0;
        for(int i = 0; i < n; i++) {
            if(accounts[i].getType() != type) {
                temp[index] = accounts[i];
                index++;
            }
        }

        return {temp, index};
    }

};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(cin, line)) {
        if (line == "----") break;
        fout << line << "\n";
    }
}

void rff(const string &path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << "\n";
    }
}

int main() {
    wtf();

    Bank bank;
    //TODO ваш код
    //TODO прочитајте BankAccount објекти од input.txt (со operator>>) и додадете ги во `bank`
    ifstream in("input.txt");
    if (!in.is_open()) {
        cout << "Не може да се отвори input.txt" << endl;
        return 1;
    }
    string broj;
    while(in>>broj) {
        if(broj == "----") {
            break;
        }
        string number = broj;
        string ime;
        string type;
        int saldo;
        in>>ime;
        in>>type;
        in>>saldo;

        BankAccount b(number, ime,type,saldo);

        bank+=b;
    }

    in.close();

    string searchNumber, filterType;
    cin >> searchNumber >> filterType;

    //TODO запишете во output1.txt: сите сметки (operator<< на bank)

    ofstream fout("output1.txt");
    fout<<bank;
    fout.close();

    //TODO запишете во output2.txt:
    //   • резултат од bank[searchNumber].print(fout2) или порака при исклучок
    //   • резултат од bank.notOfType(filterType) (operator<<)
    ofstream fout2("output2.txt");
    try {
        BankAccount temp = bank[searchNumber];
        temp.print(fout2);
    } catch (AccountNotFoundException(&e)) {
        e.print();
    }
        Bank temp2 = bank.notOfType(filterType);
        fout2<<temp2;


    fout2.close();




    cout << "All accounts:" << endl;
    rff("output1.txt");
    cout << "Search result for account " << searchNumber << ":" << endl;
    rff("output2.txt");

    return 0;
}
