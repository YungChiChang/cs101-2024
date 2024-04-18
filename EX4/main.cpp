#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string m_brand;
    string m_model;
    int m_year;
    
    Car(string x, string y, int z, int s) {
        m_brand = x;
        m_model = y;
        m_year = z;
    }
};

class BMW_Car : public Car {
private:
    string m_DriveMode = "Rear-wheel";

public:
    BMW_Car(string y, int z, int s) : Car("BMW", y, z, s) {
        cout << "Constructing BMW_Car" << endl;
    }

    string get_DriveMode() {
        return m_DriveMode;
    }
};

class AUDI_Car : public Car {
private:
    string m_DriveMode = "Front-wheel";

public:
    AUDI_Car(string y, int z, int s) : Car("Audi", y, z, s) {
        cout << "Constructing AUDI_Car" << endl;
    }

    string get_DriveMode() {
        return m_DriveMode;
    }
};

class BENZ_Car : public Car {
private:
    string m_DriveMode = "Front-wheel";

public:
    BENZ_Car(string y, int z, int s) : Car("Benz", y, z, s) {
        cout << "Constructing BENZ_Car" << endl;
    }

    string get_DriveMode() {
        return m_DriveMode;
    }
};

int main() {
    BMW_Car car_1("X5", 2023, 6);
    cout << car_1.m_brand << " : Drive Mode = " << car_1.get_DriveMode() << endl;

    AUDI_Car car_2("A1", 2023, 5);
    cout << car_2.m_brand << " : Drive Mode = " << car_2.get_DriveMode() << endl;
    
    BENZ_Car car_3("A1", 2023, 5);
    cout << car_3.m_brand << " : Drive Mode = " << car_3.get_DriveMode() << endl;

    return 0;
}
