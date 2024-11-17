#include <vector>
#include "num.h"

//这个文件定义的方法用来进行数之间的运算

num::num(string &initialization_string) {
    if (initialization_string.empty()) {
        type = 0;
        return;
    }
    string copied_string = initialization_string;
    //先去除前面多余的0
    int index = 0;
    while (index < copied_string.size() - 1) {
        if (copied_string[index] == '0' && copied_string[index + 1] != '.') {
            index++;
        } else {
            break;
        }
    }
    copied_string = copied_string.substr(index);
    absolute_num_string = copied_string;
    //先判断是不是常量；
    if (copied_string == "PI" || copied_string == "+PI" || copied_string == "-PI") {
        type = 2;
        absolute_num_string = "3.1415926535";
        precision = 10;
        sign = (copied_string[0] == 'P' || copied_string[0] == '+') ? 1 : -1;
        return;
    }
//    if (copied_string == "e" || copied_string == "+e" || copied_string == "-e") {
//        type = 2;
//        absolute_num_string = "2.718281828";
//        precision = 9;
//        sign = (copied_string[0] == 'e' || copied_string[0] == '+') ? 1 : -1;
//        return;
//    }
    //检查这串字符串的合法性
    for (int i = 0; i < copied_string.size(); i++) {
        if (copied_string[i] - '0' >= 0 && copied_string[i] - '0' <= 9)
            continue;
        else if (i == 0 && copied_string.size() != 1 && copied_string[i] == '+') {
            sign = 1;
            absolute_num_string = copied_string.substr(1);//取不带符号的部分存起来
            copied_string = copied_string.substr(1);
            continue;
        } else if (i == 0 && copied_string.size() != 1 && copied_string[i] == '-') {
            sign = -1;
            absolute_num_string = copied_string.substr(1);//取不带符号的部分存起来
            copied_string = copied_string.substr(1);
            continue;
        } else {
            goto check_double;
        } //this is impossible to be a longlong;
    }
    type = 1;
    return;
    check_double:
    precision = 0;
    //check whether a double;
    int precision_begin = 0, precision_end = (int) copied_string.size() - 1;
    for (int i = 0; i < copied_string.size(); i++) {
        //if there is a sign, then it should be at the beginning, and it should have the following digits;
        if (i == 0 && copied_string.size() != 1 && copied_string[i] == '+') {
            sign = 1;
            absolute_num_string = copied_string.substr(1);
            copied_string = copied_string.substr(1);
            continue;
        } else if (i == 0 && copied_string.size() != 1 && copied_string[i] == '-') {
            sign = -1;
            absolute_num_string = copied_string.substr(1);
            copied_string = copied_string.substr(1);
            continue;
        } else if (copied_string[i] - '0' >= 0 && copied_string[i] - '0' <= 9)
            continue;
        else if (copied_string[i] == '.') {
            //verify whether there are digits before it and after it;
            if (i == 0 || i == copied_string.size() - 1 ||
                copied_string[i - 1] - '0' < 0 ||
                copied_string[i - 1] - '9' > 0 ||
                copied_string[i + 1] == 'e' ||
                copied_string[i + 1] == 'E') {
                type = 0;
                return;
            }
            precision_begin = i + 1;
        } else if (copied_string[i] == 'e' || copied_string[i] == 'E') {
            if (precision_begin != 0) {
                precision_end = i - 1;
            }
            //judge there is an integer after 'e' of 'E';
            for (int j = i + 1; j < copied_string.size(); j++) {
                if (j == i + 1 && j != copied_string.size() &&
                    (copied_string[j] == '+' || copied_string[j] == '-'))
                    continue;
                else if (copied_string[j] - '0' < 0 || copied_string[j] - '9' > 0) {
                    type = 0;
                    return;
                }
            }
            //如果有小数点
            if (precision_begin != 0) {
                precision = precision_end - precision_begin + 1;
                //将含e的字符串转成只有小数点的字符串；
                int exponent = atoi(copied_string.substr(i + 1).c_str());
                if (exponent >= 0) {
                    absolute_num_string = copied_string.substr(0, precision_begin - 1);
                    for (int j = 0; j < exponent; j++) {
                        if (j < precision) {
                            absolute_num_string += copied_string[j + precision_begin];
                        } else {
                            absolute_num_string += "0";
                        }
                    }
                    absolute_num_string += ".";
                    if (exponent < precision) {
                        for (int j = exponent; j < precision; j++) {
                            absolute_num_string += copied_string[j + precision_begin];
                        }
                        for (int j = 0; j < exponent; j++) {
                            absolute_num_string += "0";
                        }
                    } else {
                        for (int j = 0; j < precision; j++) {
                            absolute_num_string += "0";
                        }
                    }
                } else {
                    if (precision_begin - 1 > abs(exponent)) {
                        absolute_num_string = copied_string.substr(0, precision_begin - 1 - abs(exponent)) + "." +
                                              copied_string.substr(precision_begin - 1 - abs(exponent), abs(exponent)) +
                                              copied_string.substr(precision_begin,
                                                                   precision_end - precision_begin + 1);
                        precision += abs(exponent);
                    } else {
                        int zero_numbers = abs(exponent) - precision_begin + 2;
                        absolute_num_string = "0.";
                        for (int j = 0; j < zero_numbers - 1; j++) {
                            absolute_num_string += "0";
                        }
                        absolute_num_string += copied_string.substr(0, precision_begin - 1) +
                                               copied_string.substr(precision_begin,
                                                                    precision_end - precision_begin + 1);
                        precision += abs(exponent);
                    }
                }
            } else {
                int exponent = atoi(copied_string.substr(i + 1).c_str());
                if (exponent >= 0) {
                    precision = 0;
                    absolute_num_string = copied_string.substr(0, i);
                    for (int j = 0; j < exponent; j++) {
                        absolute_num_string += "0";

                    }
                } else {
                    if (abs(exponent) < i) {
                        absolute_num_string = copied_string.substr(0, i - abs(exponent)) + "." +
                                              copied_string.substr(i - abs(exponent), abs(exponent));
                    } else {
                        absolute_num_string = "0.";
                        for (int j = 0; j < abs(exponent) - i; j++) {
                            absolute_num_string += "0";
                        }
                        absolute_num_string += copied_string.substr(0, i);
                    }
                    precision = abs(exponent);
                }
            }
            type = 2;
            return;
        }
            //打印
        else {
            cout << "wrong number:" << copied_string << endl;
            type = 0;
            return;
        }
    }
    //if it passes the judgement for a double, then type is 2;
    if (precision_begin != 0) {
        precision = precision_end - precision_begin + 1;
    }
    type = 2;
}

