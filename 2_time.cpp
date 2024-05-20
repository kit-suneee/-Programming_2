// Реализовать класс Время. Объекты класса должны хранить значение времени (часы, минуты, секунды). 
// Перегрузить операции сравнения (>,<,!=,==), арифметические операции (в частности +,+=,-,-=) 
// и операции >>, << (для ввода/вывода). 
//Также должен быть реализован метод перевода времени из 24-х часового формата в 12-часовой.  


#include <iostream>

using namespace std;


class Time {
    friend std::ostream& operator << (std::ostream&, const Time &);
    friend std::istream& operator >> (std::istream&, Time &);

 
public:
    Time(int h, int m, int s, string p = "") { // Конструктор
        hours = h;
        minutes = m;
        seconds = s;
        part = p;
    }
    
    
    void to_12() {
        part = "AM";
        if (hours > 12) {
            part = "PM";
        }
        Time new_time(hours % 12, minutes, seconds, part);
        cout << new_time << endl;
    }
    

    bool operator<(const Time &t) const {
        if (hours < t.hours) {
            return true;
        }
        if (minutes < t.minutes) {
            return true;
        }
        if (seconds < t.seconds) {
            return true;
        }
        return false;
    } 
    
    
    bool operator==(const Time &t) const {
        if (!(*this < t) and !(t < *this)) {
            return true;
        }
        return false;
    } 
    
    
    bool operator!=(const Time &t) const {
        return !(*this == t);
    } 
    
    
    bool operator>(const Time &t) const {
        if ((*this != t) and !(t < *this)) {
            return true;
        }
        return false;
    } 
    
        
    Time operator+(const int &sec) const { 
        int delta_seconds = sec % 60;
        int delta_minutes = (sec/60) % 60;
        int delta_hours = sec/60/60;
        
        Time new_time(hours, minutes, seconds);
        new_time.hours += delta_hours;
        new_time.minutes += delta_minutes;
        new_time.seconds += delta_seconds;
        new_time.fix_time();
        
        return new_time;
    }
    
    
    Time& operator+=(const int &sec) {
        int delta_seconds = sec % 60;
        int delta_minutes = (sec/60) % 60;
        int delta_hours = sec/60/60;
        
        hours += delta_hours;
        minutes += delta_minutes;
        seconds += delta_seconds;
        this->fix_time();

        return *this;
    }
    
    
    Time operator-(const int &sec) const { 
        int delta_seconds = sec % 60;
        int delta_minutes = (sec/60) % 60;
        int delta_hours = sec/60/60;
        
        Time new_time(hours, minutes, seconds);
        new_time.hours -= delta_hours;
        new_time.minutes -= delta_minutes;
        new_time.seconds -= delta_seconds;
        new_time.fix_time();
        
        return new_time;
    }
    
    
    Time& operator-=(const int &sec) {
        int delta_seconds = sec % 60;
        int delta_minutes = (sec/60) % 60;
        int delta_hours = sec/60/60;
        
        hours -= delta_hours;
        minutes -= delta_minutes;
        seconds -= delta_seconds;
        this->fix_time();

        return *this;
    }
    
    
private:
    int hours;
    int minutes;
    int seconds;
    
    string part = "";
    
    void fix_time() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            hours %= 24;
        }
        
        if (seconds < 0) {
            seconds *= -1;
            minutes -= seconds/60;
            seconds %= 60;
        }
        if (minutes < 0) {
            minutes *= -1;
            hours -= minutes / 60;
            minutes %= 60;
        }
        if (hours < 0) {
            hours *= -1;
            hours %= 24;
        }
    }
};


istream& operator >> (istream& cin, Time &time) {
        cin >> time.hours;
        cin >> time.minutes;
        cin >> time.seconds;
        return cin;
}
    
    
std::ostream& operator << (ostream& cout, const Time &time) {
        if (time.hours < 10) {
            cout << '0';
        }
        cout << time.hours << ':';
        if (time.minutes < 10) {
            cout << '0';
        }
        cout << time.minutes << ":";
        if (time.seconds < 10) {
            cout << '0';
        }
        cout << time.seconds << " " << time.part;
        return cout;
}
    


int main() {
    
    Time t1(14, 20, 50);
    Time t2(14, 20, 50);
    cout << (t1 > t2) << endl;
    
    Time t_new = t1 + (19 * 60 * 60 + 55 * 60 + 15);
    cout << t_new << endl;
    
    t_new -= 1 * 60 * 60 + 1 * 60 + 5;
    cout << t_new << endl;
    
    t1.to_12();

    return 0;
}
