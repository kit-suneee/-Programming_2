// Реализовать класс Матрица. Перегрузить математические операции +,+=,-,-=, *,*=, 
// перегрузить операции >> и << для ввода/вывода матрицы. 

#include <iostream>

using namespace std;


class Matrix {
    friend std::ostream& operator << (std::ostream&, const Matrix &);
    friend std::istream& operator >> (std::istream&, Matrix &);

 
public:
    Matrix(int rows, int cols) { // Конструктор
        str = rows;
        col = cols;
        Matr = new double*[rows];
        for (int i = 0; i < rows; i++)
            Matr[i] = new double[cols];
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                Matr[i][j] = 0; // Заполняем нулями
        }
        
        
    ~Matrix() { // Деструктор
        for (int i = 0; i < str; i++)
            delete[] Matr[i];
        }
    
        
    Matrix operator+(const int &num) const { 
            Matrix result(str, col);
            for (int i = 0; i < str; i++)
                for (int j = 0; j < col; j++)
                    result.Matr[i][j] = Matr[i][j] + num;
            return result;
    }
    
    
    Matrix& operator+=(const int &num) {
            for (int i = 0; i < str; i++)
                for (int j = 0; j < col; j++)
                    Matr[i][j] = Matr[i][j] + num;
            return *this;
    }
    
    
    Matrix operator-(const int &num) const {
            Matrix result(str, col);
            for (int i = 0; i < str; i++)
                for (int j = 0; j < col; j++)
                    result.Matr[i][j] = Matr[i][j] - num;
            return result;
    }
    
    
    Matrix& operator-=(const int &num) {
            for (int i = 0; i < str; i++)
                for (int j = 0; j < col; j++)
                    Matr[i][j] = Matr[i][j] - num;
            return *this;
    }
    

    Matrix operator*(const int &num) const {
            Matrix result(str, col);
            for (int i = 0; i < str; i++)
                for (int j = 0; j < col; j++)
                    result.Matr[i][j] = Matr[i][j] * num;
            return result;
    }
    
    
    Matrix& operator/=(const int &num) {
            for (int i = 0; i < str; i++)
                for (int j = 0; j < col; j++)
                    Matr[i][j] = Matr[i][j] / num;
            return *this;
    }

    
private:
    double **Matr;
    int str; //строки матрицы
    int col; //столбцы матрицы
};


istream& operator >> (istream& cin, Matrix &matrix) {
        int row = matrix.str;
        int col = matrix.col;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                cin >> matrix.Matr[i][j];
        return cin;
}
    
    
std::ostream& operator << (ostream& cout, const Matrix &matrix) {
        int row = matrix.str;
        int col = matrix.col;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++)
                cout << matrix.Matr[i][j] << '\t';
            cout << std::endl;
        }
        return cout;
}
    


int main() {
    
    Matrix m(5, 4);
    cout << m << endl;
    
    auto m2 = m + 2;
    m2 += 5;
    m2 /= 7;
    cout << m2 << endl;
    
    return 0;
}