num num::Operate(num &num1, num &num2, char operator_char, bool &success) {
    switch (operator_char) {
        case '+': {
            return num::add(num1, num2);
        }
        case '-': {
            return num::minus(num1, num2);
        }
        case '*': {
            return num::multiply(num1, num2);
        }
        case '/': {
            return num::divide(num1, num2);
        }
        case '%': {
            return num::module(num1, num2);
        }
        default: {
            return num::exponent(num1, num2, success);
        }
    }
}


void num::PrintInfo() const {
    cout << absolute_num_string << " " << precision << " " << sign << " " << type << " " << endl;
}

num num::add(num &num1, num &num2) {
    if (num1.sign != num2.sign) {
        num new_num(num2.absolute_num_string);
        new_num.sign = num2.sign * (-1);
        return num::minus(num1, new_num);
    } else { //符号相同
        string result_string, copied_num1 = num1.absolute_num_string, copied_num2 = num2.absolute_num_string;
        if (num1.type == 1 && num2.type == 1) {
            while (copied_num1.size() > copied_num2.size()) {
                copied_num2 = "0" + copied_num2;
            }
            while (copied_num2.size() > copied_num1.size()) {
                copied_num1 = "0" + copied_num1;
            }
            vector<int> result_vector(copied_num1.size() + 1, 0);
            for (int i = (int) copied_num1.size(); i > 0; i--) {
                result_vector[i] += copied_num1[i - 1] + copied_num2[i - 1] - '0' - '0';
                result_vector[i - 1] += result_vector[i] / 10;
                result_vector[i] %= 10;
                result_string = to_string(result_vector[i]) + result_string;
            }
            result_string = (num1.sign == 1 ? "" : "-") + (result_vector[0] == 0 ? "" : to_string(result_vector[0])) +
                            result_string;
        } else if (num1.type == 1 && num2.type == 2) {
            num1.precision = 1;
            num1.absolute_num_string += ".0";
            num1.type = 2;
            copied_num1 = num1.absolute_num_string;
            goto add_floating_point_numbers;
        } else if (num2.type == 1 && num1.type == 2) {
            num2.precision = 1;
            num2.absolute_num_string += ".0";
            num2.type = 2;
            copied_num2 = num2.absolute_num_string;
            goto add_floating_point_numbers;
        }
            //处理浮点数相加
        else if (num1.type == 2 && num2.type == 2) {
            add_floating_point_numbers:
            //将小数点对齐；
            //先在后面补零
            if (num1.precision < num2.precision) {
                for (int i = 0; i < num2.precision - num1.precision; i++) {
                    copied_num1 += "0";
                }
            } else {
                for (int i = 0; i < num1.precision - num2.precision; i++) {
                    copied_num2 += "0";
                }
            }
            //在前面补零：
            while (copied_num1.size() > copied_num2.size()) {
                copied_num2 = "0" + copied_num2;
            }
            while (copied_num2.size() > copied_num1.size()) {
                copied_num1 = "0" + copied_num1;
            }
            //计算
            vector<int> result_vector(copied_num1.size() + 1, 0);
            for (int i = (int) copied_num1.size(); i > 0; i--) {
                if (copied_num1[i - 1] == '.') {
                    result_vector[i] = '.';
                    result_string = '.' + result_string;
                } else if (copied_num1[i - 2] == '.') //进位要进到小数点前面去；
                {
                    result_vector[i] += copied_num1[i - 1] + copied_num2[i - 1] - '0' - '0';
                    result_vector[i - 2] += result_vector[i] / 10;
                    result_vector[i] %= 10;
                    result_string = to_string(result_vector[i]) + result_string;
                } else {
                    result_vector[i] += copied_num1[i - 1] + copied_num2[i - 1] - '0' - '0';
                    result_vector[i - 1] += result_vector[i] / 10;
                    result_vector[i] %= 10;
                    result_string = to_string(result_vector[i]) + result_string;
                }
            }
            result_string = (num1.sign == 1 ? "" : "-") + (result_vector[0] == 0 ? "" : to_string(result_vector[0])) +
                            result_string;
        }
        num result(result_string);
        return result;
    }
}

