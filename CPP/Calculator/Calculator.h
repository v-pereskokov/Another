#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <cmath>

/*
 * \brief Перечесление приоритетов операторов
 */
enum Priority
{
    low, /*!< Низкий приоритет(для '+' и '-')*/
    medium, /*!< Средний приоритет(для '*' и '/')*/
    high, /*!< Высокий приоритет(для '^')*/
    error = -1 /*!< В случае иных операторов(или символов)*/
};

/*
 * \brief Класс для вычисления значения многочлена
 */
class Calculator
{
public:
    /*
     * Конструктор
     * \param target Входная строка
     */
    Calculator(const std::string &target);
    
    /*
     * Присваивает значение переменной класса новую строку и считает ее значение
     * \param target Входная строка
     */
    void setTarget(const std::string &target);
    
    /*
     * Возвращает значение многочлена
     */
    double result();
    
private:
    /*
     * Вычисление значения многочлена
     */
    void calculation();
    
    /*
     * Проверка символа(оператор ли)
     * \param operators Проверяемый символ
     */
    bool isOperator(char operators);
    
    /*
     * Возвращает приоритет оператора
     * \param operators Проверяемый оператор
     */
    Priority priority(char operators);
    
    /*
     * Выполнение арифметических действий в зависимости от оператора
     * \param operators Оператор
     */
    void action(char operators);
    
private:
    double _result; /*!< Результат вычислений*/
    std::string _target;/*!< Строка с многочленом*/
    std::stack<char> _operators; /*!< Стек операторов*/
    std::stack<double> _values; /*!< Стек чисел*/
};
