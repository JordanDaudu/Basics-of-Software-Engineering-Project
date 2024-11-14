//
// Created by Jordan Daudu on 14/11/2024.
//

#include "User.h"
#include <cstring>
#include <iostream>
using namespace std;

User::User()
{
    id = '0';
    password = '0';
    firstName = '0';
    lastName = '0';
    age = 0;
    location = '0';
    phoneNumber = 0;
}
User::User(string id, string password, string firstName, string lastName, int age, string loc,
           unsigned int phoneNum)
{
    this->id = id;
    this->password = password;
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    location = loc;
    phoneNumber = phoneNum;
}
User::~User() {}

void User::print()
{
    cout << "test" << endl;
}