num num::minus(num &num1, num &num2) {
    if (num1.sign != num2.sign) {//符号不同
        num new_num(num2.absolute_num_string);
        new_num.sign = num2.sign * (-1);
        return num::add(num1, new_num);
    } else { //符号相同
        string result_string, copied_num1 = num1.absolute_num_string, copied_num2 = num2.absolute_num_string;
        if (num1.type == 1 && num2.type == 1) {
            while (copied_num1.size() > copied_num2.size()) {
                copied_num2 = "0" + copied_num2;
            }
            while (copied_num2.size() > copied_num1.size()) {
                copied_num1 = "0" + copied_num1;
            }
            //整数的减法
            vector<int> result_vector(copied_num1.size() + 1, 0);
            for (int i = copied_num1.size(); i > 0; i--) {
                result_vector[i] += copied_num1[i - 1] - copied_num2[i - 1];
                if (result_vector[i] < 0) {
                    result_vector[i] += 10;
                    result_vector[i - 1]--;
                }
            }
            if (result_vector[0] == -1) {
                int i;
                for (i = copied_num1.size(); i > 0; i--) {
                    if (result_vector[i] != 0) {
                        result_vector[i] = 10 - result_vector[i];
                        i--;
                        break;
                    }
                }
                for (int j = i; j > 0; j--) {
                    result_vector[j] = 9 - result_vector[j];
                }
            }
            if (result_vector[0] == -1) {
                result_string += (num1.sign == 1 ? "-" : "");
            } else {
                result_string += (num1.sign == 1 ? "" : "-");
            }
            //去掉前面的0；
            int j = 1;
            while (result_vector[j] == 0 && j != result_vector.size() - 1) {
                j++;
            }
            for (; j < result_vector.size(); j++) {
                result_string += to_string(result_vector[j]);
            }
        } else if (num1.type == 1 && num2.type == 2) {
            num1.precision = 1;
            num1.absolute_num_string += ".0";
            num1.type = 2;
            copied_num1 = num1.absolute_num_string;
            goto minus_floating_point_numbers;
        } else if (num2.type == 1 && num1.type == 2) {
            num2.precision = 1;
            num2.absolute_num_string += ".0";
            num2.type = 2;
            copied_num2 = num2.absolute_num_string;
            goto minus_floating_point_numbers;
        }
            //处理浮点数相加
        else if (num1.type == 2 && num2.type == 2) {
            minus_floating_point_numbers:
            //将小数点对齐；
            //先在后面补零
            if (num1.precision < num2.precision) {
                for (int i = 0; i < num2.precision - num1.precision; i++) {
                    copied_num1 += "0";
                }
            } else {
                for (int i = 0; i < num1.precision - num2.precision; i++) {
                    copied_num2 += "0";
                }
            }
            //在前面补零：
            while (copied_num1.size() > copied_num2.size()) {
                copied_num2 = "0" + copied_num2;
            }
            while (copied_num2.size() > copied_num1.size()) {
                copied_num1 = "0" + copied_num1;
            }
            //浮点数的减法
            vector<int> result_vector(copied_num1.size() + 1, 0);
            for (int i = copied_num1.size(); i > 0; i--) {
                if (copied_num1[i - 1] == '.') {
                    result_vector[i] = '.';
                } else if (copied_num1[i - 2] == '.') {
                    result_vector[i] += copied_num1[i - 1] - copied_num2[i - 1];
                    if (result_vector[i] < 0) {
                        result_vector[i] += 10;
                        result_vector[i - 2]--; //越过小数点借位；
                    }
                } else {
                    result_vector[i] += copied_num1[i - 1] - copied_num2[i - 1];
                    if (result_vector[i] < 0) {
                        result_vector[i] += 10;
                        result_vector[i - 1]--;
                    }
                }
            }
            if (result_vector[0] == -1) {
                int i;
                for (i = copied_num1.size(); i > 0; i--) {
                    if (result_vector[i] != 0 && result_vector[i] != '.') {
                        result_vector[i] = 10 - result_vector[i];
                        i--;
                        break;
                    }
                }
                for (int j = i; j > 0; j--) {
                    if (result_vector[j] != '.') {
                        result_vector[j] = 9 - result_vector[j];
                    }
                }
            }
            if (result_vector[0] == -1) {
                result_string += (num1.sign == 1 ? "-" : "");
            } else {
                result_string += (num1.sign == 1 ? "" : "-");
            }
            //去掉前面的0；
            int j = 1;
            while (result_vector[j] == 0 && result_vector[j + 1] != '.') {
                j++;
            }
            for (; j < result_vector.size(); j++) {
                if (result_vector[j] == '.') {
                    result_string += ".";
                } else {
                    result_string += to_string(result_vector[j]);
                }
            }
        }
        num result(result_string);
        return result;
    }
}

