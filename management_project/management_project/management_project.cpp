#include <iostream>
#include <string>
#include <nanodbc.h>
#include <exception>
#include <vector>
#include "Structures.h"
#include "UserCRUD.h"
#include "TeamsCRUD.h"
#include "InsertFunctions.h"
#include "ProjectsCRUD.h"

using namespace std;

vector<TASK> getTasks(nanodbc::connection conn)
{
	vector<TASK> tasks;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Tasks]
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
	const string taskName = enterText();
	statement.bind(0, taskName.c_str());

	cout << "Enter the task's description: ";
	const string taskDesc = enterText();
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
	const string title = enterText();
	statement.bind(0, title.c_str());

	cout << "Enter the team's new description: ";
	const string desc = enterText();
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

bool deleteTaskById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        DELETE 
            FROM [ProjectManagement].[dbo].[Task]
            WHERE Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);

	return result.affected_rows() != 0;
}

int main()
{
	try
	{
		nanodbc::string connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=(localdb)\\MSSQLLocalDB;DATABASE=ProjectManagement;Trusted_Connection=yes;"); // an ODBC connection string to your database

		nanodbc::connection conn(connstr);

		/*do
		{
			runProgram(conn);
		} while (runProgram(conn));*/

		//insertUser(conn);
		//getAllUsers(conn);
		//editUserById(conn, 3);

		//insertTeam(conn);
		//getAllTeams(conn);
		//editTeamById(conn, 1);

		//getAllProjects(conn);
		//insertProject(conn);
		//editProjectById(conn, 2);

		//getAllTasks(conn);
		//insertTask(conn);
		editTaskById(conn, 2);

		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
