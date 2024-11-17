#include <map>
#include "functions.h"

//这个文件用来判断输入是想进行什么样的操作


void OperateManyTimes() {
    while (true) {
        string expression_string;
        getline(cin, expression_string);
        if (expression_string == "AC") {
            break;
        }
        bool have_equal_sign = false, have_f_or_F = false, have_comma = false, success = true;
        for (int i = 0; i < expression_string.size(); i++) {
            if (expression_string[i] == '=') {
                have_equal_sign = true;
            }

            if (expression_string[i] == ',') {
                have_comma = true;
            }
        }
        if ((expression_string[0] == 'f' || expression_string[0] == 'F') && expression_string.size() > 1 &&
            expression_string[1] == '(') {
            have_f_or_F = true;
        }
        //除了最后一项可以是‘=’外，其他都不能是‘=’，若满足就看看符不符合第一种运算
        if (!have_equal_sign) {
            //先处理数学函数
            if (expression_string.size() >= 4 && expression_string.substr(0, 4) == "root") {
                //先做一个检查，输入格式要符合
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[4] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    //看一看是一个参数还是两个参数
                    int comma_index = -1;
                    for (int i = 0; i < expression_string.size(); i++) {
                        if (expression_string[i] == ',') {
                            comma_index = i;
                            break;
                        }
                    }
                    if (comma_index == -1) //只有一个参数
                    {
                        cout << "Invalid input!Check and input again!" << endl;
                        continue;
                    } else //两个参数
                    {
                        string num_string = expression_string.substr(5, comma_index - 5),
                                index_string = expression_string.substr(comma_index + 1,
                                                                        expression_string.size() - comma_index - 2);
                        num argument_num(num_string), argument_index(index_string);
                        //第二个参数要是一个正整数，且负数只能开奇次方根
                        int i = atoi(index_string.c_str());
                        if (argument_num.type == 0 || argument_index.type != 1 ||
                            argument_num.sign == -1 && i % 2 == 0 || i == 0) {
                            cout << "Invalid input!Check and input again!" << endl;
                            continue;
                        } else {
                            cout << (argument_num.sign == -1 ? "-" : "")
                                 << num::root(argument_num, i).absolute_num_string << endl;
                        }
                    }
                }
            } else if (expression_string.size() >= 4 && expression_string.substr(0, 4) == "sqrt") {
                //先做一个检查
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[4] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    string argument_string = expression_string.substr(5, expression_string.size() - 6);
                    num argument_num(argument_string);
                    //不能是负数
                    if (argument_num.type == 0 || argument_num.sign != 1) {
                        cout << "Invalid input!Check and input again!" << endl;
                        continue;
                    } else {
                        num n = num::root(argument_num, 2);
                        cout << n.absolute_num_string << endl;
                    }
                }
            } else if (expression_string.size() >= 4 && expression_string.substr(0, 4) == "ceil") {
                //先做一个检查
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[4] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    //看看中间是啥
                    string argument_string = expression_string.substr(5, expression_string.size() - 6);
                    num argument_num(argument_string);
                    if (argument_num.type == 0) {
                        cout << "Invalid input!Check and input again!" << endl;
                        continue;
                    } else {
                        cout << num::ceil(argument_string) << endl;
                    }
                }
            } else if (expression_string.size() >= 5 && expression_string.substr(0, 5) == "floor") {
                //先做一个检查
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[5] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    string argument_string = expression_string.substr(6, expression_string.size() - 7);
                    num argument_num(argument_string);
                    if (argument_num.type == 0) {
                        cout << "Invalid input!Check and input again!" << endl;
                        continue;
                    } else {
                        cout << num::floor(argument_string) << endl;
                    }
                }
            } else if (expression_string.size() >= 5 && expression_string.substr(0, 5) == "round") {
                //先做一个检查
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[5] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    //看一看是一个参数还是两个参数
                    int comma_index = -1;
                    for (int i = 0; i < expression_string.size(); i++) {
                        if (expression_string[i] == ',') {
                            comma_index = i;
                            break;
                        }
                    }
                    if (comma_index == -1) //只有一个参数
                    {
                        string argument_string = expression_string.substr(6, expression_string.size() - 7);
                        num argument_num(argument_string);
                        if (argument_num.type == 0) {
                            cout << "Invalid input!Check and input again!" << endl;
                            continue;
                        } else {
                            cout << num::round(argument_string, 0) << endl;
                        }
                    } else //视为两个参数
                    {
                        string num_string = expression_string.substr(6, comma_index - 6),
                                precision_string = expression_string.substr(comma_index + 1,
                                                                            expression_string.size() - comma_index - 2);
                        num argument_num(num_string), argument_precision(precision_string);
                        if (argument_num.type == 0 || argument_precision.type != 1) {
                            cout << "Invalid input!Check and input again!" << endl;
                            continue;
                        } else {
                            int i = atoi(precision_string.c_str());
                            cout << num::round(num_string, i) << endl;
                        }
                    }
                }
            } else if (expression_string.size() >= 5 && expression_string.substr(0, 5) == "sigma") {
                //先做一个检查
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[5] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    //统计逗号个数,并记录位置
                    int comma_index[2]{0}, index = 0;
                    bool valid_comma = true;
                    for (int i = 0; i < expression_string.size(); i++) {
                        if (expression_string[i] == ',') {
                            if (index < 2) {
                                comma_index[index++] = i;
                            } else {
                                //逗号个数如果大于2
                                valid_comma = false;
                                break;
                            }
                        }
                    }
                    //防止逗号格数小于2；
                    valid_comma *= comma_index[0] * comma_index[1];
                    if (!valid_comma) {
                        cout << "Invalid input!Check and input again!" << endl;
                        continue;
                    } else {
                        string variable_function = expression_string.substr(6, comma_index[0] - 6),
                                lower_bound_string = expression_string.substr(comma_index[0] + 1,
                                                                              comma_index[1] - comma_index[0] - 1),
                                upper_bound_string = expression_string.substr(comma_index[1] + 1,
                                                                              expression_string.size() -
                                                                              comma_index[1] - 2);
                        num lower_bound_num(lower_bound_string), upper_bound_num(upper_bound_string);
                        if (lower_bound_num.type != 1 || upper_bound_num.type != 1 || lower_bound_num.sign != 1 ||
                            num::minus(upper_bound_num, lower_bound_num).sign < 0) //下限必须小于上限，且都是自然数
                        {
                            cout << "Invalid input!Check and input again!" << endl;
                            continue;
                        } else {
                            //先将变量找出来
                            string variable;
                            for (int i = 0; i < variable_function.size(); i++) {
                                if (variable_function[i] != '+' && variable_function[i] != '-' &&
                                    variable_function[i] != '*' && variable_function[i] != '/' &&
                                    variable_function[i] != '%' && variable_function[i] != '^' &&
                                    variable_function[i] != '(' && variable_function[i] != ')') {
                                    for (char c: variable_function.substr(i)) {
                                        if (c != '+' && c != '-' && c != '*' && c != '/' && c != '%' && c != '^' &&
                                            c != '(' && c != ')') {
                                            variable += c;
                                        } else {
                                            goto tab;
                                        }
                                    }
                                }
                            }
                            tab:
                            int begin = atoi(lower_bound_string.c_str()), end = atoi(upper_bound_string.c_str());
                            string zero_string = "0";
                            num result(zero_string);
                            for (int i = begin; i <= end; i++) {
                                string s = "(" + to_string(i) + ")", copied_function = variable_function;
                                int pos = 0;
                                while ((pos = (int) copied_function.find(variable, pos)) != string::npos) {
                                    copied_function.replace(pos, variable.size(), s);
                                    pos += (int) s.size();
                                }
                                bool pass = true;
                                num result_i = OperateAnExpression(copied_function, pass);
                                if (!pass) {
                                    cout << "Invalid input!Check and input again!" << endl;
                                    goto end;;
                                } else {
                                    result = num::add(result, result_i);
                                }
                            }
                            cout << (result.sign == -1 ? "-" : "") << result.absolute_num_string << endl;
                        }
                    }
                }
            } else if (expression_string.size() >= 3 && expression_string.substr(0, 3) == "sin") {
                //先做一个检查，输入格式要符合
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[3] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    //看一看是一个参数还是两个参数
                    int comma_index = -1;
                    for (int i = 0; i < expression_string.size(); i++) {
                        if (expression_string[i] == ',') {
                            comma_index = i;
                            break;
                        }
                    }
                    if (comma_index == -1) //只有一个参数
                    {
                        cout << "Invalid input!Check and input again!" << endl;
                        continue;
                    } else //两个参数
                    {
                        string num_string = expression_string.substr(4, comma_index - 4),
                                index_string = expression_string.substr(comma_index + 1,
                                                                        expression_string.size() - comma_index - 2);
                        num argument_num(num_string), argument_index(index_string);
                        //第二个参数要是一个正整数
                        int i = atoi(index_string.c_str());
                        if (argument_num.type == 0 || argument_index.type != 1) {
                            cout << "Invalid input!Check and input again!" << endl;
                            continue;
                        } else {
                            cout << (num::sin(argument_num, i).sign == -1 ? "-" : "")
                                 << num::sin(argument_num, i).absolute_num_string << endl;
                        }
                    }
                }
            } else if (expression_string.size() >= 3 && expression_string.substr(0, 3) == "cos") {
                //先做一个检查，输入格式要符合
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[3] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    //看一看是一个参数还是两个参数
                    int comma_index = -1;
                    for (int i = 0; i < expression_string.size(); i++) {
                        if (expression_string[i] == ',') {
                            comma_index = i;
                            break;
                        }
                    }
                    if (comma_index == -1) //只有一个参数
                    {
                        cout << "Invalid input!Check and input again!" << endl;
                        continue;
                    } else //两个参数
                    {
                        string num_string = expression_string.substr(4, comma_index - 4),
                                index_string = expression_string.substr(comma_index + 1,
                                                                        expression_string.size() - comma_index - 2);
                        num argument_num(num_string), argument_index(index_string);
                        //第二个参数要是一个正整数
                        int i = atoi(index_string.c_str());
                        if (argument_num.type == 0 || argument_index.type != 1) {
                            cout << "Invalid input!Check and input again!" << endl;
                            continue;
                        } else {
                            cout << (num::cos(argument_num, i).sign == -1 ? "-" : "")
                                 << num::cos(argument_num, i).absolute_num_string << endl;
                        }
                    }
                }
            } else if (expression_string.size() >= 9 && expression_string.substr(0, 9) == "factorial") {
                //先做一个检查
                if (expression_string[expression_string.size() - 1] != ')' || expression_string[9] != '(') {
                    cout << "Invalid input!Check and input again!" << endl;
                    continue;
                } else {
                    string argument_string = expression_string.substr(10, expression_string.size() - 11);
                    num argument_num(argument_string);
                    if (argument_num.type != 1 || argument_num.sign != 1) {
                        cout << "Invalid input!Check and input again!" << endl;
                        continue;
                    } else {
                        cout << num::factorial(argument_string) << endl;
                    }
                }
            } else {
                CheckExpressionValidity(expression_string, success);
                if (!success) {
                    cout << "Invalid input!Check and input again!" << endl;
                } else {
                    num result = OperateAnExpression(expression_string, success);
                    if (!success) {
                        cout << "Invalid input!Check and input again!" << endl;
                    } else {
                        cout << (result.sign == -1 ? "-" : "") << result.absolute_num_string << endl;
                    }
                }
            }

        } else {
            if (have_f_or_F) {
                string result = OperateAFunction(expression_string, success);
                if (!success) {
                    cout << "Invalid input!Check and input again!" << endl;
                } else {
                    cout << result << endl;
                }
            } else {
                OperateAnExpressionWithVariables(expression_string, success);
                if (!success) {
                    cout << "Invalid input!Check and input again!" << endl;
                }
            }
        }
        end:;
    }
}

