#include <iostream>
#include <list> // using to make lists of objects
#include <limits> // using to check maximums
#include <cctype> // using library to check if a string is using only letters
#include <memory> // library to manage dynamic memories
#include <cstring> // string library
#include <fstream> // file library
#include <vector>
#include <sstream>
#include <filesystem>
#include "User.h"
#include "Candidate.h"
#include "Employer.h"
#include "Job_Listing.h"
#include "Job_Submission.h"
#include "utils.h"
#define USERS_DATA "../DataBase/Users Data"
#define JOBS_DATA "../DataBase/Jobs Data"
#define SUBMISSIONS_DATA "../DataBase/Submissions Data"
#define RESUMES_BANK "../Resumes/" // it's the bank of all the resumes that we uploaded in "Resumes" not the saved ones in candidate
using namespace std;
namespace fs = filesystem;
int User::UID = 0, Job_Listing::UID = 0, Job_Submission::UID = 0;

// Files functions START -----------------------------------------------------------------------------------------------
/// Function to update file of user data when changing in real time
/// \param current_user
void update_user_in_file(const shared_ptr<User>& current_user) {
    ifstream inputFile(USERS_DATA);

    if (!inputFile.is_open()) {
        cerr << "Error opening users file for reading!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Read and process each line
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string id, first_name, last_name, phone_number;
        int age, location, type;

        // Extract fields
        getline(ss, id, ',');
        getline(ss, first_name, ',');
        getline(ss, last_name, ',');
        ss >> age;
        ss.ignore(1, ',');
        ss >> location;
        ss.ignore(1, ',');
        getline(ss, phone_number);

        // Check if this is the current user's record
        if (id == current_user->getId()) {
            // Update the user's information
            if(strcmp(current_user->getType(), "Candidate") == 0)
                type = 1;
            else
                type = 2;
            stringstream updated_line;
            updated_line << current_user->getId() << ","
                        << current_user->getPassword() << ","
                        << current_user->getFirstName() << ","
                        << current_user->getLastName() << ","
                        << current_user->getAge() << ","
                        << current_user->getLocationID() << ","
                        << current_user->getPhoneNumber() << ","
                        << type;
            lines.push_back(updated_line.str());
        } else {
            // Keep the line as is
            lines.push_back(line);
        }
    }
    inputFile.close();

    // Write updated lines back to the file
    ofstream outputFile(USERS_DATA, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error opening users file for writing!" << endl;
        return;
    }

    for (const auto& currentLine : lines) {
        outputFile << currentLine << "\n";
    }
    outputFile.close();
}
/// Function to update job submission name in files
/// \param oldJobName = Current job name to be replaced
/// \param newJobName = New job name
void update_job_submissions_name_in_file(const string& oldJobName, const string& newJobName)
{
    ifstream inputFile(SUBMISSIONS_DATA);

    if (!inputFile.is_open()) {
        cerr << "Error opening jobs file for reading!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Process each line in the file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string candidateId, employerId, jobName;

        // Extract fields from the line
        getline(ss, candidateId, ',');  // Candidate's id (name/email)
        getline(ss, employerId, ',');   // Employer's id (name/email)
        getline(ss, jobName, ',');      // Job name

        // Check if this line matches the job name to be updated
        if (jobName == oldJobName) {
            // Update the record with the new job name
            stringstream updated_line;
            updated_line << candidateId << "," << employerId << "," << newJobName;
            lines.push_back(updated_line.str());
        } else {
            // Keep the line as is
            lines.push_back(line);
        }
    }
    inputFile.close();
    // Write the updated lines back to the file
    ofstream outputFile(SUBMISSIONS_DATA, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error opening submissions file for writing!" << endl;
        return;
    }
    for (const auto& currentLine : lines) {
        outputFile << currentLine << "\n";
    }
    outputFile.close();
}
/// Function to update file of job listing in real time
/// \param job = job offer
/// \param newName = Have to provide name as this is key to identify when changing to a new one
void update_job_in_file(const shared_ptr<Job_Listing>& job, const string& newName) {
    ifstream inputFile(JOBS_DATA);

    if (!inputFile.is_open()) {
        cerr << "Error opening jobs file for reading!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Process each line in the file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name, description, employerIdFromFile;
        int position, experience, profession, location, salary, paid;

        // Extract fields from the line
        getline(ss, name, ',');
        getline(ss, description, ',');
        ss >> position;
        ss.ignore(1, ',');
        ss >> experience;
        ss.ignore(1, ',');
        ss >> profession;
        ss.ignore(1, ',');
        ss >> location;
        ss.ignore(1, ',');
        ss >> salary;
        ss.ignore(1, ',');
        ss >> paid;
        ss.ignore(1, ',');
        getline(ss, employerIdFromFile);

        // Check if this line matches the job to be updated
        if (name == job->getName()) {
            // Update the record with the new details
            stringstream updated_line;
            updated_line << newName << ","
                        << job->getDescription() << ","
                        << job->getPositionID() << ","
                        << job->getExperience() << ","
                        << job->getProfessionID() << ","
                        << job->getLocationID() << ","
                        << job->getSalary() << ","
                        << job->getPaid() << ","
                        << employerIdFromFile;
            lines.push_back(updated_line.str());
        } else {
            // Keep the line as is
            lines.push_back(line);
        }
    }
    inputFile.close();
    // Write the updated lines back to the file
    ofstream outputFile(JOBS_DATA, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error opening jobs file for writing!" << endl;
        return;
    }

    for (const auto& currentLine : lines) {
        outputFile << currentLine << "\n";
    }
    outputFile.close();
}