num num::multiply(num &num1, num &num2) {
    //先忽略小数点
    string result_string, copied_num1, copied_num2;
    for (char j: num1.absolute_num_string) {
        if (j != '.') {
            copied_num1 += j;
        }
    }
    for (char j: num2.absolute_num_string) {
        if (j != '.') {
            copied_num2 += j;
        }
    }
    vector<long> operand1_vector(copied_num1.size() / 4 + 1, 0);
    for (int i = copied_num1.size() - 1, digit = 1, j = operand1_vector.size() - 1; i >= 0; i--) {
        operand1_vector[j] += (copied_num1[i] - '0') * digit;
        if (digit == 1000) {
            digit = 1;
            j--;
        } else digit *= 10;
    }
    vector<long> operand2_vector(copied_num2.size() / 4 + 1, 0);
    for (int i = copied_num2.size() - 1, digit = 1, j = operand2_vector.size() - 1; i >= 0; i--) {
        operand2_vector[j] += (copied_num2[i] - '0') * digit;
        if (digit == 1000) {
            digit = 1;
            j--;
        } else digit *= 10;
    }
    vector<long> result_vector(operand1_vector.size() + operand2_vector.size(), 0);
    for (int i = operand1_vector.size() - 1; i >= 0; i--) {
        for (int j = operand2_vector.size() - 1; j >= 0; j--) {
            result_vector[i + j + 1] += (long) operand1_vector[i] * operand2_vector[j];
            result_vector[i + j] += result_vector[i + j + 1] / 10000;
            result_vector[i + j + 1] %= 10000;
        }
    }
    for (long l: result_vector) {
        for (int i = 0; i < 4 - to_string(l).size(); i++) {
            result_string += "0";
        }
        result_string += to_string(l);
    }
    //加小数点
    if (num1.precision + num2.precision != 0) {
        result_string = result_string.substr(0, result_string.size() - num1.precision - num2.precision)
                        + "."
                        + result_string.substr(result_string.size() - num1.precision - num2.precision);
    }
    //去掉前面的0；
    int not_zero_index = 0;
    while (result_string[not_zero_index] == '0' && not_zero_index != result_string.size() - 1 &&
           result_string[not_zero_index + 1] != '.') {
        not_zero_index += 1;
    }
    result_string = (num1.sign * num2.sign == 1 ? "" : "-") + result_string.substr(not_zero_index);
    num result(result_string);
    return result;
}

//取平均值
num num::mean_value(num &left, num &right) {
    num n1 = num::add(left, right);
    string result_string = (n1.sign == 1 ? "" : "-"), copied_string = n1.absolute_num_string;
    //结果的长度取决于最后一个数字的奇偶性；
    if ((copied_string[copied_string.size() - 1] - '0') % 2 == 0) {
        vector<int> result_vector(copied_string.size(), 0);
        for (int i = 0; i < copied_string.size() - 1; i++) {
            if (copied_string[i + 1] == '.') {
                result_vector[i] += (copied_string[i] - '0') / 2;
                result_vector[i + 2] += (copied_string[i] - '0') % 2 * 5;
            } else if (copied_string[i] == '.') {
                result_vector[i] = '.';
            } else {
                result_vector[i] += (copied_string[i] - '0') / 2;
                result_vector[i + 1] += (copied_string[i] - '0') % 2 * 5;
            }
        }
        result_vector[copied_string.size() - 1] += (copied_string[copied_string.size() - 1] - '0') / 2;
        //去掉前面的0；
        int j = 0;
        while (result_vector[j] == 0 && j != result_vector.size() - 1 && result_vector[j + 1] != '.') {
            j++;
        }
        for (int i = j; i < result_vector.size(); i++) {
            if (result_vector[i] == '.') {
                result_string += ".";
            } else {
                result_string += to_string(result_vector[i]);
            }
        }
    } else {
        vector<int> result_vector(copied_string.size() + 1, 0);
        for (int i = 0; i < copied_string.size(); i++) {
            if (copied_string[i + 1] == '.') {
                result_vector[i] += (copied_string[i] - '0') / 2;
                result_vector[i + 2] += (copied_string[i] - '0') % 2 * 5;
            } else if (copied_string[i] == '.') {
                result_vector[i] = '.';
            } else {
                result_vector[i] += (copied_string[i] - '0') / 2;
                result_vector[i + 1] += (copied_string[i] - '0') % 2 * 5;
            }
        }
        //去掉前面的0；
        int j = 0;
        while (result_vector[j] == 0 && j != result_vector.size() - 1 && result_vector[j + 1] != '.') {
            j++;
        }
        for (int i = j; i < result_vector.size() - 1; i++) {
            if (result_vector[i] == '.') {
                result_string += ".";
            } else {
                result_string += to_string(result_vector[i]);
            }
        }
        //有可能整数除以二之后变成小数
        result_string += (n1.precision == 0 ? "." : "") + to_string(result_vector[result_vector.size() - 1]);
    }
    num result(result_string);
    return result;
}

