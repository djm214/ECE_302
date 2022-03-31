#include "bitset.hpp"

  
  Bitset::Bitset() //Default Constructor
  { 
    N = 8; //sets size to 8
    data = new char[N];

    for(intmax_t i = 0; i < N; i++)
    {
      data[i] = '0'; //fills the array with 0's
    }
    validity = true;
  }

  
  Bitset::Bitset(intmax_t size) // Constructor with size perameters
  {
    validity = true; //initializes validity to true, re-evaluated later
    N = size; //sets size to specific value
    data = new char[N]; //allocation

    if(N <= 0)
    {
      validity = false; //sets the data as invalid if N<=0
    } 

    for(intmax_t i = 0; i < N; i++)
    {
      data[i] = '0'; //fills array of size with zeros FROM RIGHT TO LEFT!!!
    }
  }

  
  Bitset::Bitset(const std::string & value) // Constructor that initializes the value with string in the form "00010000"
  {
      /*
      validity = true; //initializes validity to true, re-evaluated later

      N = value.length(); //set length of array to the length of the input string
      for(intmax_t i = (N-1); i >= 0; --i)
      {
          if((value[i] != '0') && (value[i] != '1')) //if any character is not 0 or 1, the set is invalid
          {validity = false;}
          val[i] = value[(N-1) - i]; //copy string to array FROM RIGHT TO LEFT!!!
      }
      */
  }

  Bitset::~Bitset() 
  {
      delete [] data; //deletes data pointer
  } //Simple destructor

  //Should only return the private variable N
  intmax_t Bitset::size() const
  {
      return N; //returns the size N variable
  }

  //Determines if the data is usable/good
  bool Bitset::good() const
  {
      return (validity == true);
  }

  //Sets the value at index to 1
  void Bitset::set(intmax_t index)
  {
      /*
      if((index > (N-1)) || (index < 0)) //if index doesnt fall in [0,N-1] it is invalid
      { validity = false; }

      val[index] = '1'; //set to 1
      */
  }

  //Sets the value at index to 0
  void Bitset::reset(intmax_t index)
  {
      /*
      if((index > (N-1)) || (index < 0)) //if index doesnt fall in [0,N-1] it is invalid
      { validity = false; }

      val[index] = '0'; //reset to 0
      */
  }

  //Toggles the bit at index
  void Bitset::toggle(intmax_t index)
  {
      /*
      if((index > (N-1)) || (index < 0)) //if index doesnt fall in [0,N-1] it is invalid
      { validity = false; }

      if(val[index] == '1') //if it was 1, change to 0
      {
        val[index] = '0'; //reset to 0
      } else if(val[index] == '0') //if it was 0, change to 1
      {
        val[index] = '1'; //set to 1
      }
      */
  }

  //Checks to see if the bit at index is 1
  bool Bitset::test(intmax_t index)
  {
      /*
      if((index > (N-1)) || (index < 0)) //if index doesnt fall in [0,N-1] it is invalid
      { validity = false; }
      
      return(val[index] == '1');
      */
  }

  //Stores value of array as a string
  std::string Bitset::asString() const
  {
      /*
      std::string rep;
      
      for(intmax_t i = (N-1); i >= 0; i--)
      {
          rep = rep + val[i];
      }

      return rep;
      */
  }