#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include <bits/stdc++.h>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

//Contact Troy if having troubles

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	if(!cutTest2(candidateStringVector,currentStringVector))
	{
		return; //if cutTest2 doesn't pass, there is no reason to continue, so leave the function
	}
	
	for(int i = 0; i < currentStringVector.size(); i++)
	{
		candidateStringVector.push_back(currentStringVector.at(i)); //adds an element to the candidateStringVector from the vector of available words
		currentStringVector.erase(currentStringVector.begin()+i); //erases element of currentStringVector at index i

		//recursive call that passed is candidateStringVector with an element i from the stringVector added to the vector with
		//that same element removed from the stringVector
		recursiveFindPalindromes(candidateStringVector,currentStringVector);

		//This basically undo's what I did before the recursive call i.e adding to candidateVector and removing from stringVector
		currentStringVector.insert(currentStringVector.begin()+i,candidateStringVector.back());
		candidateStringVector.pop_back();
	}

	if(currentStringVector.size() == 0) //base case
	{
		if(isPalindrome(candidateStringVector)) //if the unique candidate stringVector is a palindrome, add the vector to the vector of vectors
		{
			vectorofvectors.push_back(candidateStringVector); //adds the candidateStringVector to the vector of vectors
			num++; //increments number of palindromes included
		}
	}
}

// private function to determine if a string is a palindrome

//IT IS IMPORTANT TO NOTE HERE THAT I CHANGED THE ORIGINAL FUNCTION SO THAT THE FUNCTION IS ABLE
//TO CHANGE THE VECTOR INTO A SINGLE STRING VARIABLE FOR ME	

bool FindPalindrome::isPalindrome(std::vector<std::string> stringVector) const
{
	locale loc;
	std::string currentString; //this string will hold all of my words concatenated into one variable

	for(int i = 0; i < stringVector.size(); i++)
	{
		currentString += stringVector.at(i); //this will store every word in the vector into one string variable
	}

	// make sure that the string is lower case...
	convertToLowerCase(currentString);

	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	num = 0; //initializes number of palindromes to zero
}

FindPalindrome::~FindPalindrome()
{
}

int FindPalindrome::number() const
{
	return num; //returns the num variable that keeps track of the ammount of palindromes 
}

void FindPalindrome::clear()
{
	words.clear(); //this will clear the vector of all words added
	num = 0; //sets num equal to 0

	for(int i = 0; i < vectorofvectors.size(); i++)
	{
		vectorofvectors.erase(vectorofvectors.begin() + i); //erases the entirety of all palindromes stored in the vectorofvectors variable
	}
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	//odd number of characters can only appear once

	std::string totalString; //totalString is a modifiable version of stringVector

	int increment,evenChecker,oddCounter; //creates increment 
	char oddChar; //will contain the character that is odd
	oddCounter = 0;


	for(int k = 0; k <stringVector.size(); k++)
	{
		totalString += stringVector.at(k); //copies the values in the first vector into a modifiable string variable
	}

	convertToLowerCase(totalString); //converts the string to lowercase

	for(int i = 0; i < totalString.size(); i++)
	{
		if(totalString.at(i) != oddChar)
		{
			increment = std::count(totalString.begin(),totalString.end(),totalString.at(i)); //counts the occurence of the character at i

			evenChecker = increment % 2; //checks if count is divisible by 2

			if(evenChecker != 0) //if count % 2 is not 0, it is not even
			{
				if(oddCounter == 1)
				{
					return false; //if oddCounter is already 1, anothe element appears an odd ammount
				}

				oddChar = totalString.at(i); //sets the odd character to the oddChar variable
				oddCounter++; //increases the ammount of times an oddValue character appears in the vector
			}
		}
	}
	return true;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	std::string small,large,vect1,vect2;

	for(int i = 0; i < stringVector1.size(); i++)
	{
		vect1 += stringVector1.at(i); //stores all words in vector into one string
	}

	for(int i = 0; i < stringVector2.size(); i++)
	{
		vect2 += stringVector2.at(i); //stores all words in vector into one string
	}

	convertToLowerCase(vect1); //converts the concatenated vectors to lowercase
	convertToLowerCase(vect2);

	if(vect1.size() < vect2.size())
	{
		small = vect1; //smaller character (vect1 in this case) count stored in small
		large = vect2; //larger character (vect2 in this case) count stored in large
	}
	else
	{
		small = vect2; //smaller character (vect2 in this case) count stored in small
		large = vect1; //larger character (vect1 in this case) count stored in large
	}

	int count = 0; //this will hold the ammount of times a character appears in the small AND large strings

	for(int i = 0; i< small.size(); i++)
	{
		//small string loop
		for(int j = 0; j < large.size();j++)
		{
			//large string loop
			if(small[i] == large[j])
			{
				count++; //count is incremented by one if the small character is equal to a large character
			}
		}

		if(count == 0)
		{
			return false; //if there was no matching character in vectors 1 and 2
		}
		else
		{
			count = 0; //set count to zero
		}
	}
	return true;
}

