// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
	clear(); //calls the clear function for destruction
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	clear(); //this will ensure that the vector is empty and not tainted from previous runs

	//---------------------------------------------------------------------------------------
	//Begin Checks/Tests
	//--------------------------------------------------------------------------------------

	copyString = inputString; //creates a mutable version of the input string
	int ammount_of_spaces = 0; //will track the ammount of white spaces

	if(inputString.empty())
	{
		return false; //if the string is empty, tokenizer fails
	}

	for(int i = 0; i < copyString.length(); i++)
	{
		if(copyString[i] == " ")
		{
			ammount_of_spaces++; //increases the ammount of white spaces
		}
	}

	if(ammount_of_spaces == copyString.length())
	{
		clear(); //make sure that the vector is cleared per project guidelines
		return false; //tokenizing fails if there is only whitespace
	}

	if(copyString[0] != '<' || copyString[copySting.length() - 1] != '>')
	{
		clear();
		return false; //if the first and last characters are not '<' and '>' respectively, tokenizing fails
	}



	

	return true;

}  // end

// TODO: Implement a helper function to delete attributes from a START_TAG
// or EMPTY_TAG string (you can change this...)
static std::string deleteAttributes(std::string input)
{
	int found = input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	while(found!=std::string::npos)
	{
		input.erase(input.begin()+found); //erases element at the found location
		found = input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"); //re-evaluates found variable
	}
	return input;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	return false;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	return false;
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	return -1;
}

