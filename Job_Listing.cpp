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
    uid = ++UID;
    employerUID = 0;
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
    employerUID = 0;
    uid = ++UID;
    paid = false;
}

Job_Listing::Job_Listing(string name, string text, int position, int experience, int profession, int location, int newSalary,
                         bool paid, int employerUID, weak_ptr<User> employer)
{
    this->name = std::move(name);
    description = std::move(text);
    setPosition(position);
    setExperience(experience);
    setProfession(profession);
    setLocation(location);
    salary = newSalary;
    this->paid = paid;
    this->employerUID = employerUID;
    uid = ++UID;
    this->employer = employer;
}
Job_Listing::~Job_Listing()
{
    //cout << "Job_Listing::destructor" << endl;
}

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
int Job_Listing::getUid() const {return uid;}
int Job_Listing::getEmployerUID() const {return employerUID;}

string Job_Listing::getPositionID(int choice) const
{
    if(choice == 1)
        return "Full-time";
    else if(choice == 2)
        return "Half-time";
    return "";
}
int Job_Listing::getPositionID() const
{
    if(position == "Full-time")
        return 1;
    else
        return 2;
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
int Job_Listing::getProfessionID() const
{
    if(profession == "Software engineer")
        return 1;
    else if(profession == "Electrical engineer")
        return 2;
    else if(profession == "Civil engineer")
        return 3;
    else if(profession == "Mechanical engineer")
        return 4;
    else if(profession == "Industrial engineering and management")
        return 5;
    else if(profession == "Chemical engineering")
        return 6;
    else
        return 0;
}
weak_ptr<User> Job_Listing::getEmployer() const {return employer;}
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
int Job_Listing::getLocationID() const
{
    if(location == "Jerusalem region")
        return 1;
    else if(location == "Northern region")
        return 2;
    else if(location == "Haifa region")
        return 3;
    else if(location == "Central region")
        return 4;
    else if(location == "Tel-Aviv region")
        return 5;
    else if(location == "Southern region")
        return 6;
    else
        return 0;
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
        case 5:
            experience = 5;
            break;
        default:
            experience = 0;
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
    shared_ptr<User> employerPtr = employer.lock(); // getting pointer if it exists
    cout << "|Name: " << name << "|" << endl;
    cout << " Description: " << description << endl;
    cout << " - Position: " << position << endl;
    if(experience == 0)
        cout << " - Experience: " << experience << " No experience needed" << endl;
    if(experience == 1)
        cout << " - Experience: " << experience << " Year" << endl;
    if(experience >= 2)
        cout << " - Experience: " << experience << " Years" << endl;
    cout << " - Profession: " << profession << endl;
    if(location == "None")
        cout << " - Location: No location" << endl;
    else
        cout << " - Location: " << location << endl;
    if(salary != 0)
        cout << " - Salary: " << salary << endl;
    cout << " - UID: " << uid << endl;
    if (employerPtr) // checking if an instance of employer in shared_ptr exist
        cout << " - Employer name: " << employerPtr->getFirstName() << " " << employerPtr->getLastName() << endl;
}