/// Function to save users to file when updating review
/// \param user_list
void save_users_in_file(const list<shared_ptr<User>>& user_list) {

    ofstream file(USERS_DATA, ios::trunc);  // Open the file in truncation mode to overwrite it

    if (!file.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // Iterate over all users and write their data to the file
    for (const auto& user : user_list) {
        file << user->getId() << "," << user->getPassword() << ","
             << user->getFirstName() << "," << user->getLastName() << ","
             << user->getAge() << "," << user->getLocationID() << ","
             << user->getPhoneNumber() << ",";

        // Save employer-specific data (reviews)
        if (auto employer = dynamic_pointer_cast<Employer>(user)) {
            file << "2"; // Type: Employer

            // Save reviews
            for (const auto& review : employer->getReviews()) {
                file << "|" << review->getReviewerFirstName() << ","
                     << review->getReviewerLastName() << "," << review->getReview();
            }
        } else if (dynamic_pointer_cast<Candidate>(user)) {
            file << "1"; // Type: Candidate
        }

        file << "\n"; // End of line for this user
    }

    file.close();
    cout << "|User data saved successfully!" << endl;
}

/// Function to delete job submission from file when deleting from candidate side
/// \param candidateID
void delete_job_submissions_by_candidate_ID(const string& candidateID) {
    ifstream inputFile(SUBMISSIONS_DATA);

    if (!inputFile.is_open()) {
        cerr << "Error opening submission file for reading!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Read all lines from the file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string candidateId, employerId, jobName;

        // Assuming the order in the file is: candidateId (ID), employerId (ID), jobName
        getline(ss, candidateId, ',');  // Candidate's ID (string)
        getline(ss, employerId, ',');   // Employer's ID (string)
        getline(ss, jobName, ',');      // Job name (string)

        // If the candidate ID doesn't match the one we want to delete, keep the line
        if (candidateId != candidateID) {
            lines.push_back(line);
        }
    }

    inputFile.close();

    // Write the updated lines back to the file
    ofstream outputFile(SUBMISSIONS_DATA, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error opening submission file for writing!" << endl;
        return;
    }

    for (const auto& currentLine : lines) {
        outputFile << currentLine << "\n";
    }
    outputFile.close();

    cout << "Job submissions associated with candidate ID " << candidateID << " have been deleted." << endl;
}

/// Function to delete job submission from file when deleting from employer side
/// \param employerID
void delete_job_submissions_by_employer_ID(const string& employerID) {
    ifstream inputFile(SUBMISSIONS_DATA);

    if (!inputFile.is_open()) {
        cerr << "Error opening submission file for reading!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Read all lines from the file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string candidateId, employerId, jobName;

        // Assuming the order in the file is: candidateId (ID), employerId (ID), jobName
        getline(ss, candidateId, ',');  // Candidate's ID (string)
        getline(ss, employerId, ',');   // Employer's ID (string)
        getline(ss, jobName, ',');      // Job name (string)

        // If the employer ID doesn't match the one we want to delete, keep the line
        if (employerId != employerID) {
            lines.push_back(line);
        }
    }

    inputFile.close();

    // Write the updated lines back to the file
    ofstream outputFile(SUBMISSIONS_DATA, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error opening submission file for writing!" << endl;
        return;
    }

    for (const auto& currentLine : lines) {
        outputFile << currentLine << "\n";
    }
    outputFile.close();

    cout << "Job submissions associated with employer ID " << employerID << " have been deleted." << endl;
}

/// Function to delete job listing from file using employer ID
/// \param employerId
void delete_job_by_employer_ID(const string& employerId) {
    ifstream inputFile(JOBS_DATA);
    if (!inputFile.is_open()) {
        cerr << "Error opening jobs file for reading!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Read all lines from the file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string jobEmployerId;
        string originalLine = line;  // Save the entire line to preserve its content

        // Assuming employer ID is the 9th comma-separated value in the job data
        for (int i = 0; i < 8; ++i) {
            getline(ss, line, ',');  // Skip the first 8 values
        }
        getline(ss, jobEmployerId, ',');  // Get the employer ID

        // If the employer ID doesn't match the one we want to delete, keep the original line
        if (jobEmployerId != employerId) {
            lines.push_back(originalLine);
        }
    }
    inputFile.close();

    // Write the updated lines back to the file
    ofstream outputFile(JOBS_DATA, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error opening jobs file for writing!" << endl;
        return;
    }

    for (const auto& currentLine : lines) {
        outputFile << currentLine << "\n";
    }
    outputFile.close();

    cout << "Job listings associated with employer ID " << employerId << " have been deleted." << endl;
}

/// Function to delete user from file list
/// \param filePath
/// \param userIdToDelete
void delete_user_from_file(const string& filePath, const string& userIdToDelete)
{
    ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Read all lines from the file and store them in a vector
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string userId;
        getline(ss, userId, ','); // Extract the first field (user ID)

        // Check if the user ID matches the one to delete
        if (userId != userIdToDelete)
            lines.push_back(line); // Keep the line if it doesn't match
    }
    inputFile.close();

    // Write the updated data back to the file
    ofstream outputFile(filePath, ios::trunc); // Open in truncate mode
    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (const auto& currentLine : lines) {
        outputFile << currentLine << "\n";
    }
    outputFile.close();

    cout << "|User with ID \"" << userIdToDelete << "\" deleted successfully!" << endl;
}

/// Function to load all jobs submissions in the file to the current run of the system
/// \param user_list
/// \param job_list
/// \param jobs_Submission_List
void load_job_applications(const list<shared_ptr<User>>& user_list, const list<shared_ptr<Job_Listing>>& job_list, list<shared_ptr<Job_Submission>>& jobs_Submission_List)
{
    ifstream file(SUBMISSIONS_DATA);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string candidateId, employerId, jobName;
            int jobUID = 0;

            // Parse the comma-separated values
            getline(ss, candidateId, ',');  // Candidate's id (name/email)
            getline(ss, employerId, ',');   // Employer's id (name/email)
            getline(ss, jobName, ',');      // Job name

            // Convert candidate and employer ids to uid's
            shared_ptr<User> candidate = nullptr;
            shared_ptr<User> employer = nullptr;

            // Find candidate by id
            for (const auto& user : user_list) {
                if (user->getId() == candidateId) {
                    candidate = user;
                    break;
                }
            }

            // Find employer by id
            for (const auto& user : user_list) {
                if (user->getId() == employerId) {
                    employer = user;
                    break;
                }
            }
            // Find job by id
            for (const auto& job:job_list){
                if(job->getName() == jobName){
                    jobUID = job->getUid();
                    break;
                }
            }

            if (candidate && employer) {
                // Create the job submission using found uids
                shared_ptr<Job_Submission> submission = make_shared<Job_Submission>(
                        candidate->getUid(), employer->getUid(), jobUID);
                jobs_Submission_List.push_back(submission);
            }
        }

        file.close();
        cout << "||Job applications loaded successfully from file!||" << endl;
    } else {
        cerr << "Error opening job submission file!" << endl;
    }
}

/// Function to load all jobs listing in the file to the current run of the system
/// \param job_list
/// \param user_list
void load_job_offers(list<shared_ptr<Job_Listing>>& job_list, const list<shared_ptr<User>>& user_list)
{
    ifstream file(JOBS_DATA);

    if (file.is_open()) {
        string line;

        // Iterate over each line in the file and load job listings
        while (getline(file, line)) {
            stringstream ss(line);
            string name, text, userId;
            int position, experience, profession, location, salary;
            bool paid;

            // Parse the comma-separated values from the file
            getline(ss, name, ',');
            getline(ss, text, ',');
            ss >> position;
            ss.ignore(); // Ignore the comma
            ss >> experience;
            ss.ignore(); // Ignore the comma
            ss >> profession;
            ss.ignore(); // Ignore the comma
            ss >> location;
            ss.ignore(); // Ignore the comma
            ss >> salary;
            ss.ignore(); // Ignore the comma
            ss >> paid;
            ss.ignore(); // Ignore the comma
            getline(ss, userId, '\n'); // User ID of the employer

            // Find the corresponding employer from user_list using userId
            shared_ptr<User> user = nullptr;
            for (const auto& u : user_list) {
                if (u->getId() == userId) {  // Match the userId from job offer
                    user = u;
                    break;
                }
            }

            // If user is found, and it's an employer, create the job listing
            if (user)
            {
                // Get the current UID of the employer
                int currentUID = user->getUid();

                // Create the job listing with the found employer's userId and UID
                shared_ptr<Job_Listing> job = make_shared<Job_Listing>(name, text, position, experience, profession, location, salary, paid, currentUID, user);
                job_list.push_back(job);

                // Optionally, you can also add the job to the employer's job list
                if (auto employer = dynamic_pointer_cast<Employer>(user)) {
                    employer->addJobListing(job);
                }
            } else {
                cerr << "Warning: Could not find user with ID " << userId << " for job offer \"" << name << "\"." << endl;
            }
        }
        file.close();
        cout << "||Job offers loaded successfully from file!||" << endl;
    } else {
        cerr << "Error opening job offers file!" << endl;
    }
}

