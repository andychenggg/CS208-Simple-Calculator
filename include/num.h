#include <iostream>
using namespace std;
class num{
public:
    int precision = 0;
    int type;//0 means an invalid number, 1 means an integer, 2 means a floating-point number;
    int sign = 1;
    string absolute_num_string;//不含符号位的数字
    explicit num(string & string1);
    static num Operate(num & num1, num & num2, char operator_char, bool & success);
    void PrintInfo() const;
    static num add(num &num1, num &num2);
    static num minus(num &num1, num &num2);
    static num multiply(num &num1, num &num2);
    static num mean_value(num &left, num &right);
    static num integral_mean_value(num &left, num &right);
    static num divide(num &num1, num &num2);
    static num module(num &num1, num &num2);
    static string round(string num_string, int precision);
    static string round_up(string num_string);
    static string round_down(string num_string);
    static string floor(string num_string);
    static string ceil(string num_string);
    static num exponent(num &num1, num &num2, bool & success);
    static string factorial(string biggest_integer);
    static num root(num number, int index);
    static num sin(num value, int index);
    static num cos(num value, int precision);
};

class MyOperator {
public:
    char operator_symbol;
    int left_operand_index;
    MyOperator(char operator_symbol, int left_operand_index);
};
