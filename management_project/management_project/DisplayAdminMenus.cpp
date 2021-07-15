#include <iostream>
#include "InsertFunctions.h"
using namespace std;

void displayAdminLogMenu()
{
	system("cls");
	cout << endl;
	cout << u8"█   █▀█ █▀▀   █▀▄▀█ ▄▀█ █▄ █ ▄▀█ █▀▀ █▀▀ █▀▄▀█ █▀▀ █▄ █ ▀█▀   █▀▄▀█ █▀▀ █▄ █ █ █" << endl;
	cout << u8"█▄▄ █▄█ █▄█   █ ▀ █ █▀█ █ ▀█ █▀█ █▄█ ██▄ █ ▀ █ ██▄ █ ▀█  █    █ ▀ █ ██▄ █ ▀█ █▄█" << endl;
	cout << endl << endl << endl;
	printSpaces(23); cout << u8"╔══════════════════════════════╗" << endl;
	printSpaces(25); cout << "1. Create log" << endl;
	printSpaces(25); cout << "2. Edit log" << endl;
	printSpaces(25); cout << "3. List all logs" << endl;
	printSpaces(25); cout << "4. Delete log" << endl;
	printSpaces(25); cout << "5. List logs of certain task" << endl;
	printSpaces(25); cout << "0. Exit" << endl;
	printSpaces(23); cout << u8"╚══════════════════════════════╝" << endl;
}

void displayAdminTaskMenu()
{
	system("cls");
	cout << endl;
	cout << u8"▀█▀ ▄▀█ █▀ █▄▀   █▀▄▀█ ▄▀█ █▄ █ ▄▀█ █▀▀ █▀▀ █▀▄▀█ █▀▀ █▄ █ ▀█▀   █▀▄▀█ █▀▀ █▄ █ █ █" << endl;
	cout << u8" █  █▀█ ▄█ █ █   █ ▀ █ █▀█ █ ▀█ █▀█ █▄█ ██▄ █ ▀ █ ██▄ █ ▀█  █    █ ▀ █ ██▄ █ ▀█ █▄█" << endl;
	cout << endl << endl << endl;
	printSpaces(26); cout << u8"╔══════════════════════════╗" << endl;
	printSpaces(33); cout << "1. Create task" << endl;
	printSpaces(33); cout << "2. Edit task" << endl;
	printSpaces(33); cout << "3. List all tasks" << endl;
	printSpaces(33); cout << "4. Delete task" << endl;
	printSpaces(33); cout << "5. Logs" << endl;
	printSpaces(33); cout << "0. Exit" << endl;
	printSpaces(26); cout << u8"╚══════════════════════════╝" << endl;
}

void displayAdminProjectManagementMenu()
{
	system("cls");
	cout << endl;
	cout << u8"█▀█ █▀█ █▀█   █ █▀▀ █▀▀ ▀█▀   █▀▄▀█ ▄▀█ █▄ █ ▄▀█ █▀▀ █▀▀ █▀▄▀█ █▀▀ █▄ █ ▀█▀   █▀▄▀█ █▀▀ █▄ █ █ █" << endl;
	cout << u8"█▀▀ █▀▄ █▄█ █▄█ ██▄ █▄▄  █    █ ▀ █ █▀█ █ ▀█ █▀█ █▄█ ██▄ █ ▀ █ ██▄ █ ▀█  █    █ ▀ █ ██▄ █ ▀█ █▄█" << endl;
	cout << endl << endl << endl;
	printSpaces(38); cout << u8"╔═════════════════════════════╗" << endl;
	printSpaces(40); cout << "1. Create project" << endl;
	printSpaces(40); cout << "2. Edit project" << endl;
	printSpaces(40); cout << "3. List all projects" << endl;
	printSpaces(40); cout << "4. Delete project" << endl;
	printSpaces(40); cout << "5. Assign a team to a project" << endl;
	printSpaces(40); cout << "6. Tasks & logs" << endl;
	printSpaces(40); cout << "0. Exit" << endl;
	printSpaces(38); cout << u8"╚═════════════════════════════╝" << endl;
}

