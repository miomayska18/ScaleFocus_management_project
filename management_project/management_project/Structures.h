#pragma once

struct USER
{
	int id = 0;
	string username = "";
	string password = "";
	string firstName = "";
	string lastName = "";
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateLastChange = "";
	int idLastChange = 0;
	bool isAdmin = 0;

	void displayUser();
};

struct TEAM
{
	int id = 0;
	string teamName = "";
	int projectId = 0;
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateLastChange = "";

	void displayTeam();
};

struct PROJECT
{
	int id = 0;
	string name = "";
	string description = "";
	int ownerId = 0;
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateLastChange = "";

	void displayProject();
};

struct TASK
{
	int id = 0;
	string title = "";
	string description = "";
	int projectId = 0;
	bool status = false;

	void displayTask();
};

struct LOG
{
	int id = 0;
	int userId = 0;
	int timeSpent = 0;
	string date = "";
	int taskId = 0;

	void displayLog();
};
