#include <iostream>
#include "Structures.h"
#include <nanodbc.h>
#include <vector>
#include <string>
#include "InsertFunctions.h"
using namespace std;

vector<TEAM> getTeams(nanodbc::connection conn)
{
	vector<TEAM> teams;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Teams]
		WHERE
			IsDeleted<>1
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		TEAM team;
		team.id = result.get<int>("Id");
		team.teamName = result.get<nanodbc::string>("TeamName", "");
		team.projectId = result.get<int>("ProjectId");
		team.dateOfCreation = result.get<nanodbc::string>("DateCreation", "");
		team.idOfCreator = result.get<int>("IdCreator");
		team.dateLastChange = result.get<nanodbc::string>("DateLastChange", "");
		team.idLastChange = result.get<int>("IdLastChange");

		teams.push_back(team);
	}

	return teams;
}

void getAllTeams(nanodbc::connection conn)
{
	vector<TEAM> teams = getTeams(conn);

	for (size_t i = 0; i < teams.size(); i++)
	{
		printSpaces(2); cout << u8"╔═════════════════════════════════════════════════════════════╗" << endl << endl;
		teams[i].displayTeam();
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

void insertTeam(nanodbc::connection conn, USER& user)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            [ProjectManagement].[dbo].[Teams]
            (TeamName, ProjectId, DateCreation, IdCreator, DateLastChange, IdLastChange)
            VALUES
            (?, ?, GETDATE(), ?, GETDATE(), ?)
    )"));

	printSpaces(4); cout << "Enter the team's name: ";
	const string teamName = enterText(true);
	statement.bind(0, teamName.c_str());

	printSpaces(4); cout << "Enter the assigned project id: ";
	const int projectId = enterInt();
	statement.bind(1, &projectId);

	//cout << "Enter your id: ";
	//const int creatorId = enterInt();
	statement.bind(2, &user.id);
	statement.bind(3, &user.id);

	execute(statement);
}

void editTeamById(nanodbc::connection conn, const int& id, USER& user)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE [ProjectManagement].[dbo].[Teams]
        SET    
            TeamName = ?, 
			IdLastChange = ?,
			DateLastChange = GETDATE()
		WHERE	
			Id = ?
    )"));



	printSpaces(4); cout << "Enter the team's new name: ";
	const string name = enterText(true);
	statement.bind(0, name.c_str());

	//cout << "Enter your id: ";
	//const int modifierId = enterInt();
	statement.bind(1, &user.id);

	statement.bind(2, &id);

	execute(statement);
}

void deleteTeamById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE 
           Teams
		SET
			IsDeleted = 1
        WHERE 
			Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);
}

void insertUserIntoTeam(nanodbc::connection conn, const int& teamId)
{
	system("cls");
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            [ProjectManagement].[dbo].[UsersTeams]
            (UserId, TeamId)
            VALUES
            (?, ?)
    )"));

enter:
	cout << "Enter the id of the user you want to add to this team: ";
	const int& userId = enterInt();

	statement.bind(0, &userId);
	statement.bind(1, &teamId);

	execute(statement);

	system("cls");
	int choice;
	cout << "What do you want to do now?" << endl;
	cout << "Enter 1 to add another user to this team" << endl;
	cout << "Enter 0 to get back to the menu " << endl;
exit:
	cout << "Enter your choice: ";
	choice = enterInt();
	switch (choice)
	{
	case 0: return;
		break;
	case 1: goto enter;
		break;
	default: cout << "Please enter a valid option!" << endl;
		goto exit;
		break;
	}
}