num OperateAnExpression(string &expression_string, bool &success) {
    while (true) {
        //如果化简成一个数，那么认为计算完毕；
        {
            for (int i = 0; i < expression_string.size(); i++) {
                if ((i != 0 && (expression_string[i] == '+' || expression_string[i] == '-')) ||
                    expression_string[i] == '*' || expression_string[i] == '/' ||
                    expression_string[i] == '%' || expression_string[i] == '^' ||
                    expression_string[i] == '(' || expression_string[i] == ')') {
                    goto deduction;
                }
            }
            num result(expression_string);
            return result;
        }
        deduction:
        //先算一下一共有多少个括号,找出最优先计算的那个括号的表达式
        int left_parentheses_numbers = 0, right_parentheses_numbers = 0, most_priority = 0, most_priority_left_index = 0, most_priority_right_index =
                (int) expression_string.size() - 1;
        for (int i = 0; i < expression_string.size(); i++) {
            if (expression_string[i] == '(') {
                left_parentheses_numbers++;
            }
            if (expression_string[i] == ')') {
                right_parentheses_numbers++;
            }
            if (left_parentheses_numbers - right_parentheses_numbers > most_priority) {
                most_priority = left_parentheses_numbers - right_parentheses_numbers;
                most_priority_left_index = i + 1;
            }
        }
        for (int i = most_priority_left_index; i < expression_string.size(); i++) {
            if (expression_string[i] == ')') {
                most_priority_right_index = i - 1;
                break;
            }
        }
        string sub_expression2 = expression_string.substr(most_priority_left_index,
                                                          most_priority_right_index - most_priority_left_index + 1);
        string sub_expression1 = (most_priority_left_index > 1) ? expression_string.substr(0,
                                                                                           most_priority_left_index - 1)
                                                                : "";
        string sub_expression3 = (most_priority_right_index + 2 < expression_string.size()) ? expression_string.substr(
                most_priority_right_index + 2) : "";
        expression_string = "";
        expression_string.append(sub_expression1);
        expression_string.append(OperateAnExpressionWithoutParentheses(sub_expression2, success));//处理不带括号的子式
        expression_string.append(sub_expression3);
        if (!success) {
            string s;
            num n(s);
            return n;
        }
    }

}

