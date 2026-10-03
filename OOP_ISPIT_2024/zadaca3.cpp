//
// Created by aleks on 6/16/2025.
//

#include <iostream>
#include <cstring>
#include<fstream>

using namespace std;

class NoProductFoundException : exception {
    string category;
public:
    NoProductFoundException(string category) {
        this->category = category;
    }
    void print() {
        cout<<"No products from category "<<category<<" were found in the store"<<endl;
    }
};

class Product {
    string name;
    string category;
    int price;
    int available;
public:
    Product(string name = " ", string category = " ", int price = 0, int available = 0) {
        this->name = name;
        this->category = category;
        this->price = price;
        this->available = available;
    }

    friend ostream& operator<<(ostream& out, Product& p) {
        out<<p.name<<" ("<<p.category<<") "<<p.available<<" x "<<p.price<<" = "<<p.totalPrice()<<endl;
        return out;
    }


    int totalPrice() {
        int total = price * available;
        return total;
    }

    bool sameCategory(string c) {
        return category == c;
    }

};

class Store {
    Product *products;
    int number;
public:
    Store(Product* products = nullptr, int number = 0) {
        this->number = number;
        this->products = new Product[number];
        for(int i = 0; i < number; i++) {
            this->products[i] = products[i];
        }
    }

    ~Store() {
        delete[]this->products;
    }

    Store(const Store& o) {
        this->number = o.number;
        this->products = new Product[o.number];
        for(int i = 0; i < o.number; i++) {
            this->products[i] = o.products[i];
        }
    }

    Store& operator=(const Store& o) {
        if(this != &o) {
            delete[]this->products;
            this->number = o.number;
            this->products = new Product[o.number];
            for(int i = 0; i < o.number; i++) {
                this->products[i] = o.products[i];
            }
        }
        return *this;
    }

    Store& operator+=(Product p) {
        Product* temp = new Product[number + 1];
        for(int i = 0; i < number; i++) {
            temp[i] = products[i];
        }
        temp[number] = p;
        number++;
        delete[]products;
        products = temp;

        return *this;
    }

    friend ostream& operator<<(ostream& out, Store& s) {
        for(int i = 0; i < s.number; i++) {
            out<<s.products[i];
        }
        return out;
    }




    Store fromCategory(string &category) {
        int count = 0;
        Product *temp = new Product[number + 1];
        for(int i = 0; i < number; i++) {
            if(products[i].sameCategory(category)) {
                temp[count] = products[i];
                count++;
            }
        }
    if (count == 0) {
        delete[]temp;
        throw NoProductFoundException(category);
    }
        return {temp, count};

    }
};



void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`
    ifstream fin("input.txt");
    string line;
    while(getline(fin, line)) {
        if(line == "----") {
            break;
        }
        string name;
        string category;
        int price;
        int number;
        name = line;
        getline(fin, category);
        fin >> price;
        fin >> number;
        fin.ignore();
        Product p = Product(name, category, price, number);
            s += p;
    }
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line
    ofstream fout("output1.txt");
    fout<<s;
    fout.close();


    ofstream fout2("output2.txt");
    Store temp;
    try {
        temp = s.fromCategory(category);
        fout2<<temp<<endl;
    } catch (NoProductFoundException &e) {
        e.print();
    };
    fout2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}