/// Function to load all users in the file to the current run of the system
/// \param user_list
void load_users(list<shared_ptr<User>>& user_list)
{
    ifstream file(USERS_DATA);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, password, first_name, last_name;
            int age, location, phone_number, choice;

            // Parse the comma-separated values
            getline(ss, id, ',');
            getline(ss, password, ',');
            getline(ss, first_name, ',');
            getline(ss, last_name, ',');
            ss >> age;
            ss.ignore(); // Ignore the comma
            ss >> location;
            ss.ignore(); // Ignore the comma
            ss >> phone_number;
            ss.ignore(); // Ignore the comma
            ss >> choice;
            ss.ignore(); // Ignore the comma after choice

            // Create the appropriate user object
            shared_ptr<User> user;
            if (choice == 1) {
                user = make_shared<Candidate>(id, password, first_name, last_name, age, location, phone_number);
            } else if (choice == 2) {
                user = make_shared<Employer>(id, password, first_name, last_name, age, location, phone_number);
            } else {
                cerr << "Error: Invalid user type choice!" << endl;
                continue;  // Skip invalid users
            }

            // Parse reviews for Employer
            if (choice == 2) {
                string reviewData;
                while (getline(ss, reviewData, '|')) {  // Assume reviews are separated by '|'
                    stringstream reviewStream(reviewData);
                    string reviewerFirstName, reviewerLastName, reviewText;
                    // Parse reviewer name and review text
                    getline(reviewStream, reviewerFirstName, ',');
                    getline(reviewStream, reviewerLastName, ',');
                    getline(reviewStream, reviewText);

                    // Add the review to the Employer object
                    shared_ptr<Employer> employer = dynamic_pointer_cast<Employer>(user);
                    if (employer) {
                        employer->addReview(reviewText, reviewerFirstName, reviewerLastName); // Using the addReview method
                    } else {
                        cerr << "Error: User is not an employer!" << endl;
                    }
                }
            }

            // Add the user to the list
            user_list.push_back(user);
        }
        file.close();
        cout << "||Users loaded successfully from file!||" << endl;
    } else {
        cerr << "Error opening file for reading! Starting with an empty user list." << endl;
    }
}
// Files functions END -------------------------------------------------------------------------------------------------

