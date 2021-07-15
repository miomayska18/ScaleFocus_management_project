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
#include "DisplayAdminMenus.h"
using namespace std;



void adminLogMenu(nanodbc::connection conn, USER& user)
{
	do {
		displayAdminLogMenu();
	enter:
		printSpaces(23); cout << "Enter your choice: ";

		short int choice = enterInt();
		system("cls");
		int id;
		switch (choice)
		{
		case 1: insertLog(conn);
			break;
		case 2:
			cout << "Enter the id of the log you want to edit: ";
			id = enterInt();
			editLogById(conn, id);
			break;
		case 3: getAllLogs(conn);
			break;
		case 4:
			cout << "Enter the id of the log you want to delete: ";
			id = enterInt();
			deleteLogById(conn, id);
			break;
		case 5:
			cout << "Enter the id of the task you want to see the logs for: ";
			id = enterInt();
			getAllCertainLogs(conn, id);
			//cout << "LOGS" << endl;
			break;
		case 0: return;
		default: cout << "Please enter a valid option!" << endl;
			goto enter;
			break;
		}
	} while (true);
}

void adminTaskMenu(nanodbc::connection conn, USER& user)
{
	do {
		displayAdminTaskMenu();
	enter:
		printSpaces(26); cout << "Enter your choice: ";

		short int choice = enterInt();
		system("cls");
		int id;
		switch (choice)
		{
		case 1: insertTask(conn, user);
			break;
		case 2:
			cout << "Enter the id of the task you want to edit: ";
			id = enterInt();
			editTaskById(conn, id, user);
			break;
		case 3: getAllTasks(conn);
			break;
		case 4:
			cout << "Enter the id of the project you want to delete: ";
			id = enterInt();
			deleteTaskById(conn, id);
			break;
		case 5:
			//cout << "LOGS" << endl;
			adminLogMenu(conn, user);
			break;
		case 0: return;
		default: cout << "Please enter a valid option!" << endl;
			goto enter;
			break;
		}
	} while (true);
}

void adminProjectMenu(nanodbc::connection conn, USER& user)
{
	do {
		displayProjectManagementMenu();
	enter:
		printSpaces(40); cout << "Enter your choice: ";

		short int choice = enterInt();
		system("cls");
		int id;
		switch (choice)
		{
		case 1: insertProject(conn, user);
			break;
		case 2:
			cout << "Enter the id of the project you want to edit: ";
			id = enterInt();
			editProjectById(conn, id, user);
			break;
		case 3: getAllProjects(conn);
			break;
		case 4:
			cout << "Enter the id of the project you want to delete: ";
			id = enterInt();
			deleteProjectById(conn, id);
			break;
		case 5:
			//cout << "TASKS AND LOGS" << endl;
			adminTaskMenu(conn, user);
			break;
		case 0: return;
		default: cout << "Please enter a valid option!" << endl;
			goto enter;
			break;
		}
	} while (true);
}

void adminTeamMenu(nanodbc::connection conn, USER& user)
{
	do {
		displayAdminTeamMenu();
	enter:
		printSpaces(26); cout << "Enter your choice: ";

		short int choice = enterInt();
		system("cls");
		int id;
		switch (choice)
		{
		case 1: insertTeam(conn, user);
			break;
		case 2:
			cout << "Enter the id of the team you want to edit: ";
			id = enterInt();
			editTeamById(conn, id, user);
			break;
		case 3: getAllTeams(conn);
			break;
		case 4:
			cout << "Enter the id of the team you want to delete: ";
			id = enterInt();
			deleteTeamById(conn, id);
			break;
		case 5:
			cout << "Enter the id of the team you want to enter users into: ";
			id = enterInt();
			insertUserIntoTeam(conn, id);
			break;
		case 0: return;
		default: cout << "Please enter a valid option!" << endl;
			goto enter;
			break;
		}
	} while (true);
}

void adminUserMenu(nanodbc::connection conn, USER& user)
{
	do {
		displayAdminUserMenu();
	enter:
		printSpaces(26); cout << "Enter your choice: ";

		short int choice = enterInt();
		system("cls");
		int id;
		switch (choice)
		{
		case 1: insertUser(conn, user);
			break;
		case 2:
			cout << "Enter the id of the user you want to edit: ";
			id = enterInt();
			editUserById(conn, id, user);
			break;
		case 3: getAllUsers(conn);
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
		displayAdminMenu();
	enter:
		printSpaces(19);  cout << "Enter your choice: ";

		int choice = enterInt();
		system("cls");

		switch (choice)
		{
		case 1:
			adminUserMenu(conn, user);
			break;
		case 2:
			adminTeamMenu(conn, user);
			break;
		case 3:
			adminProjectMenu(conn, user);
			break;
		case 0:
			goodbyeMessage();
			system("PAUSE");
			return;
		default: printSpaces(19); cout << "Please enter a valid option!" << endl;
			goto enter;
			break;
		}
	} while (true);
}