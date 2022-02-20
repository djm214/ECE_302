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
  int index = 2;            //offset from variables to operator

  for(int i = 0; i < postfix.size(); i++)
  {
    switch(postfix.at(i))
    {
      case '+':  //case for all operators
      case '-':
      case '*':
      case '/':

        operatorStack.push_back(postfix.at(i)); //adds the operator to the operatorStack

        //if there are multiple operators in a row, parnthasis are involved
        if(postfix.at(i+1) == '+' ||postfix.at(i+1) == '-' ||postfix.at(i+1) == '*' ||postfix.at(i+1) == '/')
        {
          postfix.push_back('(');             //add a starting parenthasis
          prefix.push_back(postfix.at(i-2));  //add a
          while(postfix.at(i+1) == '+' ||postfix.at(i+1) == '-' ||postfix.at(i+1) == '*' ||postfix.at(i+1) == '/')
          {
            prefix.push_back(postfix.at(i));
            prefix.push_back(postfix.at(i - index));
            index = index*2;
            i++;
          }
          prefix.push_back(postfix.at(i));
          prefix.push_back(postfix.at(i - index));

          index = 2;

          prefix.push_back(')');
        }
        
      break;

      default: 

      prefix.push_back(i);

      break;
    }
  }

/*
  while(operandStack.size() != 0) //while the size of the operand stack is nonzero
  {
   
    prefix.push_back(operandStack.front());  //pushback the last element of the operand Stack

    if(operatorStack.size() != 0)
    {
      prefix.push_back(operatorStack.back()); //pushback the last element of the operator Stack
      operatorStack.pop_back(); //check to make sure the operandStack size is nonzero before using pop_back
    }
    operandStack.pop_back(); //already evaluated if non-zero in the while loop
    
  }
*/

}