//平均值向下取整
num num::integral_mean_value(num &left, num &right) {
    //两个整数的整数平均值；
    num n1 = num::add(left, right);
    string result_string = (n1.sign == 1 ? "" : "-"), copied_string = n1.absolute_num_string;
    vector<int> result_vector(copied_string.size(), 0);
    for (int i = 0; i < copied_string.size() - 1; i++) {
        result_vector[i] += (copied_string[i] - '0') / 2;
        result_vector[i + 1] += (copied_string[i] - '0') % 2 * 5;
    }
    result_vector[copied_string.size() - 1] += (copied_string[copied_string.size() - 1] - '0') / 2;
    //去掉前面的0；
    int j = 0;
    while (result_vector[j] == 0) {
        j++;
    }
    for (int i = j; i < result_vector.size(); i++) {
        result_string += to_string(result_vector[i]);
    }
    num result(result_string);
    return result;
}

num num::divide(num &num1, num &num2) {
    string result_string, copied_num1 = num1.absolute_num_string, copied_num2 = num2.absolute_num_string;
    string str1 = copied_num1, str2 = copied_num2;
    num abs_num1(str1), abs_num2(str2);
    if (num1.type == 1 && num2.type == 1)//整除
    {
        //看看这两个数的绝对值大小；
        if (num::minus(abs_num1, abs_num2).sign < 0) {
            result_string = "0";
            num result(result_string);
            return result;
        } else {
            int digits_difference = int(copied_num1.size() - copied_num2.size());
            string lower_bound = "1", upper_bound = "1";
            for (int i = 0; i < digits_difference + 1; i++) {
                upper_bound += "0";
            }
            for (int i = 0; i < digits_difference - 1; i++) {
                lower_bound += "0";
            }
            num number_lower_bound(lower_bound), number_upper_bound(upper_bound);
            num result(lower_bound);
            while (!(minus(number_upper_bound, number_lower_bound).absolute_num_string == "1" &&
                     result.absolute_num_string == number_lower_bound.absolute_num_string)) {
                result = integral_mean_value(number_lower_bound, number_upper_bound);
                num result_mul_num2 = multiply(result, abs_num2);
                if (minus(abs_num1, result_mul_num2).sign < 0) {
                    number_upper_bound = result;
                } else if (minus(abs_num1, result_mul_num2).sign > 0) {
                    number_lower_bound = result;
                } else {
                    break;
                }
            }
            //计算符号；
            result.sign = num1.sign * num2.sign;
            return result;
        }
    } else if (num1.type == 1 && num2.type == 2) {
        num1.precision = 1;
        num1.absolute_num_string += ".0";
        num1.type = 2;
        copied_num1 = num1.absolute_num_string;
        goto add_floating_point_numbers;
    } else if (num2.type == 1 && num1.type == 2) {
        num2.precision = 1;
        num2.absolute_num_string += ".0";
        num2.type = 2;
        copied_num2 = num2.absolute_num_string;
        goto add_floating_point_numbers;
    } else if (num1.type == 2 && num2.type == 2) {
        add_floating_point_numbers:
        //将小数点对齐；
        //先在后面补零
        if (num1.precision < num2.precision) {
            for (int i = 0; i < num2.precision - num1.precision; i++) {
                copied_num1 += "0";
            }
        } else {
            for (int i = 0; i < num1.precision - num2.precision; i++) {
                copied_num2 += "0";
            }
        }
        //看看这两个数的绝对值大小；
        int digits_difference = int(copied_num1.size() - copied_num2.size());
        string lower_bound, upper_bound;
        if (num::minus(abs_num1, abs_num2).sign < 0) {
            //第一个数的绝对值小于第二个数
            lower_bound = "1";
            upper_bound = "1";
            for (int i = 0; i < abs(digits_difference) + 1; i++) {
                lower_bound = "0" + lower_bound;
            }
            for (int i = 0; i < abs(digits_difference) - 1; i++) {
                upper_bound = "0" + upper_bound;
            }
            //加上小数点；
            if (lower_bound[0] == '0') {
                lower_bound = "0." + lower_bound.substr(1);
            }
            if (upper_bound[0] == '0') {
                upper_bound = "0." + upper_bound.substr(1);
            }
        } else {//第一个数的绝对值大于等于第二个数
            lower_bound = "1";
            upper_bound = "1";
            for (int i = 0; i < digits_difference + 1; i++) {
                upper_bound += "0";
            }
            for (int i = 0; i < digits_difference - 1; i++) {
                lower_bound += "0";
            }
        }
        //相乘的结果及其差值；
        num number_lower_bound(lower_bound), number_upper_bound(upper_bound);


        num mul_outcome = multiply(number_lower_bound, abs_num2);
        string difference = minus(abs_num1, mul_outcome).absolute_num_string;
        num upper_lower_difference(difference);
        //将精度设为阈值
        int result_precision = (num2.precision > num1.precision) ? num2.precision : num1.precision;
        string result_precision_string = "0.";
        for (int i = 0; i < result_precision - 1; i++) {
            result_precision_string += "0";
        }
        result_precision_string += "1";
        num num_precision(result_precision_string);
        //未知精度的结果
        num mid(lower_bound);
        while (minus(upper_lower_difference, num_precision).sign != -1) {
            mid = mean_value(number_lower_bound, number_upper_bound);
            num result_mul_num2 = multiply(mid, abs_num2);
            if (minus(abs_num1, result_mul_num2).sign < 0) {
                number_upper_bound = mid;
            } else {
                number_lower_bound = mid;
            }
            string difference_ = minus(abs_num1, result_mul_num2).absolute_num_string;
            num upper_lower_difference_(difference_);
            upper_lower_difference = upper_lower_difference_;
        }
        result_string = round(mid.absolute_num_string, result_precision);
        num result(result_string);
        //计算符号；
        result.sign = num1.sign * num2.sign;
        return result;
    }
    num result(result_string);
    return result;
}

