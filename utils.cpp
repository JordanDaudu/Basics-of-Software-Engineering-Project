//
// Created by idanv on 16/12/2024.
//
#include "utils.h"
bool is9DigitInt(int num)
{
    if(num >= 100000000 && num <= 999999999)
        return true;
    return false;
}
/// Function to check if string input is using only letters
/// \return acceptable value (string with letters)
string getValidString()
{
    string value;
    while (true)
    {
        getline(cin, value); // read the entire line
        bool isValid = true;

        for (char c : value)
        {
            if (!isalpha(c)) // check if the character is not a letter
            {
                isValid = false;
                break;
            }
        }

        if (isValid)
            break; // exit loop if input is valid
        else
            cerr << "Invalid input. Please enter letters only." << endl;
    }
    return value;
}
/// Function to check if integer input is indeed a integer
/// \return = acceptable value (integer)
int getValidInt()
{
    int value;
    while(true)
    {
        if(cin >> value) // successful read
            break;
        else
        {
            cerr << "Invalid input. please enter a valid input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
        }
    }
    return value;
}
