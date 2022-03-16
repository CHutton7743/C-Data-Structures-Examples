#ifndef BIG_INTEGER_CPP
#define BIG_INTEGER_CPP
#include "BigInteger.h"

using namespace std;

class IllegalArgumentException
{
  public:

    string what() const throw()
    {
      return "Input must only contain numbers and '-'";
    }
};

// default constructor
BigInteger::BigInteger()
          : DoublyLinkedList<int>(), negative(false)
{
}
// string constructor
BigInteger::BigInteger(const string & input)
          : DoublyLinkedList<int>(), negative(input[0] == '-')

  // try catch block to test if the input is valid
{
  try
  {
    if(!isDigits(input))
    {
      throw IllegalArgumentException();
    }
  }
  catch(const IllegalArgumentException& e)
  {
    cout << e.what() << '\n';
    return;
  }

  for(int i = 0; i < input.length(); i++)
  {
    if(i == 0 && input.at(i) == '-')
    {
      continue;
    }
    int digit = input.at(i) - '0';
    insertLast(digit);
  }
}

// copy constructor
BigInteger::BigInteger(const BigInteger & input)
          : DoublyLinkedList<int>(), negative(input.negative)
{
  Node<int>* runner = input.first;
  for(int i = 0; i < input.length; i++)
  {
    insertLast(runner->data);
    runner = runner->next;
  } 
}

// destructor
BigInteger::~BigInteger()
{
   while(iterator != NULL)
  {
    iterator = last->next;
    delete last;
    last = iterator;
  }
}

// returns if the big int is negative or not
bool BigInteger::isNegative()
{
  return negative;
}

// overides the = operator to set this big int = to the input big int
BigInteger BigInteger::operator=(const BigInteger & input)
{
  if(length > 0)
  {
    clear();
  }
  Node<int>* output = input.first;
  for(int i = 0; i < input.length; i++)
  {
    insertLast(output->data);
    output = output->next;
  }
  return *this;
}

// overrides the + operator to add two big ints together. checks corner cases for - or + numbers.
BigInteger BigInteger::operator+(BigInteger & RHS)
{
  if(negative && !RHS.negative)
  {
    BigInteger left(*this);
    left.negative = false;
    if(left == RHS)
    {
      BigInteger output("0");
      return output;
    }

    if(left > RHS)
    {
      BigInteger output = left - RHS;
      output.negative = true;
      return output;
    }

    BigInteger output = RHS - left;
    output.negative = false;
    return output;
  }

  if(!negative && RHS.negative)
  {
    BigInteger right(RHS);
    right.negative = false;
    if(*this == right)
    {
      BigInteger output("0");
      return output;
    }

    if(*this < right)
    {
      BigInteger output = right - *this;
      output.negative = true;
      return output;
    }

    BigInteger output = *this - RHS;
    output.negative = false;
    return output;
  }

  BigInteger output;
  RHS.setIteratorLast();
  setIteratorLast();

  int carry = 0;
  int result = 0;

  while(!RHS.isIteratorNULL() || !isIteratorNULL())
  {
    int left = 0;
    int right = 0;
    if(!RHS.isIteratorNULL())
    {
      right = RHS.getData();
    }
    if(!isIteratorNULL())
    {
      left = getData();
    }
    result = right + left + carry;
    output.insertFirst(result%10);
    if(result >= 10)
    {
      carry = 1;
    }
    else
    {
      carry = 0;
    }

    if(!RHS.isIteratorNULL())
    {      
      RHS.prev();
    }
    if(!isIteratorNULL())
    {
      prev();
    }
    result = 0;
  }
  
  if(carry == 1)
  {
    output.insertFirst(1);
  }

  if(negative && RHS.negative)
  {
    output.negative = true;
  }

  return output;

  /*
  set both iterators to end of list (ones place)
  int carry = 0;
  while(either number exists)
    add numbers together plus carry
    push result%10
    if(result > 10)
      carry = 1;
      recursiveFunction(carry = 1)
  if(carry = 1)
    insertFront(1);
  */
}

