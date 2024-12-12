# Basics-of-Software-Engineering-Project
קורס יסודות הנדסת תוכנה - פרוייקט

<h3 align="center">Basic git commands:<h3>
git init - create dir and open new "project"<br />
git add - מכין קבצים שארצה להכניס לבראנץ<br />
git commit -m "" - שומר את הקבצים שהכנתי בבראנץ<br />
git branch branch_name - מייצר ענף חדש בפרוייקט בשם שאבחר<br />
git branch - יציג את הענפים שקיימים כרגע בפרוייקט<br />
git checkout branch_name - יעביר אותנו לבראנץ | ענף אחר<br />


<h3 align="center">Progress indicator<h3>
<h2 align="left"> Main menu: </h2>
1.	register ✅<br />
2.	login ✅<br />
3.	exit ✅<br />

<h2 align="left"> Register menu: </h2>
input id, password, first name, last name, age, location, phone number ✅<br />

<h2 align="left"> Candidate menu: </h2>
1.	search for jobs ✅<br />
2.	apply for job ✅<br />
3.	upload resume ✅<br />
4.	view submission history and status ✅<br />
5.  View my own profile ✅<br />
6.	edit profile 🆗(still needs resume checked further)<br />
7.	average salary calculator ✅<br />
8.	leave review on employer ✅<br />
9.  view reviews on employer ✅<br />
10.	delete account ✅<br />
11.	Frequently asked questions / tips ✅<br />
12.	logout ✅<br />

<h2 align="left"> Employer menu: </h2>
1.	publish submission ✅<br />
2.	edit submission ✅<br />
3.	delete submission ✅<br />
4.	published jobs ✅<br />
5.  View my own profile ✅<br />
6.	view profile of candidates to accept / deny 🆗(still needs to check properly resume)<br />
7.	search for jobs ✅<br />
8.  view reviews posted on me ✅<br />
9.	pay to advertise ✅<br />
10.	delete account ✅<br />
11.	Frequently asked questions / tips ✅<br />
12.	logout ✅<br />

<h2 align="left"> How to add resume files properly? </h2>
There is a folder named "Resumes", the code will immediately read from there the user should input the filename that is located there to read.
For example inside folder "Resumes" there is a file named "resume1" whenever asked for a filepath the user should input "resume1".<br />

<h2 align="left"> How is data stored inside files? </h2>
There is inside "Database" folder a file named "DataBase Explanation" that it's written there how each file information is seperated.<br />
There is 4 data files in total:<br />
1. Users data - stores all the info on a user, if user is employer also stores his / her reviews.<br />
2. Jobs data - stores all job listings / offers.<br />
3. Submissions data - Stores all submissions by candidate for job offers.<br />
4. Candidate Resumes - Stores information on resumes.<br />