string OperateAnExpressionWithoutParentheses(string &expression_string, bool &success) {
    vector<num> num_vector;
    vector<MyOperator> plus_minus_vector;
    vector<MyOperator> multiply_divide_module_vector;
    vector<MyOperator> exponent_vector;
    for (int i = 0; i < expression_string.size(); i++) {
        if (expression_string[i] >= '0' && expression_string[i] <= '9'
            || expression_string[i] == 'e' || expression_string[i] == 'E'
            || (i != 0 && (expression_string[i - 1] > '9' || expression_string[i - 1] < '0') &&
                (expression_string[i] == '+' || expression_string[i] == '-'))                 //这里用来处理类似5+-3的情况
            || (i == 0 && (expression_string[i] == '+' || expression_string[i] == '-'))
            || expression_string[i] == 'P') {
            string num_string;
            num_string += expression_string[i];
            i++;
            int k = i;
            while (i < expression_string.size() && (expression_string[i] >= '0' && expression_string[i] <= '9'
                                                    || expression_string[i] == 'e' || expression_string[i] == 'E'
                                                    || expression_string[i] == '.'
                                                    || ((expression_string[i] == '+' || expression_string[i] == '-') &&
                                                        i == 0)
                                                    || ((expression_string[i] == '+' || expression_string[i] == '-') &&
                                                        i != 0 && (expression_string[i - 1] == 'e' ||
                                                                   expression_string[i - 1] == 'e'))
                                                    || expression_string[i] == 'P' || expression_string[i] == 'I')) {
                num_string += expression_string[i];
                i++;
            }
            i--;
            num num_operand(num_string);
            num_vector.push_back(num_operand);
        } else if (expression_string[i] == '+' || expression_string[i] == '-') {
            MyOperator myOperator(expression_string[i], (int) num_vector.size() - 1);
            plus_minus_vector.push_back(myOperator);
        } else if (expression_string[i] == '*' || expression_string[i] == '/' || expression_string[i] == '%') {
            MyOperator myOperator(expression_string[i], (int) num_vector.size() - 1);
            multiply_divide_module_vector.push_back(myOperator);
        } else if (expression_string[i] == '^') {
            MyOperator myOperator(expression_string[i], (int) num_vector.size() - 1);
            exponent_vector.push_back(myOperator);
        }
    }


    for (auto &i: exponent_vector) {
        num num1 = num::Operate(num_vector[i.left_operand_index], num_vector[i.left_operand_index + 1], '^', success);
        if (!success) {
            return "";
        }
        num_vector[i.left_operand_index] = num1;
        for (int j = i.left_operand_index + 1; j < num_vector.size() - 1; j++) {
            num_vector[j] = num_vector[j + 1];
        }
        num_vector.pop_back();
        for (auto &j: exponent_vector) {
            if (j.left_operand_index > i.left_operand_index) {
                j.left_operand_index--;
            }
        }
        for (auto &j: plus_minus_vector) {
            if (j.left_operand_index > i.left_operand_index) {
                j.left_operand_index--;
            }
        }
        for (auto &j: multiply_divide_module_vector) {
            if (j.left_operand_index > i.left_operand_index) {
                j.left_operand_index--;
            }
        }
    }
    for (int i = 0; i < multiply_divide_module_vector.size(); i++) {
        num num1 = num::Operate(num_vector[multiply_divide_module_vector[i].left_operand_index],
                                num_vector[multiply_divide_module_vector[i].left_operand_index + 1],
                                multiply_divide_module_vector[i].operator_symbol, success);
        num_vector[multiply_divide_module_vector[i].left_operand_index] = num1;
        for (int j = multiply_divide_module_vector[i].left_operand_index + 1; j < num_vector.size() - 1; j++) {
            num_vector[j] = num_vector[j + 1];
        }
        num_vector.pop_back();
        for (int j = i + 1; j < multiply_divide_module_vector.size(); j++) {
            multiply_divide_module_vector[j].left_operand_index--;
        }
        for (auto &j: plus_minus_vector) {
            if (j.left_operand_index > multiply_divide_module_vector[i].left_operand_index) {
                j.left_operand_index--;
            }
        }
    }
    for (int i = 0; i < plus_minus_vector.size(); i++) {
        num num1 = num::Operate(num_vector[plus_minus_vector[i].left_operand_index],
                                num_vector[plus_minus_vector[i].left_operand_index + 1],
                                plus_minus_vector[i].operator_symbol, success);
        num_vector[plus_minus_vector[i].left_operand_index] = num1;
        for (int j = plus_minus_vector[i].left_operand_index + 1; j < num_vector.size() - 1; j++) {
            num_vector[j] = num_vector[j + 1];
        }
        num_vector.pop_back();
        for (int j = i + 1; j < plus_minus_vector.size(); j++) {
            plus_minus_vector[j].left_operand_index--;
        }
    }
//      最后只剩下num_vector[0]一个数了
    return ((num_vector[0].sign == 1) ? "" : "-") + num_vector[0].absolute_num_string;
}

