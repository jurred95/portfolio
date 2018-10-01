//
// Started by Tom on 2/9/18.
//

#include "bigint.h"
#include <iostream>
#include <string>
#include <fstream>


void bigint::strip_zeros() {
//this function strips leading zeros off bigint
//loops running through size of number and asking if it is > 1 and if the
//back of the number == 0 then pop off the leading zeros until it is
//reached
while(number.size() > 1 && number.back() == 0){
    number.pop_back();
  }
}

/* Constructors
 *
 * */

bigint::bigint() {
  //this default constructor sets the constructor to zero
  //clearing the number vector
  number.clear();
  //pushing 0 into the number vector and setting it to a default value
  number.push_back(0);

}

bigint::bigint(const std::vector<vec_bin> &that) {
//clear out number vector
number.clear();
//setting the vector number equal to place holder that
number = that;
//strip leading zeros
strip_zeros();


}

bigint::bigint(unsigned long long i) {
  //1234..for example more algebra %10 to get remainer then /10 and so on and so on
  //need a for loop

  //clear vector number
  number.clear();
  //boolean variable to show that loop is complete
  bool end = false;

  while (!end){
// setting variable rem to show that modulus of the numbers are then push_back
//into number
    int rem = i % 10;
    //std:: cout << "this is rem " << rem << std::endl;
    number.push_back(rem);
//after modulating then you divide to get the rest of the integer
    i = i / 10;

    if( i == 0){
      end = true;
    }




  }
  //strip leading zeros
strip_zeros();
}

bigint::bigint(std::string str) {
number.clear();
//iterative loop to run the length of the string and push back the indexed value
//minus ascii value of 48 to return a string with the value of bigint
for(int i = str.length() - 1; i >=0; i--){

  number.push_back(int(str[i] - 48));
}
//strip leading zeros
strip_zeros();
}

bigint::bigint(std::ifstream &infile) {
  number.clear();
  //decalring string names for line and str
  std:: string line;
  std:: string str;
  //loop to read and write contents of file
  while(getline(infile, line)){
//every line gets added to the str variable
      str += line;

    }
    //str is then passed through bigint and set as this which is a point reference
    //to number
    *this = bigint(str);

strip_zeros();
}

bigint::bigint(const bigint &that) {
  number.clear();
  //setting bigint(str) = to placeholder that
  *this = that;
strip_zeros();
}


/* Number Access
 *
 * */
const std::vector<vec_bin> &bigint::getNumber() const {
  //getting the number vector to access the vector
  return number;
}

vec_bin bigint::operator[](size_t index) const {

//getting the number indeced by the size of the index.
    return number[index];
}


/** Comparators
 *
 * */
bool bigint::operator==(const bigint &that) const {
  //returning the vector = the place holder that of number
  return this-> number == that.number;
}

bool bigint::operator!=(const bigint &that) const {
  //returning that the above are not equal
  return ! (*this == that);
}

bool bigint::operator<(const bigint &that) const {
  //comparing if that is less than this
  //else to see if this is < that
  if(that.number.size() < number.size()){
    return false;
  }else if(number.size() < that.number.size()){
    return true;
  }
//loop runnning digit by digit to check which one is greater
  for(int i = number.size() - 1; i >= 0; i--){
      if(that.number[i] < number[i]){
        return false;
      } else if( number[i] < that.number[i]){
        return true;
      }

  }
}

bool bigint::operator<=(const bigint &that) const {
  // checking usign the not operator if not this greater than that
  return !((*this) > that);
}

bool bigint::operator>(const bigint &that) const {
  //seeing if not this is less than that and if this is not euqal to that
  //this is playing off the less than operator to create our greater than operator
  return (!((*this) < that) && !((*this) == that));
}

bool bigint::operator>=(const bigint &that) const {
  //returning is not this < that
  return !((*this) < that);
}


/** Addition
 *
 * */