void delete_candidate(list<shared_ptr<User>> &user_list, shared_ptr<User> &current_user, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    string name = current_user->getFirstName();
    list<shared_ptr<User>>::iterator user_list_index;
    list<shared_ptr<Job_Submission>>::iterator jobs_submission_index;
    for(jobs_submission_index = jobs_Submission_List.begin(); jobs_submission_index != jobs_Submission_List.end(); jobs_submission_index++)
        if((*jobs_submission_index)->getCandidateUID() == current_user->getUid())
        {
            jobs_submission_index = jobs_Submission_List.erase(jobs_submission_index);
            jobs_submission_index--; // erasing is making index++ so we go one down again
        }
    // deleting properly from files
    delete_user_from_file(USERS_DATA, current_user->getId());
    delete_job_submissions_by_candidate_ID(current_user->getId());
    Candidate::deleteResume(current_user->getId());
    // deleting candidate from list of users
    for(user_list_index = user_list.begin(); user_list_index != user_list.end(); user_list_index++)
    {
        if((*user_list_index)->getUid() == current_user->getUid())
        {
            user_list.erase(user_list_index);
            break;
        }
    }
    cout << "Successfully removed " << name << " from system, all job submissions related to user have been erased as well." << endl;
    cout << "Thank you for using our system." << endl;
}
/// Function that deletes completely all related information to employer
/// \param user_list = user list of all users in the system
/// \param current_user = pointer to the current user
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List = list of all submissions to listings in the system
void delete_employer(list<shared_ptr<User>> &user_list, shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    string name = current_user->getFirstName();
    list<shared_ptr<User>>::iterator user_list_index;
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    list<shared_ptr<Job_Submission>>::iterator jobs_submission_index;
    for(jobs_index = job_list.begin(); jobs_index != job_list.end(); jobs_index++)
    {
        if((*jobs_index)->getEmployerUID() == current_user->getUid())
        {
            for(jobs_submission_index = jobs_Submission_List.begin(); jobs_submission_index != jobs_Submission_List.end(); jobs_submission_index++) // deleting submission that are connected to this listing
                if((*jobs_submission_index)->getJob_listingUID() == (*jobs_index)->getUid())
                {
                    jobs_submission_index = jobs_Submission_List.erase(jobs_submission_index);
                    jobs_submission_index--; // erasing is making index++ so we go one down again
                }
            jobs_index = job_list.erase(jobs_index);
            jobs_index--; // erasing is making index++ so we go one down again
        }
    }
    // deleting properly from files
    delete_user_from_file(USERS_DATA, current_user->getId());
    delete_job_by_employer_ID(current_user->getId());  // Delete jobs associated with the employer in the "Jobs Data" file
    delete_job_submissions_by_employer_ID(current_user->getId());
    // deleting employer from list of users
    for(user_list_index = user_list.begin(); user_list_index != user_list.end(); user_list_index++)
    {
        if((*user_list_index)->getUid() == current_user->getUid())
        {
            user_list.erase(user_list_index);
            break;
        }
    }

    cout << "Successfully removed " << name << " from system, all job listing and submissions related have been erased as well." << endl;
    cout << "Thank you for using our system." << endl;
}
/// Function that deletes a job listing of a employer with UID, it also deletes any submission to this listing
/// \param current_user = pointer to the current user
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List = list of all job submissions in the system
void delete_job_listing(shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int uid;
    string name;
    bool found = false;
    Employer *employer = dynamic_cast<Employer *>(current_user.get());
    list<shared_ptr<Job_Listing>>& my_job_listings = employer->getMyJobListings(); // getting a reference to the inside list of jobs that employer has
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    list<shared_ptr<Job_Submission>>::iterator jobs_submission_index;
    shared_ptr<Job_Listing> currentJobListing;
    shared_ptr<Job_Submission> currentJobSubmission;
    cout << "Which job listing you would like to delete? type it's UID: ";
    uid = getValidInt();
    for(jobs_index = my_job_listings.begin(); jobs_index != my_job_listings.end(); jobs_index++) // deleting from employer own list
        if((*jobs_index)->getUid() == uid)
        {
            found = true;
            name = (*jobs_index)->getName();
            jobs_index = my_job_listings.erase(jobs_index);
            break;
        }
    if(!found)
    {
        cout << "Error! given UID isn't a listing, returning to main menu..." << endl;
        return;
    }
    for(jobs_submission_index = jobs_Submission_List.begin(); jobs_submission_index != jobs_Submission_List.end(); jobs_submission_index++) // deleting submission that are connected to this listing
        if((*jobs_submission_index)->getJob_listingUID() == uid)
        {
            jobs_submission_index = jobs_Submission_List.erase(jobs_submission_index);
            jobs_submission_index--; // erasing is making index++ so we go one down again
        }
    for(jobs_index = job_list.begin(); jobs_index != job_list.end(); jobs_index++) // deleting from system list
        if((*jobs_index)->getUid() == uid)
        {
            jobs_index = job_list.erase(jobs_index);
            jobs_index--; // erasing is making index++ so we go one down again
        }

    // deleting properly from files
    delete_job_by_employer_ID(current_user->getId());  // Delete jobs associated with the employer in the "Jobs Data" file
    delete_job_submissions_by_employer_ID(current_user->getId());
    cout << "|Successfully removed job listing \"" << name << "\"!" << endl;
}
void pay_to_advertise_employer(shared_ptr<User> &current_user)
{
    int choice, uid;
    Employer *employer = dynamic_cast<Employer *>(current_user.get());
    if(employer->isMyJobListingsEmpty())
    {
        cout << "You have no job listing. Returning to main menu..." << endl;
        return;
    }
    cout << "Would you like to pay X amount to advertise your listing?\n1.Yes\n2.No" << endl;
    do
    {
        choice = getValidInt();
        if(choice <= 0 || choice >= 3)
            cout << "Error! input not supported, try again" << endl;
    }
    while(choice <= 0 || choice >= 3);
    if(choice == 2)
    {
        cout << "Returning to main menu..." << endl;
        return;
    }
    list<shared_ptr<Job_Listing>> my_job_listings = employer->getMyJobListings();
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    employer->printJobListings();
    cout << "\nWhich job listing would you like to pay X to advertise? type corresponding UID: ";
    uid = getValidInt();
    for(jobs_index = my_job_listings.begin(); jobs_index != my_job_listings.end(); jobs_index++)
        if((*jobs_index)->getUid() == uid)
        {
            if((*jobs_index)->getPaid())
            {
                cout << "You already paid to advertise this listing." << endl;
                cout << "Returning to main menu..." << endl;
                return;
            }
            (*jobs_index)->setPaid(true);
            update_job_in_file(*jobs_index, (*jobs_index)->getName());
            cout << "|Paid successfully! listing is now advertised." << endl;
            cout << "Returning to main menu..." << endl;
            return;
        }
    cout << "Error! no job listing that corresponds to this UID, returning to main menu..." << endl;
}
/// Function to change parameters of a job listing that the employer published
/// \param current_user = pointer to the current user
void edit_job_listing(shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list)
{
    int choice, uid, type;
    string text;
    bool nameTaken = false;
    Employer *employer = dynamic_cast<Employer *>(current_user.get());
    list<shared_ptr<Job_Listing>> my_job_listings;
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    my_job_listings = employer->getMyJobListings();
    cout << "your published jobs: " << endl;
    for (jobs_index = my_job_listings.begin(); jobs_index != my_job_listings.end(); jobs_index++) {
        if ((*jobs_index)->getEmployerUID() == current_user->getUid())
            (*jobs_index)->print();
    }
    cout << "Type the job UID that you would like to edit: ";
    uid = getValidInt();
    for(jobs_index = my_job_listings.begin(); jobs_index != my_job_listings.end(); jobs_index++)
        if((*jobs_index)->getUid() == uid)
        {
            do
            {
                cout << "Which field would you like to edit?:" << endl;
                cout << "1.Name\n2.Description\n3.Position\n4.Experience\n5.Profession\n6.Location\n7.Salary\n8.Go back to main menu" << endl;
                choice = getValidInt();
                switch (choice)
                {
                    case 1:
                    {
                        cout << "Type new name: ";
                        cin.ignore(); // completely clears the input
                        while(true)
                        {
                            nameTaken = false;
                            getline(cin, text);
                            for(auto i = job_list.begin(); i != job_list.end(); i++)
                                if((*i)->getName() == text)
                                {
                                    cout << "This job name is already used, please input another name: ";
                                    nameTaken = true;
                                }
                            if(nameTaken)
                                continue;
                            if(!text.empty())
                                break;
                            cout << "Name cannot be empty. Please enter again: ";
                        }
                        update_job_in_file(*jobs_index, text);
                        update_job_submissions_name_in_file((*jobs_index)->getName(), text);
                        (*jobs_index)->setName(text);
                        cout << "|Successfully changed name, going back to editing menu..." << endl;
                        break;
                    }
                    case 2:
                    {
                        cout << "Type new description: ";
                        cin.ignore(); // completely clears the input
                        while(true)
                        {
                            getline(cin, text);
                            if(!text.empty())
                                break;
                            cout << "description cannot be empty. Please enter again: ";
                        }
                        (*jobs_index)->setDescription(text);
                        cout << "|Successfully changed description, going back to editing menu..." << endl;
                        break;
                    }
                    case 3:
                    {
                        do
                        {
                            cout << "What is the new position of this job?:\n1.Full-time\n2.Half-time\n";
                            type = getValidInt();
                            if(type != 1 && type != 2)
                                cout << "Error! input not supported, try again" << endl;
                        }
                        while(type != 1 && type != 2);
                        (*jobs_index)->setPosition(type);
                        cout << "|Successfully changed position, going back to editing menu..." << endl;
                        break;
                    }
                    case 4:
                    {
                        do
                        {
                            cout << "How many years of experience are you looking for?:\n0.No experience\n1.1 year\n2.2 years\n3.3 years\n4.4 years\n5.5+ years\n";
                            type = getValidInt();
                            if(type < 0 || type > 5)
                                cout << "Error! input not supported, try again" << endl;
                        }
                        while(type < 0 || type > 5);
                        (*jobs_index)->setExperience(type);
                        cout << "|Successfully changed experience, going back to editing menu..." << endl;
                        break;
                    }
                    case 5:
                    {
                        do
                        {
                            cout << "What profession are you looking for?:\n1.Software engineer\n2.Electrical engineer\n3.Civil engineer\n"
                                    "4.Mechanical engineer\n5.Industrial engineering and management\n6.Chemical engineering\n7.None\n";
                            type = getValidInt();
                            if(type <= 0 || type >= 8)
                                cout << "Error! input not supported, try again" << endl;
                        }
                        while(type <= 0 || type >= 8);
                        (*jobs_index)->setProfession(type);
                        cout << "|Successfully changed profession, going back to editing menu..." << endl;
                        break;
                    }
                    case 6:
                    {
                        do
                        {
                            cout << "Which new location is this job located?:\n1.Jerusalem region\n2.Northern region\n3.Haifa region\n"
                                    "4.Central region\n5.Tel-Aviv region\n6.Southern region\n7.No location\n";
                            type = getValidInt();
                            if(type <= 0 || type >= 8)
                                cout << "Error! input not supported, try again" << endl;
                        }
                        while(type <= 0 || type >= 8);
                        (*jobs_index)->setLocation(type);
                        cout << "|Successfully changed location, going back to editing menu..." << endl;
                        break;
                    }
                    case 7:
                    {
                        do
                        {
                            cout << "What is the new salary of the job?\nNote: If you would like to not specify the amount input 0: ";
                            type = getValidInt();
                            if(type < 0)
                                cout << "Error! input not supported, salary can't be negative try again" << endl;
                        }
                        while(type < 0);
                        (*jobs_index)->setSalary(type);
                        cout << "|Successfully changed salary, going back to editing menu..." << endl;
                        break;
                    }
                    case 8:
                        cout << "Going back to main menu..." << endl;
                        break;
                    default:
                        cout << "Error! input not supported, try again" << endl;
                }
                if (choice != 8 && choice != 1) // Update the job listing in the file
                    update_job_in_file(*jobs_index, (*jobs_index)->getName());
            }
            while(choice != 8);
            return;
        }
    cout << "Error! given UID isn't a listing, returning to main menu..." << endl;
}
/// Function that prints the employer reviews
/// \param current_user = pointer to the current user
void employer_view_own_reviews(shared_ptr<User> &current_user)
{
    Employer *employer = dynamic_cast<Employer *>(current_user.get());
    employer->printReviews();
}
/// Function for candidate to view an employer reviews
/// \param user_list = list of all users in the system
void view_reviews(list<shared_ptr<User>> &user_list)
{
    string first_name, last_name;
    list<shared_ptr<User>>::iterator user_list_index;
    cout << "Type the full name of the employer you would like to see reviews of" << endl;
    cout << "First name: ";
    cin.ignore();
    first_name = getValidString();
    cout << "Last name: ";
    last_name = getValidString();
    for(user_list_index = user_list.begin(); user_list_index != user_list.end(); user_list_index++)
        if((*user_list_index)->getFirstName() == first_name && (*user_list_index)->getLastName() == last_name)
        {
            if(strcmp((*user_list_index)->getType(), "Employer") != 0)
            {
                cout << "Error! user is not an employer, returning to main menu..." << endl;
                return;
            }
            Employer *employer = dynamic_cast<Employer *>(user_list_index->get());
            employer->printReviews();
            return;
        }
    cout << "Error! user given isn't in the system, returning to main menu" << endl;
}
/// Function to add a review to a specific employer
/// \param current_user = pointer to the current user
/// \param user_list = list of all users in the system
void addReview(shared_ptr<User> &current_user, list<shared_ptr<User>> &user_list)
{
    string first_name, last_name, text;
    list<shared_ptr<User>>::iterator user_list_index;
    cout << "To leave a review type the employer first name and last name" << endl;
    cout << "First name: ";
    cin.ignore();
    first_name = getValidString();
    cout << "Last name: ";
    last_name = getValidString();
    for(user_list_index = user_list.begin(); user_list_index != user_list.end(); user_list_index++)
        if((*user_list_index)->getFirstName() == first_name && (*user_list_index)->getLastName() == last_name)
        {
            if(strcmp((*user_list_index)->getType(), "Employer") != 0)
            {
                cout << "Error! this user isn't an employer therefore you can't leave a review on it's profile" << endl;
                cout << "Returning to main menu..." << endl;
                return;
            }
            cout << "Type your review: ";
            getline(cin, text);
            Employer *employer = dynamic_cast<Employer *>(user_list_index->get());
            employer->addReview(text, current_user->getFirstName(), current_user->getLastName());
            // Save updated data immediately after review is added
            save_users_in_file(user_list);  // Save data directly after review is added
            cout << "|Added review successfully! returning to main menu..." << endl;
            return;
        }
    cout << "Error! user given isn't in the system, returning to main menu..." << endl;
}
/// Function to edit profile
/// \param current_user = pointer to the current user
void edit_profile(shared_ptr<User> &current_user)
{
    int choice, number, location;
    string text;
    do
    {
        cout << "What would you like to edit?\n1.First name\n2.Last name\n3.Age\n4.Location\n5.Phone number\n6.Resume\n7.Go back to main menu" << endl;
        choice = getValidInt();
        switch (choice)
        {
            case 1:
                cout << "Type new first name: ";
                cin.ignore();
                text = getValidString();
                current_user->setFirstName(text);
                cout << "|Changed first name successfully!\n going back to editing menu..." << endl;
                break;
            case 2:
                cout << "Type new last name: ";
                cin.ignore();
                text = getValidString();
                current_user->setLastName(text);
                cout << "|Changed last name successfully!\n going back to editing menu..." << endl;
                break;
            case 3:
            {
                cout << "Type your age: ";
                do
                {
                    number = getValidInt();
                    if(number < 0)
                        cerr << "Error! age cannot be a negative number, try again: ";
                    else if(number < 18)
                        cout << "You can't change your age to below 18, try again: " << endl;
                }
                while(number < 18);
                current_user->setAge(number);
                cout << "|Changed age successfully!\n going back to editing menu..." << endl;
                break;
            }
            case 4:
                cout << "What is your new region of living?: " << endl;
                cout << "1.Jerusalem region\n2.Northern region\n3.Haifa region\n4.Central region\n5.Tel-Aviv region\n6.Southern region\n";
                do
                {
                    location = getValidInt();
                    if(location <= 0 || location >= 7)
                        cout << "Error! input not supported, try again" << endl;
                }
                while(location <= 0 || location >= 7);
                current_user->setLocation(location);
                cout << "|Changed location successfully!\n going back to editing menu..." << endl;
                break;
            case 5:
            {
                bool is9Digit = false;
                do
                {
                    cout << "Type in your new phone number in format XXXXXXXXX (9 digits without 0 at the start): 0";
                    number = getValidInt();
                    if(is9DigitInt(number))
                        is9Digit = true;
                    else
                        cout << "Number given isn't 9 digits, try again" << endl;
                }
                while(!is9Digit);
                current_user->setPhoneNumber(number);
                cout << "|Changed phone number successfully!\n going back to editing menu..." << endl;
                break;
            }
            case 6:
            {
                string filepath;
                Candidate* candidate = dynamic_cast<Candidate*>((current_user).get());
                cout << "Type the new file name in Resumes you want to change your resume to: ";
                cin >> filepath;
                candidate->changeResume(RESUMES_BANK+filepath);
                break;
            }
            case 7:
                cout << "Going back to main menu..." << endl;
                break;
            default:
                cout << "Error! input not supported, try again" << endl;
        }
    }
    while(choice != 7);
    // Persist changes to the file after editing
    update_user_in_file(current_user);
}
/// Function to view and accept submission that employer received
/// \param current_user = pointer to the current user
/// \param user_list = list of all users in the system
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List =  list of all job submissions in the system
void employer_view_candidate_submission(shared_ptr<User> &current_user, list<shared_ptr<User>> &user_list, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    bool found = false;
    int choice, counter = 0;
    list<shared_ptr<User>>::iterator candidate_index;
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    list<shared_ptr<Job_Submission>>::iterator job_submission_index;
    for(job_submission_index = jobs_Submission_List.begin(); job_submission_index != jobs_Submission_List.end(); job_submission_index++)
    {
        if((*job_submission_index)->getEmployerUID() == current_user->getUid() && (*job_submission_index)->getStatus() == "Waiting for response")
        {
            cout << "\\\\Submission " << ++counter << " waiting for response//" << endl;
            found = true;
            for(jobs_index = job_list.begin(); jobs_index != job_list.end(); jobs_index++)
                if((*jobs_index)->getUid() == (*job_submission_index)->getJob_listingUID())
                {
                    (*jobs_index)->print();
                    break;
                }
            for(candidate_index = user_list.begin(); candidate_index != user_list.end(); candidate_index++)
                if((*candidate_index)->getUid() == (*job_submission_index)->getCandidateUID())
                {
                    cout << "---Candidate information---" << endl;
                    (*candidate_index)->print();
                    Candidate* candidate = dynamic_cast<Candidate*>((*candidate_index).get());
                    cout << candidate->getResume();
                    break;
                }
            cout << "[^Submission UID: " << (*job_submission_index)->getUid() << "^]\n" << endl;
        }
    }
    if(!found)
    {
        cout << "No submission(s) to view yet." << endl;
        return;
    }
    cout << "-------------------------------" << endl;
    do
    {
        cout << "Would you like to accept / reject a submission?\n1.Yes\n2.No" << endl;
        choice = getValidInt();
        if(choice != 1 && choice != 2)
            cout << "Error! input not supported, try again" << endl;
    }
    while(choice != 1 && choice != 2);
    if(choice == 1)
    {
        cout << "Type the submission UID that you would like to accept / reject: ";
        choice = getValidInt();
        found = false;
        for(job_submission_index = jobs_Submission_List.begin(); job_submission_index != jobs_Submission_List.end(); job_submission_index++)
        {
            if((*job_submission_index)->getUid() == choice && (*job_submission_index)->getEmployerUID() == current_user->getUid())
            {
                do
                {
                    found = true;
                    cout << "What action would you like to do?\n1.Accept\n2.Reject\n3.Nothing" << endl;
                    choice = getValidInt();
                    if(choice <= 0 || choice >= 4)
                        cout << "Error! input not supported, try again" << endl;
                }
                while(choice <= 0 || choice >= 4);
                (*job_submission_index)->setStatus(choice);
                if(choice == 1)
                    cout << "|Successfully accepted submission!" << endl;
                else if(choice == 2)
                    cout << "|Successfully rejected submission!" << endl;
            }
        }
        if(!found)
            cout << "Error! given UID isn't a submission." << endl;
    }
    cout << "Returning to menu..." << endl;
}
/// function for candidate to view his submission history and check it's current status
/// \param current_user = pointer to the current user
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List = list of all job submissions in the system
void candidate_view_submission_history(shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    bool found = false;
    list<shared_ptr<Job_Listing>>::reverse_iterator jobs_index;
    list<shared_ptr<Job_Submission>>::reverse_iterator job_submission_index;
    // finding all candidate job submissions trough UID
    for(job_submission_index = jobs_Submission_List.rbegin(); job_submission_index != jobs_Submission_List.rend(); ++job_submission_index)
    {
        if((*job_submission_index)->getCandidateUID() == current_user->getUid())
        {
            found = true;
            // if found a job submission then find it's listing and print it
            for(jobs_index = job_list.rbegin(); jobs_index != job_list.rend(); ++jobs_index)
                if((*jobs_index)->getUid() == (*job_submission_index)->getJob_listingUID())
                {
                    (*jobs_index)->print();
                    break;
                }
            cout << " - Current status is: " << (*job_submission_index)->getStatus() << endl;
            cout << "-------------------------------" << endl;
        }
    }
    if(!found)
        cout << "No submission(s)." << endl;
}
/// function for candidate to apply to a job listing
/// \param current_user = pointer to the current user
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List = list of all job submissions in the system
void candidate_apply_for_job(shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int uid;
    bool found = false;
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    shared_ptr<Job_Listing> current_job;
    cout << "Type the UID of the job you would like to apply to: ";
    cin >> uid;
    // finding if the given job uid exist in the database
    for(jobs_index = job_list.begin(); jobs_index != job_list.end(); jobs_index++)
        if(uid == (*jobs_index)->getUid())
        {
            current_job = *jobs_index;
            found = true;
        }
    if(!found)
    {
        cout << "Error! given UID does not exist in the system, redirecting to menu." << endl;
        return;
    }
    jobs_Submission_List.push_back(make_shared<Job_Submission>(current_user->getUid(), current_job->getEmployerUID(), current_job->getUid()));

    weak_ptr<User> current_employer = current_job->getEmployer();
    // Lock the weak_ptr to get a shared_ptr
    shared_ptr<User> employer = current_employer.lock();
    // Create and write to the file
    ofstream file(SUBMISSIONS_DATA, ios::app);
    if (file.is_open())
    {
        // Save the submissions data (user ID, job UID, employer UID)
        file << current_user->getId() << ","  // Candidate's user ID
             << employer->getId() << ","  // Employer's user ID
             << current_job->getName() << ","  // Job name
             << "\n";

        file.close();
    }
    else
        cerr << "Error opening file for writing!" << endl;

    cout << "|Successfully applied to job listing \"" << current_job->getName() << "\"" << endl;
}
/// Function that is printing all the jobs under pointed employer
/// \param current_user = pointer to the current user
void employer_published_jobs(shared_ptr<User> &current_user)
{
    Employer *employer = dynamic_cast<Employer *>(current_user.get());
    employer->printJobListings();
}
/// Calculate the average of a chosen profession
/// \param job_list = list of all job listing in the system
void calculate_profession_average_salary(list<shared_ptr<Job_Listing>> &job_list)
{
    int choice;
    int size = 0;
    float sum = 0.0;
    float average = 0.0;
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    do
    {
        cout << "Which profession would you like to check the average?:\n1.Software engineer\n2.Electrical engineer\n3.Civil engineer\n"
                "4.Mechanical engineer\n5.Industrial engineering and management\n6.Chemical engineering\n";
        cin >> choice;
        if(choice <= 0 || choice >= 7)
            cout << "Error! input not supported, try again" << endl;
    }
    while(choice <= 0 || choice >= 7);
    for(jobs_index = job_list.begin(); jobs_index != job_list.end(); jobs_index++)
        if((*jobs_index)->getProfession() == (*jobs_index)->getProfessionID(choice) && (*jobs_index)->getSalary() > 0)
        {
            sum += float((*jobs_index)->getSalary());
            size++;
        }
    if(size == 0)
    {
        cout << "There is no job in the system with a specified salary in this profession." << endl;
        return;
    }
    average = sum / float(size);
    cout << "The average is: " << average << endl;
}
/// Search function for Candidate
/// \param current_user = pointer to the current user
/// \param job_list = list of all job listing in the system
void search_job(shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int position, experience, profession, location, choice = 0;
    bool found = false;
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    do
    {
        if(strcmp(current_user->getType(), "Candidate") == 0)
            cout << "What position would you like search for?:\n1.Full-time\n2.Half-time\n";
        else if(strcmp(current_user->getType(), "Employer") == 0)
            cout << "What position would you like to research jobs offerings?:\n1.Full-time\n2.Half-time\n";
        position = getValidInt();
        if(position != 1 && position != 2)
            cout << "Error! input not supported, try again" << endl;
    }
    while(position != 1 && position != 2);
    do
    {
        if(strcmp(current_user->getType(), "Candidate") == 0)
            cout << "In which profession are you looking for a job?:\n1.Software engineer\n2.Electrical engineer\n3.Civil engineer\n"
                    "4.Mechanical engineer\n5.Industrial engineering and management\n6.Chemical engineering\n7.No profession\n";
        else if(strcmp(current_user->getType(), "Employer") == 0)
            cout << "In which profession are you looking to search jobs?:\n1.Software engineer\n2.Electrical engineer\n3.Civil engineer\n"
                    "4.Mechanical engineer\n5.Industrial engineering and management\n6.Chemical engineering\n7.No profession\n";
        profession = getValidInt();
        if(profession <= 0 || profession >= 8)
            cout << "Error! input not supported, try again" << endl;
    }
    while(profession <= 0 || profession >= 8);
    do
    {
        if(profession == 7)
        {
            experience = 0;
            break;
        }
        if(strcmp(current_user->getType(), "Candidate") == 0)
            cout << "How many years of experience do you have?:\n0.No experience\n1.1 year\n2.2 years\n3.3 years\n4.4 years\n5.5+ years\n";
        else if(strcmp(current_user->getType(), "Employer") == 0)
            cout << "How many years of experience would you like to search jobs in?:\n0.No experience\n1.1 year\n2.2 years\n3.3 years\n4.4 years\n5.5+ years\n";
        experience = getValidInt();
        if(experience < 0 || experience > 5)
            cout << "Error! input not supported, try again" << endl;
    }
    while(experience < 0 || experience > 5);
    do
    {
        cout << "Which location would you like to search in?:\n1.Jerusalem region\n2.Northern region\n3.Haifa region\n"
                "4.Central region\n5.Tel-Aviv region\n6.Southern region\n7.Doesn't matter" << endl;
        location = getValidInt();
        if(location <= 0 || location >= 8)
            cout << "Error! input not supported, try again" << endl;
    }
    while(location <= 0 || location >= 8);
    for(jobs_index = job_list.begin(); jobs_index != job_list.end(); jobs_index++)
        if((*jobs_index)->getPaid())
        {
            found = true;
            (*jobs_index)->print();
            cout << "^^^Paid advertisement^^^" << endl;
        }
    for(jobs_index = job_list.begin(); jobs_index != job_list.end(); jobs_index++)
        if((*jobs_index)->getPosition() == (*jobs_index)->getPositionID(position) && (*jobs_index)->getExperience() <= experience &&
        ((*jobs_index)->getProfession() == (*jobs_index)->getProfessionID(profession) || (*jobs_index)->getProfession() == "None")  &&
        ((*jobs_index)->getLocation() == (*jobs_index)->getLocationID(location) || location == 7 || (*jobs_index)->getLocation() == "None") &&
        !(*jobs_index)->getPaid())
        {
            found = true;
            (*jobs_index)->print();
        }
    if(!found)
    {
        cout << "No result found!\n" << endl;
        return;
    }
    if(strcmp(current_user->getType(), "Candidate") == 0)
    {
        do
        {
            cout << "\nWould you like to apply for a job?\n1. Yes\n2. No" << endl;
            choice = getValidInt();
            if(choice <= 0 || choice >= 3)
                cout << "Error! input not supported, try again" << endl;
        }
        while(choice <= 0 || choice >= 3);
    }
    if(choice == 1)
        candidate_apply_for_job(current_user, job_list, jobs_Submission_List);
    cout << endl;
}

