// Реализовать класс Вклад. Данные - процентная ставка, срок, возможность пополнения/снятия денег. 
// Методы – пополнение/снятие денег (операции +,-), расчет дохода. Вывод реквизитов на экран (перегрузка операции <<)   

#include <iostream>
#include <cmath>

using namespace std;


class Deposit {
    
    friend std::ostream& operator << (std::ostream&, const Deposit &);
    friend std::istream& operator >> (std::istream&, Deposit &);

public:
    Deposit(int start_value, double _rate, int _period, bool _add_flag = true) { // Конструктор
        value = start_value;
        rate = _rate;
        period_months = _period;
        add_flag = _add_flag;
    }
    
    double count_income() {
        return pow(value * (1 + rate / 100), period_months);
    }

    
    Deposit operator+(const int &add_value) const { 
        if (!add_flag) {
            cout << "Вклад нельзя пополнить!" << endl;
            return *this;
        }
        Deposit res(value + add_value, rate, period_months);
        return res;
    }
    Deposit operator-(const int &add_value) const { 
        if (!add_flag) {
            cout << "Нельзя снять средства с вклада!" << endl;
            return *this;
        }
        Deposit res(value - add_value, rate, period_months);
        return res;
    }

    
private:
    int value;
    double rate;
    int period_months;
    bool add_flag;
};


std::ostream& operator << (ostream& cout, const Deposit &d) {
    cout << "Сумма: " << d.value << endl;
    cout << "Ставка: " << d.rate << endl;
    cout << "Расчетный период: " << d.period_months << endl;
    return cout;
}



int main() {
    
    Deposit d(1000, 15, 12, false);
    cout << d << endl;
    
    d = d + 1000;
    return 0;
}
