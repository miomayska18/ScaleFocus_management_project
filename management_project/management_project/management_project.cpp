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

using namespace std;

void adminUserMenu(nanodbc::connection conn, USER& user)
{
	do {
		system("cls");
		cout << "		USER MANAGEMENT MENU		" << endl;
		cout << "1. Create user" << endl;
		cout << "2. Edit user" << endl;
		cout << "3. List all users" << endl;
		cout << "4. Delete user" << endl;
		cout << "0. Exit" << endl;
	enter:
		cout << endl;
		cout << "Enter your choice: ";

		short int choice = enterInt();
		system("cls");
		int id;
		switch (choice)
		{
		case 1: insertUser(conn);
			break;
		case 2:
			cout << "Enter the id of the user you want to edit: ";
			id = enterInt();
			editUserById(conn, id);
			break;
		case 3: getAllUsers(conn, user);
			break;
		case 4:
			cout << "Enter the id of the user you want to delete: ";
			id = enterInt();
			deleteUserById(conn, id);
			break;
		case 0: return;
		default: cout << "Please enter a valid option!" << endl;
			goto enter;
			break;
		}
	} while (true);
}

void adminMenu(nanodbc::connection conn, USER& user)
{
	do {
		system("cls");
		cout << "		ADMIN MENU			" << endl;
		cout << "1. Users operations" << endl;
		cout << "2. Teams opeartions" << endl;
		cout << "3. Projects operations" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice: ";

		int choice = enterInt();
		system("cls");

		switch (choice)
		{
		case 1: //cout << "User menu with CRUD" << endl;
			adminUserMenu(conn, user);
			break;
		case 2: cout << "Teams menu with crud options" << endl;
			break;
		case 3: cout << "Projects menu with CRUD" << endl;
			break;
		case 0: return;
		}
	} while (true);
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
			adminMenu(conn, user);
			//cout << "admin menu" << endl;
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
		//deleteTeamById(conn, 1);

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
