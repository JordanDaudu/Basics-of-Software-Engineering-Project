//
// Created by Jordan Daudu on 14/11/2024.
//

#include "Candidate.h"

Candidate::Candidate(): User()
{}
Candidate::Candidate(string id, string password, string firstName, string lastName, int age, string loc,
                     unsigned int phoneNum): User(id, password, firstName, lastName, age, loc, phoneNum)
                     {}
