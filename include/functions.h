#pragma once
#include <iostream>
#include <vector>
#include "num.h"
using namespace std;
void OperateManyTimes();
num OperateAnExpression(string & expression_string, bool &success);
string OperateAnExpressionWithoutParentheses(string  &expression_string, bool &success);
void CheckExpressionValidity(string & expression_string, bool &success);
string OperateAFunction(string &expression_string, bool & valid);
void OperateAnExpressionWithVariables(string &expression_string, bool & valid);
bool IsSign(char c);