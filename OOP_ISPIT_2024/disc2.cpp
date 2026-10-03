#include <iostream>
#include <cstring>
using namespace std;

class InvalidSerialNumberFormatException {
private:
    string serialNumber;
public:
    InvalidSerialNumberFormatException(string serialNumber) {
        this->serialNumber = serialNumber;
    }

    void printMessage() const {
        cout << "The serial number " << serialNumber
             << " is invalid machine serial number format." << endl;
    }
};

class Machine {
protected:
    string model;
    int powerConsumption;
    float price;
    string serialNumber;

public:
    Machine(string model, int powerConsumption, string serialNumber) {
        if (serialNumber.length() != 12 || serialNumber.find(' ') != string::npos) {
            throw InvalidSerialNumberFormatException(serialNumber);
        }
        this->model = model;
        this->powerConsumption = powerConsumption;
        this->serialNumber = serialNumber;
    }

    virtual float calculateCost() = 0;
    virtual void showDetails() = 0;
    virtual ~Machine() = default;
};





class WashingMachine : public Machine {
private:
    int capacity;

public:
    WashingMachine(string model, int powerConsumption, string serialNumber, int capacity)
        : Machine(model, powerConsumption, serialNumber), capacity(capacity) {}

    float calculateCost() override {
        if (capacity > 8) {
            price = 500 * 1.12f;
        } else {
            price = 500;
        }
        price += (powerConsumption / 100.0f) * 20;
        return price;
    }

    void showDetails() override {
        cout << "Washing Machine " << model << " cost: " << calculateCost() << "$" << endl;
    }
};

class DryingMachine : public Machine {
private:
    bool sensor;

public:
    DryingMachine(string model, int powerConsumption, string serialNumber, bool sensor)
        : Machine(model, powerConsumption, serialNumber), sensor(sensor) {}

    float calculateCost() override {
        if (sensor) {
            price = 600 * 1.15f;
        } else {
            price = 600;
        }
        price += (powerConsumption / 100.0f) * 25;
        return price;
    }

    void showDetails() override {
        cout << "Drying Machine " << model << " cost: " << calculateCost() << "$" << endl;
    }
};

void calculatePercentageOfCost(Machine **machines, int n) {
    float totalCost = 0, washingCost = 0, dryingCost = 0;

    for (int i = 0; i < n; i++) {
        float cost = machines[i]->calculateCost();
        totalCost += cost;

        if (dynamic_cast<WashingMachine *>(machines[i]) != nullptr) {
            washingCost += cost;
        } else {
            dryingCost += cost;
        }
    }

    cout << "The total cost of washing machines is " << washingCost << "$, which is "
         << (washingCost / totalCost) * 100 << "% of the total cost of machines." << endl;

    cout << "The total cost of drying machines is " << dryingCost << "$, which is "
         << (dryingCost / totalCost) * 100 << "% of the total cost of machines." << endl;
}

Machine **createMachines(int &n) {
    Machine **machines = new Machine *[n];
    string model, serialNumber;
    int t, powerConsumption, value;

    for (int i = 0; i < n; i++) {
        cin >> t >> model >> powerConsumption >> serialNumber >> value;
        try {
            if (t == 1) {
                machines[i] = new WashingMachine(model, powerConsumption, serialNumber, value);
            } else {
                machines[i] = new DryingMachine(model, powerConsumption, serialNumber, value);
            }
        } catch (InvalidSerialNumberFormatException &e) {
            e.printMessage();
            n--;
            i--;
        }
    }
    return machines;
}

void cleanUp(Machine **machines, int n) {
    for (int i = 0; i < n; i++) {
        delete machines[i];
    }
    delete[] machines;
}

int main() {
    int testCase, n;
    cin >> testCase;

    switch (testCase) {
    case 1: {
        cout << "TESTING ABSTRACT CLASS AND CHILD CLASSES" << endl;
        cin >> n;
        Machine **machines = createMachines(n);
        for (int i = 0; i < n; i++) {
            machines[i]->showDetails();
        }
        cleanUp(machines, n);
        cout << "ABSTRACT CLASS AND CHILD CLASSES OK" << endl;
        break;
    }
    case 2: {
        cout << "TEST EXCEPTION HANDLING" << endl;
        cin >> n;
        Machine **machines = createMachines(n);
        for (int i = 0; i < n; i++) {
            machines[i]->showDetails();
        }
        cleanUp(machines, n);
        cout << "EXCEPTION HANDLING OK" << endl;
        break;
    }
    default: {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION" << endl;
        cin >> n;
        Machine **machines = createMachines(n);
        for (int i = 0; i < n; i++) {
            machines[i]->showDetails();
        }
        calculatePercentageOfCost(machines, n);
        cleanUp(machines, n);
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION OK" << endl;
        break;
    }
    }

    return 0;
}