bigint bigint::add(const bigint &that) const {

//declaring vector to store addition numbers intvector
//variable below are where i store carry, maximum and summation values
  std:: vector<vec_bin> intvector;

  int intsum = 0;

  int maximum = 0;

  int carry = 0;

  int digitone = 0;

  int digittwo = 0;
//checking to see which number is larger
  if(number.size() >= that.number.size()){

   maximum = number.size();


  } else{

   maximum = that.number.size();

  }


  for( int i = 0; i < maximum; i++){


//ternary operators checking to see what values i should return
//they are padded with zeros just incase that are 0
    digitone = (i >= number.size() ) ? 0 : number[i];

    digittwo = (i >= that.number.size() ) ?  0 : that.number[i];

    intsum = digitone + digittwo + carry;
//divide by ten to adjust for values
    carry = intsum / 10;
//pushback new sum into vector
    intvector.push_back(intsum % 10);
  }

  intvector.push_back(carry);

return intvector;

}
//overloading operators for addition by describing how to add this and that
//this ties into our comparator operators
bigint bigint::operator+(const bigint &that) const {
  return (*this).add(that);
}

bigint &bigint::operator+=(const bigint &that) {

  (*this) = add(that);

  return (*this);
}

bigint &bigint::operator++() {

  bigint biginttemp = (*this) + 1;

  (*this) =  biginttemp;

  return (*this);
}

bigint bigint::operator++(int) {

  bigint biginttemp = (*this);

  (*this) = (*this) + 1;

  return biginttemp;

}


/** Subtraction
 *
 * */

bigint bigint::subtract(const bigint &that) const {

//subtraction methods
//start with throwing an error if this is less that that
//we do not accept negative numbers
//this is the same set up as addition
  if(*this < that){
  throw "NOT ALLOWED";
  }
  std:: vector<vec_bin> intvector;

  int intsub = 0;

  int maximum = number.size();


  int take = 0;


  int digitone = 0;

  int digittwo = 0;


  for( int i = 0; i < maximum; i++){

    digitone = (i >= number.size() ) ?  0 : number[i];
    digittwo = (i >= that.number.size() ) ? 0 : that.number[i];
    intsub = digitone - digittwo + take;

//as opposed to carry the take uses -1 and 0 and these conditionals check if
//the take is less than 0 than turn your take to -1 else return 0


    if(intsub < 0){
      intsub = intsub + 10;
      take = -1;
    } else{
      take = 0;
    }

    intvector.push_back(intsub % 10);
}
    return intvector;
}

//overloading operators by declaring what to do with this and that
bigint bigint::operator-(const bigint &that) const {
  return (*this).subtract(that);
}

bigint &bigint::operator-=(const bigint &that) {
   bigint biginttemp = *this - that;
  (*this) = biginttemp;
  return (*this);
}

bigint &bigint::operator--() {
  (*this) =  (*this)- 1;

  return (*this);
}

bigint bigint::operator--(int) {
   bigint biginttemp = (*this) - 1;

  (*this) = biginttemp;

  return biginttemp;
}


/** Multiplication
 *
 * */

bigint bigint::multiply(const bigint &that) const {
//multiplication method by using addition += by looping that
//we can += this to a new variable and return the value

bigint  total = 0;
for(bigint i = 0; i < that; i++){

    total += *this;

}

return total;



}
//overloading the operators
bigint bigint::operator*(const bigint &that) const {
  return (*this).multiply(that);
}

bigint &bigint::operator*=(const bigint &that) {
  (*this) = multiply(that);
  return (*this);
}


/** Division
 *
 * */

bigint bigint::divide(const bigint &that) const {
//declaring a temporary value and answer value to assign values to
  bigint tempvar = 0;
  bigint answer = 0;
//checking to see if that is greater than this to simply return zeros
//for example you cannnot divide 1/5 you will simply return 0
  if(that > (*this)){
    return answer;
//if they are qual than return 1 i.e 5/5 = 1
  }else if((*this) == that){
    return answer + 1;
  }
//loop to use addition to do the division
  for(bigint i = 0; i < *this; i++){
    tempvar += that;
    if(tempvar > (*this)){
      return answer;
    }
    answer ++;
  }
return answer;
}
//overloading the operators
bigint bigint::operator/(const bigint &that) const {
  return (*this).divide(that);
}

