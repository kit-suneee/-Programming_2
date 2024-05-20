// Реализовать иерархию классов «Застройщик» 


#include <iostream>

using namespace std;


class Builder {
  public:
    virtual void wakeUp() = 0;
    virtual void breakfast() = 0;
    virtual void rest() = 0;
    
    void eval() {
        wakeUp();
        breakfast();
        rest();
    }
    
    string getStatus() {
        return pet_status;
    }
    
  protected:
    string pet_status;
};
 
class CatBuilder: public Builder
{
  public:
    CatBuilder() {
        pet_status = "Котик спит";
    }
    
    void wakeUp() {
        cout << "Котик проснулся" << endl;
        pet_status = "Проснувшийся котик";
    }
    
    void breakfast() {
        cout << "Котик кушает" << endl;
        pet_status = "Сытый котик";
    }
    
    void rest() {
        cout << "Котик грызёт цветы" << endl;
        pet_status = "Счастливый котик";
    }
};


class BunnyBuilder: public Builder
{
  public:
    BunnyBuilder() {
        pet_status = "Кролик спит";
    }
    
    void wakeUp() {
        cout << "Кролик проснулся" << endl;
        pet_status = "Проснувшийся кролик";
    }
    
    void breakfast() {
        cout << "Кролик кушает морковку" << endl;
        pet_status = "Сытый Кролик";
    }
    
    void rest() {
        cout << "Кролик переворачивает домик" << endl;
        pet_status = "Счастливый кролик";
    }
};


int main() {
    
    CatBuilder object;
    object.eval();
    cout << "Результат: " << object.getStatus() << endl;
    
    return 0;
}
