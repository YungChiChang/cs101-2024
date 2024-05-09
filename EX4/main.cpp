#include <iostream>
#include <string>
using namespace std;
class Engine {};
class Fueltank {
private:
    int m_FueltankCapacity;
    int m_Gas_grade;
public:
    Fueltank(int FueltankCapacity = 3000, int Gas = 98) {
        m_FueltankCapacity = FueltankCapacity;
        m_Gas_grade = Gas;
    }
    int fuel_up(int v, int gas) {
        if (v > m_FueltankCapacity) {
            cout << "Error: FueltankCapacity: " << m_FueltankCapacity << " but fuel up: " << v << endl;
            return -1;
             cout << "fuel up:" << v << " Gas_grade: " << gas << endl;
        }
        m_FueltankCapacity -= v;
        cout << "fuel up:" << v << " Gas_grade: " << gas << endl;
        return v;
    }
    int set_Gas_grade(int Gas_grade) {
        if (Gas_grade != 98 && Gas_grade != 95) {
            cout << "Error: Gas_grade: " << Gas_grade << " Correct Gas_grade: " << m_Gas_grade << endl;
            return -1;
        }
        m_Gas_grade = Gas_grade;
        cout << "Set Gas_grade = " << Gas_grade << endl;
        return Gas_grade;
    }
    int get_Gas_grade() {
        return m_Gas_grade;
    }
    int get_FueltankCapacity() {
        return m_FueltankCapacity;
    }
};
class Car {
private:
    Engine m_Engine;
    Fueltank m_Fueltank;
    int m_MaxSeating;
    int m_price;
    int m_base;
    string m_brand;
    string m_model;
    int m_year;
    void m_UpdatePrice(int base = 500000) {
        m_base = base;
    }
public:
    Car(string x, string y, int z, int s) {
        m_brand = x;
        m_model = y;
        m_year = z;
        m_MaxSeating = s;
        cout << "Constructing " << m_brand << "_Car" << endl;
    }
    string get_brand() {
        return m_brand;
    }
    int get_Gas_grade() {
        return m_Fueltank.get_Gas_grade();
    }
    int set_Gas_grade(int gas = 98) {
        return m_Fueltank.set_Gas_grade(gas);
    }
    int fuel_up(int v, int gas = 98) {
    if (v > m_Fueltank.get_FueltankCapacity()) {
        cout << "Error: FueltankCapacity: " << m_Fueltank.get_FueltankCapacity() << " but fuel up: " << v << endl;
        if (gas != m_Fueltank.get_Gas_grade()) {
        cout << "Error: Gas_grade: " << gas << " Correct Gas_grade: " << m_Fueltank.get_Gas_grade() << endl;
        return -1;
        }
        else{
        cout << "fuel up:" << v << " Gas_grade: " << gas << endl;
        return -1;
        }
    }
    if (gas != m_Fueltank.get_Gas_grade()) {
        cout << "Error: Gas_grade: " << gas << " Correct Gas_grade: " << m_Fueltank.get_Gas_grade() << endl;
        return -1;
    }
    int result = m_Fueltank.fuel_up(v, gas);
    if (result != -1) {
        return result;
    }
    return result;
}
};
int main() {
    Car car_2("Audi", "A1", 2021, 2);
    cout << car_2.get_brand() << " : Gas_grade = " << car_2.get_Gas_grade() << endl;
    car_2.set_Gas_grade(95);
    cout << car_2.get_brand() << " : Gas_grade = " << car_2.get_Gas_grade() << endl;
    car_2.fuel_up(300, 95);
    return 0;
}
