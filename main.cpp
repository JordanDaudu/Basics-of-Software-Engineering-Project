#include <iostream>
#include <list>
#include "User.h"
#include "Candidate.h"
#include "Employer.h"
#include "Job_Listing.h"
#include "Job_Submission.h"
using namespace std;
int User::UID = 0, Job_Listing::UID = 0, Job_Submission::UID = 0;

/// Function to view and accept submission that employer received
/// \param currentUser = pointer to the current user
/// \param userList = list of all users in the system
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List =  list of all job submissions in the system
void employerViewCandidateSubmission(shared_ptr<User> &currentUser, list<shared_ptr<User>> &userList, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    bool found = false;
    int choice, counter = 0;
    list<shared_ptr<User>>::iterator candidateIndex;
    list<shared_ptr<Job_Listing>>::iterator jobsIndex;
    list<shared_ptr<Job_Submission>>::iterator jobSubmissionIndex;
    for(jobSubmissionIndex = jobs_Submission_List.begin(); jobSubmissionIndex != jobs_Submission_List.end(); jobSubmissionIndex++)
    {
        if((*jobSubmissionIndex)->getEmployerUID() == currentUser->getUid() && (*jobSubmissionIndex)->getStatus() == "Waiting for response")
        {
            cout << "\\\\Submission " << ++counter << " waiting for response//" << endl;
            found = true;
            for(jobsIndex = job_list.begin(); jobsIndex != job_list.end(); jobsIndex++)
                if((*jobsIndex)->getUid() == (*jobSubmissionIndex)->getJob_listingUID())
                {
                    (*jobsIndex)->print();
                    break;
                }
            for(candidateIndex = userList.begin(); candidateIndex != userList.end(); candidateIndex++)
                if((*candidateIndex)->getUid() == (*jobSubmissionIndex)->getCandidateUID())
                {
                    cout << "Candidate information: " << endl;
                    (*candidateIndex)->print();
                    break;
                }
            cout << "[^Submission UID: " << (*jobSubmissionIndex)->getUid() << "^]" << endl;
        }
    }
    if(!found)
    {
        cout << "No submission to view yet." << endl;
        return;
    }
    cout << "-------------------------------" << endl;
    do
    {
        cout << "Would you like to accept / reject a submission?\n1.Yes\n2.No" << endl;
        cin >> choice;
        if(choice != 1 && choice != 2)
            cout << "Error! input not supported, try again" << endl;
    }
    while(choice != 1 && choice != 2);
    if(choice == 1)
    {
        cout << "Type the submission UID that you would like to accept / reject: ";
        cin >> choice;
        for(jobSubmissionIndex = jobs_Submission_List.begin(); jobSubmissionIndex != jobs_Submission_List.end(); jobSubmissionIndex++)
        {
            if((*jobSubmissionIndex)->getUid() == choice)
            {
                do
                {
                    cout << "What action would you like to do?\n1.Accept\n2.Reject\n3.Nothing" << endl;
                    cin >> choice;
                    if(choice <= 0 || choice >= 4)
                        cout << "Error! input not supported, try again" << endl;
                }
                while(choice <= 0 || choice >= 4);
                (*jobSubmissionIndex)->setStatus(choice);
                if(choice == 1)
                    cout << "Successfully accepted submission!" << endl;
                else if(choice == 2)
                    cout << "Successfully rejected submission!" << endl;
            }
        }
    }
    cout << "Returning to menu..." << endl;
}
/// function for candidate to view his submission history and check it's current status
/// \param currentUser = pointer to the current user
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List = list of all job submissions in the system
void candidateViewSubmissionHistory(shared_ptr<User> &currentUser, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    bool found = false;
    list<shared_ptr<Job_Listing>>::reverse_iterator jobsIndex;
    list<shared_ptr<Job_Submission>>::reverse_iterator jobSubmissionIndex;
    // finding all candidate job submissions trough UID
    for(jobSubmissionIndex = jobs_Submission_List.rbegin(); jobSubmissionIndex != jobs_Submission_List.rend(); ++jobSubmissionIndex)
    {
        if((*jobSubmissionIndex)->getCandidateUID() == currentUser->getUid())
        {
            found = true;
            // if found a job submission then find it's listing and print it
            for(jobsIndex = job_list.rbegin(); jobsIndex != job_list.rend(); ++jobsIndex)
                if((*jobsIndex)->getUid() == (*jobSubmissionIndex)->getJob_listingUID())
                {
                    (*jobsIndex)->print();
                    break;
                }
            cout << " - Current status is: " << (*jobSubmissionIndex)->getStatus() << endl;
            cout << "-------------------------------" << endl;
        }
    }
    if(!found)
        cout << "No submission." << endl;
}
/// function for candidate to apply to a job listing
/// \param currentUser = pointer to the current user
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List = list of all job submissions in the system
void candidateApplyForJob(shared_ptr<User> &currentUser, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int uid;
    bool found = false;
    list<shared_ptr<Job_Listing>>::iterator jobsIndex;
    shared_ptr<Job_Listing> currentJob;
    cout << "Type the UID of the job you would like to apply to: ";
    cin >> uid;
    // finding if the given job uid exist in the database
    for(jobsIndex = job_list.begin(); jobsIndex != job_list.end(); jobsIndex++)
        if(uid == (*jobsIndex)->getUid())
        {
            currentJob = *jobsIndex;
            found = true;
        }
    if(!found)
    {
        cout << "Error! given UID does not exist in the system, redirecting to menu." << endl;
        return;
    }
    jobs_Submission_List.push_back(make_shared<Job_Submission>(currentUser->getUid(), currentJob->getEmployerUID(), currentJob->getUid()));
    cout << "|Successfully applied to job listing \"" << currentJob->getName() << "\"" << endl;
}
/// Function that is printing all the jobs under pointed employer
/// \param currentUser = pointer to the current user
void employerPublishedJobs(shared_ptr<User> &currentUser)
{
    Employer *tmp = dynamic_cast<Employer *>(currentUser.get());
    if(tmp->checkListEmpty())
    {
        cout << "No published jobs." << endl;
        return;
    }
    tmp->printJobListings();
}
/// Calculate the average of a chosen profession
/// \param job_list = list of all job listing in the system
void calculateProfessionAverage(list<shared_ptr<Job_Listing>> &job_list)
{
    int choice;
    int size = 0;
    int sum = 0;
    float average;
    list<shared_ptr<Job_Listing>>::iterator jobsIndex;
    do
    {
        cout << "Which profession would you like to check the average?:\n1.Software engineer\n2.Electrical engineer\n3.Civil engineer\n"
                "4.Mechanical engineer\n5.Industrial engineering and management\n6.Chemical engineering\n";
        cin >> choice;
        if(choice <= 0 || choice >= 7)
            cout << "Error! input not supported, try again" << endl;
    }
    while(choice <= 0 || choice >= 7);
    for(jobsIndex = job_list.begin(); jobsIndex != job_list.end(); jobsIndex++)
        if((*jobsIndex)->getProfession() == (*jobsIndex)->getProfessionID(choice))
        {
            sum += (*jobsIndex)->getSalary();
            size++;
        }
    average = float(sum) / float(size);
    if(average == 0.0)
        cout << "There is no job in the system with a salary in this profession." << endl;
    else
        cout << "The average is: " << average << endl;
}
/// Search function for Candidate
/// \param currentUser = pointer to the current user
/// \param job_list = list of all job listing in the system
void searchJob(shared_ptr<User> &currentUser, list<shared_ptr<Job_Listing>> &job_list)
{
    int position, experience, profession, location;
    list<shared_ptr<Job_Listing>>::iterator jobsIndex;
    do
    {
        cout << "What position would you like?:\n1.Full-time\n2.Half-time\n";
        cin >> position;
        if(position != 1 && position != 2)
            cout << "Error! input not supported, try again" << endl;
    }
    while(position != 1 && position != 2);
    do
    {
        cout << "How many years of experience do you have?:\n0.No experience\n1.1 year\n2.2 years\n3.3 years\n4.4 years\n5.5+ years\n";
        cin >> experience;
        if(experience < 0 || experience > 5)
            cout << "Error! input not supported, try again" << endl;
    }
    while(experience < 0 || experience > 5);
    do
    {
        cout << "What profession are you looking for?:\n1.Software engineer\n2.Electrical engineer\n3.Civil engineer\n"
                "4.Mechanical engineer\n5.Industrial engineering and management\n6.Chemical engineering\n7.None\n";
        cin >> profession;
        if(profession <= 0 || profession >= 8)
            cout << "Error! input not supported, try again" << endl;
    }
    while(profession <= 0 || profession >= 8);
    do
    {
        cout << "Which location would you like to search in?:\n1.Jerusalem region\n2.Northern region\n3.Haifa region\n"
                "4.Central region\n5.Tel-Aviv region\n6.Southern region\n";
        cin >> location;
        if(location <= 0 || location >= 7)
            cout << "Error! input not supported, try again" << endl;
    }
    while(location <= 0 || location >= 7);
    for(jobsIndex = job_list.begin(); jobsIndex != job_list.end(); jobsIndex++)
        if((*jobsIndex)->getPaid())
        {
            (*jobsIndex)->print();
            cout << "^^^Paid advertisement^^^" << endl;
        }
    for(jobsIndex = job_list.begin(); jobsIndex != job_list.end(); jobsIndex++)
        if((*jobsIndex)->getPosition() == (*jobsIndex)->getPositionID(position) && (*jobsIndex)->getExperience() == experience &&
        (*jobsIndex)->getProfession() == (*jobsIndex)->getProfessionID(profession) && (*jobsIndex)->getLocation() == (*jobsIndex)->getLocationID(location) &&
        !(*jobsIndex)->getPaid())
            (*jobsIndex)->print();
    cout << endl;
}