void CheckExpressionValidity(string &expression_string, bool &valid) {
    if (expression_string.empty()) {
        valid = false;
        return;
    }
    bool parentheses_in_pairs = 1, correctly_use_parentheses = 1, correctly_input_operands = 1, no_consecutive_operators = 1, no_invalid_character = 1;
    int left_parentheses_numbers = 0, right_parentheses_numbers = 0;
    for (int i = 0; i < expression_string.size(); i++) {
        if (expression_string[i] >= '0' && expression_string[i] <= '9'
            || expression_string[i] == 'e' || expression_string[i] == 'E'
            || expression_string[i] == '.') {

        } else if (expression_string[i] == '+' || expression_string[i] == '-'
                   || expression_string[i] == '*' || expression_string[i] == '/'
                   || expression_string[i] == '%' || expression_string[i] == '^') {
            if (i < expression_string.size() - 1) {
                if (expression_string[i + 1] == '+' || expression_string[i + 1] == '-'
                    || expression_string[i + 1] == '*' || expression_string[i + 1] == '/'
                    || expression_string[i + 1] == '%' || expression_string[i + 1] == '^' ||
                    expression_string[i + 1] == ')') //运算符不能连着右括号和其他运算符
                {
                    no_consecutive_operators = 0;
                } else {

                }
            } else //如果在最后一个
            {
                no_invalid_character = 0;
                break;
            }
        } else if (expression_string[i] == '(') {
            if (i != 0) {
                if (!(expression_string[i - 1] == '+' || expression_string[i - 1] == '-'
                      || expression_string[i - 1] == '*' || expression_string[i - 1] == '/'
                      || expression_string[i - 1] == '%' || expression_string[i - 1] == '^'
                      || expression_string[i - 1] == '(')) //如果不是第一个字符，那么前面一定要有一个运算符或者左括号
                {
                    correctly_use_parentheses = 0;
                    break;
                }
            }
            left_parentheses_numbers++;
        } else if (expression_string[i] == ')') {
            if (i != expression_string.size() - 1) {
                if (!(expression_string[i + 1] == '+' || expression_string[i + 1] == '-'
                      || expression_string[i + 1] == '*' || expression_string[i + 1] == '/'
                      || expression_string[i + 1] == '%' || expression_string[i + 1] == '^'
                      || expression_string[i + 1] == ')')) //如果不是最后一个字符，那么后面一定要有一个运算符或者右括号
                {
                    correctly_use_parentheses = 0;
                    break;
                }
            }
            right_parentheses_numbers++;
        } else if (expression_string[i] == 'P') {
            if (i < expression_string.size() - 1) {
                if (expression_string[++i] == 'I') {

                } else {
                    no_invalid_character = 0;
                    break;
                }
            } else {
                no_invalid_character = 0;
                break;
            }
        } else {
            cout << "wrong number:" << expression_string[i] << endl;
            valid = 0;
            return;
        }
        //这里检查括号有没有成对出现
        if (right_parentheses_numbers > left_parentheses_numbers ||
            right_parentheses_numbers != left_parentheses_numbers && i == expression_string.size() - 1) {

            parentheses_in_pairs = 0;
            break;
        }
    }
    //这里检查输入的操作数是否是一个合法的数字或者e，或者PI；
    for (int i = 0; i < expression_string.size(); i++) {
        if (expression_string[i] >= '0' && expression_string[i] <= '9'
            || expression_string[i] == 'e' || expression_string[i] == 'E'
            || (i != 0 && expression_string[i - 1] == '(' &&
                (expression_string[i] == '+' || expression_string[i] == '-'))
            || (i == 0 && (expression_string[i] == '+' || expression_string[i] == '-'))
            || expression_string[i] == 'P' || expression_string[i] == 'I') {
            string num_string;
            int k = i;
            while (i < expression_string.size() && (expression_string[i] >= '0' && expression_string[i] <= '9'
                                                    || expression_string[i] == 'e' || expression_string[i] == 'E'
                                                    || expression_string[i] == '.'
                                                    || ((expression_string[i] == '+' || expression_string[i] == '-') &&
                                                        i == 0)
                                                    || (i != 0 && expression_string[i - 1] == '(' &&
                                                        (expression_string[i] == '+' ||
                                                         expression_string[i] == '-')) //有括号包起来的正负数
                                                    || ((expression_string[i] == '+' || expression_string[i] == '-') &&
                                                        i != 0 && (expression_string[i - 1] == 'e' ||
                                                                   expression_string[i - 1] == 'e'))
                                                    || expression_string[i] == 'P' || expression_string[i] == 'I')) {
                num_string += expression_string[i];
                i++;
            }
            if (k != i) {
                i--;
            }
            num num_operand(num_string);


            if (num_operand.type == 0) {
                correctly_input_operands = 0;
                break;
            }
        }
    }
    valid = parentheses_in_pairs * correctly_use_parentheses * no_consecutive_operators * no_invalid_character *
            correctly_input_operands;
}

