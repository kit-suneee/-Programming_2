// Реализовать класс Секундомер (Таймер). Объект класса должен хранить величины замеров времени. 
// Должен быть метод запуск таймера(используем библиотеку time.h), остановки таймера, 
// сохранения значения замера времени, сброс значений. Перегрузить << для вывода информации на экран. 

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;


class Timer {
    
    friend std::ostream& operator << (std::ostream&, const Timer &);

public:
    Timer() { // Конструктор
        counter = 0;
    }
    
    void setTime(int _counter) {
        counter = _counter;
    }
    
    void reset() {
        counter = 0;
    }
    
    void start() {
        if (counter == 0) {
            cout << "Для начала установите таймер" << endl;
            return;
        }
        begin_time = clock();
    }
    
    void stop() {
        if (counter == 0) {
            cout << "Для начала установите таймер" << endl;
            return;
        }
        auto time_delta = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
        counter = time_delta >= counter ? 0 : counter - time_delta;
        
        cout << "Прошло: " << time_delta << " секунд" << endl;
        cout << *this << endl;
    }
    
    
private:
    int counter;
    clock_t begin_time;
};


std::ostream& operator << (ostream& cout, const Timer &t) {
        cout << "Осталось: " << t.counter << " секунд";
        return cout;
}


int main() {
    
    Timer timer;
    timer.start();
    
    timer.setTime(20);
    timer.start();
    timer.stop();
    
    timer.start();
    timer.stop();
    // cout << timer << endl;
    
    return 0;
}
