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
		tasks[i].displayTask();
		cout << endl;
	}

}

void insertTask(nanodbc::connection conn)
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

	cout << "Enter the task's title: ";
	const string taskName = enterText(false);
	statement.bind(0, taskName.c_str());

	cout << "Enter the task's description: ";
	const string taskDesc = enterText(false);
	statement.bind(1, taskDesc.c_str());

	cout << "Enter the assigned project id: ";
	const int projectId = enterInt();
	statement.bind(2, &projectId);

	cout << "Enter the assigned user's id: ";
	const int assigneeId = enterInt();
	statement.bind(3, &assigneeId);

	int statusNum;
	cout << "Choose the status of this task: " << endl;
	cout << "1. Pending" << endl;
	cout << "2. In progress" << endl;
	cout << "3. Complete" << endl;
enter:
	cout << "Enter your choice: ";
	statusNum = enterInt();

	switch (statusNum)
	{
	case 1: statement.bind(4, status[0].c_str());
		break;
	case 2: statement.bind(4, status[1].c_str());
		break;
	case 3: statement.bind(4, status[2].c_str());
		break;
	default: cout << "Please choose from the available options!" << endl;
		goto enter;
	}



	cout << "Enter your id: ";
	const int creatorId = enterInt();
	statement.bind(5, &creatorId);
	statement.bind(6, &creatorId);

	execute(statement);
}

void editTaskById(nanodbc::connection conn, const int& id)
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

	cout << "Enter the task's new title: ";
	const string title = enterText(false);
	statement.bind(0, title.c_str());

	cout << "Enter the team's new description: ";
	const string desc = enterText(false);
	statement.bind(1, desc.c_str());

	int statusNum;
	cout << "Choose the status of this task: " << endl;
	cout << "1. Pending" << endl;
	cout << "2. In progress" << endl;
	cout << "3. Complete" << endl;
enter:
	cout << "Enter your choice: ";
	statusNum = enterInt();

	switch (statusNum)
	{
	case 1: statement.bind(2, status[0].c_str());
		break;
	case 2: statement.bind(2, status[1].c_str());
		break;
	case 3: statement.bind(2, status[2].c_str());
		break;
	default: cout << "Please choose from the available options!" << endl;
		goto enter;
	}

	cout << "Enter the assigned user's id: ";
	const int assigneeId = enterInt();
	statement.bind(3, &assigneeId);

	cout << "Enter your id: ";
	const int chngId = enterInt();
	statement.bind(4, &chngId);

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
