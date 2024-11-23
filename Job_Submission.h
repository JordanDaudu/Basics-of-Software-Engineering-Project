//
// Created by Jordan Daudu on 23/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_JOB_SUBMISSION_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_JOB_SUBMISSION_H
#include <iostream>
using namespace std;

class Job_Submission
        {
        private:
            int candidateUID;
            int employerUID;
            int job_listingUID;
            int status;
            int uid;
            static int UID;
        public:
            Job_Submission();
            Job_Submission(int candidateUID, int employerUID,int job_listingUID);
            ~Job_Submission();
            int getCandidateUID() const;
            int getEmployerUID() const;
            int getJob_listingUID() const;
            string getStatus() const;
            int getUid() const;
            void setStatus(int choice);
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_JOB_SUBMISSION_H
