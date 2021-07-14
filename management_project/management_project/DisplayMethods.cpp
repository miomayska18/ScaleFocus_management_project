#include <iostream>
#include "Structures.h"
#include "InsertFunctions.h"
using namespace std;

void USER::displayUser()
{
	printSpaces(4); cout << "User id: " << this->id << endl;
	printSpaces(4); cout << "Username: " << this->username << endl;
	printSpaces(4); cout << "Password: " << this->password << endl;
	printSpaces(4); cout << "Firsrt name: " << this->firstName << endl;
	printSpaces(4); cout << "Last name: " << this->lastName << endl;
	printSpaces(4); cout << "Date of creation of this profile: " << this->dateOfCreation << endl;
	printSpaces(4); cout << "Id of creator of this profile: " << this->idOfCreator << endl;
	printSpaces(4); cout << "Date of the last modification: " << this->dateLastChange << endl;
	printSpaces(4); cout << "Id of the user that last modified this profile: " << this->idLastChange << endl;
	printSpaces(4); cout << "Is this user an admin: ";
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
	printSpaces(4); cout << "Team id: " << this->id << endl;
	printSpaces(4); cout << "Team name: " << this->teamName << endl;
	printSpaces(4); cout << "Assigned project id: " << this->projectId << endl;
	printSpaces(4); cout << "Date of creation: " << this->dateOfCreation << endl;
	printSpaces(4); cout << "Id of creator: " << this->idOfCreator << endl;
	printSpaces(4); cout << "Date of last modification: " << this->dateLastChange << endl;
	printSpaces(4); cout << "Id of last modificator: " << this->idLastChange<< endl;
}

void PROJECT::displayProject()
{
	printSpaces(4); cout << "Project id: " << this->id << endl;
	printSpaces(4); cout << "Project's name: " << this->name << endl;
	printSpaces(4); cout << "Description: " << this->description << endl;
	printSpaces(4); cout << "Owner id: " << this->ownerId << endl;
	printSpaces(4); cout << "Date of creation: " << this->dateOfCreation << endl;
	printSpaces(4); cout << "Id of creator: " << this->idOfCreator << endl;
	printSpaces(4); cout << "Date of last modification: " << this->dateLastChange << endl;
	printSpaces(4); cout << "Id of last modification: " << this->idLastChange << endl;
}

void TASK::displayTask()
{
	printSpaces(4); cout << "Task id: " << this->id << endl;
	printSpaces(4); cout << "Task title: " << this->title << endl;
	printSpaces(4); cout << "Description: " << this->description << endl;
	printSpaces(4); cout << "Project id: " << this->projectId << endl;
	printSpaces(4); cout << "Assignee id: " << this->assigneeId << endl;
	printSpaces(4); cout << "Task status: " << this->status << endl;
	printSpaces(4); cout << "Date of creation: " << this->dateOfCreation << endl;
	printSpaces(4); cout << "Id of creator: " << this->idOfCreator << endl;
	printSpaces(4); cout << "Date of last modification: " << this->dateLastChange << endl;
	printSpaces(4); cout << "Id of last modification: " << this->idLastChange << endl;
}

void LOG::displayLog()
{
	printSpaces(4); cout << "Log id: " << this->id << endl;
	printSpaces(4); cout << "User id: " << this->userId << endl;
	printSpaces(4); cout << "Timse spent working (in hours): " << this->timeSpent << endl;
	printSpaces(4); cout << "Date: " << this->date << endl;
	printSpaces(4); cout << "Task id: " << this->taskId << endl;
}