//帮助四舍五入
string num::round(string num_string, int precision) {
    string return_string, copied_string = num_string;
    num num1(copied_string);
    num_string = num1.absolute_num_string;
    if (num1.type == 2) {
        //处理小数；
        int i = 0;
        for (; i < num_string.size(); i++) {
            if (num_string[i] == '.') {
                break;
            }
        }
        if (num_string.size() - 1 - i > precision) {
            //如果现在的小数位数大于精度
            string s1, s2;
            if (precision != 0) {
                //精度不等于零
                s1 = num_string.substr(0, i + precision + 1);
            } else {
                s1 = num_string.substr(0, i);
            }
            for (int j = 0; j < i + precision; j++) {
                if (num_string[j] == '.') {
                    s2 += '.';
                } else {
                    s2 += "0";
                }
            }
            int c = (num_string[i + precision + 1] > '4' ? 1 : 0);
            s2 += to_string(c);
            num n1(s1), n2(s2);
            return_string = add(n1, n2).absolute_num_string;
        } else {
            return_string = num_string;
            for (int j = (int) num_string.size() - 1; j < i + precision; j++) {
                return_string += "0";
            }
        }
    } else {
        if (precision == 0) {
            return_string = num_string;
        } else {
            return_string = num_string + ".";
            for (int i = 0; i < precision; i++) {
                return_string += "0";
            }
        }
    }
    return_string = (num1.sign == -1 ? "-" : "") + return_string;
    return return_string;
}

string num::round_up(string abs_string) {
    num abs_num(abs_string);
    string result_string;
    if (abs_num.type == 1) {
        result_string = abs_string;
    } else {
        //处理小数先把小数点给找出来；
        int dot_index = -1;
        for (int i = 0; i < abs_string.size(); i++) {
            if (abs_string[i] == '.') {
                dot_index = i;
                break;
            }
        }
        bool need_plus_one = false;
        for (int i = dot_index + 1; i < abs_string.size(); i++) {
            if (abs_string[i] != '0') {
                need_plus_one = true;
                break;
            }
        }
        if (need_plus_one) {
            string one = "1", integral_part = abs_string.substr(0, dot_index);
            num number_one(one), integer_num(integral_part);
            result_string = add(number_one, integer_num).absolute_num_string;
        } else {
            result_string = abs_string.substr(0, dot_index);
        }
    }
    return result_string;
}

string num::round_down(string abs_string) {
    num abs_num(abs_string);
    string result_string;
    if (abs_num.type == 1) {
        result_string = abs_string;
    } else {
        //处理小数先把小数点给找出来；
        int dot_index = -1;
        for (int i = 0; i < abs_string.size(); i++) {
            if (abs_string[i] == '.') {
                dot_index = i;
                break;
            }
        }
        result_string = abs_string.substr(0, dot_index);
    }
    return result_string;
}