bigint &bigint::operator/=(const bigint &that) {
  bigint biginttemp = (*this) / that;
 (*this) = biginttemp;
return (*this);
}


/** Modulo
 *
 * */
 bigint bigint::mod(const bigint &that) const {
//assigning temp value
//checking to see if it is == to 0 first to return 0
//or equal to 1 to return 1
//otherwise minus this from this/that * that to return value
   bigint tempvar = 0;
   if(((*this) / that) == 0){
     return *this;
   }//else if(((*this) / that) == 1){
     //return tempvar;
   else{
     tempvar = (*this) - (((*this) / that) * that);
   }
   return tempvar;

 }
//overloading operators
 bigint bigint::operator%(const bigint &that) const {
   return (*this).mod(that);
 }

 bigint &bigint::operator%=(const bigint &that) {
   bigint biginttemp = (*this) % that;
   (*this) = biginttemp;
   return (*this);
 }


/** Power
 *
 * */

bigint bigint::pow(unsigned long long n) {
  //starting out total at 1 to return same value for exponential function
  //*= this to multiply the number by designated n value

  bigint  total = 1;
  for(bigint i = 0; i < n; i++){

      total *= (*this);

  }

  return total;

}



/** Display methods
 *
 * */

std::ostream &operator<<(std::ostream &os, const bigint &bigint1) {
 //pretty much the same as file i/o this is going specifically to an ostream
 //and not a files
 //cout to ostream
 //setting variable string out to the pointer this (which reference number)
 //to to_string to set the value
  std:: string stringout = bigint1.to_string(true);

  os << stringout;

  return os;
}

std::string bigint::to_string(bool commas) const {
  //declaring variable
  std::string strversion;
  //counter
  int counter = 0;
  //loop to run through size of vector - 1 and read it backward
  for(int i = number.size() - 1; i >= 0; i--) {

    //assigning indexed number value to a variable and declaring obstructor
    //as a standard
    std::string string2char = std::to_string(number[i]);
    //boolean to make sure that commas are added
    if (commas == true){
      //assigning variable to new version
    strversion += string2char;
    counter ++;
    //conditional statment to add comments Only when it is modded by 3 and not = 0
    if((number.size() - counter) % 3 == 0 && i != 0){
      strversion += ",";
    }
  }
    else{
      //else if it needs no commas
    strversion += string2char;
  }


  }
  //return final value
  return strversion;
}

std::string bigint::scientific(unsigned int decimal_points) const {
//variable string declared to append new string value
  std:: string strsci;
// adding each character tp the variable strsci
  strsci += char(number[number.size()-1] + '0');
//adding a period to each value
  strsci += ".";
//loop to check for where to put decimal points
  for(int i =2; i < decimal_points + 2; i++){

    strsci += char(number[number.size() - i] + '0');

  }
//to add E notation to number
  strsci += "E";
//conditional to show that if it is bigger than nine where to place
//E and create notation
  if(number.size() - 1 > 9){
    strsci += std::to_string(number.size()-1);

  } else {
    strsci += char((number.size()-1) + '0');
  }

//return scientific notated number
  return strsci;
}

void bigint::to_file(std::ofstream &outfile, unsigned int wrap) {
  //setting variable string out to the pointer this (which reference number)
  //to to_string to set the value
    std:: string stringout = this->to_string();
//loop to run through the size of the vector accessed
    for (int i =0; i <stringout.length(); i++){
//left shifting the indexed values to the outfile
      outfile << stringout[i];
      //conditional to show that if it reaches the end of the line to add new lines
      //character
      if((i + 1) % wrap == 0){
        outfile << std::endl;
      }
    }
}
