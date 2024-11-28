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
Employer::~Employer()
{
    cout << "Employer::destructor" << endl;
    /*
    shared_ptr<Job_Listing> currentJob;
    list<shared_ptr<Job_Listing>>::iterator i;
    for(i = myJobListings.begin(); i != myJobListings.end(); i++)
    {
        currentJob = *i;
        myJobListings.remove(currentJob);
    }
*/
}
char *Employer::getType() const
{
    return "Employer";
}

void Employer::addJobListing(shared_ptr<Job_Listing> job)
{
    myJobListings.push_back(job);
}

void Employer::addReview(const string& text, const string& firstName, const string& lastName)
{
    reviews.push_back(make_shared<Review>(text, firstName, lastName));
}

void Employer::printJobListings()
{
    if(myJobListings.empty())
    {
        cout << "No published jobs." << endl;
        return;
    }
    list<shared_ptr<Job_Listing>>::iterator jobsIndex;
    for(jobsIndex = myJobListings.begin(); jobsIndex != myJobListings.end(); jobsIndex++)
        (*jobsIndex)->print();
}

void  Employer::printReviews()
{
    if(reviews.empty())
    {
        cout << "No published reviews." << endl;
        return;
    }
    list<shared_ptr<Review>>::reverse_iterator reviewIndex;
    for(reviewIndex = reviews.rbegin(); reviewIndex != reviews.rend(); ++reviewIndex)
        (*reviewIndex)->print();
}

bool Employer::checkListEmpty() const
{
    if(myJobListings.empty())
        return true;
    return false;
}