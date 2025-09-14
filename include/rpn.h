#pragma once
#include <stack>
#include <string>

/**
* @brief Evaluates a mathematical expression in Reverse Polish Notation (RPN).
*
* @param expression A string containing the RPN expression (e.g., "2 3 +").
* Tokens must be separated by spaces.
* @return double The result of the evaluated expression.
* @exception std::invalid_argument Thrown if the expression is invalid,
* contains an unknown operator, or attempts division by zero.
*/

double evaluate_rpn(const std::string& expression);

// Вспомогательные функции для новых операций
void handle_operator(const std::string& token, std::stack<double>& stack);
void handle_function(const std::string& token, std::stack<double>& stack);
void handle_stack_operation(const std::string& token, std::stack<double>& stack);
void handle_comparison(const std::string& token, std::stack<double>& stack);
