#include<iostream>

using namespace std;


class Flight {
private:
    string name;
    string source;
    string destination;
    int price;
public:
    Flight() {
        name = "";
        source = "";
        destination = "";
        price = 100;
    }


    Flight(string name, string source, string destination, int price) {
        this->name = name;
        this->source = source;
        this->destination = destination;
        this->price = price;
    }

    Flight(const Flight &o) {
        this->name = o.name;
        this->source = o.source;
        this->price = o.price;
        this->destination = o.destination;
    }

    int getPrice() {
        return price;
    }

    string getFrom() {
        return source;
    }

    string getTo() {
        return destination;
    }

    string getFlightName() {
        return name;
    }
};

class Airport {
private:
    string airportname;
    int flightcount;
    Flight *flights;
public:
    Airport() {
        airportname = "";
        flightcount = 0;
    }

    Airport(string airportname, int flightcount, Flight *flights) {
        this->airportname = airportname;
        this->flightcount = flightcount;
        this->flights = new Flight[flightcount];
        for (int i = 0; i < flightcount; i++) {
            this->flights[i] = flights[i];
        }
    }

    ~Airport() {
        delete[] flights;
    }

    Flight cheapestFlight() {
        Flight najevtin = flights[0];
        for(int i = 0; i < flightcount; i++) {
            if (najevtin.getPrice() > flights[i].getPrice()) {
                najevtin = flights[i];
            }
        }

        return najevtin;
    }
};

int main() {
    char airport_name[50];
    int n;
    Flight flights[100];
    cin >> airport_name >> n;
    for (int i = 0; i < n; i++) {
        char flight_name[100], from[50], to[50];
        int price;
        cin >> flight_name >> from >> to;
        cin >> price;
        Flight flight(flight_name, from, to, price);
        flights[i] = Flight(flight);
    }

    Airport airport(airport_name, n, flights);
    Flight cheapest = airport.cheapestFlight();
    cout << "The cheapest flight is: " << cheapest.getFlightName() << " from " <<
    cheapest.getFrom() << " to "
    << cheapest.getTo() << " and it costs " << cheapest.getPrice() << "$";
    return 0;
}