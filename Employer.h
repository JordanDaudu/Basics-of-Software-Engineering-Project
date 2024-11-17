//
// Created by Jordan Daudu on 14/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
#include "User.h"

class Employer: public User
        {
        private:

        public:
            Employer();
            Employer(string id, string password, string firstName, string lastName,
                int age, string loc, unsigned int phoneNum);
            virtual ~Employer();
            virtual char *getType() const;
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