/// Publish function for employer
/// \param currentUser = pointer to the current user
/// \param job_list = list of all job listing in the system
void publishJobOffer(shared_ptr<User> &currentUser, list<shared_ptr<Job_Listing>> &job_list)
{
    string name, text;
    int position, experience, profession, location, salary;
    bool paid;
    cout << "||Publishing a job offer||" << endl;
    cout << "Type the name of the job offer: ";
    cin.ignore(); // completely clears the input
    while(true)
    {
        getline(cin, name);
        if(!name.empty())
            break;
        cout << "Name cannot be empty. Please enter again: ";
    }
    cout << "Type a brief description of the job: ";
    while(true)
    {
        getline(cin, text);
        if(!text.empty())
            break;
        cout << "description cannot be empty. Please enter again: ";
    }
    do
    {
        cout << "What position is this job?:\n1.Full-time\n2.Half-time\n";
        cin >> position;
        if(position != 1 && position != 2)
            cout << "Error! input not supported, try again" << endl;
    }
    while(position != 1 && position != 2);
    do
    {
        cout << "How many years of experience are you looking for?:\n0.No experience\n1.1 year\n2.2 years\n3.3 years\n4.4 years\n5.5+ years\n";
        cin >> experience;
        if(experience < 0 || experience > 5)
            cout << "Error! input not supported, try again" << endl;
    }
    while(experience < 0 || experience > 5);
    do
    {
        cout << "What profession are you looking for?:\n1.Software engineer\n2.Electrical engineer\n3.Civil engineer\n"
                "4.Mechanical engineer\n5.Industrial engineering and management\n6.Chemical engineering\n7.None\n";
        cin >> profession;
        if(profession <= 0 || profession >= 8)
            cout << "Error! input not supported, try again" << endl;
    }
    while(profession <= 0 || profession >= 8);
    do
    {
        cout << "Which location is this job located?:\n1.Jerusalem region\n2.Northern region\n3.Haifa region\n"
                "4.Central region\n5.Tel-Aviv region\n6.Southern region\n";
        cin >> location;
        if(location <= 0 || location >= 7)
            cout << "Error! input not supported, try again" << endl;
    }
    while(location <= 0 || location >= 7);
    do
    {
        cout << "What is the salary of the job?\nNote: If you would like to not specify the amount input 0: ";
        cin >> salary;
        if(salary < 0)
            cout << "Error! input not supported, salary can't be negative try again" << endl;
    }
    while(salary < 0);
    cout << "Would you like to pay X amount to advertise your job listing?" << endl;
    cout << "Advertisement makes it so your listing is displayed in every search!\n0.No\n1.Yes" << endl;
    cin >> paid;
    job_list.push_back(make_shared<Job_Listing>(name, text, position, experience, profession, location, salary, paid, currentUser->getUid()));
    // adding to the employer the job to the array of jobs he / she has
    Employer *tmp = dynamic_cast<Employer *>(currentUser.get());
    shared_ptr<Job_Listing> lastAdded = job_list.back();
    tmp->addJobListing(lastAdded);
}

