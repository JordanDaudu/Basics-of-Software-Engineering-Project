#include <iostream>
#include <list>
#include <typeinfo>
#include "User.h"
#include "Candidate.h"
#include "Employer.h"
using namespace std;

// Function of the menu that the candidate uses
void candidateMenu(list<shared_ptr<User>> &userList, shared_ptr<User> &currentUser)
{
    int choice;
    cout << "||Welcome " << currentUser->getFirstName() << "||" << endl;
    do
    {
        cout << "1.Search for jobs\n2.Apply for job\n3.Upload resume\n4.Submission history\n5.Edit profile\n"
                "6.Average salary calculator\n7.Leave review on employer\n8.Delete account\n"
                "9.Frequently asked question / Tips\n10.Logout" << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
            {

            }
            // need to add all functions
            case 10:
                cout << "Leaving system..." << endl;
        }
    }
    while(choice != 10);
}

// Function of the menu that the employer uses
void employerMenu(list<shared_ptr<User>> &userList, shared_ptr<User> &currentUser)
{
    int choice;
    cout << "||Welcome " << currentUser->getFirstName() << "||" << endl;
    do
    {
        cout << "1.Publish submission\n2.Edit submission\n3.Delete submission\n4.Published jobs\n"
                "5.View candidate profiles to accept / deny\n""6.Search for jobs\n"
                "7.Pay to advertise\n8.Delete account\n""9.Frequently asked question / Tips\n10.Logout" << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
            {

            }
            // need to add all functions
            case 10:
                cout << "Leaving system..." << endl;
        }
    }
    while(choice != 10);
}

// Function to register a new user into the system
void registerUser(list<shared_ptr<User>> &user)
{
    int choice;
    cout << "Which user are you?\n1.Candidate\n2.Employer" << endl;
    cin >> choice;
    if(choice != 1 && choice != 2)
    {
        cout << "Error, not a supported input, going back." << endl;
        return;
    }
    string id, password, firstName, lastName, location;
    int age;
    unsigned int phoneNumber;
    cout << "Type your id: ";
    cin >> id;
    cout << "Type your password: ";
    cin >> password;
    cout << "Type you first name and then last name: ";
    cin >> firstName >> lastName;
    cout << "What is your age?: ";
    cin >> age;
    cout << "What is your city of living?: ";
    cin >> location;
    cout << "Type in your phone number: ";
    cin >> phoneNumber;
    if(choice == 1)
         user.push_back(make_shared<Candidate>(id, password, firstName, lastName, age, location, phoneNumber));
    else if(choice == 2)
        user.push_back(make_shared<Employer>(id, password, firstName, lastName, age, location, phoneNumber));
}

// Function to log into the system
shared_ptr<User> loginUser(list<shared_ptr<User>> &user, shared_ptr<User> &currentUser)
{
    bool found = false;
    string id, password;
    cout << "Type you id to login: ";
    cin >> id;
    cout << "Type your password: ";
    cin >> password;
    for(auto i = user.begin(); i != user.end(); i++)
    {
        if((*i)->getId() == id && (*i)->getPassword() == password)
            //return *i;
            currentUser = *i;
    }
    if(strcmp(currentUser->getType(), "Candidate") == 0)
        candidateMenu(user, currentUser);
    else if(strcmp(currentUser->getType(), "Employer") == 0)
        employerMenu(user, currentUser);
    cout << "Id or password is incorrect." << endl;
    return nullptr;
}

// function of the main menu of the system
shared_ptr<User> mainMenu(list<shared_ptr<User>> &user)
{
    int choice;
    shared_ptr<User> currentUser;
    do
    {
        cout << "1.Register\n2.Login\n3.Exit" << endl;
        cin >> choice;
        if(choice <= 0 || choice >= 4)
            cout << "Not supported input, try again.\n ";
        if(choice == 1)
            registerUser(user);
        else if(choice == 2)
        {
            currentUser = loginUser(user, currentUser);
            if(currentUser == nullptr)
                continue;
            return currentUser;
        }
        else if(choice == 3)
            return nullptr;
    }
    while(choice != 3);
}

int main()
{
    int choice;
    // using shared ptr, so it will delete automatically without needing delete
    list<shared_ptr<User>> userList;
    shared_ptr<User> currentUser;
    list<shared_ptr<User>>::iterator i;
    cout << userList.size();
    //adding 3 admin user for testing and deleting a user to see if it works
    userList.push_back(make_shared<User> ("admin", "1111", "admin", "user", 0, "none", 054));
    userList.push_back(make_shared<User> ("bdmin", "1111", "bdmin", "user", 0, "none", 054));
    userList.push_back(make_shared<User> ("cdmin", "1111", "cdmin", "user", 0, "none", 054));
    for(i = userList.begin(); i != userList.end(); i++)
    {
        if((*i)->getId() == "bdmin")
        {
            currentUser = *i;
            userList.remove(currentUser);
            currentUser = nullptr;
            break;
        }
    }
    for(i = userList.begin(); i != userList.end(); i++)
        (*i)->print();

    // start of the system in main
    cout << "~~~Job search system~~~" << endl;
    currentUser = mainMenu(userList);
    if(currentUser == nullptr)
    {
        cout << "Goodbye!" << endl;
        return 0;
    }


    // ALL THE CODE BELOW IS FOR TESTING PURPOSES
    /*
    do
    {
        cout << "1.Register\n2.Login\n3.Exit" << endl;
        cin >> choice;
        if(choice <= 0 || choice >= 4)
            cout << "Not supported input, try again.\n ";
        if(choice == 1)
            registerUser(userList);
        else if(choice == 2)
        {
            currentUser = loginUser(userList);
            if(currentUser == nullptr)
                continue;
            break;
        }
        else if(choice == 3)
            return 0;
    }
    while(choice != 3);
    for(i = userList.begin(); i != userList.end(); i++)
        (*i)->print();
    */
    if(strcmp(currentUser->getType(), "Candidate") == 0)
        cout << "Candidate login" << endl;
    else if(strcmp(currentUser->getType(), "Employer") == 0)
        cout << "Employer login" << endl;
    //delete userList.back();
    userList.pop_back();
    for(i = userList.begin(); i != userList.end(); i++)
        (*i)->print();
    return 0;
}
