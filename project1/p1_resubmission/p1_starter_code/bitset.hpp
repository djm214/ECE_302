#ifndef BITSET_HPP
#define BITSET_HPP
#include <string>

class Bitset{
public:

  //Default Constructor
  Bitset();

  // Constructor with size perameters
  Bitset(intmax_t size);

  // Constructor that initializes the value with string in the form "00010000"
  Bitset(const std::string & value);

  //Simple destructor
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

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

  //Stores value of array as a string
  std::string asString() const;

private:

  intmax_t N; /**Here, I declare N as the size of the array*/
  char * data; //pointer to an array
  bool validity; //this will be used to track if the data is valid
};

#endif
