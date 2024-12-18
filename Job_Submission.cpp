//
// Created by Jordan Daudu on 23/11/2024.
//

#include "Job_Submission.h"

Job_Submission::Job_Submission()
{
    candidateUID = 0;
    employerUID = 0;
    job_listingUID = 0;
    status = 0;
    uid = ++UID;
}
Job_Submission::Job_Submission(int candidateUID, int employerUID, int job_listingUID)
{
    this->candidateUID = candidateUID;
    this->employerUID = employerUID;
    this->job_listingUID = job_listingUID;
    status = 0;
    uid = ++UID;
}
Job_Submission::~Job_Submission()
{
    //cout << "Job_Submission::destructor" << endl;
}

int Job_Submission::getCandidateUID() const {return candidateUID;}
int Job_Submission::getEmployerUID() const {return employerUID;}
int Job_Submission::getJob_listingUID() const {return job_listingUID;}
int Job_Submission::getUid() const {return uid;}

string Job_Submission::getStatus() const
{
    if(status == 1)
        return "Accepted";
    else if(status == 2)
        return "Rejected";
    else
        return "Waiting for response";
}
void Job_Submission::setStatus(int choice)
{
    if(choice == 1)
        status = 1;
    else if(choice == 2)
        status = 2;
    else
        status = 0;
}

