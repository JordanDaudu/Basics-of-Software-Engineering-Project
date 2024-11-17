#include <iostream>
#include <list>
#include <typeinfo>
#include "User.h"
#include "Candidate.h"
#include "Employer.h"
using namespace std;

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
shared_ptr<User> loginUser(list<shared_ptr<User>> &user)
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
            return *i;
    }
    cout << "Id or password is incorrect." << endl;
    return nullptr;
}

int main()
{
    shared_ptr<User> currentUser;
    int choice = 1;
    int size = 0;
    // using shared ptr, so it will delete automatically without needing delete
    list<shared_ptr<User>> userList;
    list<shared_ptr<User>>::iterator i;
    cout << userList.size();
    //adding jordan user for testing
    while(choice == 1)
    {
        //User x("Jordan", "1111", "Jordan", "Daudu", 22, "Ashdod", 054);
        //userList.push_back(x);
        userList.push_back(make_shared<User> ("Jordan", "1111", "Jordan", "Daudu", 22, "Ashdod", 054));
        cin >> choice;
        size++;
    }
    for(i = userList.begin(); i != userList.end(); i++)
        (*i)->print();
    cout << "~~~Job search system~~~" << endl;
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
