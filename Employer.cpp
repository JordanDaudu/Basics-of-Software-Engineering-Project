//
// Created by Jordan Daudu on 14/11/2024.
//

#include "Employer.h"
#include "utils.h"

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
    //cout << "Employer::destructor" << endl;
}

char *Employer::getType() const
{
    return "Employer";
}
list<shared_ptr<Job_Listing>>& Employer::getMyJobListings() {return myJobListings;}
list<shared_ptr<Review>>& Employer::getReviews() {return reviews;}

void Employer::addJobListing(shared_ptr<Job_Listing> job)
{
    myJobListings.push_back(job);
}

void Employer::addReview(const string& text, const string& firstName, const string& lastName)
{
    reviews.push_back(make_shared<Review>(text, firstName, lastName));
}

bool Employer::isMyJobListingsEmpty() const
{
    if(myJobListings.empty())
        return true;
    return false;
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

void Employer::printReviews()
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
void Employer::printMenu() const
{
    string topBorder = "+------------------------------------------------------+";
    string bottomBorder = "+------------------------------------------------------+";
    string divider = "|                                                      |";

    cout << topBorder << endl;
    cout << "|" << string((54 - 8 - firstName.length()) / 2, ' ') << "Welcome " << firstName
         << string(54 - 8 - firstName.length() - ((54 - 8 - firstName.length()) / 2), ' ') << "|" << endl;
    cout << divider << endl;

    cout << "|  1. Publish job offer                                |" << endl;
    cout << "|  2. Edit job offer                                   |" << endl;
    cout << "|  3. Delete job offer                                 |" << endl;
    cout << "|  4. View published jobs                              |" << endl;
    cout << "|  5. View my own profile                              |" << endl;
    cout << "|  6. View candidate(s) profile to accept / reject     |" << endl;
    cout << "|  7. Search for jobs                                  |" << endl;
    cout << "|  8. View reviews posted on me                        |" << endl;
    cout << "|  9. Pay to advertise                                 |" << endl;
    cout << "| 10. Delete account                                   |" << endl;
    cout << "| 11. Frequently asked question / Tips                 |" << endl;
    cout << "| 12. Logout                                           |" << endl;

    cout << bottomBorder << endl;
}
void Employer::printFAQ() const
{
    int choice;
    do
    {
        cout << "\nList of common questions:" << endl;
        cout << "1. Can I use the same account as an employer and as a candidate?" << endl;
        cout << "2. How much time does it take after uploading a job to accept it to the system?" << endl;
        cout << "3. How many jobs offers can I submit at the same time?" << endl;
        cout << "4. How can I see the candidates that applied for my job(s)?" << endl;
        cout << "5. Can I edit my job listing after uploading it?" << endl;
        cout << "6. Exit" << endl;
        do
        {
            choice = getValidInt();
            if(choice <= 0 || choice >= 7)
                cout << "Error! input not supported, try again" << endl;
        }
        while(choice <= 0 || choice >= 7);
        switch (choice)
        {
            case 1: {
                cout << "No, each account has different features, so it is impossible." << endl;
                break;
            }
            case 2: {
                cout << "Instantly, our system immediately uploads the job listing to the jobs list of the system." << endl;
                break;
            }
            case 3: {
                cout << "There is no limit." << endl;
                break;
            }
            case 4: {
                cout << "In the menu, there is a option \"View candidate profiles to accept / deny\" click it." << endl;
                break;
            }
            case 5: {
                cout << "Yes, it is possible there is an option \"Edit job offer\" in the menu to edit submissions." << endl;
                break;
            }
            default:
                cout << "Hope you got the information you want, redirecting to main menu..." << endl;
        }
    }
    while (choice != 6);
}