//
// Created by aleks on 6/15/2025.
//
//
// Created by aleks on 6/15/2025.
//
#include<iostream>
#include<cstring>

using namespace std;

enum typeC {
  standard, loyal, vip
};

class  UserExistsException : exception {
public:
  UserExistsException() {
  cout<<"The user already exists in the list!"<<endl;
}
};

class Customer {
private:
  char name[50];
  char email[50];
  typeC tc;
  int osnpop;
  int doppop;
  int proizvodi;
public:
  Customer(char *name = (char*)" ", char *email = (char*)" ", typeC tc = standard, int proizvodi = 0) {
    strcpy(this->name, name );
    strcpy(this->email, email);
    this->tc = tc;
    this->proizvodi = proizvodi;
    this->osnpop = 10;
    this->doppop = 20;
  }

  friend ostream& operator<< (ostream& out, Customer& c) {
    out<<c.name<<endl;
    out<<c.email<<endl;
    out<<c.proizvodi<<endl;
    if(c.tc == standard) {
      out<<"standard "<<"0"<<endl;
    } else if (c.tc == loyal) {
      out<<"loyal "<<c.osnpop<<endl;
    } else if (c.tc == vip) {
      out<<"vip "<<c.doppop + c.osnpop<<endl;
    }
    return out;
  }

  bool sameaddress(Customer &e) {
    return strcmp(email, e.email) == 0;
  }

  typeC gettype() {
    return tc;
  }

  int getproizvodi() {
    return proizvodi;
  }

  void settype(typeC c) {
    tc = c;
  }

  void setDiscount1(int c) {
    osnpop = c;
  }
};



class FINKI_bookstore {
Customer* customers;
  int n;
public:
  FINKI_bookstore(Customer* customers = nullptr, int n = 0) {
    this->n = n;
    this->customers = new Customer[n];
    for(int i = 0; i < n; i++) {
      this->customers[i] = customers[i];
    }
  }

  ~FINKI_bookstore() {
    delete[]this->customers;
  }

  FINKI_bookstore& operator += (Customer& c) {

    for(int i = 0; i < n; i++) {
      if(customers[i].sameaddress(c)) {
        throw UserExistsException();
      }
    }

    Customer *temp = new Customer[n + 1];
    for(int i = 0; i < n; i++) {
      temp[i] = customers[i];
    }
    temp[n] = c;
    delete[]customers;
    customers = temp;
    n++;
    
    return *this;
  }

  FINKI_bookstore &operator=(const FINKI_bookstore &other) {
    if (this != &other) {
      delete [] this->customers;
      this->n=other.n;
      this->customers = new Customer[n];
      for (int i = 0; i < n; i++) {
        this->customers[i] = other.customers[i];
      }
    }
    return *this;
  }

  void update() {
    for(int i = 0; i < n; i++) {
      if(customers[i].gettype() == loyal && customers[i].getproizvodi() > 10) {
        customers[i].settype(vip);
      }
      if(customers[i].gettype() == standard && customers[i].getproizvodi() > 5) {
        customers[i].settype(loyal);
      }

    }
  }

  friend ostream& operator<< (ostream& out, FINKI_bookstore& f) {
    for(int i = 0; i < f.n; i++) {
      out<<f.customers[i];
    }
    return out;
  }

 void setCustomers(Customer* customers, int n) {
    this->n = n;
    this->customers = new Customer[n];
    for(int i = 0; i < n; i++) {
      this->customers[i] = customers[i];
    }
  }
};

int main(){
  int testCase;
  cin >> testCase;
  int MAX = 50;
  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);

    try {
      fc+=c;
    } catch (UserExistsException(&e)) {};
    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}