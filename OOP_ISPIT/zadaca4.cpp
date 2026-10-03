//
// Created by aleks on 5/21/2025.
//
#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here
enum Size {
  small, large, family
};

class Pizza {
protected:
  char name[20];
  char ingredients[100];
  float pricee;
public:
  Pizza (char *name, char *ingredients, float pricee) {
    strcpy(this->name, name);
    strcpy(this->ingredients, ingredients);
    this->pricee = pricee;
  }

  virtual float price() = 0;
};

class FlatPizza : public Pizza {
  Size size;

public:
  FlatPizza(char *name, char *ingredients, float pricee) : Pizza(name, ingredients, pricee) {
    strcpy(this->name, name);
    strcpy(this->ingredients, ingredients);
    this->pricee = pricee;
    this->size = small;
  }
  FlatPizza(char *name, char *ingredients, float pricee, Size size) : Pizza(name, ingredients, pricee) {
    strcpy(this->name, name);
    strcpy(this->ingredients, ingredients);
    this->pricee = pricee;
    this->size = size;
  }

  float price() override {
    if (size == small) {
      return pricee*=1.1;
    } else if (size == large) {
      return pricee*=1.2;
    } else if (size == family) {
      return pricee*=1.3;
    }
  }
  friend ostream& operator<<(ostream& out, FlatPizza &p) {
    out<<p.name<<": "<<p.ingredients<<", ";
    if(p.size == small) {
    out<<"small";} else
      if (p.size == large) {
        out<<"large";
      } else
        if(p.size == family) {
          out<<"family";
        }out<<" - "<<p.price()<<endl;
    return out;
  }

};

class FoldedPizza : public Pizza {
  bool WhiteFlour;
public:FoldedPizza(char *name, char *ingredients, float pricee) : Pizza(name, ingredients, pricee) {
  strcpy(this->name, name);
  strcpy(this->ingredients, ingredients);
  this->pricee = pricee;
  this->WhiteFlour = true;
};

   FoldedPizza(char *name, char *ingredients, float pricee, bool flour) : Pizza(name, ingredients, pricee) {
      strcpy(this->name, name);
      strcpy(this->ingredients, ingredients);
      this->pricee = pricee;
      this->WhiteFlour = flour;
  };

  float price() override {
    if (WhiteFlour == true) {
      pricee*=1.1;
    } else pricee*=1.3;
  }

  friend ostream& operator<<(ostream& out, FoldedPizza& p) {
    out<<p.name<<": "<<p.ingredients<<", ";
    if(p.WhiteFlour == true) {
      out<<"wf";
    } else out<<"nwf";
    out<<" - "<<p.price()<<endl;
    return out;
  }

  void setWhiteFlour(bool s) {
    WhiteFlour = s;
  }


};

bool operator<(Pizza& a , Pizza &b) {
  return a.price() < b.price();
}

Pizza& expensivePizza(Pizza **pizzas, int n) {
  int maxid;
  for (int i = 0; i < n - 1; i++) {
    if (pizzas[i]->price() > pizzas[i + 1]->price()) {
      maxid = i;
    }
  }

  return *pizzas[maxid];
}


// Testing

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
