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
	int size = inputString.size(); //store the size of the string
	int location,length; //will hold the location for variaous things throught the code
	char secondCharacter; //will be used to determine the tag type
	char element[100]; //will be used to hold the string version of a <> element up to 100 characters
	std::string copyString = inputString; //will contain a copied version
	std::string elementString;

	if(inputString[0] != '<' || inputString[size - 1] != '>')
	{
		return false; //if the first and last characters are not '<' and '>' respectively
	}

	while(copyString.size() != 0)
	{
		if(copyString[0] == '<') //this is a tag of SOME sort
		{
			location = copyString.find_first_of('>'); //find the location of the character '>'
			length = copyString.copy(element, location, 0); //copies the entire string to element
			element[length] = '\0';

			copyString.erase(copyString.begin(),copyString.begin() + length); //erases the copied portion

			int startCount = 0;
			int endCount = 0;

			elementString = element; //stores the element array in a string

			for(int i = 0; i < elementString.size(); i++)
			{
				if(element[i] == '<')
				{
					startCount++; //increment start count
				}
				else if(element[i] == '>')
				{
					endCount++; //increment end count
				}
			}

			if(startCount > 1 || endCount > 1)
			{
				clear();
				return false; //incorrect grammar
			}

			secondCharacter = element[1];

			switch(secondCharacter)
			{
				case '?':
				if(elementString[elementString.size()-2] == '?')
				{
					tokenizedInputVector.push_back(TokenStruct{StringTokenType::DECLARATION, std::string(elementString)}); //push back a token struct of DECLARATION
				}
				else
				{
					clear();
					return false;
				}
				break;

				case '/':

				tokenizedInputVector.push_back(TokenStruct{StringTokenType::END_TAG, std::string(elementString)}); //push back a token struct of END_TAG

				break;

				default:

				if(elementString[elementString.size()-2] == '/')
				{
					tokenizedInputVector.push_back(TokenStruct{StringTokenType::EMPTY_TAG, std::string(elementString)}); //push back a token struct of EMPTY_TAG
				}
				else
				{
					tokenizedInputVector.push_back(TokenStruct{StringTokenType::START_TAG, std::string(elementString)}); //push back a token struct of START_TAG
				}

			}


		}
		else //this mush be content
		{
			location = copyString.find_first_of('<'); //finds when the next element begins. This must be content
			location--; //dont want to copy the < in the copies string
			length = copyString.copy(element,location, 0); //copies to element
			element[length] = '\0';
			elementString = element;

			copyString.erase(copyString.begin(),copyString.begin() + length); //erases copied area

			for(int i = 0; i < elementString.size(); i++)
			{
				if(elementString[i] == '<' || elementString[i] == '>')
				{
					return false; //the grammar is incorrect
				}
			}

			tokenizedInputVector.push_back(TokenStruct{StringTokenType::CONTENT, std::string(elementString)}); //push backa token struct of CONTENT
		}
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

