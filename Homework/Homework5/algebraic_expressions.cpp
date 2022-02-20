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

  for(int i = 0; i < postfix.size(); i++)
  {
    switch(postfix.at(i))
    {
      case ("+" || "-" || "*" || "/") //case operator

      operatorStack.push_back(); //adds the operator to the operatorStack

      break;

      case("a"||"b"||"c"||"d"||"e"||"f"||"g"||"h"||"i"||"j"||"k"||"l"||"m"||"n"||"o"
           "p"||"q"||"r"||"s"||"t"||"u"||"v"||"w"||"x"||"y"||"z")

        prefix.push_back(); //adds a prefix to the operandStack

      break;
    }
  }

  while(operandStack.size()) //while the size of the operand stack is nonzero
  {
    
  }
  
}
