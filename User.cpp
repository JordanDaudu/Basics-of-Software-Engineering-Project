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
    uid = ++UID;
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
    uid = ++UID;
}

char *User::getType() const
{
    return "User";
}
User::~User() {cout << "user::destructor" << endl;}

string User::getId() const {return id;}
string User::getPassword() const {return password;}
string User::getFirstName() const {return firstName;}
string User::getLastName() const {return lastName;}
int User::getAge() const {return age;}
string User::getLocation() const {return location;}
unsigned int User::getPhoneNumber() const {return phoneNumber;}
int User::getUid() const {return uid;}

void User::print()
{
    cout << "Full name: " << firstName << " " << lastName << endl;
    cout << "Age: " << age << endl;
    cout << "Location: " << location << endl;
    cout << "Phone number: " << phoneNumber << endl;
}
