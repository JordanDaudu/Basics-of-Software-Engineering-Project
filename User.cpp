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

string User::getId() const {return id;}
string User::getPassword() const {return password;}
string User::getFirstName() const {return firstName;}
string User::getLastName() const {return lastName;}
int User::getAge() const {return age;}
string User::getLocation() const {return location;}
unsigned int User::getPhoneNumber() const {return phoneNumber;}

void User::print()
{
    cout << "test: " << firstName << endl;
}
