//
// Created by aleks on 6/17/2025.
//
#include <iostream>
#include <cstring>

using namespace std;

//Your code here

class Museum {
protected:
    string name;
    string city;
    double ticket;
    int hours;
public:
    Museum(string name = " ", string city = " ", double ticket = 0, int hours = 0) {
        this->name = name;
        this->city = city;
        this->ticket = ticket;
        this-> hours = hours;
    }

    virtual void printDetail() = 0;
    virtual double calculateTicketCost() = 0;

    int getHours () {
        return hours;
    }
};

class ScientificMuseum : public  Museum {
    bool exhibits;
    int presentations;
public:
    ScientificMuseum(string name = " ", string city = " ", double ticket = 0, int hours = 0, bool exhibits = false, int presentations = 0) : Museum(name, city, ticket, hours) {
        this->exhibits = exhibits;
        this->presentations = presentations;
    }

    double calculateTicketCost() override {
        double ticketprice = ticket;
        if(exhibits) {
            ticketprice += ticket * 0.12;
        }

        ticketprice += presentations * 6;

        return ticketprice;
    }

    void printDetail() override {
        cout<<name<<" - (Scientific) "<<city<<" "<<presentations<<" "<<calculateTicketCost()<<endl;
    }
};

class ArtMuseum : public Museum {
    bool exhibitions;
    int artworks;
public:
    ArtMuseum(string name = " ", string city = " ", double ticket = 0, int hours = 0, bool exhibitions = false, int artworks = 0) : Museum(name, city, ticket, hours) {
        this->exhibitions = exhibitions;
        this->artworks = artworks;
    }

    double calculateTicketCost() override {
        double ticketprice = ticket;
        if (exhibitions) {
            ticketprice -= ticket * 0.18;
        }

        ticketprice += artworks * 3;

        return ticketprice;
    }

    void printDetail() override {
        cout<<name<<" - (Art) "<<city<<" "<<exhibitions<<" "<<calculateTicketCost()<<endl;
    }

};

int findCheapestScientificMuseum(Museum **m, int n) {
    int index = -1;
    double min = 999;
    for(int i = 0; i < n; i++) {
        if(dynamic_cast<ScientificMuseum*>(m[i]) && m[i]->calculateTicketCost() <= min) {
            if(m[i]->calculateTicketCost() == min) {
                if(m[i]->getHours() >= m[index]->getHours()) {
                    index = i;
                    min = m[i]->getHours();
                }
            } else {
                index = i;
                min = m[i]->calculateTicketCost();
            }
        }


    }

    return index;
}


int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Museum** m = new Museum*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if(cheapest_sci_museum_index>=0){
            m[cheapest_sci_museum_index]->printDetail();
        }else{
            cout << "Scientific Museum not found in the array!"<<endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}