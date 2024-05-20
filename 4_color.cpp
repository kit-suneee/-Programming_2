// Реализовать класс Цвет (модель RGB). Данные – значение красного, зеленого и синего каналов. 
// Методы: проверка значения на корректность, перегрузка операций сравнения ==, !=, операций >>, << для ввода/вывода цвета. 

#include <iostream>

using namespace std;



class ColorRGB {
    friend std::ostream& operator << (std::ostream&, const ColorRGB &);
    friend std::istream& operator >> (std::istream&, ColorRGB &);

 
public:
    ColorRGB(int _r, int _g, int _b) { // Конструктор
        if (!setColor(_r, _g, _b)) {
            r = 0;
            g = 0;
            b = 0;
            cout << "Setted default values: (0, 0, 0)" << endl;
        }
    }
    
    
    bool operator==(const ColorRGB &c) const {
        if ((c.r == r) and (c.g == g) and (c.b == b)) return true;
        return false;
    } 
    
    
    bool operator!=(const ColorRGB &c) const {
        return !(*this == c);
    } 
    
    
private:
    int r;
    int g;
    int b;
    
    bool check_num(int color) {
        return (color >= 0) and (color <= 256);
    }
    
    bool setColor(int _r, int _g, int _b) {
        if (check_num(_r) and (check_num(_g)) and check_num(_b)) {
            r = _r;
            g = _g;
            b = _b;
            return true;
        }
        cout << "Color value should be in [1, 255]" << endl;
        return false;
        
    }
};


istream& operator >> (istream& cin, ColorRGB &color) {
        cin >> color.r;
        cin >> color.g;
        cin >> color.b;
        return cin;
}
    
    
std::ostream& operator << (ostream& cout, const ColorRGB &color) {
        cout << "(" << color.r << ", " << color.g << ", " << color.b << ")";
        return cout;
}
    


int main() {
    
    ColorRGB c(1000, 10, 10);
    cout << c << endl;
    cin >> c;
    cout << c << endl;

    return 0;
}