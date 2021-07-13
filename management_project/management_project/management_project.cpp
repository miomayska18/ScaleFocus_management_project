#include <iostream>
#include <string>
#include <nanodbc.h>
#include <exception>
#include <vector>
#include "Structures.h"
#include "InsertFunctions.h"
#include "UserCRUD.h"
#include "TeamsCRUD.h"
#include "ProjectsCRUD.h"
#include "TasksCRUD.h"

using namespace std;

vector<LOG> getLogs(nanodbc::connection conn)
{
	vector<LOG> logs;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Logs]
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		LOG log;
		log.id = result.get<int>("Id");
		log.userId = result.get<int>("UserId");
		log.timeSpent = result.get<double>("TimeSpent");
		log.date = result.get<nanodbc::string>("Date");
		log.taskId = result.get<int>("TaskId");

		logs.push_back(log);
	}

	return logs;
}

void getAllLogs(nanodbc::connection conn)
{
	vector<LOG> logs = getLogs(conn);

	for (size_t i = 0; i < logs.size(); i++)
	{
		logs[i].displayLog();
		cout << endl;
	}

}

void insertLog(nanodbc::connection conn)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            [ProjectManagement].[dbo].[Logs]
            (UserId, TimeSpent, Date, TaskId)
            VALUES
            (?, ?, ?, ?)
    )"));

	cout << "Enter the user's id: ";
	const int userId = enterInt();
	statement.bind(0, &userId);

	cout << "Enter the time spent working (in hours): ";
	const double timeSpent = enterDouble();
	statement.bind(1, &timeSpent);

	cout << "Enter the date (format: 2021-07-13): ";
	const string date = enterText(true);
	statement.bind(2, date.c_str());

	cout << "Enter the task's id: ";
	const int taskId = enterInt();
	statement.bind(3, &taskId);

	execute(statement);
}

void editLogById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE [ProjectManagement].[dbo].[Logs]
        SET    
            UserId = ?, 
			TimeSpent = ?,
			Date = ?,
			TaskId = ?
		WHERE	
			Id = ?
    )"));



	cout << "Enter the new assigned user's id: ";
	const int userId = enterInt();
	statement.bind(0, &userId);

	cout << "Enter the time spent (in hours): ";
	const double timeSpent = enterDouble();
	statement.bind(1, &timeSpent);

	cout << "Enter the date (format: 2021-07-13): ";
	const string date = enterText(true);
	statement.bind(2, date.c_str());

	cout << "Enter the task's id: ";
	const int taskId = enterInt();
	statement.bind(3, &taskId);

	statement.bind(4, &id);

	execute(statement);
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
		//editTaskById(conn, 2);

		//getAllLogs(conn);
		//insertLog(conn);
		editLogById(conn, 1);


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