// overrides the - operator to subtracts 1 big int from the other one. Checks corner cases for - or + numbers.
BigInteger BigInteger::operator-(BigInteger & RHS)
{
  if(*this == RHS)
  {
    BigInteger output("0");
    return output;
  }

  if(negative && RHS.negative)
  {
    if(*this == RHS)
    {
      BigInteger output("0");
      return output;
    }

    BigInteger left(*this);
    left.negative = false;
    BigInteger right(RHS);
    right.negative = false;

    if(left > right)
    {
      BigInteger output = left - right;
      output.negative = true;
      return output;
    }

    if(left < right)
    {
      cout << "*this > RHS" << endl;
      BigInteger output = right - left;
      return output;
    }
  }

  //start of extra code
  if(negative && !RHS.negative)
  {
    BigInteger left(*this);
    left.negative = false;

    BigInteger output = left + RHS;
    output.negative = true;
    return output;
  }

  if(!negative && RHS.negative)
  {
    BigInteger right(RHS);
    right.negative = false;

    BigInteger output = *this + right;
    output.negative = false;
    return output;
  }
  //end of extra code

  BigInteger output;
  int result = 0;

  if(RHS > *this)
  {
    output = RHS - *this;
    output.negative = true;
    return output;
  }

  setIteratorLast();
  RHS.setIteratorLast();

  while(!RHS.isIteratorNULL() || !isIteratorNULL())
  {
    if(RHS.isIteratorNULL())
    {
      while(!isIteratorNULL())
      {
        output.insertFirst(getData());
        prev();
      }

      return output;
    }

    if(getData() < 0)
    {
      iterator->data += 10;
      iterator->prev->data -=1; //might overflow here
    }

    result = getData() - RHS.getData();
    if(result < 0)
    {
      result += 10;
      iterator->prev->data -= 1;
    }
      output.insertFirst(result);

    if(!RHS.isIteratorNULL())
    {      
      RHS.prev();
    }
    if(!isIteratorNULL())
    {
      prev();
    }
  }
  output.setIteratorFirst();
  while(output.getData() == 0)
  {
    output.deleteFirst();
  }
  return output;

  /*
  if(right > left)
    BigInteger output = right - left;
    output.negative = true;
    return output;
  set both iterators to end of list (ones place)
  int result = 0
  while(either iterator isn't null)
    if(this.data less than 0)
      this.data += 10  (double check these lines)
      this.prev.data -= 1 (if no prev.data, answer is negative)
    result = this.data - RHS.data
    if(result less than 0)
      result += 10
      this.prev.data -= 1
    
      
  */
}

// test to see if two big integers are equal and returns bool
bool BigInteger::operator==(BigInteger & input)
{
  if(input.negative != negative)
  {
    return false;
  }

  if(input.getLength() != getLength())
  {
    return false;
  }

  setIteratorFirst();
  input.setIteratorFirst();
  while(!isIteratorNULL() && !input.isIteratorNULL())
  {
    if(getData() != input.getData())
    {
      return false;
    }

    if(!hasNext() || !input.hasNext())
    {
      if((hasNext() && !input.hasNext()) || (!hasNext() && input.hasNext()))
      {
        return false;
      }
      break;
    }
    next();
    input.next();
  }

  return true;
}

// overrides the > operator and returns a bool once the testis performed
bool BigInteger::operator>(BigInteger & input)
{
  if(negative && !input.negative)
  {
    return false;
  }

  if(!negative && input.negative)
  {
    return true;
  }

  if(!negative && !input.negative && (length - input.length) != 0)
  {
    return (length - input.length) > 0;
  }

  if(negative && input.negative && (length - input.length) != 0)
  {
    return (length - input.length) < 0;
  }

  setIteratorFirst();
  input.setIteratorFirst();
  while(getData() == input.getData())
  {
    next();
    input.next();
  }

  if(negative && input.negative) // -90 < -80
  {
    return getData() < input.getData();
  }

  return getData() > input.getData();
}

// overrides the < operator that checks if the left is less than the right. returns bool.
bool BigInteger::operator<(BigInteger & input)
{
  if(negative && !input.negative)
  {
    return true;
  }

  if(!negative && input.negative)
  {
    return false;
  }

  if(!negative && !input.negative && (length - input.length) != 0)
  {
    return (length - input.length) < 0;
  }

  if(negative && input.negative && (length - input.length) != 0)
  {
    return (length - input.length) > 0;
  }

  setIteratorFirst();
  input.setIteratorFirst();
  while(getData() == input.getData())
  {
    next();
    input.next();
  }

  if(negative && input.negative)
  {
    return getData() > input.getData();
  }

  return getData() < input.getData();
}

// overrieds the >= which tests to see if the left bigint is greater than or equal to the right big int. returns bool.
bool BigInteger::operator>=(BigInteger & input)
{
  if(*this == input)
  {
    return true;
  }

  if(*this > input)
  {
    return true;
  }

  return false;
}

// tests the left big int to see if it is less than or equal to the right big int. returns bool.
bool BigInteger::operator<=(BigInteger & input)
{
  if(*this == input)
  {
    return true;
  }

  if(*this < input)
  {
    return true;
  }

  return false;
}

void BigInteger::print()
{
  if(isNegative())
  {
    cout << "- ";
  }
  setIteratorFirst();

  while(!isIteratorNULL())
  {
    cout << getData() << "->";
    next();
  }
  cout << "null" << endl;
  cout << "Is negative: " << negative << endl;
}

ostream& operator<<(ostream& os, BigInteger & input)
{
  if(input.isNegative())
  {
    os << '-';
  }

  input.setIteratorFirst();
  while(!input.isIteratorNULL())
  {
    os << input.getData();
    input.next();
  }
  return os;
}

// opens an ifstream to read the file and then turns the next line of the file into a string
// that string then gets passed into a BIGINT constructor and turned into a big int.
istream& operator>>(istream& is, BigInteger &input)
{
  ifstream myFile;
  myFile.open("test.txt");
  string myLine;
  if(myFile.is_open())
  {
    getline(myFile, myLine);
    is >> myLine;
    input = BigInteger(myLine);
  }
  else
  {
    cout << "Couldn't open file" << endl;
  }
  return is;
}

// helper function to determine if a valid input is being given to the constructors that contains only digits or -
bool BigInteger::isDigits(const string &input)
{
    return input.find_first_not_of("-0123456789") == string::npos;
}

#endif