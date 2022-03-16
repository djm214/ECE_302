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
	//--------------------------------Begin Checks/Tests-------------------------------------
	//---------------------------------------------------------------------------------------

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

	if(copyString[0] != '<' || copyString[copyString.length() - 1] != '>')
	{
		clear();
		return false; //if the first and last characters are not '<' and '>' respectively, tokenizing fails
	}

	//---------------------------------------------------------------------------------------
	//--------------------------------Begin Tokenization-------------------------------------
	//---------------------------------------------------------------------------------------

	bool tag = false; //determines if the XML is a tag or not
	std::string element,content,plain_name; //will hold the strings fro mrkup elements and content and the name of a tag with no attributes
	TokenStruct to_be_pushed; //a token struct that will be pushed onto the vector

	for(int j = 0; j < copyString.length(); j++)
	{
		if(copyString[j] == '<')
		{
			element.push_back('<'); //push < onto the string
			tag = true;
			continue;
		}
		else if(copyString[j] == '>')
		{
			element.push_back('>'); //push > onto the string

			int startCount = 0;
			int endCount = 0;

			for(int k = 0; k < copyString.length(); k++)
			{
				if(copyString[k] == '<')
				{
					startCount++; //increases the count of < 
				}
				if(copyString[k] == '>')
				{
					endCount++; //increases the count of >
				}
				if(startCount > 1 || endCount > 1)
				{
					clear();
					return false; //nested brackets
				}
			}

			switch(element[1])
			{
				case '/':

				if(element[element.length() - 2] == '/')
				{
					clear(); 
					return false; //tokenizer fails if </.../> is true, since this is invalid
				}
				else
				{
					to_be_pushed.tokenType = END_TAG; //if in the form of </...> it is an end tag
				}

				break;

				case '?':

				if(element[element.length() - 2] != '?')
				{
					clear();
					return false; //if the declaration is missing a ?
				}
				else
				{
					to_be_pushed.tokenType = DECLARATION; //<?...?> is Declaration form
				}

				break;

				default:

				if(element[element.length() - 2] == '/')
				{
					to_be_pushed.tokenType = EMPTY_TAG; //<.../> is Empty tag form
				}
			}

			for(int l = 1; l < element.length(); l++) //this will copy the plain name to a string plain_name
			{
				if(element[l] !=  ' ' && element[l] != '>') //as long as the character isn't a space or >, add to the plain_name string
				{
					if((l == element.length() - 2) && ((element[l] == '/') || (element[l] == '?'))) 
					{
						break; //skip the '/' or '?' if the element is an empty_tag or declaration
					}
					if((l == 1) && ((element[l] == '/') || (element[l] == '?'))) 
					{
						continue; //exclude the '/' or '?' if the element is a declaration or if the element is an end tag
					}
					plain_name.push_back(element[l]);
				}
				else
				{
					break;
				}
			}

			if(plain_name.empty())
			{
				clear();
				return false; //tokenizing fails here by empty name
			}

			if(plain_name[0] == '0' || plain_name[0] == '1' || plain_name[0] == '2' || plain_name[0] == '3' || plain_name[0] == '4' || plain_name[0] == '5' || plain_name[0] == '6' || plain_name[0] == '7' || plain_name[0] == '8' || plain_name[0] == '9' || plain_name[0] == '-' || plain_name[0] == '.') 
			{
				clear();
				return false; //tokenizing fails here by bad begining character
			}
			
		}

		if(tag)
		{
			element.push_back(copySting[j]); //if the item IS a tag
		}
		else
		{
			content.push_back(copySting[j]); //if the item is content, append to content string
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

