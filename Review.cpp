//
// Created by Jordan Daudu on 28/11/2024.
//

#include "Review.h"

Review::Review() {review = nullptr;}

Review::Review(string text, string firstName, string lastName)
{
    review = text;
    this->firstName = firstName;
    this->lastName = lastName;
}

Review::~Review() {cout << "Review::destructor" << endl;}

string Review::getReview() const {return review;}

void Review::print() const
{
    cout << "- " << firstName << " " << lastName << endl;
    cout << "   " << review << endl;
}