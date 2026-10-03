//
// Created by aleks on 5/21/2025.
//
#include <iostream>
#include <cstring>

using namespace std;

class NoProductFoundException : public exception {
private:
    string category;

public:
    NoProductFoundException(const string &category = "") {
        this->category = category;
    }

    void print() {
        cout << "No products from category " << category << " were found in the store" << endl;
    }
};

class Product {
    string name;
    string category;
    int price;
    int stock;
public:
    Product(string name = " ", string category = " ", int price = 1, int stock = 1) {
        this->name = name;
        this->category = category;
        this->price = price;
        this->stock = stock;
    }

    friend ostream& operator<<(ostream& out, Product& p) {
        out<<p.name<<" "<<p.category<<" "<<p.price<<" "<<p.stock<<endl;
        return out;
    }

    int totalPrice() {
        return price * stock;
    }

    string getCategory() {
        return category;
    }
};

class Store {
    Product* products;
    int amount;
public:
    Store(Product *products, int amount) {
        this->amount = amount;
        products = new Product[amount];
        for(int i = 0; i < amount; i++) {
            this->products[i] = products[i];
        }
    }

    Store operator+=(Product a) {
        products[amount++] = a;
    }

    friend ostream& operator<<(ostream& out, Store& s) {
        for (int i = 0; i < s.amount; i++) {
            out<<s.products[i]<<" ";
        }
        return out;
    }


    Store fromCategory(string &category) {
        int counter = 0;
        Product *temp = new Product[amount + 1];
        for (int i = 0; i < amount; i++) {
            if (products[i].getCategory() == category) {
                temp[counter] = products[i];
                counter++;
            }
        }
        if (counter == 0) {
            delete[] temp;
            throw NoProductFoundException(category);
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


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line


    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}