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
#include "LogsCRUD.h"

using namespace std;

USER getLoggedUserInfo(nanodbc::connection conn, string username, string password)
{
	USER user;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Users]
		WHERE
			UserName = ? AND Password = ?
    )"));
	statement.bind(0, username.c_str());
	statement.bind(1, password.c_str());

	auto result = execute(statement);
	
	while (result.next())
	{
		user.id = result.get<int>("Id");
		user.username = result.get<nanodbc::string>("UserName", "");
		user.password = result.get<nanodbc::string>("Password", "");
		user.firstName = result.get<nanodbc::string>("FirstName", "");
		user.lastName = result.get<nanodbc::string>("LastName", "");
		user.dateOfCreation = result.get<nanodbc::string>("DateOfCreation", "");
		user.idOfCreator = result.get<int>("IdOfCreator");
		user.dateLastChange = result.get<nanodbc::string>("DateLastChange", "");
		user.idLastChange = result.get<int>("IdLastChange");
		user.isAdmin = result.get<int>("IsAdmin");
	}
	return user;
}

void loginMenu(nanodbc::connection conn, USER& user)
{
	cout << "		LOG IN			" << endl;
	cout << "Username: "; const string username = enterText(false);
	cout << "Password: "; const string password = enterText(false);

	user = getLoggedUserInfo(conn, username, password);

	if (user.id>0) 
	{
		if (username == "admin" and password == "adminpass")
		{
			cout << "admin menu" << endl;
			user.displayUser();
		}
		else
		{
			cout << "User menu" << endl;
		}
	}
	else {
		cout << "User ne e nameren :/" << endl;
	}
}


int main()
{
	try
	{
		nanodbc::string connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=(localdb)\\MSSQLLocalDB;DATABASE=ProjectManagement;Trusted_Connection=yes;"); // an ODBC connection string to your database

		nanodbc::connection conn(connstr);

		USER loggedUser{};

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
		//editLogById(conn, 1);

		loginMenu(conn, loggedUser);


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