/// Publish function for employer
/// \param current_user = pointer to the current user
/// \param job_list = list of all job listing in the system
void publish_job_offer(shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list)
{
    string name, text;
    int position, experience, profession, location, salary;
    bool paid, nameTaken = false;
    cout << "||Publishing a job offer||" << endl;
    cout << "Type the name of the job offer: ";
    cin.ignore(); // completely clears the input
    while(true)
    {
        nameTaken = false;
        getline(cin, name);
        for(auto i = job_list.begin(); i != job_list.end(); i++)
            if((*i)->getName() == name)
            {
                cout << "This job name is already used, please input another name: ";
                nameTaken = true;
            }
        if(nameTaken)
            continue;
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
        position = getValidInt();
        if(position != 1 && position != 2)
            cout << "Error! input not supported, try again" << endl;
    }
    while(position != 1 && position != 2);
    do
    {
        cout << "What profession are you looking for?:\n1.Software engineer\n2.Electrical engineer\n3.Civil engineer\n"
                "4.Mechanical engineer\n5.Industrial engineering and management\n6.Chemical engineering\n7.None\n";
        profession = getValidInt();
        if(profession <= 0 || profession >= 8)
            cout << "Error! input not supported, try again" << endl;
    }
    while(profession <= 0 || profession >= 8);
    do
    {
        if(profession == 7)
        {
            experience = 0;
            cout << "Defaulting years of experience to '0' as no profession was selected" << endl;
            break;
        }
        cout << "How many years of experience in the profession are you looking for?:\n0.No experience\n1.1 year\n2.2 years\n3.3 years\n4.4 years\n5.5+ years\n";
        experience = getValidInt();
        if(experience < 0 || experience > 5)
            cout << "Error! input not supported, try again" << endl;
    }
    while(experience < 0 || experience > 5);
    do
    {
        cout << "Which location is this job located?:\n1.Jerusalem region\n2.Northern region\n3.Haifa region\n"
                "4.Central region\n5.Tel-Aviv region\n6.Southern region\n7.No location\n";
        location = getValidInt();
        if(location <= 0 || location >= 8)
            cout << "Error! input not supported, try again" << endl;
    }
    while(location <= 0 || location >= 8);
    do
    {
        cout << "What is the salary of the job?\nNote: If you would like to not specify the amount input 0: ";
        salary = getValidInt();
        if(salary < 0)
            cout << "Error! input not supported, salary can't be negative try again" << endl;
    }
    while(salary < 0);
    cout << "Would you like to pay X amount to advertise your job listing?" << endl;
    cout << "Advertisement makes it so your listing is displayed in every search!\n0.No\n1.Yes" << endl;
    paid = getValidInt();
    job_list.push_back(make_shared<Job_Listing>(name, text, position, experience, profession, location, salary, paid, current_user->getUid(), current_user));
    // adding to the employer the job to the array of jobs he / she has
    Employer *tmp = dynamic_cast<Employer *>(current_user.get());
    shared_ptr<Job_Listing> last_added = job_list.back();
    tmp->addJobListing(last_added);

    // Create and write to the file
    ofstream file(JOBS_DATA, ios::app); // Open file in append mode
    if (file.is_open())
    {
        file << name << "," << text << "," << position << "," << experience << ","
             << profession << "," << location << "," << salary << "," << paid << ","
             << current_user->getId() << "\n"; // Save the job listing details

        file.close();
    }
    else
        cerr << "Error opening file for writing!" << endl;
    cout << "||Successfully added listing!||" << endl;
}