string OperateAFunction(string &expression_string, bool &valid) {
    int left_parentheses_count = 0, right_parentheses_count = 0, equal_sign_index = -1, equal_sign_count = 0;
    for (int i = 0; i < expression_string.size(); i++) {
        if (expression_string[i] == '(') {
            left_parentheses_count++;
        } else if (expression_string[i] == ')' && i + 1 < expression_string.size() && expression_string[i + 1] == '=') {
            right_parentheses_count++;
        } else if (expression_string[i] == '=') {
            equal_sign_index = i;
            equal_sign_count++;
        }
        //括号顺序不对
        if (right_parentheses_count > left_parentheses_count) {
            valid = false;
            return "";
        }
    }
    //括号成对出现，等号只有一个，且不在最后
    if (right_parentheses_count != left_parentheses_count || equal_sign_count != 1 ||
        expression_string[expression_string.size() - 1] == '=') {
        valid = false;
        return "";
    }
    vector<string> string_vec;
    string key_string;
    for (int i = 2; i <= equal_sign_index; i++) {
        if (expression_string[i] != ',' && expression_string[i] != ')') {
            key_string += expression_string[i];
        } else {
            string_vec.push_back(key_string);
            key_string = "";
        }
    }
    string num_value_string;
    getline(cin, num_value_string);
    //检查格式；
    if (num_value_string[0] != 'f' && num_value_string[0] != 'F') {
        valid = false;
        return "";
    }
    for (int i = 0; i < num_value_string.size(); i++) {
        if (num_value_string[i] == '(' && i != 1 || num_value_string[i] != '(' && i == 1) {
            valid = false;
            return "";
        } else if (num_value_string[i] == ')' && i != num_value_string.size() - 1 ||
                   num_value_string[i] != ')' && i == num_value_string.size() - 1) {
            valid = false;
            return "";
        } else if (num_value_string[i] == '=') {
            valid = false;
            return "";
        }
    }
    //将数值存起来
    vector<num> num_vec;
    string value_string;
    for (int i = 2; i < num_value_string.size(); i++) {
        if (num_value_string[i] != ',' && num_value_string[i] != ')') {
            value_string += num_value_string[i];
        } else {
            num n1(value_string);
            num_vec.push_back(n1);
            value_string = "";
        }
    }
    //两个vector要有相同的长度；
    if (num_vec.size() != string_vec.size()) {
        valid = false;
        return "";
    } else {
        //存起函数表达式：
        string function_expression = expression_string.substr(equal_sign_index + 1);
        map<string, num> variable_map;
        for (int i = 0; i < num_vec.size(); i++) {
            variable_map.insert(make_pair(string_vec[i], num_vec[i]));
        }
        string maybe_variable, final_expression;
        for (int i = 0; i < function_expression.size(); i++) {
            if (!IsSign(function_expression[i])) {
                maybe_variable += function_expression[i];
            } else {
                if (!maybe_variable.empty()) {
                    if (variable_map.count(maybe_variable) <= 0) {
                        CheckExpressionValidity(maybe_variable, valid);
                        //如果表达式不合法；
                        if (!valid) {
                            return "";
                        } else {
                            final_expression += maybe_variable;
                            maybe_variable = "";
                        }
                    } else {
                        num n1 = variable_map.find(maybe_variable)->second;
                        final_expression += "(";
                        final_expression += (n1.sign == 1 ? "" : "-") + n1.absolute_num_string + ")";
                        maybe_variable = "";
                    }
                }
                final_expression += function_expression[i];
            }
        }
        if (!maybe_variable.empty()) {
            if (variable_map.count(maybe_variable) <= 0) {
                CheckExpressionValidity(maybe_variable, valid);
                //如果表达式不合法；
                if (!valid) {
                    return "";
                } else {
                    final_expression += maybe_variable;
                    maybe_variable = "";
                }
            } else {
                num n1 = variable_map.find(maybe_variable)->second;
                final_expression += "(";
                final_expression += (n1.sign == 1 ? "" : "-") + n1.absolute_num_string + ")";
                maybe_variable = "";
            }
        }
        num result = OperateAnExpression(final_expression, valid);
        return ((result.sign == -1 ? "-" : "") + result.absolute_num_string);

    }
}

