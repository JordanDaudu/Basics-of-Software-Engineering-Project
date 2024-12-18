//
// Created by Jordan Daudu on 14/11/2024.
//

#include "Candidate.h"
#include "utils.h"
#include <vector>
#define CANDIDATE_RESUMES "../DataBase/Candidate Resumes"

Candidate::Candidate(): User()
{gotResume = false; loadResume();}
Candidate::Candidate(string id, string password, string firstName, string lastName, int age, string loc,
                     unsigned int phoneNum): User(id, password, firstName, lastName, age, loc, phoneNum)
{gotResume = false; loadResume();}
Candidate::Candidate(string id, string password, string firstName, string lastName, int age,
                     int loc, int phoneNum): User(id, password, firstName, lastName, age, loc, phoneNum)
{gotResume = false; loadResume();}
Candidate::~Candidate()
{
    //cout << "Candidate::destructor" << endl;
}
char *Candidate::getType() const
{
    return "Candidate";
}
string Candidate::getResume() const
{
    if (this->gotResume)
    {
        cout << "\n|Resume content:" << endl;
        return resume;
    }
    cout << "Resume content: No resume found for " << this->getId();
    return "\n";
}
bool Candidate::getGotResume() const {return gotResume;}
void Candidate::printMenu() const
{
    string topBorder = "+------------------------------------------------------+";
    string bottomBorder = "+------------------------------------------------------+";
    string divider = "|                                                      |";

    cout << topBorder << endl;
    cout << "|" << string((54 - 8 - firstName.length()) / 2, ' ') << "Welcome " << firstName
         << string(54 - 8 - firstName.length() - ((54 - 8 - firstName.length()) / 2), ' ') << "|" << endl;
    cout << divider << endl;

    cout << "|  1. Search for jobs                                  |" << endl;
    cout << "|  2. Apply for job                                    |" << endl;
    cout << "|  3. Upload resume                                    |" << endl;
    cout << "|  4. View Submission history and status               |" << endl;
    cout << "|  5. View my own profile                              |" << endl;
    cout << "|  6. Edit profile                                     |" << endl;
    cout << "|  7. Average salary calculator                        |" << endl;
    cout << "|  8. Leave review on employer                         |" << endl;
    cout << "|  9. View reviews on employer                         |" << endl;
    cout << "| 10. Delete account                                   |" << endl;
    cout << "| 11. Frequently asked question / Tips                 |" << endl;
    cout << "| 12. Logout                                           |" << endl;

    cout << bottomBorder << endl;
}
void Candidate::printFAQ() const
{
    int choice;
    do
    {
        cout << "\nList of common questions:" << endl;
        cout << "1. Do I have to upload my resume to use this site?" << endl;
        cout << "2. How do I find the right job for me?" << endl;
        cout << "3. Is there a way to search for a job without any experience?" << endl;
        cout << "4. How do I apply to a job?" << endl;
        cout << "5. How can I check the status of my submission?" << endl;
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
                cout << "No, it’s not required to upload your resume to use this site" << endl
                     << "but it’s recommended to make your profile more attractive for potential employers to employ you." << endl;
                break;
            }
            case 2: {
                cout << "By using the filters in the search option, you can find the right job for you. " << endl;
                break;
            }
            case 3: {
                cout << "Yes, you can search for jobs without any experience by filtering with 0 years of experience." << endl;
                break;
            }
            case 4: {
                cout << "After searching you will be given job offers with uid, you can apply immeditely or in the main menu with a uid  click \"apply for job\" and use the uid of the job offer." << endl;
                break;
            }
            case 5: {
                cout << "In the main menu you have an option \"View submission history and status\" click it and you will have information on all your history of submissions." << endl;
                break;
            }
            default:
                cout << "Hope u got the information u want, redirecting to main menu..." << endl;
        }
    }
    while (choice != 6);
}
void Candidate::uploadResume(const string &resumeFilePath)
{
    ifstream resumeFile(resumeFilePath);
    if (!resumeFile) {
        cerr << "Error opening resume file: " << resumeFilePath << endl;
        cout << "Returning to main menu..." << endl;
        return;
    }

    // Read the content of the resume file into a stringstream.
    ostringstream resumeContent;
    resumeContent << resumeFile.rdbuf();
    this->resume = resumeContent.str(); // Store the resume content in the class attribute.
    this->gotResume = true;

    resumeFile.close();

    // Save the resume to the "DataBase/Candidate Resumes" file.
    ofstream databaseFile(CANDIDATE_RESUMES, ios::app); // Open the file in append mode.

    if (!databaseFile) {
        cerr << "Error opening database file for writing: " << CANDIDATE_RESUMES << endl;
        cout << "Returning to main menu..." << endl;
        return;
    }

    // Store the candidate ID and resume content in the file
    // Append the end marker "@#$%^&*" to mark the end of the resume.
    databaseFile << this->getId() << "," << this->resume << "@#$%^&*\n";

    cout << "|Resume uploaded successfully!" << endl;
    databaseFile.close();
}
void Candidate::loadResume()
{
    ifstream databaseFile(CANDIDATE_RESUMES);

    if (!databaseFile) {
        cerr << "Error opening database file for reading: " << CANDIDATE_RESUMES << endl;
        return;
    }

    string line;
    stringstream resumeContentStream;

    while (getline(databaseFile, line)) {
        istringstream lineStream(line);
        string candidateId;

        // Extract candidate ID (assuming candidate ID and resume are comma-separated)
        getline(lineStream, candidateId, ',');

        // If the candidate ID matches, read the resume content
        if (candidateId == this->getId()) {
            // Clear any previous resume content
            resumeContentStream.str("");
            resumeContentStream.clear();

            // Continue reading lines for the resume content
            while (getline(databaseFile, line)) {
                // If the end marker "@#$%^&*" is found, stop reading the resume
                if (line.find("@#$%^&*") != string::npos) {
                    break;
                }
                resumeContentStream << line << "\n";  // Append resume content to the stringstream
            }

            this->resume = resumeContentStream.str();  // Set resume content in the class
            this->gotResume = true;  // Mark that the resume is loaded
            break;
        }
    }
    databaseFile.close();

//    if (this->gotResume) {
//        cout << "||Resume loaded successfully for candidate ID: " << this->getId() << "||"<< endl;
//    } else {
//        cout << "||No resume found for candidate ID: " << this->getId() << "||" << endl;
//    }
}

