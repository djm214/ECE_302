#ifndef BITSET_HPP
#define BITSET_HPP
#include <string>

class Bitset{
public:

  // Default Constructor
  Bitset();

  // Constructor with size perameters
  Bitset(intmax_t size);

  // Constructor that initializes the value with string in the form "00010000"
  Bitset(const std::string & value);

  // Default Destructor
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete; //only functions to not make class copy-able

  //Should only return the private variable N
  intmax_t size() const;

  //Determines if the data is usable/good
  bool good() const;
  
  //Sets the value at index to 1
  void set(intmax_t index);

  //Sets the value at index to 0
  void reset(intmax_t index);

  //Toggles the bit at index
  void toggle(intmax_t index);

  //Checks to see if the bit at index is 1
  bool test(intmax_t index);

  //Returns the BitSet as a string of characters
  std::string asString() const;

  static const intmax_t MAXLENGTH = 20; /**I define the max number of bits to be 20 here */

private:

  intmax_t N; /**Here, I declare N as the size of the array*/
  char val[MAXLENGTH]; /**Here, I declare an array of characters
                         That will serve as the binary value*/
  bool validity; //this will be used to track if the data is valid
  
};

#endif