void OperateAnExpressionWithVariables(string &expression_string, bool &valid) {
    string copied_expression_string = expression_string;
    //判断是一个等号还是多个等号；
    int equal_sign_num = 0, last_equal_sign_index = -1;
    for (int i = 0; i < copied_expression_string.size(); i++) {
        if (copied_expression_string[i] == '=') {
            equal_sign_num++;
            last_equal_sign_index = i;
        }
    }
    map<string, num> variable_map;
    if (equal_sign_num == 1) {
        int left_index = 0, right_index = last_equal_sign_index + 1;
        while (true) {
            string variable_key_string, variable_value_string;
            for (; copied_expression_string[left_index] != ',' &&
                   copied_expression_string[left_index] != '='; left_index++) {
                variable_key_string += copied_expression_string[left_index];
            }
            if (copied_expression_string[left_index] == ',') {
                left_index++;
            }
            for (; right_index < copied_expression_string.size() &&
                   copied_expression_string[right_index] != ','; right_index++) {
                variable_value_string += copied_expression_string[right_index];
            }
            if (copied_expression_string[right_index] == ',') {
                right_index++;
            }
            num value_num(variable_value_string);
            if (variable_map.count(variable_key_string) > 0 || value_num.type == 0) //如果变量重复赋值
            {
                valid = false;
                return;
            } else {
                variable_map.insert(make_pair(variable_key_string, value_num));
            }
            if (copied_expression_string[left_index] == '=' && right_index == copied_expression_string.size()) {
                break;
            } else if (copied_expression_string[left_index] == '=' ^
                       right_index == copied_expression_string.size()) //如果变量个数和值的个数不相等；
            {
                valid = false;
                return;
            }
        }
    } else {
        //保证等于号后面还有东西
        if (last_equal_sign_index == copied_expression_string.size() - 1) {
            valid = false;
            return;
        } else {
            string value_string = copied_expression_string.substr(last_equal_sign_index + 1);
            //检验该值合法不合法
            num value_num(value_string);
            if (value_num.type == 0) {
                valid = false;
                return;
            } else {
                int find_key_index = 0;
                while (find_key_index < last_equal_sign_index) {
                    string key_string;
                    for (; copied_expression_string[find_key_index] != '='; find_key_index++) {
                        key_string += copied_expression_string[find_key_index];
                    }
                    if (copied_expression_string[find_key_index] == '=') {
                        find_key_index++;
                    }
                    if (variable_map.count(key_string) > 0) //如果变量重复赋值
                    {
                        valid = false;
                        return;
                    } else {
                        num copied_value_num = value_num;
                        variable_map.insert(make_pair(key_string, copied_value_num));
                    }
                }
            }
        }
    }

//多次重复输入：
    string new_expression_string;
    while (true) {
        getline(cin, new_expression_string);
        int new_equal_sign_num = 0, new_last_equal_sign_index = -1;
        for (int i = 0; i < new_expression_string.size(); i++) {
            if (new_expression_string[i] == '=') {
                new_equal_sign_num++;
                new_last_equal_sign_index = i;
            }
        }
        //如果没有等号就break;
        if (new_last_equal_sign_index == -1) {
            break;
        }
        if (new_equal_sign_num == 1) {
            int left_index = 0, right_index = new_last_equal_sign_index + 1;
            while (true) {
                string variable_key_string, variable_value_string;
                for (; new_expression_string[left_index] != ',' &&
                       new_expression_string[left_index] != '='; left_index++) {
                    variable_key_string += new_expression_string[left_index];
                }
                if (new_expression_string[left_index] == ',') {
                    left_index++;
                }
                for (; right_index < new_expression_string.size() &&
                       new_expression_string[right_index] != ','; right_index++) {
                    variable_value_string += new_expression_string[right_index];
                }
                if (new_expression_string[right_index] == ',') {
                    right_index++;
                }
                num value_num(variable_value_string);
                if (variable_map.count(variable_key_string) > 0 || value_num.type == 0) //如果变量重复赋值
                {
                    valid = false;
                    return;
                } else {
                    variable_map.insert(make_pair(variable_key_string, value_num));
                }
                if (new_expression_string[left_index] == '=' && right_index == new_expression_string.size()) {
                    break;
                } else if (new_expression_string[left_index] == '=' ^
                           right_index == new_expression_string.size()) //如果变量个数和值的个数不相等；
                {
                    valid = false;
                    return;
                }
            }
        } else {
            //保证等于号后面还有东西
            if (new_last_equal_sign_index == new_expression_string.size() - 1) {
                valid = false;
                return;
            } else {
                string value_string = new_expression_string.substr(new_last_equal_sign_index + 1);
                //检验该值合法不合法
                num value_num(value_string);
                if (value_num.type == 0) {
                    valid = false;
                    return;
                } else {
                    int find_key_index = 0;
                    while (find_key_index < new_last_equal_sign_index) {
                        string key_string;
                        for (; new_expression_string[find_key_index] != '='; find_key_index++) {
                            key_string += new_expression_string[find_key_index];
                        }
                        if (new_expression_string[find_key_index] == '=') {
                            find_key_index++;
                        }
                        if (variable_map.count(key_string) > 0) //如果变量重复赋值
                        {
                            valid = false;
                            return;
                        } else {
                            num copied_value_num = value_num;
                            variable_map.insert(make_pair(key_string, copied_value_num));
                        }
                    }
                }
            }
        }
    }
    //处理最终的表达式
    string maybe_variable, final_expression;
    for (int i = 0; i < new_expression_string.size(); i++) {
        if (!IsSign(new_expression_string[i])) {
            maybe_variable += new_expression_string[i];
        } else {
            if (!maybe_variable.empty()) {
                if (variable_map.count(maybe_variable) <= 0) {
                    CheckExpressionValidity(maybe_variable, valid);
                    //如果表达式不合法；
                    if (!valid) {
                        return;
                    } else {
                        final_expression += maybe_variable;
                        maybe_variable = "";
                    }
                } else {
                    num n1 = variable_map.find(maybe_variable)->second;
                    final_expression += "(";
                    final_expression += (n1.sign == 1 ? "" : "-") + n1.absolute_num_string + ")";
                    maybe_variable = "";
                }
            }
            final_expression += new_expression_string[i];
        }
    }
    if (!maybe_variable.empty()) {
        if (variable_map.count(maybe_variable) <= 0) {
            CheckExpressionValidity(maybe_variable, valid);
            //如果表达式不合法；
            if (!valid) {
                return;
            } else {
                final_expression += maybe_variable;
                maybe_variable = "";
            }
        } else {
            num n1 = variable_map.find(maybe_variable)->second;
            final_expression += "(";
            final_expression += (n1.sign == 1 ? "" : "-") + n1.absolute_num_string + ")";
            maybe_variable = "";
        }
    }
    num result = OperateAnExpression(final_expression, valid);
    cout << (result.sign == -1 ? "-" : "") << result.absolute_num_string << endl;
}

bool IsSign(char c) {
    bool is_sign = (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '(' || c == ')');
    return is_sign;
}