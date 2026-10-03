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
    int quantity;
public:
    Product(string name = " ", string category = " ", int price = 0, int quantity = 0) {
        this->name = name;
        this->category = category;
        this->price = price;
        this->quantity = quantity;
    }

    int totalPrice() {
        return quantity * price;
    }

    friend ostream& operator<<(ostream& out, Product &p) {
        out<<p.name<<" ("<<p.category<<") "<<p.quantity<<" x "<<p.price<<" = "<<p.totalPrice()<<endl;
        return out;
    }

    bool sameCategory(string cate) {
        return category == cate;
    }
};

class Store {
    Product* products;
    int n;
public:
    Store(Product* products = nullptr, int n = 0) {
        this->n = n;
        this->products = new Product[n];
        for(int i = 0; i < n; i++) {
            this->products[i] = products[i];
        }
    }

    int getN() {
        return n;
    }

    ~Store() {
        delete[]this->products;
    }

    Store(const Store& o) {
        this->n = o.n;
        this->products = new Product[o.n];
        for(int i = 0; i < n; i++) {
            this->products[i] = o.products[i];
        }
    }

    Store& operator= (const Store& o) {
        if(this != &o) {
            delete[]this->products;
            this->n = o.n;
            this->products = new Product[o.n];
            for(int i = 0; i < n; i++) {
                this->products[i] = o.products[i];
            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, Store& s) {
        for(int i = 0; i < s.n; i++) {
            out<<s.products[i];
        }
        return out;
    }

    Store& operator+= (Product p) {
        Product* temp;
        temp = new Product[n+1];

        for(int i = 0; i < n; i++) {
            temp[i] = products[i];
        }
        temp[n] = p;
        delete[]products;
        products = temp;
        n++;

        return *this;
    }

    Store fromCategory (string &category) {
        Product* temp = new Product[n];
        int index = 0;
        for(int i = 0; i < n; i++) {
            if(products[i].sameCategory(category)) {
                temp[index] = products[i];
                index++;
            }
        }

        if (index == 0) {
            delete[]temp;
            throw NoProductFoundException(category);
        }

        return {temp, index};
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
        string categor;
        int quantity;
        int price;
        name = line;
        fin>>categor;
        fin>>price;
        fin>>quantity;
        fin.ignore();

        Product p(name,categor,price,quantity);

        s+=p;
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