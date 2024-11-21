//
// Created by Jordan Daudu on 20/11/2024.
//

#ifndef BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_JOB_LISTING_H
#define BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_JOB_LISTING_H
#include <iostream>
using namespace std;

class Job_Listing
        {
        private:
            string name;
            string description;
            string position;
            int experience;
            string profession;
            string location;
            int salary;
            bool paid;
        public:
            Job_Listing();
            Job_Listing(string name, string description, string position, int exp, string profession, string loc, int salary);
            Job_Listing(string name, string text, int position, int experience, int profession, int location, int newSalary, bool paid);
            ~Job_Listing();
            char *getType() const;
            string getName() const;
            string getDescription() const;
            string getPosition() const;
            int getExperience() const;
            string getProfession() const;
            string getLocation() const;
            int getSalary() const;
            bool getPaid() const;
            void setName(string text);
            void setDescription(string text);
            void setPosition(int choice);
            void setExperience(int choice);
            void setProfession(int choice);
            void setLocation(int choice);
            void setSalary(int newSalary);
            void setPaid(bool choice);
        };


#endif //BASICS_OF_SOFTWARE_ENGINEERING_PROJECT_JOB_LISTING_H