void displayAdminTeamMenu()
{
	system("cls");
	cout << endl;
	cout << u8"▀█▀ █▀▀ ▄▀█ █▀▄▀█   █▀▄▀█ ▄▀█ █▄ █ ▄▀█ █▀▀ █▀▀ █▀▄▀█ █▀▀ █▄ █ ▀█▀   █▀▄▀█ █▀▀ █▄ █ █ █" << endl;
	cout << u8" █  ██▄ █▀█ █ ▀ █   █ ▀ █ █▀█ █ ▀█ █▀█ █▄█ ██▄ █ ▀ █ ██▄ █ ▀█  █    █ ▀ █ ██▄ █ ▀█ █▄█" << endl;
	cout << endl << endl << endl;
	printSpaces(26); cout << u8"╔══════════════════════════╗" << endl;
	printSpaces(29); cout << "1. Create team" << endl;
	printSpaces(29); cout << "2. Edit team" << endl;
	printSpaces(29); cout << "3. List all teams" << endl;
	printSpaces(29); cout << "4. Delete team" << endl;
	printSpaces(29); cout << "5. Add a user to a team" << endl;
	printSpaces(29); cout << "0. Exit" << endl;
	printSpaces(26); cout << u8"╚══════════════════════════╝" << endl;
}

void displayAdminUserMenu()
{
	system("cls");
	cout << endl;
	cout << u8"█ █ █▀ █▀▀ █▀█   █▀▄▀█ ▄▀█ █▄ █ ▄▀█ █▀▀ █▀▀ █▀▄▀█ █▀▀ █▄ █ ▀█▀   █▀▄▀█ █▀▀ █▄ █ █ █" << endl;
	cout << u8"█▄█ ▄█ ██▄ █▀▄   █ ▀ █ █▀█ █ ▀█ █▀█ █▄█ ██▄ █ ▀ █ ██▄ █ ▀█  █    █ ▀ █ ██▄ █ ▀█ █▄█" << endl;
	cout << endl << endl << endl;
	printSpaces(26); cout << u8"╔══════════════════════════╗" << endl;
	printSpaces(32); cout << "1. Create user" << endl;
	printSpaces(32); cout << "2. Edit user" << endl;
	printSpaces(32); cout << "3. List all users" << endl;
	printSpaces(32); cout << "4. Delete user" << endl;
	printSpaces(32); cout << "0. Exit" << endl;
	printSpaces(26); cout << u8"╚══════════════════════════╝" << endl;
}

void displayAdminMenu()
{
	system("cls");
	cout << endl;
	printSpaces(12); cout << u8" ▄▀█ █▀▄ █▀▄▀█ █ █▄ █   █▀▄▀█ █▀▀ █▄ █ █ █" << endl;
	printSpaces(12); cout << u8" █▀█ █▄▀ █ ▀ █ █ █ ▀█   █ ▀ █ ██▄ █ ▀█ █▄█" << endl;
	cout << endl << endl << endl;
	printSpaces(19); cout << u8"╔══════════════════════════╗" << endl;
	printSpaces(23); cout << "1. Users operations" << endl;
	printSpaces(23); cout << "2. Teams opeartions" << endl;
	printSpaces(23); cout << "3. Projects operations" << endl;
	printSpaces(23); cout << "0. Exit" << endl;
	printSpaces(19); cout << u8"╚══════════════════════════╝" << endl;
}

void goodbyeMessage()
{
	system("cls");
	cout << endl << endl;
	printSpaces(12); cout << u8" ██████╗  ██████╗  ██████╗ ██████╗     ██████╗ ██╗   ██╗███████╗" << endl;
	printSpaces(12); cout << u8"██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗    ██╔══██╗╚██╗ ██╔╝██╔════╝" << endl;
	printSpaces(12); cout << u8"██║  ███╗██║   ██║██║   ██║██║  ██║    ██████╔╝ ╚████╔╝ █████╗  " << endl;
	printSpaces(12); cout << u8"██║   ██║██║   ██║██║   ██║██║  ██║    ██╔══██╗  ╚██╔╝  ██╔══╝  " << endl;
	printSpaces(12); cout << u8"╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝    ██████╔╝   ██║   ███████╗" << endl;
	printSpaces(12); cout << u8" ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝     ╚═════╝    ╚═╝   ╚══════╝" << endl;
	cout << endl << endl << endl << endl << endl;
}