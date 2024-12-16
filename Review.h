//
// Created by Jordan Daudu on 28/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_REVIEW_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_REVIEW_H
#include <iostream>
#include "utils.h"
using namespace std;

class Review
        {
        private:
            string review;
            string firstName;
            string lastName;
        public:
            Review();
            Review(string text, string firstName, string lastName);
            ~Review();
            string getReview() const;
            string getReviewerFirstName() const;
            string getReviewerLastName() const;
            void print() const;

        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_REVIEW_H
