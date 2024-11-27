//
// Created by Jordan Daudu on 14/11/2024.
//

#include "User.h"
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
           int phoneNum)
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
User::User(string id, string password, string firstName, string lastName, int age, int loc,
           int phoneNum)
{
    this->id = id;
    this->password = password;
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    setLocation(loc);
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

void User::setFirstName(string name) {firstName = name;}
void User::setLastName(string name) {lastName = name;}
void User::setAge(int newAge) {age = newAge;}
void User::setPhoneNumber(int phoneNum) {phoneNumber = phoneNum;}
void User::setLocation(int choice)
{
    switch (choice) {
        case 1:
            location = "Jerusalem region";
            break;
        case 2:
            location = "Northern region";
            break;
        case 3:
            location = "Haifa region";
            break;
        case 4:
            location = "Central region";
            break;
        case 5:
            location = "Tel-Aviv region";
            break;
        case 6:
            location = "Southern region";
            break;
        default:
            location = "None";
    }
}
void User::print()
{
    cout << "Full name: " << firstName << " " << lastName << endl;
    cout << "Age: " << age << endl;
    cout << "Location: " << location << endl;
    cout << "Phone number: " << phoneNumber << endl;
}