/// Function of the menu that the candidate uses
/// \param userList = user list of all users in the system
/// \param currentUser = pointer to the current user
/// \param job_list = list of all job listing in the system
void candidateMenu(list<shared_ptr<User>> &userList, shared_ptr<User> &currentUser, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int choice;
    do
    {
        cout << "\n||Welcome " << currentUser->getFirstName() << "||" << endl;
        cout << "1.Search for jobs\n2.Apply for job\n3.Upload resume\n4.View Submission history and status\n5.Edit profile\n"
                "6.Average salary calculator\n7.Leave review on employer\n8.Delete account\n"
                "9.Frequently asked question / Tips\n10.Logout" << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                searchJob(currentUser, job_list);
                break;
            }
            case 2:
            {
                candidateApplyForJob(currentUser, job_list, jobs_Submission_List);
                break;
            }
            case 4:
            {
                candidateViewSubmissionHistory(currentUser, job_list, jobs_Submission_List);
                break;
            }
            case 6:
            {
                calculateProfessionAverage(job_list);
                break;
            }
            // need to add all functions
            case 10:
                cout << "Leaving system..." << endl;
                break;
            default:
                cout << "Error! input not supported, try again" << endl;
        }
    }
    while(choice != 10);
}

/// Function of the menu that the employer uses
/// \param userList = user list of all users in the system
/// \param currentUser = pointer to the current user
/// \param job_list = list of all job listing in the system
void employerMenu(list<shared_ptr<User>> &userList, shared_ptr<User> &currentUser, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int choice;
    do
    {
        cout << "\n||Welcome " << currentUser->getFirstName() << "||" << endl;
        cout << "1.Publish submission\n2.Edit submission\n3.Delete submission\n4.View published jobs\n"
                "5.View candidate profiles to accept / deny\n""6.Search for jobs\n"
                "7.Pay to advertise\n8.Delete account\n""9.Frequently asked question / Tips\n10.Logout" << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                publishJobOffer(currentUser, job_list);
                cout << "||Successfully added listing!||" << endl;
                break;
            }
            case 4:
            {
                employerPublishedJobs(currentUser);
                break;
            }
            case 5:
            {
                employerViewCandidateSubmission(currentUser, userList, job_list, jobs_Submission_List);
                break;
            }
            // need to add all functions
            case 10:
                cout << "Leaving system..." << endl;
                break;
            default:
                cout << "Error! input not supported, try again" << endl;
        }
    }
    while(choice != 10);
}

