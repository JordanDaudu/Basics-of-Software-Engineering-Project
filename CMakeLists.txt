cmake_minimum_required(VERSION 3.27)
project(Basics_of_Software_Engineering_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Basics_of_Software_Engineering_Project main.cpp
        User.cpp
        User.h
        Candidate.cpp
        Candidate.h
        Employer.cpp
        Employer.h
        Job_Listing.cpp
        Job_Listing.h
        Job_Submission.cpp
        Job_Submission.h
        Review.cpp
        Review.h)
