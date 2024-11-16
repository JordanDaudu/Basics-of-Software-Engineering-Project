//
// Created by Jordan Daudu on 14/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_CANDIDATE_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_CANDIDATE_H
#include "User.h"

class Candidate: virtual public User
        {
        private:

        public:
            Candidate();
            Candidate(string id, string password, string firstName, string lastName,
                int age, string loc, unsigned int phoneNum);
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_CANDIDATE_H