string num::floor(string num_string) {
    num n1(num_string);
    if (n1.sign == 1) {
        //如果是正数
        return round_down(n1.absolute_num_string);
    } else {
        //如果是负数
        return ("-" + round_up(n1.absolute_num_string));
    }
}

string num::ceil(string num_string) {
    num n1(num_string);
    if (n1.sign == 1) {
        //如果是正数
        return round_up(n1.absolute_num_string);
    } else {
        //如果是负数
        return ("-" + round_down(n1.absolute_num_string));
    }
}


num num::module(num &num1, num &num2) {
    string result_string, copied_num1 = num1.absolute_num_string, copied_num2 = num2.absolute_num_string;
    string str1 = copied_num1, str2 = copied_num2;
    num abs_num1(str1), abs_num2(str2);
    //看看这两个数的绝对值大小；
    if (num::minus(abs_num1, abs_num2).sign < 0) {
        num result(abs_num1);
        result.sign = num1.sign;
        return result;
    } else if (num1.type == 1 && num2.type == 1)//整除取余
    {
        int digits_difference = int(copied_num1.size() - copied_num2.size());
        string lower_bound = "1", upper_bound = "1";
        for (int i = 0; i < digits_difference + 1; i++) {
            upper_bound += "0";
        }
        for (int i = 0; i < digits_difference - 1; i++) {
            lower_bound += "0";
        }
        num number_lower_bound(lower_bound), number_upper_bound(upper_bound);
        num quotient(lower_bound);
        while (!(minus(number_upper_bound, number_lower_bound).absolute_num_string == "1" &&
                 quotient.absolute_num_string == number_lower_bound.absolute_num_string)) {
            quotient = integral_mean_value(number_lower_bound, number_upper_bound);
            num result_mul_num2 = multiply(quotient, abs_num2);
            if (minus(abs_num1, result_mul_num2).sign < 0) {
                number_upper_bound = quotient;
            } else if (minus(abs_num1, result_mul_num2).sign > 0) {
                number_lower_bound = quotient;
            } else {
                break;
            }
        }
        string s1 = num1.absolute_num_string, s2 = multiply(quotient, abs_num2).absolute_num_string;
        num n1(s1), n2(s2);
        num result = minus(n1, n2);
        result.sign = num1.sign;
        return result;

    } else if (num1.type == 1 && num2.type == 2) {
        num1.precision = 1;
        num1.absolute_num_string += ".0";
        num1.type = 2;
        copied_num1 = num1.absolute_num_string;
        goto add_floating_point_numbers;
    } else if (num2.type == 1 && num1.type == 2) {
        num2.precision = 1;
        num2.absolute_num_string += ".0";
        num2.type = 2;
        copied_num2 = num2.absolute_num_string;
        goto add_floating_point_numbers;
    }
        //处理浮点数相加
    else if (num1.type == 2 && num2.type == 2) {
        add_floating_point_numbers:
        //将小数点对齐；
        //先在后面补零
        if (num1.precision < num2.precision) {
            for (int i = 0; i < num2.precision - num1.precision; i++) {
                copied_num1 += "0";
            }
        } else {
            for (int i = 0; i < num1.precision - num2.precision; i++) {
                copied_num2 += "0";
            }
        }
        int digits_difference = int(copied_num1.size() - copied_num2.size());
        string lower_bound, upper_bound;
        //第一个数的绝对值大于等于第二个数
        lower_bound = "1";
        upper_bound = "1";
        for (int i = 0; i < digits_difference + 1; i++) {
            upper_bound += "0";
        }
        for (int i = 0; i < digits_difference - 1; i++) {
            lower_bound += "0";
        }

        //相乘的结果及其差值；
        num number_lower_bound(lower_bound), number_upper_bound(upper_bound);
        num mul_outcome = multiply(number_lower_bound, abs_num2);
        string difference = minus(abs_num1, mul_outcome).absolute_num_string;
        num upper_lower_difference(difference);
        //商
        num quotient(lower_bound);
        while (true) {
            quotient = integral_mean_value(number_lower_bound, number_upper_bound);
            if (minus(quotient, number_lower_bound).absolute_num_string == "0") {
                break;
            }
            num result_mul_num2 = multiply(quotient, abs_num2);
            if (minus(abs_num1, result_mul_num2).sign < 0) {
                number_upper_bound = quotient;
            } else {
                number_lower_bound = quotient;
            }
        }
        string s1 = abs_num1.absolute_num_string, s2 = multiply(quotient, abs_num2).absolute_num_string;
        num n1(s1), n2(s2);
        num result = minus(n1, n2);
        result.sign = num1.sign;
        return result;
    }
    num result(result_string);
    return result;
}

