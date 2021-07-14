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
#include "Login.h"
#include "AdminMenus.h"

using namespace std;

void welcomeMessage()
{
	cout << endl;
	printSpaces(12); cout << u8"  ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗ " << endl;
	printSpaces(12); cout << u8"  ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝ " << endl;
	printSpaces(12); cout << u8"  ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗   " << endl;
	printSpaces(12); cout << u8"  ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝   " << endl;
	printSpaces(12); cout << u8"  ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗ " << endl;
	printSpaces(12); cout << u8"   ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝ " << endl;
	cout << endl;
}

void loginMenu(nanodbc::connection conn, USER& user)
{
	welcomeMessage();
	printSpaces(35); cout << u8"█   █▀█ █▀▀   █ █▄ █" << endl;
	printSpaces(35); cout << u8"█▄▄ █▄█ █▄█   █ █ ▀█" << endl;
	cout << endl << endl;
	printSpaces(5); cout << "Username: "; const string username = enterText(false);
	printSpaces(5); cout << "Password: "; const string password = enterText(false);

	user = getLoggedUserInfo(conn, username, password);

	if (user.id>0) 
	{
		if (username == "admin" and password == "adminpass")
		{
			adminMenu(conn, user);
			//cout << "admin menu" << endl;
		}
		else
		{
			cout << "User menu currently not available, sorry" << endl;
		}
	}
	else {
		cout << "User ne e nameren :/" << endl;
	}
}

int main()
{
	system("chcp 65001");
	system("cls");
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
		//deleteUserById(conn, 1003);

		//insertTeam(conn);
		//getAllTeams(conn);
		//editTeamById(conn, 1);
		//deleteTeamById(conn, 1);

		//getAllProjects(conn);
		//insertProject(conn);
		//editProjectById(conn, 2);
		//deleteProjectById(conn, 2);

		//getAllTasks(conn);
		//insertTask(conn);
		//editTaskById(conn, 2);
		//deleteTaskById(conn, 2);

		//getAllLogs(conn);
		//insertLog(conn);
		//editLogById(conn, 1);
		//deleteLogById(conn, 1);

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
