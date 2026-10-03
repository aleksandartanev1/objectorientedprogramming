//
// Created by aleks on 3/25/2025.
//

#include<iostream>
#include <stdarg.h>
using namespace std;

class List {
private:
    int n;
    int *array;

public:
    List (int _array[], int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            array[i] = _array[i];
        }
    }
    List(const List &other) {
        n = other.n;
        array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = other.array[i];
        }
    }

    List& operator=(const List &other) {
        if (this != &other) {
            delete[] array;
            n = other.n;
            array = new int[n];
            for (int i = 0; i < n; i++) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }


    List () {
        n = 10;
        array[100];
    }

    ~List();


    int sum() {
        int suma = 0;
        for (int i = 0; i < n; i++) {
            suma += array[i];
        }
        return suma;
    }

    double average() {
        int avg = 0;
        for (int i = 0; i < n; i++) {
            avg += array[i];
        }
        return avg/n;
    }

    void pecati() {
        cout << n << ": ";
        for (int i = 0; i < n; ++i) {
            cout << array[i] << ' ';
        }
        cout << "sum: " << sum() << " average: " << average() << '\n';
    }
};

List::~List() {
    delete[] array;
}


class ListContainer {
private:
    List ni[100];
    int k;
    int o = 0;

public:
    ListContainer(List _ni[], int _k, int _l) {
        o = _l;
        k = _k;
        for (int i = 0; i < k; i++) {
            ni[i] = _ni[i];
        }
    }

    ListContainer (int k = 0, int l = 0) {}


~ListContainer(){};


    void print(){
        if (k==0) {
            cout << "The list is empty\n";
            return;
        }
        for (int i = 0; i < k; ++i) {
            cout << "List number: " << i+1 << " List info: ";
            ni[i].pecati();

        }
        cout << "Sum: " << sum() << " Average: " << average() << '\n';
        cout << "Successful attempts: "<< k << " Failed attempts: "
             << o - k  << '\n';
    }

    int sum () {
        int suma = 0;
        for (int i = 0; i < k; i++) {
            suma += ni[i].sum();
        }
        return suma;
    }

    double average() {
        int sumaavg = 0;
        for (int i = 0; i < k; i++) {
            sumaavg+=ni[i].sum();
        }
        return (double)sumaavg / k;
    }

    void addNewList(List l) {
        if (k < 100) {  // Проверка дали има простор
            ni[k] = l;  // Користи оператор =
            k++;        // Зголемување на бројот на листи
        }
        o++;  // Зголемување на бројот на обиди (успешни + неуспешни)
    }
};


int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}