/// Function of the menu that the candidate uses
/// \param user_list = user list of all users in the system
/// \param current_user = pointer to the current user
/// \param job_list = list of all job listing in the system
void candidate_menu(list<shared_ptr<User>> &user_list, shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int choice;
    do
    {
        current_user->printMenu();
        do
        {
            choice = getValidInt(); // checking if choice is valid input (also checking if integer)
            if(choice <= 0 || choice >= 13)
                cout << "Error! input not supported, try again" << endl;
        }
        while(choice <= 0 || choice >= 13);
        switch (choice)
        {
            case 1:
            {
                search_job(current_user, job_list, jobs_Submission_List);
                break;
            }
            case 2:
            {
                candidate_apply_for_job(current_user, job_list, jobs_Submission_List);
                break;
            }
            case 3:
            {
                Candidate* candidate = dynamic_cast<Candidate*>((current_user).get());
                if(candidate->getGotResume())
                {
                    cout << "You already uploaded a resume, returning to main menu..." << endl;
                    break;
                }
                string path;
                cout << "Type the file name in Resumes:" << endl;
                cin >> path;
                current_user->uploadResume(RESUMES_BANK+path);
                break;
            }
            case 4:
            {
                candidate_view_submission_history(current_user, job_list, jobs_Submission_List);
                break;
            }
            case 5:
            {
                current_user->print();
                break;
            }
            case 6:
            {
                edit_profile(current_user);
                break;
            }
            case 7:
            {
                calculate_profession_average_salary(job_list);
                break;
            }
            case 8:
            {
                addReview(current_user, user_list);
                break;
            }
            case 9:
            {
                view_reviews(user_list);
                break;
            }
            case 10:
            {
                cout << "Are you sure you would like to delete your user? this action is irreversible!\n1.Yes\n2.No" << endl;
                do
                {
                    choice = getValidInt(); // checking if choice is valid input (also checking if integer)
                    if(choice <= 0 || choice >= 3)
                        cout << "Error! input not supported, try again" << endl;
                }
                while(choice <= 0 || choice >= 3);
                if(choice == 2)
                {
                    cout << "Cancelled deletion of user, returning to main menu..." << endl;
                    break;
                }
                delete_candidate(user_list, current_user, jobs_Submission_List);
                choice = 12;
                break;
            }
            case 11:
            {
                current_user->printFAQ();
                break;
            }
            case 12:
                cout << "Leaving system..." << endl;
                break;
            default:
                cout << "Error! input not supported, try again" << endl;
        }
    }
    while(choice != 12);
}