bool FindPalindrome::add(const string & value)
{
	int found = value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	//above is a function that I found online that can find the position of the first time one of the
	//above characters is not included in the string

	std::vector<std::string> emptyVector; //an empty vector used int the recursive call

	std::string copyValue = value; //copies the value into a variable that can be changed so it can be plugged into changeToLowerCase() later
	convertToLowerCase(copyValue); //converts the value to lowercase

	std::string vectorCopyValue; //creates a string variable that will hold a copy of what words.at() will hold

	if(found != std::string::npos)
	{
		return false; //if the value of the function is not the end of the string, an illegal character was implemented
	}

	for(int i = 0; i < words.size(); i++)
	{
		vectorCopyValue = words.at(i); 
		convertToLowerCase(vectorCopyValue); //this will conver the value at words(i) to lowercase

		if(copyValue == vectorCopyValue) //combs entirety of words added into main vector already
		{
			return false; //makes sure that each new word is unique, disregaurding case sensitivity
		}
	}

	words.push_back(value); //adds the word to the vector

	if(cutTest1(words)) //only caluculate possible palindromes if cutTest1 passes
	{
		num = 0; //resets the number of palindromes found, so that it is re-evaluated with each add
		recursiveFindPalindromes(emptyVector,words); //calls the recursive function
	}

	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	int found;
	bool passed = true; //initializes a bool variable set to true, which is reevaluated for every word
	std::vector<std::string> emptyVector; //creates an empty vector to be used in the recursive call

	std::string copyValue,vectorCopyValue; //these contain modifiable copies of the values passed in through to the function

	for(int k = 0; k < stringVector.size(); k++)
	{
		copyValue = stringVector.at(k); //creates a copyValue that can be manipulated
		convertToLowerCase(copyValue);

		//below is an int variable that is set to the index of the first occurance of a non a-z or A-Z value
		found = copyValue.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

		if(found != std::string::npos) //if that variable is not the end string character, there was an illegal character involved
		{
			passed =  false; //if the value of the function is not the end of the string, an illegal character was implemented
		}

		for(int i = 0; i < words.size(); i++)
		{
			vectorCopyValue = words.at(i); 
			convertToLowerCase(vectorCopyValue); //this will conver the value at words(i) to lowercase

			if(copyValue == vectorCopyValue) //combs entirety of words added into main vector already
			{
				passed = false; //makes sure that each new word is unique, disregaurding case sensitivity
			}
		}
	}

	if(!passed)
	{
		return false; //if passed was evaluated false by any of the words, the test fails
	}
		
	for(int k = 0; k < stringVector.size(); k++)
	{
		words.push_back(stringVector.at(k)); //if and only if all words pass, append them to words private variable 
	}

	if(cutTest1(words)) //only caluculate possible palindromes if cutTest1 passes
	{
		num = 0; //resets the number of palindromes found, so that it is re-evaluated with each add
		recursiveFindPalindromes(emptyVector,words); //calls the recursive function
	}

	return true; //passes the test if passed is true
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return vectorofvectors; //returns the vector of vectors private variable
}
