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

		getAllTasks(conn);

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
