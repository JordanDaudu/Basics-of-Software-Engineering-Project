# Basics-of-Software-Engineering-Project

<h3 align="center">Basic git commands:<h3>

  <img align="right" alt="IMAGE" src="Photos/Git Commands.jpeg" width="300" height="150" />
git init - create dir and open new "project"<br />
git add - מכין קבצים שארצה להכניס לבראנץ<br />
git commit -m "" - שומר את הקבצים שהכנתי בבראנץ<br />
git branch branch_name - מייצר ענף חדש בפרוייקט בשם שאבחר<br />
git branch - יציג את הענפים שקיימים כרגע בפרוייקט<br />
git checkout branch_name - יעביר אותנו לבראנץ | ענף אחר<br />


<h3 align="center">Progress indicator<h3>
<h2 align="left"> Main menu: </h2>
  <img align="right" alt="IMAGE" src="Photos/Main Menu.jpeg" width="350" height="100" />
1.	Register ✅<br />
2.	Login ✅<br />
3.	Exit ✅<br />

<h2 align="left"> Register menu: </h2>
Input user type, id, password, first name, last name, age, location, phone number ✅<br />

<h2 align="left"> Candidate menu: </h2>
<img align="right" alt="IMAGE" src="Photos/Candidate Menu.jpeg" width="340" height="340" />
1.	Search for jobs ✅<br />
2.	Apply for job ✅<br />
3.	Upload resume ✅<br />
4.	View submission(s) history and status ✅<br />
5.  View my own profile ✅<br />
6.	Edit profile ✅<br />
7.	Average salary calculator ✅<br />
8.	Leave review on employer ✅<br />
9.  View reviews on employer ✅<br />
10.	Delete account ✅<br />
11.	Frequently asked questions / tips ✅<br />
12.	Logout ✅<br />

<h2 align="left"> Employer menu: </h2>
<img align="right" alt="IMAGE" src="Photos/Employer Menu.jpeg" width="340" height="340" />
1.	publish job offer ✅<br />
2.	edit job offer ✅<br />
3.	delete job offer ✅<br />
4.	View published jobs ✅<br />
5.  View my own profile ✅<br />
6.	View candidate profiles to accept / deny ✅<br />
7.	Search for jobs ✅<br />
8.  View reviews posted on me ✅<br />
9.	Pay to advertise ✅<br />
10.	Delete account ✅<br />
11.	Frequently asked questions / tips ✅<br />
12.	Logout ✅<br />

<h2 align="left"> How to add resume files properly? </h2>
There is a folder named "Resumes", the code will immediately read from there the user should input the filename that is located there to read.
For example inside folder "Resumes" there is a file named "resume1" whenever asked for a filepath the user should input "resume1".<br />

<h2 align="left"> How is data stored inside files? </h2>
There is inside "Database" folder a file named "DataBase Explanation" that it's written there how each file information is seperated.<br />
There is 4 data files in total:<br />
1. Users data - stores all the info on a user, if user is employer also stores his / her reviews.<br />
2. Jobs data - stores all job listings / offers.<br />
3. Submissions data - Stores all submissions by candidate for job offers.<br />
4. Candidate Resumes - Stores information on resumes (part of candidate data).<br />
Note: Files are not where data is stored in real time, only for loading when first running the program.<br />
In real time data is stored in 3 lists: user_list, job_list, jobs_Submission_List<br />

<h2 align="left"> Data Flow Diagram </h2>
<img align="middle" alt="IMAGE" src="Photos/Basics of software engineering project Data Flow Diagram level 2.png" width="1080" height="1080" />

<h2 align="left"> Use Case Diagram Candidate </h2>
<img align="middle" alt="IMAGE" src="Photos/Use case Diagram Candidate.png" width="1080" height="1080" />

<h2 align="left"> Use Case Diagram Employer </h2>
<img align="middle" alt="IMAGE" src="Photos/Use case Diagram Employer.png" width="1080" height="1080" />
