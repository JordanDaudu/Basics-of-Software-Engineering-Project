//
// Created by Jordan Daudu on 14/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_CANDIDATE_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_CANDIDATE_H
#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Candidate: virtual public User
        {
        private:
            string resume;
            bool gotResume;
        public:
            Candidate();
            Candidate(string id, string password, string firstName, string lastName,
                int age, string loc, unsigned int phoneNum);
            Candidate(string id, string password, string firstName, string lastName,
                      int age, int loc, int phoneNum);
            virtual ~Candidate();
            virtual char *getType() const;
            string getResume() const;
            bool getGotResume() const;
            virtual void printMenu() const;
            virtual void printFAQ() const;
            virtual void uploadResume(const string& resumeFilePath);
            static void deleteResume(const std::string& userId);
            void changeResume(const string &newResumeFilePath);
            void loadResume();
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_CANDIDATE_H
