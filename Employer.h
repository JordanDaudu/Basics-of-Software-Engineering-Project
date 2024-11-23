//
// Created by Jordan Daudu on 14/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
#include "User.h"
#include "Job_Listing.h"
#include <list>

class Employer: public User
        {
        private:
            list<shared_ptr<Job_Listing>> myJobListings;
        public:
            Employer();
            Employer(string id, string password, string firstName, string lastName,
                int age, string loc, unsigned int phoneNum);
            virtual ~Employer();
            virtual char *getType() const;
            void addJobListing(shared_ptr<Job_Listing> job);
            void printJobListings();
            bool checkListEmpty() const;
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
