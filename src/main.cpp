#include "rpn.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <random>
#include <algorithm>

// Глобальный генератор случайных чисел
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);

// Вспомогательные функции
double power(double a, double b) { return std::pow(a, b); }
double modulo(double a, double b) { 
    if (b == 0) throw std::runtime_error("Division by zero");
    return std::fmod(a, b); 
}
double factorial(double n) {
    if (n < 0) throw std::runtime_error("Factorial of negative number");
    if (n == 0 || n == 1) return 1;
    double result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

// Обработка операторов
void handle_operator(const std::string& token, std::stack<double>& stack) {
    if (token == "+") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double b = stack.top(); stack.pop();
        double a = stack.top(); stack.pop();
        stack.push(a + b);
    }
    else if (token == "-") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double b = stack.top(); stack.pop();
        double a = stack.top(); stack.pop();
        stack.push(a - b);
    }
    else if (token == "*") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double b = stack.top(); stack.pop();
        double a = stack.top(); stack.pop();
        stack.push(a * b);
    }
    else if (token == "/") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double b = stack.top(); stack.pop();
        if (b == 0) throw std::runtime_error("Division by zero");
        double a = stack.top(); stack.pop();
        stack.push(a / b);
    }
    else if (token == "^") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double b = stack.top(); stack.pop();
        double a = stack.top(); stack.pop();
        stack.push(power(a, b));
    }
    else if (token == "%") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double b = stack.top(); stack.pop();
        double a = stack.top(); stack.pop();
        stack.push(modulo(a, b));
    }
    else if (token == "~") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(-a);
    }
    else if (token == "++") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(a + 1);
    }
    else if (token == "--") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(a - 1);
    }
    else if (token == "!") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(factorial(a));
    }
}

// Обработка математических функций
void handle_function(const std::string& token, std::stack<double>& stack) {
    if (token == "sqrt") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        if (a < 0) throw std::runtime_error("Square root of negative number");
        stack.push(std::sqrt(a));
    }
    else if (token == "abs") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(std::abs(a));
    }
    else if (token == "sin") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(std::sin(a));
    }
    else if (token == "cos") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(std::cos(a));
    }
    else if (token == "tan") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(std::tan(a));
    }
    else if (token == "asin") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        if (a < -1 || a > 1) throw std::runtime_error("asin argument out of range");
        stack.push(std::asin(a));
    }
    else if (token == "acos") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        if (a < -1 || a > 1) throw std::runtime_error("acos argument out of range");
        stack.push(std::acos(a));
    }
    else if (token == "atan") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(std::atan(a));
    }
    else if (token == "ln") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        if (a <= 0) throw std::runtime_error("ln of non-positive number");
        stack.push(std::log(a));
    }
    else if (token == "log") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        if (a <= 0) throw std::runtime_error("log of non-positive number");
        stack.push(std::log10(a));
    }
    else if (token == "floor") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(std::floor(a));
    }
    else if (token == "ceil") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(std::ceil(a));
    }
    else if (token == "round") {
        if (stack.empty()) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        stack.push(std::round(a));
    }
    else if (token == "rand") {
        stack.push(dis(gen));
    }
    else if (token == "min") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double b = stack.top(); stack.pop();
        double a = stack.top(); stack.pop();
        stack.push(std::min(a, b));
    }
    else if (token == "max") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double b = stack.top(); stack.pop();
        double a = stack.top(); stack.pop();
        stack.push(std::max(a, b));
    }
}

// Операции со стеком
void handle_stack_operation(const std::string& token, std::stack<double>& stack) {
    if (token == "dup") {
        if (stack.empty()) throw std::runtime_error("Stack is empty");
        stack.push(stack.top());
    }
    else if (token == "swap") {
        if (stack.size() < 2) throw std::runtime_error("Not enough operands");
        double a = stack.top(); stack.pop();
        double b = stack.top(); stack.pop();
        stack.push(a);
        stack.push(b);
    }
    else if (token == "drop") {
        if (stack.empty()) throw std::runtime_error("Stack is empty");
        stack.pop();
    }
    else if (token == "clear") {
        while (!stack.empty()) stack.pop();
    }
    else if (token == "stack") {
        std::stack<double> temp = stack;
        std::vector<double> elements;
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        std::cout << "Stack: ";
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

// Операции сравнения
void handle_comparison(const std::string& token, std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Not enough operands");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    
    if (token == "==") stack.push(a == b ? 1.0 : 0.0);
    else if (token == "!=") stack.push(a != b ? 1.0 : 0.0);
    else if (token == "<") stack.push(a < b ? 1.0 : 0.0);
    else if (token == ">") stack.push(a > b ? 1.0 : 0.0);
    else if (token == "<=") stack.push(a <= b ? 1.0 : 0.0);
    else if (token == ">=") stack.push(a >= b ? 1.0 : 0.0);
}

// Основная функция калькулятора (УЖЕ СУЩЕСТВУЕТ - НЕ МЕНЯТЬ)
double evaluate_rpn(const std::string& expression) {
    std::stack<double> stack;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        // Константы
        if (token == "pi") {
            stack.push(3.14159265358979323846);
        }
        else if (token == "e") {
            stack.push(2.71828182845904523536);
        }
        // Операторы
        else if (token == "+" || token == "-" || token == "*" || token == "/" ||
                 token == "^" || token == "%" || token == "~" || token == "++" ||
                 token == "--" || token == "!") {
            handle_operator(token, stack);
        }
        // Функции
        else if (token == "sqrt" || token == "abs" || token == "sin" || token == "cos" ||
                 token == "tan" || token == "asin" || token == "acos" || token == "atan" ||
                 token == "ln" || token == "log" || token == "floor" || token == "ceil" ||
                 token == "round" || token == "rand" || token == "min" || token == "max") {
            handle_function(token, stack);
        }
        // Операции со стеком
        else if (token == "dup" || token == "swap" || token == "drop" || 
                 token == "clear" || token == "stack") {
            handle_stack_operation(token, stack);
        }
        // Операции сравнения
        else if (token == "==" || token == "!=" || token == "<" || token == ">" ||
                 token == "<=" || token == ">=") {
            handle_comparison(token, stack);
        }
        // Числа
        else {
            try {
                double value = std::stod(token);
                stack.push(value);
            }
            catch (const std::exception&) {
                throw std::runtime_error("Invalid token: " + token);
            }
        }
    }
    
    if (stack.size() != 1 && !stack.empty()) {
        throw std::runtime_error("Invalid expression - multiple values left on stack");
    }
    if (stack.empty()) {
        throw std::runtime_error("Empty result");
    }
    
    return stack.top();
}
