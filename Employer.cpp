//
// Created by Jordan Daudu on 14/11/2024.
//

#include "Employer.h"
Employer::Employer(): User()
{}
Employer::Employer(string id, string password, string firstName, string lastName, int age, string loc,
                     unsigned int phoneNum): User(id, password, firstName, lastName, age, loc, phoneNum)
{}
Employer::~Employer() {cout << "Employer::destructor" << endl;}
char *Employer::getType() const
{
    return "Employer";
}