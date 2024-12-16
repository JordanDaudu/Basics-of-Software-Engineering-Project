//
// Created by Jordan Daudu on 14/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
#include "User.h"
#include "Job_Listing.h"
#include "Review.h"
#include <list>
#include <memory> // library to manage dynamic memories
#include "utils.h"

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
            list<shared_ptr<Job_Listing>>& getMyJobListings();
            list<shared_ptr<Review>>& getReviews();
            void addJobListing(shared_ptr<Job_Listing> job);
            void addReview(const string& text, const string& firstName, const string& lastName);
            bool isMyJobListingsEmpty() const;
            void printJobListings();
            void printReviews();
            virtual void printMenu() const;
            virtual void printFAQ() const;
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_EMPLOYER_H
