#pragma once

struct USER
{
	int id = 0;
	std::string username = "";
	std::string password = "";
	std::string firstName = "";
	std::string lastName = "";
	std::string dateOfCreation = "";
	int idOfCreator = 0;
	std::string dateLastChange = "";
	int idLastChange = 0;
	bool isAdmin = 0;

	void displayUser();
};

struct TEAM
{
	int id = 0;
	std::string teamName = "";
	int projectId = 0;
	std::string dateOfCreation = "";
	int idOfCreator = 0;
	std::string dateLastChange = "";
	int idLastChange = 0;

	void displayTeam();
};

struct PROJECT
{
	int id = 0;
	std::string name = "";
	std::string description = "";
	int ownerId = 0;
	std::string dateOfCreation = "";
	int idOfCreator = 0;
	std::string dateLastChange = "";
	int idLastChange = 0;

	void displayProject();
};

struct TASK
{
	int id = 0;
	std::string title = "";
	std::string description = "";
	int projectId = 0;
	std::string status = "";
	std::string dateOfCreation = "";
	int idOfCreator = 0;
	std::string dateLastChange = "";
	int idLastChange = 0;

	void displayTask();
};

struct LOG
{
	int id = 0;
	int userId = 0;
	int timeSpent = 0;
	std::string date = "";
	int taskId = 0;

	void displayLog();
};
