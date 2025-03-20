#include <chrono>
#include <limits>
#include <locale>

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace chrono;

template <class TypeMultiply>
bool isSafeMultiply (TypeMultiply mult01, TypeMultiply mult02, TypeMultiply &multResult) {

if (mult01 == 0 || mult02 == 0) {
    multResult = 0;
    return false;
}

multResult = mult01 * mult02;
if(mult01 == (multResult/mult02)) {
    return true;
} else {
    return false;
}

}

template <class TypeMultiply>
void calculateTimeFactorialLoopFunc(void) 
{

  auto timeStart = steady_clock::now();


  TypeMultiply multiplier      = 1,
               factorialResult = 1;

  while (isSafeMultiply<TypeMultiply>(factorialResult, multiplier, factorialResult)) 
  {
    cout << setw(3) << multiplier << setw(27) << factorialResult << endl;
    ++multiplier;
  }

  // calculate timeElapsed as described in the assignment
  auto timeElapsed = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

  cout << endl;
  cout << "Unsigned overflow at : " << setw(20) << multiplier <<endl;
  cout << "Time Elapsed (nano)  : " << setw(20) << timeElapsed.count() << endl;

}//calculateTimeFactorialLoopFunc

 //------------------------------------------
template <class TypeMultiply>
void factorialRecursiveFunc (TypeMultiply &multiplier, TypeMultiply factorialResult) {

  if (isSafeMultiply<TypeMultiply>(factorialResult, multiplier, factorialResult)) 
  {
    cout << setw(3) << multiplier << setw(27) << factorialResult << endl;
    factorialRecursiveFunc (++multiplier, factorialResult);
  }
  return;

}//factorialRecursive

 //------------------------------------------  
template <class TypeMultiply>
void calculateTimeFactorialRecursiveFunc() {

  auto timeStart = steady_clock::now();

  TypeMultiply mult01 = 1;
  factorialRecursiveFunc <TypeMultiply> (mult01, 1);

  // calculate timeElapsed as described in the assignment
  auto timeElapsed = duration_cast<nanoseconds> (steady_clock::now() - timeStart);
  
  cout << endl;
  cout << "Unsigned overflow at : " << setw(20) << mult01 <<endl;
  cout << "Time Elapsed (nano)  : " << setw(20) << timeElapsed.count() << endl;

}//calculateTimeFactorialRecursiveFunc()

template <class TYPESIZE> 
class FactorialCalculationClass {

private:
  unsigned typeSizeBits;

public:

  // Constructor
  FactorialCalculationClass(unsigned typeSize) {
    typeSizeBits = typeSize;
      
  }

  void executeFactorialForType() {

    cout <<
      typeSizeBits <<
      " bit unsigned Factorial Loop" << endl <<
      "------------------------------" << endl;
    calculateTimeFactorialLoopFunc <TYPESIZE>();
    cout << endl << endl;

    cout <<
      typeSizeBits <<
      " bit unsigned Factorial Recursion" << endl <<
      "-----------------------------------" << endl;
    calculateTimeFactorialRecursiveFunc <TYPESIZE>();
    cout << endl << endl;

  }

};// template <class TYPESIZE> class factorialCalculationClass


int main() {
  // condition cout set to local digit separation comas (USA)
  cout.imbue(locale(""));

  FactorialCalculationClass <uint16_t> factorialCalculateUintnnObj1(16);
  FactorialCalculationClass <uint32_t> factorialCalculateUintnnObj2(32);
  FactorialCalculationClass <uint64_t> factorialCalculateUintnnObj3(64);

  factorialCalculateUintnnObj1.executeFactorialForType();
  factorialCalculateUintnnObj2.executeFactorialForType();
  factorialCalculateUintnnObj3.executeFactorialForType();

  cout << "Press the enter key once or twice to end..." << endl; cin.ignore(); cin.get();



  return 0;
}
