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
  string operandStack;      //creates a stack for the operands
  string copyPrefix;
  int size;

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

  while(operandStack.size() != 0) //while the size of the operand stack is nonzero
  {
    copyPrefix.push_back(operandStack.back());  //pushback the last element of the operand Stack

    if(operatorStack.size() != 0)
    {
      copyPrefix.push_back(operatorStack.back()); //pushback the last element of the operator Stack
      operatorStack.pop_back(); //check to make sure the operandStack size is nonzero before using pop_back
    }
    operandStack.pop_back(); //already evaluated if non-zero in the while loop
  }

  while(copyPrefix.size() != 0)
  {
    prefix.push_back(copyPrefix.back());
    copyPrefix.pop_back();
  } 
  
}