/// Function of the menu that the employer uses
/// \param user_list = user list of all users in the system
/// \param current_user = pointer to the current user
/// \param job_list = list of all job listing in the system
/// \param jobs_Submission_List = list of all submissions to listings in the system
void employer_menu(list<shared_ptr<User>> &user_list, shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int choice;
    do
    {
        current_user->printMenu();
        do
        {
            choice = getValidInt(); // checking if choice is valid input (also checking if integer)
            if((choice <= 0 || choice >= 13))
                cout << "Error! input not supported, try again" << endl;
        }
        while(choice <= 0 || choice >= 13);
        switch (choice)
        {
            case 1:
            {
                publish_job_offer(current_user, job_list);
                break;
            }
            case 2:
            {
                edit_job_listing(current_user, job_list);
                break;
            }
            case 3:
            {
                delete_job_listing(current_user, job_list, jobs_Submission_List);
                break;
            }
            case 4:
            {
                employer_published_jobs(current_user);
                break;
            }
            case 5:
            {
                current_user->print();
                break;
            }
            case 6:
            {
                employer_view_candidate_submission(current_user, user_list, job_list, jobs_Submission_List);
                break;
            }
            case 7:
            {
                search_job(current_user, job_list, jobs_Submission_List);
                break;
            }
            case 8:
            {
                employer_view_own_reviews(current_user);
                break;
            }
            case 9:
            {
                pay_to_advertise_employer(current_user);
                break;
            }
            case 10:
            {
                cout << "Are you sure you would like to delete your user? this action is irreversible!\n1.Yes\n2.No" << endl;
                do
                {
                    choice = getValidInt(); // checking if choice is valid input (also checking if integer)
                    if(choice <= 0 || choice >= 3)
                        cout << "Error! input not supported, try again" << endl;
                }
                while(choice <= 0 || choice >= 3);
                if(choice == 2)
                {
                    cout << "Cancelled deletion of user, returning to main menu..." << endl;
                    break;
                }
                delete_employer(user_list, current_user, job_list, jobs_Submission_List);
                choice = 12;
                break;
            }
            case 11:
            {
                current_user->printFAQ();
                break;
            }
            case 12:
                cout << "Leaving system..." << endl;
                break;
            default:
                cout << "Error! input not supported, try again" << endl;
        }
    }
    while(choice != 12);
}