num num::exponent(num &num1, num &num2, bool &success) {
    string result_string = "1";
    num result_num(result_string);
    if (num2.type != 1) {
        success = false;
        return result_num;
    } else if (num2.sign == 1) {
        for (int i = 0; i < atoi(num2.absolute_num_string.c_str()); i++) {
            result_num = multiply(result_num, num1);
        }
    } else {
        for (int i = 0; i < atoi(num2.absolute_num_string.c_str()); i++) {
            result_num = multiply(result_num, num1);
        }
        string one_string = "1";
        num num_one(one_string);
        result_num = divide(num_one, result_num);
    }
    return result_num;
}

string num::factorial(string biggest_integer) {
    string initial_string = "1";
    num result_num(initial_string);
    int biggest_int = atoi(biggest_integer.c_str());
    for (int i = 1; i <= biggest_int; i++) {
        string s = to_string(i);
        num n(s);
        result_num = multiply(result_num, n);
    }
    return result_num.absolute_num_string;
}

num num::root(num number, int index) {
    num abs_number = number;
    abs_number.sign = 1;
    //在这里只需要对number的绝对值开根就可以了
    //处理浮点数的开根
    //将小数点对齐；
    string lower_bound = "1", upper_bound = abs_number.absolute_num_string;
    //相乘的结果及其差值；
    num number_lower_bound(lower_bound), number_upper_bound(upper_bound);
    num mul_outcome(lower_bound);
    for (int i = 0; i < index - 1; i++) {
        mul_outcome = multiply(mul_outcome, number_lower_bound);
    }
    string difference = minus(number_upper_bound, mul_outcome).absolute_num_string;
    num upper_lower_difference(difference);
    //将精度设为阈值
    int result_precision = abs_number.precision;
    string result_precision_string = "0.";
    for (int i = 0; i < result_precision; i++) {
        result_precision_string += "0";
    }
    result_precision_string += "1";
    num num_precision(result_precision_string);
    //未知精度的结果
    num mid(lower_bound);
    while (minus(upper_lower_difference, num_precision).sign != -1) {
        mid = mean_value(number_lower_bound, number_upper_bound);
        num result_mul_num2 = mid;
        for (int i = 0; i < index - 1; i++) {
            result_mul_num2 = multiply(result_mul_num2, mid);
        }
        if (minus(abs_number, result_mul_num2).sign < 0) {
            number_upper_bound = mid;
        } else {
            number_lower_bound = mid;
        }
        string difference_ = minus(abs_number, result_mul_num2).absolute_num_string;
        num upper_lower_difference_(difference_);
        upper_lower_difference = upper_lower_difference_;
    }
    string result_string = round(mid.absolute_num_string, result_precision);
    num result(result_string);
    return result;
}

num num::sin(num value, int precision) {
    string one = "1", two = "2", result_string = "0";
    num index(one), increment(two), result(result_string);
    string precision_string = "0.";
    for (int i = 0; i < precision + 1; i++) {
        precision_string += "0";
    }
    precision_string += "1";
    num precision_num(precision_string);
    int plus_or_minus = 1;
    while (true) {
        bool must_true = true;
        num mid1 = exponent(value, index, must_true);
        string mid2_string = factorial(index.absolute_num_string);
        mid2_string += ".";
        for (int j = 0; j < precision + 5; j++) {
            mid2_string += "0";
        }
        num mid2(mid2_string);
//        cout<<mid1.absolute_num_string<<" "<<mid2_string<<endl;
        num mid3 = divide(mid1, mid2);
        if (plus_or_minus == 1) {
            result = add(result, mid3);
        } else {
            result = minus(result, mid3);
        }
        plus_or_minus *= -1;
        index = add(index, increment);
        if (minus(mid3, precision_num).sign < 0) {
            break;
        }
    }
    string result_final = round(result.absolute_num_string, precision);
    num num_final(result_final);
    num_final.sign = result.sign;
    return num_final;
}

num num::cos(num value, int precision) {
    string zero = "0", two = "2", result_string = "0";
    num index(zero), increment(two), result(result_string);
    string precision_string = "0.";
    for (int i = 0; i < precision + 1; i++) {
        precision_string += "0";
    }
    precision_string += "1";
    num precision_num(precision_string);
    int plus_or_minus = 1;
    while (true) {
        bool must_true = true;
        num mid1 = exponent(value, index, must_true);
        string mid2_string = factorial(index.absolute_num_string);
        mid2_string += ".";
        for (int j = 0; j < precision + 5; j++) {
            mid2_string += "0";
        }
        num mid2(mid2_string);
        num mid3 = divide(mid1, mid2);
        if (plus_or_minus == 1) {
            result = add(result, mid3);
        } else {
            result = minus(result, mid3);
        }
        plus_or_minus *= -1;
        index = add(index, increment);
        if (minus(mid3, precision_num).sign < 0) {
            break;
        }
    }
    string result_final = round(result.absolute_num_string, precision);
    num num_final(result_final);
    num_final.sign = result.sign;
    return num_final;
}

MyOperator::MyOperator(char operator_symbol, int left_operand_index) {
    this->operator_symbol = operator_symbol;
    this->left_operand_index = left_operand_index;
}
