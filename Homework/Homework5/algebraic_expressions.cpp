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
  string operandStack;   //creates a stack variable with a size of postfix
  string intermediate;            //creates an intermediate string value
  string operations;
  string parenthesisOpStack;
  bool parenthesisAdded = false;
  bool previousWasOp = false;
  int parenthesesInsertion = 0;

  for(int i = 0; i < postfix.size(); i++)
  {
    if(isoperator(postfix[i]))  //if the character within the index is an operator
    {
      operations.push_back(postfix[i]);

      if(previousWasOp && (i != (postfix.size()-1))) //if the last element was also an operator
      {
        operations.push_back(postfix[i]);       //adds the operation to an operationStack
        if(!parenthesisAdded)
        {
          intermediate.push_back('('); //if this is the first time entering this loop add a parenthesis
          parenthesisOpStack.push_back(postfix[i-1]); //add previous operation to a new stack
          operations.pop_back();
          parenthesesInsertion = i-1; //sets the insertion point for parentheses
          parenthesisAdded = true; //now a parenthesis has been added so set flag to true
        }

        bool whileLoopTracker = false;

        while(isoperator(postfix[i])) //while the previous character is an operator
        {
          parenthesisOpStack.push_back(postfix[i]); //load that operator into the operator stack
          i++; //increment i
          whileLoopTracker = true;
        } //this looop ultimate copies every adjacent operator into the operation stack

        if(whileLoopTracker)
        {
          i--; //decrements i once if it went through the while loop
               //this is because if the while loop failed, the character is NOT an operator
          whileLoopTracker = false; //resets flag to false
        }

        int origOpSize = parenthesisOpStack.size();

        while(parenthesisOpStack.size() != 0) //while the parenthesis stack is nonzero
        {
          intermediate.push_back(operandStack.at(operandStack.size() - parenthesisOpStack.size()-1)); //read in the first concerned variable, then the next until the end of the operand stack
         
          intermediate.push_back(parenthesisOpStack.back()); //pass in the last element of operations stack
          parenthesisOpStack.pop_back(); //delete that element
        }

        intermediate.push_back(operandStack.back());

        for(int k = origOpSize; k >= 0; k--)
        {
          operandStack.pop_back(); //erases the operands added to intermediate
        }

        if(parenthesisAdded)
        {
          intermediate.push_back(')'); //if there is no longer an operator directly after and a parenthesis was added, add a closing parenthesis
          parenthesisAdded = false; //now the parenthesisisAdded falg is rest to false
        }

        prefix.append(intermediate); //appends intermediate if it was updated
        intermediate.clear();
      }
      else
      {
        prefix.push_back(operations.back());
        operations.pop_back();

        prefix.push_back(operandStack.back());
        operandStack.pop_back();

        if(operandStack.size() != 0)
        {
          prefix.insert(prefix.begin(),operandStack.back());
          operandStack.pop_back();
        }

      }

      previousWasOp = true; //sets the previous was operator flag to one
      }
    else //if there was no operator
    {
      operandStack.push_back(postfix[i]);
      previousWasOp = false;
    }
  }
}