/// Function to register a new user into the system
/// \param user = user list of all users in the system
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

/// Function to log into the system
/// \param user = user list of all users in the system
/// \param currentUser = pointer to the current user
/// \return - if login didn't happen then return null
shared_ptr<User> loginUser(list<shared_ptr<User>> &user, shared_ptr<User> &currentUser, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    string id, password;
    cout << "Type you id to login: ";
    cin >> id;
    cout << "Type your password: ";
    cin >> password;
    currentUser = nullptr;
    for(auto i = user.begin(); i != user.end(); i++)
    {
        if((*i)->getId() == id && (*i)->getPassword() == password)
            //return *i;
            currentUser = *i;
    }
    if(currentUser == nullptr)
    {
        cout << "Id or password is incorrect." << endl;
        return nullptr;
    }
    if(strcmp(currentUser->getType(), "Candidate") == 0)
        candidateMenu(user, currentUser, job_list, jobs_Submission_List);
    else if(strcmp(currentUser->getType(), "Employer") == 0)
        employerMenu(user, currentUser, job_list, jobs_Submission_List);
    return nullptr;
}

/// function of the main menu of the system
/// \param user = list of all users in the system
/// \param job_list = list of all job listing in the system
/// \return - returning null if exiting the menu
shared_ptr<User> mainMenu(list<shared_ptr<User>> &user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int choice;
    shared_ptr<User> currentUser;
    do
    {
        cout << "1.Register\n2.Login\n3.Exit" << endl;
        cin >> choice;
        if(choice <= 0 || choice >= 4)
            cout << "Not supported input, try again." << endl;
        if(choice == 1)
            registerUser(user);
        else if(choice == 2)
        {
            currentUser = loginUser(user, currentUser, job_list, jobs_Submission_List);
            if(currentUser == nullptr)
                continue;
            return currentUser;
        }
        else if(choice == 3)
            return nullptr;
    }
    while(choice != 3);
    return nullptr;
}

int main()
{
    int choice;
    // using shared ptr, so it will delete automatically without needing delete
    list<shared_ptr<User>> userList;
    shared_ptr<User> currentUser;
    list<shared_ptr<User>>::iterator i;
    list<shared_ptr<Job_Listing>> job_list;
    shared_ptr<Job_Listing> currentJob;
    list<shared_ptr<Job_Listing>>::iterator jobsIndex;
    list<shared_ptr<Job_Submission>> jobs_Submission_List;
    shared_ptr<Job_Submission> currentJobListing;
    list<shared_ptr<Job_Submission>>::iterator jobSubmissionIndex;

    cout << userList.size();
    //adding 3 admin user for testing and deleting a user to see if it works
    userList.push_back(make_shared<Candidate> ("admin", "1111", "admin", "user", 0, "none", 054));
    userList.push_back(make_shared<User> ("bdmin", "1111", "bdmin", "user", 0, "none", 054));
    userList.push_back(make_shared<Employer> ("cdmin", "1111", "cdmin", "user", 0, "none", 054));
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

    // start of the system in main
    cout << "~~~Job search system~~~" << endl;
    currentUser = mainMenu(userList, job_list, jobs_Submission_List);
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
