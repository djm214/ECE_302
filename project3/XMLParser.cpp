// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	tokenized = false; //sets the bools to initially false
	parsed = false;
	elementNameBag = new Bag<std::string>; //allocates memory for instances of the private classes
	parseStack = new Stack<std::string>;
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
	delete elementNameBag; //delete allocated memory for the two classes
	delete parseStack;
	clear(); //calls the clear function for destruction
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	clear(); //this will ensure that the vector is empty and not tainted from previous runs

	//---------------------------------------------------------------------------------------
	//--------------------------------Begin Checks/Tests-------------------------------------
	//---------------------------------------------------------------------------------------

	std::string copyString = inputString; //creates a mutable version of the input string
	int ammount_of_spaces = 0; //will track the ammount of white spaces

	if(copyString.empty())
	{
		clear();
		return false; //if the string is empty, tokenizer fails
	}

	for(int i = 0; i < copyString.length(); i++)
	{
		if(isspace(copyString[i]))
		{
			ammount_of_spaces++; //increases the ammount of white spaces
		}
	}

	if(ammount_of_spaces == copyString.length())
	{
		clear(); //make sure that the vector is cleared per project guidelines
		return false; //tokenizing fails if there is only whitespace
	}

	//---------------------------------------------------------------------------------------
	//--------------------------------Begin Tokenization-------------------------------------
	//---------------------------------------------------------------------------------------

	bool tag = false; //determines if the XML is a tag or not
	std::string element,content,plain_name; //will hold the strings fro mrkup elements and content and the name of a tag with no attributes

	for(int j = 0; j < copyString.length(); j++)
	{
		if(copyString[j] == '<')
		{
			if(copyString[copyString.length() - 1] != '>') //property given in project description
			{
				clear();
				return false; //false due to not following proper properties
			}

			if((content.length() != 0) && (isspace(content[0]) == false)) //this occurs only when content is full and the first char is non space
			{
				TokenStruct content_to_be_pushed; //TokenStruct for CONTENT type
				content_to_be_pushed.tokenString = content; //set content string into the tokenString
				content_to_be_pushed.tokenType = CONTENT; //set the type to content

				tokenizedInputVector.push_back(content_to_be_pushed);
			}

			content.clear(); //clears the content string

			element.push_back('<'); //push < onto the string
			tag = true;
			continue;
		}
		else if(copyString[j] == '>')
		{
			element.push_back('>'); //push > onto the string

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

			for(int m = 0; m < plain_name.length(); m++)
			{
				if(plain_name[m] == '!' || plain_name[j] == '\"' || plain_name[j] == '#' || plain_name[j] == '$' 
					|| plain_name[m] == '%' || plain_name[j] == '&' || plain_name[j] == '\'' || plain_name[j] == '('
					|| plain_name[m] == '=' || plain_name[j] == '?' || plain_name[j] == '@' || plain_name[j] == '\\'
					|| plain_name[m] == '[' || plain_name[j] == ']' || plain_name[j] == '^' || plain_name[j] == '`'
					|| plain_name[m] == '|' || plain_name[j] == '{' || plain_name[j] == '}' || plain_name[j] == '~'
					|| plain_name[m] == ')' || plain_name[j] == '*' || plain_name[j] == '+' || plain_name[j] == ','
					|| plain_name[m] == '/' || plain_name[j] == ';' || plain_name[j] == '<' || plain_name[j] == '>')
				{
					clear();
					return false; //checking for illegal characters
				}
			}
			
			elementNameBag->add(plain_name); //add the name to the bag after passing all tests

			TokenStruct to_be_pushed; //a token struct that will be pushed onto the vector

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
				if(element[element.length() - 2] == '?')
				{
					clear();
					return false; //tokenization fails due to not having 2 question marks
				}
			}

			to_be_pushed.tokenString = plain_name; //add the name to the token

			tag = false; //reset tag bool to false
			element.clear();
			plain_name.clear(); //clear both element and plain_name strings

			continue; //continue to the next letter
		}

		//Begin tests that happen on a per letter basis

		if(tag == false && copyString[j] == '>')
		{
			clear();
			return false; //tokenization fails due to no matching < since it is not a tag
		}

		if(tag && copyString[j] == '<')
		{
			clear();
			return false; //tokenizing fails due to nested <
		}

		if(tag)
		{
			element.push_back(copyString[j]); //if the item IS a tag
		}
		else
		{
			content.push_back(copyString[j]); //if the item is content, append to content string
		}
	}

	tokenized = true; //set tokenized to true
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
	if(tokenized) //only continue if the string has been successfully tokenized
	{
		std::string previous,current; //creates 2 TokenStruct variables
		parsed = true; //sets the parsed variable to true
		for(int i = 0; i < tokenizedInputVector.size(); i++)
		{
			if(i == 0)
			{
				parseStack->push(tokenizedInputVector[i].tokenString); //pushed first vector element onto stack
				continue; //skip to next
			}
			if(tokenizedInputVector[i].tokenType != START_TAG || tokenizedInputVector[i].tokenType != END_TAG)
			{
				continue; //if the token is not a start or end tag, skip it
			}

			previous = parseStack->peek(); //look at what is already on the stack and store it

			parseStack->push(tokenizedInputVector[i].tokenString);

			current = parseStack->peek(); //look at what is now currently on the stack after a successful push

			if(current == previous)
			{
				if(!parseStack->pop())
				{
					parsed = false;
					return false; //if pop fails, return false
				}
				if(!parseStack->pop())
				{
					parsed = false;
					return false; //if the second pop fails return false
				}
			}
		}

		if(parseStack->isEmpty())
		{
			return true; //tests passed
		}
		else
		{
			parsed = false; //set parsed to false 
			return false;
		}
	}
	else
	{
		return false; //tokenization failed, so this cannot procceed
	}
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	tokenizedInputVector.clear(); //clears the tokenizedInputVector private variable
	elementNameBag->clear(); //clears items stored in the bag
	parseStack->clear(); //clears items stored in the stack

	tokenized = false; //re-sets the bools to be false
	parsed = false;
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector; //simply returns the tokenized input vector
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	if(tokenized && parsed)
	{
		return elementNameBag->contains(inputString); //returns a bool of true if the inputString is in the name bag
	}
	else
	{
		return false; //returns false if the tokenizing or parsing failed
	}
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	if(tokenized && parsed)
	{
		return elementNameBag->getFrequencyOf(inputString); //calls the getFrequency Bag function
	}
	else
	{
		return false; //returns false if the tokenizing or parsing failed
	}
}

