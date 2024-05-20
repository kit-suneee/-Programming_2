// Разработать класс Точка (в декартовой системе координат). Данные – координаты х,у. 
// Перегрузить операции ==,!=, >>, << для ввода/вывода точки. 
// Реализовать метод для проверки, в какой координатной четверти лежит точка, реализовать 
// метод для проверки лежит ли точка на линии, заданной уравнением, выше или ниже нее.


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>

using namespace std;


struct Expression {
    Expression(std::string token) : token(token) {}
	Expression(std::string token, Expression a) : token(token), args{ a } {}
	Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {}

	std::string token;
	std::vector<Expression> args;
};

class Parser {
public:
	explicit Parser(const char* input) : input(input) {}
	Expression parse();
private:
	std::string parse_token();
	Expression parse_simple_expression();
	Expression parse_binary_expression(int min_priority);

	const char* input;
};

std::string Parser::parse_token() {
	while (std::isspace(*input)) ++input;

	if (std::isdigit(*input)) {
		std::string number;
		while (std::isdigit(*input) || *input == '.') number.push_back(*input++);
		return number;
	}

	static const std::string tokens[] =
	{ "+", "-", "**", "*", "/", "mod", "abs", "sin", "cos", "(", ")" };
	for (auto& t : tokens) {
		if (std::strncmp(input, t.c_str(), t.size()) == 0) {
			input += t.size();
			return t;
		}
	}

	return "";
}

Expression Parser::parse_simple_expression() {
	auto token = parse_token();
	if (token.empty()) throw std::runtime_error("Invalid input");

	if (token == "(") {
		auto result = parse();
		if (parse_token() != ")") throw std::runtime_error("Expected ')'");
		return result;
	}

	if (std::isdigit(token[0]))
		return Expression(token);

	return Expression(token, parse_simple_expression());
}

int get_priority(const std::string& binary_op) {
	if (binary_op == "+") return 1;
	if (binary_op == "-") return 1;
	if (binary_op == "*") return 2;
	if (binary_op == "/") return 2;
	if (binary_op == "mod") return 2;
	if (binary_op == "**") return 3;
	return 0;
}

Expression Parser::parse_binary_expression(int min_priority) {
	auto left_expr = parse_simple_expression();

	for (;;) {
		auto op = parse_token();
		auto priority = get_priority(op);
		if (priority <= min_priority) {
			input -= op.size();
			return left_expr;
		}

		auto right_expr = parse_binary_expression(priority);
		left_expr = Expression(op, left_expr, right_expr);
	}
}

Expression Parser::parse() {
	return parse_binary_expression(0);
}

double eval(const Expression& e) {
	switch (e.args.size()) {
	case 2: {
		auto a = eval(e.args[0]);
		auto b = eval(e.args[1]);
		if (e.token == "+") return a + b;
		if (e.token == "-") return a - b;
		if (e.token == "*") return a * b;
		if (e.token == "/") return a / b;
		if (e.token == "**") return pow(a, b);
		if (e.token == "mod") return (int)a % (int)b;
		throw std::runtime_error("Unknown binary operator");
	}

	case 1: {
		auto a = eval(e.args[0]);
		if (e.token == "+") return +a;
		if (e.token == "-") return -a;
		if (e.token == "abs") return abs(a);
		if (e.token == "sin") return sin(a);
		if (e.token == "cos") return cos(a);
		throw std::runtime_error("Unknown unary operator");
	}

	case 0:
		return strtod(e.token.c_str(), nullptr);
	}

	throw std::runtime_error("Unknown expression type");
}


class Point {
    friend std::ostream& operator << (std::ostream&, const Point &);
    friend std::istream& operator >> (std::istream&, Point &);

 
public:
    Point(int _x, int _y) { // Конструктор
        x = _x;
        y = _y;
    }
    
    
    int get_quarter() {
        if ((x >= 0) and (y >= 0)) { return 1; }
        if ((x >= 0) and (y < 0)) { return 2; }
        if (y < 0) { return 3; }
        return 4;
    }
    
    
    int is_on_line(string text) {
        
        string old_str{"x"};  // какую подстроку заменить
        string new_str = to_string(x);  // на какую строку заменить
        size_t start {text.find(old_str)};           
        while (start != string::npos) // находим и заменяем все вхождения строки old_str
        {
            text.replace(start, old_str.length(), new_str); // Замена old_str на new_str
            start = text.find(old_str, start + new_str.length());
        } // Заменили х на значение
        
        Parser parser(text.c_str()); // Распарсим уравнение
        double new_y = eval(parser.parse()); // Посчитаем у для уравнения
        return y == new_y ? 0 : y < new_y ? -1 : 1;
    }
    
    
    bool operator==(const Point &p) const {
        if ((p.x == x) and p.y == y) return true;
        return false;
    } 
    
    
    bool operator!=(const Point &p) const {
        return !(*this == p);
    } 
    
    
private:
    int x;
    int y;
};


istream& operator >> (istream& cin, Point &point) {
        cin >> point.x;
        cin >> point.y;
        return cin;
}
    
    
std::ostream& operator << (ostream& cout, const Point &point) {
        cout << "(" << point.x << ", " << point.y << ")";
        return cout;
}
    


int main() {
    
    Point p(1, 3);
    cout << p << endl;
    cout << p.get_quarter() << endl;
    
    cout << p.is_on_line("3 + x") << endl; // -1, если точка ниже графика
    cout << p.is_on_line("3 * x") << endl; // 0, если лежит на линии
    cout << p.is_on_line("0 - x") << endl; // 1, если выше графика

    return 0;
}
