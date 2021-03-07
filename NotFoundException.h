//
//  NotFoundException.h
//  Goleva_a09
//
//  Created by Anastasia Golev on 12/5/20.
//

#ifndef NotFoundException_h
#define NotFoundException_h

//NotFoundExcept class from Section C3.5 replace exception w/ logic error
class NotFoundExcept : public logic_error{
public:
    NotFoundExcept( const string& msg = "") : logic_error( "Target not found: " + msg ){} //end ctor
};

#endif /* NotFoundException_h */
