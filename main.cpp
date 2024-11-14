#include <iostream>
#include "User.h"
using namespace std;
int main()
{
    User *a, *b;
    User **arr;
    int choice;
    arr = new User *[2];
    arr[0] = a;
    arr[1] = b;
    for(int i = 0; i < 2; i++)
        arr[i]->print();
    switch (choice)
    {
        case 1:

    }
}
