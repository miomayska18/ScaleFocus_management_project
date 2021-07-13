#include <iostream>
#include "Structures.h"
using namespace std;

void USER::displayUser()
{
	cout << "User id: " << this->id << endl;
	cout << "Username: " << this->username << endl;
	cout << "Password: " << this->password << endl;
	cout << "Firsrt name: " << this->firstName << endl;
	cout << "Last name: " << this->lastName << endl;
	cout << "Date of creation of this profile: " << this->dateOfCreation << endl;
	cout << "Id of creator of this profile: " << this->idOfCreator << endl;
	cout << "Date of the last modification: " << this->dateLastChange << endl;
	cout << "Id of the user that last modified this profile: " << this->idLastChange << endl;
	cout << "Is this user an admin: ";
	if (this->isAdmin)
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" << endl;
	}
}

void TEAM::displayTeam()
{
	cout << "Team id: " << this->id << endl;
	cout << "Team name: " << this->teamName << endl;
	cout << "Assigned project id: " << this->projectId << endl;
	cout << "Date of creation: " << this->dateOfCreation << endl;
	cout << "Id of creator: " << this->idOfCreator << endl;
	cout << "Date of last modification: " << this->dateLastChange << endl;
	cout << "Id of last modificator: " << this->id<< endl;
}

void PROJECT::displayProject()
{
	cout << "Project id: " << this->id << endl;
	cout << "Project's name: " << this->name << endl;
	cout << "Description: " << this->description << endl;
	cout << "Owner id: " << this->ownerId << endl;
	cout << "Date of creation: " << this->dateOfCreation << endl;
	cout << "Id of creator: " << this->idOfCreator << endl;
	cout << "Date of last modification: " << this->dateLastChange << endl;
	cout << "Id of last modification: " << this->idLastChange << endl;
}

void TASK::displayTask()
{
	cout << "Task id: " << this->id << endl;
	cout << "Task title: " << this->title << endl;
	cout << "Description: " << this->description << endl;
	cout << "Project id: " << this->projectId << endl;
	cout << "Assignee id: " << this->assigneeId << endl;
	cout << "Task status: " << this->status << endl;
	cout << "Date of creation: " << this->dateOfCreation << endl;
	cout << "Id of creator: " << this->idOfCreator << endl;
	cout << "Date of last modification: " << this->dateLastChange << endl;
	cout << "Id of last modification: " << this->idLastChange << endl;
}

void LOG::displayLog()
{
	cout << "Log id: " << endl;
	cout << "User id: " << endl;
	cout << "Timse spent working (in minutes): " << endl;
	cout << "Date: " << endl;
	cout << "Task id: " << endl;
}
