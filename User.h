//
// Created by Jordan Daudu on 14/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_USER_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_USER_H
#include <iostream>
using namespace std;

class User
        {
        protected:
            string id;
            string password;
            string firstName;
            string lastName;
            int age;
            string location;
            unsigned int phoneNumber;
        public:
            User();
            User(string id, string password, string firstName, string lastName,
                 int age, string loc, unsigned int phoneNum);
            ~User();
            void print();
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_USER_H
