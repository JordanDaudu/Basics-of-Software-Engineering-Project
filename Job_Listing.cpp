//
// Created by Jordan Daudu on 20/11/2024.
//

#include "Job_Listing.h"

Job_Listing::Job_Listing()
{
    description = nullptr;
    position = nullptr;
    experience = 0;
    profession = nullptr;
    location = nullptr;
    salary = 0;
    paid = false;
}

Job_Listing::Job_Listing(string name, string description, string position, int exp, string profession, string loc, int salary)
{
    this->name = name;
    this->description = description;
    this->position = position;
    experience = exp;
    this->profession = profession;
    location = loc;
    this->salary = salary;
}

Job_Listing::Job_Listing(string name, string text, int position, int experience, int profession, int location, int newSalary,
                         bool paid)
{
    this->name = std::move(name);
    description = std::move(text);
    setPosition(position);
    setExperience(experience);
    setProfession(profession);
    setLocation(location);
    salary = newSalary;
    this->paid = paid;
}
Job_Listing::~Job_Listing() {cout << "Job_Listing::destructor" << endl;}

char *Job_Listing::getType() const
{
    return "Job_Listing";
}

string Job_Listing::getName() const {return name;}
string Job_Listing::getDescription() const {return description;}
string Job_Listing::getPosition() const {return position;}
int Job_Listing::getExperience() const {return experience;}
string Job_Listing::getProfession() const {return profession;}
string Job_Listing::getLocation() const {return location;}
int Job_Listing::getSalary() const {return salary;}
bool Job_Listing::getPaid() const {return paid;}

string Job_Listing::getPositionID(int choice) const
{
    if(choice == 1)
        return "Full-time";
    else if(choice == 2)
        return "Half-time";
}
string Job_Listing::getProfessionID(int choice) const
{
    switch (choice)
    {
        case 1:
            return "Software engineer";
        case 2:
            return "Electrical engineer";
        case 3:
            return "Civil engineer";
        case 4:
            return "Mechanical engineer";
        case 5:
            return "Industrial engineering and management";
        case 6:
            return "Chemical engineering";
        default:
            return "None";
    }
}
string Job_Listing::getLocationID(int choice) const
{
    switch (choice)
    {
        case 1:
            return "Jerusalem region";
        case 2:
            return "Northern region";
        case 3:
            return "Haifa region";
        case 4:
            return "Central region";
        case 5:
            return "Tel-Aviv region";
        case 6:
            return "Southern region";
        default:
            return "None";
    }
}

void Job_Listing::setName(string text)
{
    name = std::move(text);
}
void Job_Listing::setDescription(string text)
{
    description = std::move(text);
}
void Job_Listing::setPosition(int choice)
{
    if(choice == 1)
        position = "Full-time";
    else if(choice == 2)
        position = "Half-time";
}
void Job_Listing::setExperience(int choice)
{
    switch (choice)
    {
        case 0:
            experience = 0;
            break;
        case 1:
            experience = 1;
            break;
        case 2:
            experience = 2;
            break;
        case 3:
            experience = 3;
            break;
        case 4:
            experience = 4;
            break;
        default:
            experience = 5;
    }
}
void Job_Listing::setProfession(int choice)
{
    switch (choice)
    {
        case 1:
            profession = "Software engineer";
            break;
        case 2:
            profession = "Electrical engineer";
            break;
        case 3:
            profession = "Civil engineer";
            break;
        case 4:
            profession = "Mechanical engineer";
            break;
        case 5:
            profession = "Industrial engineering and management";
            break;
        case 6:
            profession = "Chemical engineering";
            break;
        default:
            profession = "None";
    }
}
void Job_Listing::setLocation(int choice)
{
    switch (choice)
    {
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
void Job_Listing::setSalary(int newSalary) {salary = newSalary;}
void Job_Listing::setPaid(bool choice)
{
    if(choice == 1)
        paid = true;
    else
        paid = false;
}

void Job_Listing::print() const
{
    cout << "|" << name << "|" << endl;
    cout << " Description: " << description << endl;
    cout << " - Position: " << position << endl;
    cout << " - Experience: " << experience << endl;
    cout << " - Profession: " << profession << endl;
    cout << " - Location: " << location << endl;
    if(salary != 0)
        cout << " - Salary: " << salary << endl;
    if(paid)
        cout << "^^^Paid advertisement^^^" << endl;
}