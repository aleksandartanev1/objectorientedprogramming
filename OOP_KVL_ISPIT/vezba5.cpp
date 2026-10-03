//
// Created by aleks on 4/10/2025.
//

#include <iostream>

using namespace std;

class Product {
protected:
    string id;
    float price;
public:
    Product(string id = "PROD-123456", float price = 10.0) : id(id), price(price) {}

    ~Product() {}

    void print() {
        cout << id << " " << price << " ";
    }

    float getPrice () {
        return price;
    }
};

class DiscountProduct {
    Product product;
    int discount;
public:
    DiscountProduct () {
        product = Product("PROD-123456", 10.0);
        discount = 10;
    }

    DiscountProduct (string id, float price, int discount) {
        product = Product(id, price);
        this->discount = discount;
        if (this-> discount >= 100 || this-> discount <= 0 ) {
            this-> discount = 10;
        }
    }
    float calculatePrice() {
        return product.getPrice() - ((product.getPrice() * discount) / 100);
    }

    void print () {
        product.print();
        cout<<discount<<endl;
    }
};



DiscountProduct *createDicsProducts(int n) {
    DiscountProduct *discProducts = new DiscountProduct[n];
    string id;
    float price;
    int disc;
    for (int i = 0; i < n; i++) {
        cin >> id >> price >> disc;
        discProducts[i] = DiscountProduct(id, price, disc);
    }
    return discProducts;
}


int main() {
    int testCase;
    cin >> testCase;

    switch (testCase) {
        case 1 : {
            DiscountProduct discountProduct;
            discountProduct.print();
            break;
        }
        case 2 : {
            DiscountProduct discountProduct("CS101", 50, 5);
            discountProduct.print();
            DiscountProduct discountProduct1("CS102", 70, 10);
            discountProduct1.print();
            break;
        }
        case 3 : {
            DiscountProduct discountProduct("CS101", 50, 105);
            discountProduct.print();
            DiscountProduct discountProduct1("CS102", 70, 0);
            discountProduct1.print();
            break;
        }
        case 4: {
            DiscountProduct discountProduct("CS101", 40, 20);
            cout << discountProduct.calculatePrice();
            break;
        }
        case 5: {
            int n;
            cin >> n;
            DiscountProduct *discountProducts = createDicsProducts(n);
            for (int i = 0; i < n; i++) {
                discountProducts[i].print();
            }
            delete [] discountProducts;
            break;
        }
        default: {
            int n;
            cin >> n;

            DiscountProduct *discountProducts = createDicsProducts(n);
            for (int i = 0; i < n; i++) {
                discountProducts[i].print();
            }
            for (int i = 0; i < n; i++) {
                cout << discountProducts[i].calculatePrice() << endl;
            }
            delete [] discountProducts;
            break;
        }
    }
}

