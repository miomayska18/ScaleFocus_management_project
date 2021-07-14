#include <iostream>
#include "Structures.h"
#include <nanodbc.h>
#include <vector>
#include <string>
#include "InsertFunctions.h"
using namespace std;

vector<TASK> getTasks(nanodbc::connection conn)
{
	vector<TASK> tasks;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Tasks]
		WHERE
			IsDeleted<>1
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		TASK task;
		task.id = result.get<int>("Id");
		task.title = result.get<nanodbc::string>("Title", "");
		task.description = result.get<nanodbc::string>("Description", "");
		task.projectId = result.get<int>("ProjectId");
		task.assigneeId = result.get<int>("AssigneeId");
		task.status = result.get<nanodbc::string>("Status", "");
		task.dateOfCreation = result.get<nanodbc::string>("DateCreation", "");
		task.idOfCreator = result.get<int>("IdCreator");
		task.dateLastChange = result.get<nanodbc::string>("DateLastChange", "");
		task.idLastChange = result.get<int>("IdLastChange");

		tasks.push_back(task);
	}

	return tasks;
}

void getAllTasks(nanodbc::connection conn)
{
	vector<TASK> tasks = getTasks(conn);

	for (size_t i = 0; i < tasks.size(); i++)
	{
		printSpaces(2); cout << u8"╔═════════════════════════════════════════════════════════════╗" << endl << endl;
		tasks[i].displayTask();
		cout << endl;
		printSpaces(2); cout << u8"╚═════════════════════════════════════════════════════════════╝" << endl << endl << endl;
	}

	cout << endl << endl;
	int choice = 1;
	do {
		cout << "Enter 0 to get back to the menu: ";
		choice = enterInt();
	} while (choice != 0);
}

void insertTask(nanodbc::connection conn, USER& user)
{
	string status[3] = { "pending", "in progress", "complete" };

	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            [ProjectManagement].[dbo].[Tasks]
            (Title, Description, ProjectId, AssigneeId, Status, DateCreation, IdCreator, DateLastChange, IdLastChange)
            VALUES
            (?, ?, ?, ?, ?, GETDATE(), ?, GETDATE(), ?)
    )"));

	printSpaces(4); cout << "Enter the task's title: ";
	const string taskName = enterText(true);
	statement.bind(0, taskName.c_str());

	printSpaces(4); cout << "Enter the task's description: ";
	const string taskDesc = enterText(false);
	statement.bind(1, taskDesc.c_str());

	printSpaces(4); cout << "Enter the assigned project id: ";
	const int projectId = enterInt();
	statement.bind(2, &projectId);

	printSpaces(4); cout << "Enter the assigned user's id: ";
	const int assigneeId = enterInt();
	statement.bind(3, &assigneeId);

	int statusNum;
	printSpaces(4); cout << "Choose the status of this task: " << endl;
	printSpaces(4); cout << "1. Pending" << endl;
	printSpaces(4); cout << "2. In progress" << endl;
	printSpaces(4); cout << "3. Complete" << endl;
enter:
	printSpaces(4); cout << "Enter your choice: ";
	statusNum = enterInt();

	switch (statusNum)
	{
	case 1: statement.bind(4, status[0].c_str());
		break;
	case 2: statement.bind(4, status[1].c_str());
		break;
	case 3: statement.bind(4, status[2].c_str());
		break;
	default: printSpaces(4); cout << "Please choose from the available options!" << endl;
		goto enter;
	}



	//cout << "Enter your id: ";
	//const int creatorId = enterInt();
	statement.bind(5, &user.id);
	statement.bind(6, &user.id);

	execute(statement);
}

void editTaskById(nanodbc::connection conn, const int& id, USER& user)
{
	string status[3] = { "pending", "in progress", "complete" };

	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE [ProjectManagement].[dbo].[Tasks]
        SET    
            Title = ?, 
			Description = ?,
			Status = ?,
			AssigneeId = ?,
			IdLastChange = ?,
			DateLastChange = GETDATE()
		WHERE	
			Id = ?
    )"));

	printSpaces(4); cout << "Enter the task's new title: ";
	const string title = enterText(true);
	statement.bind(0, title.c_str());

	printSpaces(4); cout << "Enter the team's new description: ";
	const string desc = enterText(false);
	statement.bind(1, desc.c_str());

	int statusNum;
	printSpaces(4); cout << "Choose the status of this task: " << endl;
	printSpaces(4); cout << "1. Pending" << endl;
	printSpaces(4); cout << "2. In progress" << endl;
	printSpaces(4); cout << "3. Complete" << endl;
enter:
	printSpaces(4); cout << "Enter your choice: ";
	statusNum = enterInt();

	switch (statusNum)
	{
	case 1: statement.bind(2, status[0].c_str());
		break;
	case 2: statement.bind(2, status[1].c_str());
		break;
	case 3: statement.bind(2, status[2].c_str());
		break;
	default: printSpaces(4); cout << "Please choose from the available options!" << endl;
		goto enter;
	}

	printSpaces(4); cout << "Enter the assigned user's id: ";
	const int assigneeId = enterInt();
	statement.bind(3, &assigneeId);

	//cout << "Enter your id: ";
	//const int chngId = enterInt();
	statement.bind(4, &user.id);

	statement.bind(5, &id);

	execute(statement);
}

void deleteTaskById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE 
            Tasks
		SET
			IsDeleted = 1
        WHERE 
			Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);
}
