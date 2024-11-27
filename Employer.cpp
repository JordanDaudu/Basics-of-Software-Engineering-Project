//
// Created by Jordan Daudu on 14/11/2024.
//

#include "Employer.h"
Employer::Employer(): User()
{}
Employer::Employer(string id, string password, string firstName, string lastName, int age, string loc,
                     int phoneNum): User(id, password, firstName, lastName, age, loc, phoneNum)
{}
Employer::Employer(string id, string password, string firstName, string lastName, int age, int loc,
                   int phoneNum): User(id, password, firstName, lastName, age, loc, phoneNum)
{}
Employer::~Employer() {cout << "Employer::destructor" << endl;}
char *Employer::getType() const
{
    return "Employer";
}

void Employer::addJobListing(shared_ptr<Job_Listing> job)
{
    myJobListings.push_back(job);
}

void Employer::printJobListings()
{
    list<shared_ptr<Job_Listing>>::iterator jobsIndex;
    for(jobsIndex = myJobListings.begin(); jobsIndex != myJobListings.end(); jobsIndex++)
        (*jobsIndex)->print();
}

bool Employer::checkListEmpty() const
{
    if(myJobListings.empty())
        return true;
    return false;
}