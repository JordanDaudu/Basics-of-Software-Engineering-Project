//
// Created by Jordan Daudu on 14/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
#include "User.h"
#include "Job_Listing.h"
#include "Review.h"
#include <list>

class Employer: public User
        {
        private:
            list<shared_ptr<Job_Listing>> myJobListings;
            list<shared_ptr<Review>> reviews;
        public:
            Employer();
            Employer(string id, string password, string firstName, string lastName,
                int age, string loc, int phoneNum);
            Employer(string id, string password, string firstName, string lastName,
                     int age, int loc, int phoneNum);
            virtual ~Employer();
            virtual char *getType() const;
            void addJobListing(shared_ptr<Job_Listing> job);
            void addReview(const string& text, const string& firstName, const string& lastName);
            void printJobListings();
            void printReviews();
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
