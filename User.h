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
            int uid; // unique id for recognition
            static int UID; // unique id counter to make sure no same id is used
        public:
            User();
            User(string id, string password, string firstName, string lastName,
                 int age, string loc, unsigned int phoneNum);
            virtual ~User();
            virtual char *getType() const;
            string getId() const;
            string getPassword() const;
            string getFirstName() const;
            string getLastName() const;
            int getAge() const;
            string getLocation() const;
            unsigned int getPhoneNumber() const;
            int getUid() const;
            virtual void print();
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_USER_H
