#include <string>
using std::string;   //This code is using a namespace

#include <iostream>

#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix) 
{
  string operatorStack;     //creates a stack for the operators found
  string operandStack,operandStack2;      //creates a stack for the operands

  for(int i = 0; i < postfix.size(); i++)
  {
    switch(postfix.at(i))
    {
      case '+':  //case for all operators
      case '-':
      case '*':
      case '/':

      operatorStack.push_back(postfix.at(i)); //adds the operator to the operatorStack

      break;

      default: //if the character is not an operator, assume it is a variable

        operandStack.push_back(postfix.at(i)); //adds a prefix to the operandStack

      break;
    }
  }

  for(int i = 0; i < operandStack.size(); i++)
  {
    operandStack2.at(i) = operandStack.at(operandStack.size() - i); //reverses order of operand stack
  }

  operandStack = operandStack2; //sets operandStack equal to reversed operandStack

  while(operandStack.size() != 0) //while the size of the operand stack is nonzero
  {
    prefix.push_back(operandStack.front());  //pushback the last element of the operand Stack
    prefix.push_back(operatorStack.back()); //pushback the last element of the operator Stack

    if(operatorStack.size() != 0)
    {
      operatorStack.pop_back(); //check to make sure the operandStack size is nonzero before using pop_back
    }
    operandStack.pop_back(); //already evaluated if non-zero in the while loop
  }
  
}