// Function to delete a resume by candidate ID
void Candidate::deleteResume(const std::string &userId) {
    ifstream file("Database/Candidate Resumes");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Store the file contents in a vector
    vector<string> fileLines;
    string line;
    while (getline(file, line)) {
        fileLines.push_back(line);
    }
    file.close();

    // Open the file again in write mode to overwrite the content
    ofstream outFile("Database/Candidate Resumes", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    bool resumeFound = false;
    bool skipLines = false;
    for (size_t i = 0; i < fileLines.size(); ++i) {
        // If we find the userId, we need to start skipping the resume lines
        if (fileLines[i].find(userId) != string::npos) {
            resumeFound = true;
            skipLines = true;  // Start skipping the lines of this resume
        }
        // Skip all lines related to this resume (till we find the end marker)
        if (skipLines) {
            if (fileLines[i].find("@#$%^&*") != string::npos) {
                skipLines = false;  // Stop skipping once the end marker is found
            }
            continue;  // Skip the line
        }

        // Write all remaining lines back to the file
        outFile << fileLines[i] << endl;
    }

    outFile.close();

    if (resumeFound) {
        cout << "Resume for user ID: " << userId << " deleted successfully!" << endl;
    } else {
        cout << "No resume found for user ID: " << userId << endl;
    }
}

void Candidate::changeResume(const string &newResumeFilePath)
{
    ifstream resumeFile(newResumeFilePath);
    if (!resumeFile) {
        cerr << "Error opening resume file: " << newResumeFilePath << endl;
        cout << "Returning to main menu..." << endl;
        return;
    }

    // Read the content of the new resume file into a stringstream.
    ostringstream resumeContent;
    resumeContent << resumeFile.rdbuf();
    this->resume = resumeContent.str(); // Store the new resume content in the class attribute.
    this->gotResume = true;

    resumeFile.close();

    // Read the database file to find and replace the resume
    ifstream databaseFile(CANDIDATE_RESUMES);
    if (!databaseFile) {
        cerr << "Error opening database file for reading: " << CANDIDATE_RESUMES << endl;
        return;
    }

    vector<string> fileLines;
    string line;

    // Read all lines from the database file into memory
    while (getline(databaseFile, line)) {
        fileLines.push_back(line);
    }
    databaseFile.close();

    // Open the file for writing, to overwrite it with updated content
    ofstream outFile(CANDIDATE_RESUMES, ios::trunc);
    if (!outFile) {
        cerr << "Error opening database file for writing: " << CANDIDATE_RESUMES << endl;
        return;
    }

    bool resumeUpdated = false;
    bool skipLines = false;

    for (size_t i = 0; i < fileLines.size(); ++i) {
        // If the line contains the candidate's ID, update the resume content
        if (fileLines[i].find(this->getId()) != string::npos) {
            // Add the new resume content (skip the previous resume content)
            outFile << this->getId() << "," << this->resume << "@#$%^&*\n";
            resumeUpdated = true;
            skipLines = true; // Skip the old resume lines
        }

        // If skipping lines, check for the end marker and stop skipping after it
        if (skipLines) {
            if (fileLines[i].find("@#$%^&*") != string::npos) {
                skipLines = false;
            }
            continue;  // Skip these lines
        }

        // Write all remaining lines (unchanged lines) back to the file
        outFile << fileLines[i] << endl;
    }

    // If the resume was not found and updated, append the new resume at the end
    if (!resumeUpdated) {
        outFile << this->getId() << "," << this->resume << "@#$%^&*\n";
    }

    outFile.close();

    cout << "|Resume updated successfully!" << endl;
}