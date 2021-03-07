//
//  PrecondViolatedExcept.h
//  Goleva_a09
//
//  Created by Anastasia Golev on 12/5/20.
//

using namespace std;
#include <string>
#include <iostream>
#ifndef PrecondViolatedExcept_h
#define PrecondViolatedExcept_h



/* precondViolatedExcept class to throw message error */
class PrecondViolatedExcept :public logic_error {
public:
PrecondViolatedExcept(const string& msg = " ");
    
};//end PreconViolatedExcept
//constructor for precondViolatedExcept(const string& msg)
PrecondViolatedExcept::PrecondViolatedExcept(const string& msg) : logic_error("Precondition Violated Exceptions: " + msg){}

#endif /* PrecondViolatedExcept_h */