/// Function to register a new user into the system
/// \param user = user list of all users in the system
void register_user(list<shared_ptr<User>> &user)
{
    int choice;
    bool is9Digit = false, idTaken = false;
    cout << "Which user are you?\n1.Candidate\n2.Employer" << endl;
    choice = getValidInt();
    if(choice != 1 && choice != 2)
    {
        cout << "Error, input not supported, redirecting...." << endl;
        return;
    }
    string id, password, first_name, last_name;
    int age, location, phone_number;
    do
    {
        idTaken = false;
        cout << "Type your id: ";
        cin >> id;
        for(auto i = user.begin(); i != user.end(); i++)
            if((*i)->getId() == id)
                idTaken = true;
        if(idTaken)
            cout << "This id is already used by another user, please input another id." << endl;
    }
    while(idTaken);
    cout << "Type your password: ";
    cin >> password;
    cin.ignore();
    do
    {
        cout << "Type you first name: ";
        first_name = getValidString();
        if (first_name.length() > 44)
            cerr << "Error: First name is too long, try again with less characters: ";
    }
    while(first_name.length() > 44);
    cout << "Type your last name: ";
    last_name = getValidString();
    cout << "What is your age?: ";
    do
    {
        age = getValidInt();
        if(age < 0)
            cerr << "Error! age cannot be a negative number, try again: ";
        else if(age < 18)
        {
            cout << "Minors are not accepted in the system, returning to main menu..." << endl;
            return;
        }
    }
    while(age < 18);
    cout << "What is your region of living?: " << endl;
    cout << "1.Jerusalem region\n2.Northern region\n3.Haifa region\n4.Central region\n5.Tel-Aviv region\n6.Southern region\n";
    do
    {
        location = getValidInt();
        if(location <= 0 || location >= 7)
            cout << "Error! input not supported, try again" << endl;
    }
    while(location <= 0 || location >= 7);
    do
    {
        cout << "Type in your phone number in format XXXXXXXXX (9 digits without 0 at the start): 0";
        phone_number = getValidInt();
        if(is9DigitInt(phone_number))
            is9Digit = true;
        else
            cout << "Number given isn't 9 digits, try again" << endl;
    }
    while(!is9Digit);
    if(choice == 1)
         user.push_back(make_shared<Candidate>(id, password, first_name, last_name, age, location, phone_number));
    else if(choice == 2)
        user.push_back(make_shared<Employer>(id, password, first_name, last_name, age, location, phone_number));


    // Create and write to the file
    ofstream file(USERS_DATA, ios::app); // Open file in append mode
    if (file.is_open())
    {
        file << id << "," << password << "," << first_name << "," << last_name << ","
             << age << "," << location << "," << phone_number << "," << choice << "\n";
        file.close();
        cout << "|User registered and saved successfully!" << endl;
    }
    else
        cerr << "Error opening file for writing!" << endl;
}

/// Function to log into the system
/// \param user = user list of all users in the system
/// \param current_user = pointer to the current user
/// \return - if login didn't happen then return null
shared_ptr<User> login_user(list<shared_ptr<User>> &user, shared_ptr<User> &current_user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    string id, password;
    cout << "Type your id to login: ";
    cin >> id;
    cout << "Type your password: ";
    cin >> password;
    current_user = nullptr;
    for(auto i = user.begin(); i != user.end(); i++)
        if((*i)->getId() == id && (*i)->getPassword() == password)
            current_user = *i;
    if(current_user == nullptr)
    {
        cout << "Id or password is incorrect." << endl;
        return nullptr;
    }
    if(strcmp(current_user->getType(), "Candidate") == 0)
        candidate_menu(user, current_user, job_list, jobs_Submission_List);
    else if(strcmp(current_user->getType(), "Employer") == 0)
        employer_menu(user, current_user, job_list, jobs_Submission_List);
    return nullptr;
}

/// function of the main menu of the system
/// \param user = list of all users in the system
/// \param job_list = list of all job listing in the system
/// \return - returning null if exiting the menu
shared_ptr<User> main_menu(list<shared_ptr<User>> &user, list<shared_ptr<Job_Listing>> &job_list, list<shared_ptr<Job_Submission>> &jobs_Submission_List)
{
    int choice;
    shared_ptr<User> current_user;
    do
    {
        cout << "1.Register\n2.Login\n3.Exit" << endl;
        choice = getValidInt();
        if(choice <= 0 || choice >= 4)
            cout << "Not supported input, try again." << endl;
        if(choice == 1)
            register_user(user);
        else if(choice == 2)
        {
            current_user = login_user(user, current_user, job_list, jobs_Submission_List);
            if(current_user == nullptr)
                continue;
            return current_user;
        }
        else if(choice == 3)
            return nullptr;
    }
    while(choice != 3);
    return nullptr;
}

int main()
{
    // using shared ptr, so it will delete automatically without needing to delete
    // test
    list<shared_ptr<User>> user_list;
    shared_ptr<User> current_user;
    list<shared_ptr<User>>::iterator i;
    list<shared_ptr<Job_Listing>> job_list;
    shared_ptr<Job_Listing> current_job;
    list<shared_ptr<Job_Listing>>::iterator jobs_index;
    list<shared_ptr<Job_Submission>> jobs_Submission_List;
    shared_ptr<Job_Submission> currentJobListing;
    list<shared_ptr<Job_Submission>>::iterator job_submission_index;

    // Loading data properly from files of previous runs
    load_users(user_list);
    load_job_offers(job_list, user_list);
    load_job_applications(user_list, job_list, jobs_Submission_List);

    // start of the system in main
    cout << "~~~Job search system~~~" << endl;
    current_user = main_menu(user_list, job_list, jobs_Submission_List);
    if (current_user == nullptr)
    {
        cout << "Goodbye!" << endl;
        return 0;
    }
    return 0;
}