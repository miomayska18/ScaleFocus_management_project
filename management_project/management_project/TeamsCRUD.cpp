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
		teams[i].displayTeam();
		cout << endl;
	}

}

void insertTeam(nanodbc::connection conn)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            [ProjectManagement].[dbo].[Teams]
            (TeamName, ProjectId, DateCreation, IdCreator, DateLastChange, IdLastChange)
            VALUES
            (?, ?, GETDATE(), ?, GETDATE(), ?)
    )"));

	cout << "Enter the team's name: ";
	const string teamName = enterText(false);
	statement.bind(0, teamName.c_str());

	cout << "Enter the assigned project id: ";
	const int projectId = enterInt();
	statement.bind(1, &projectId);

	cout << "Enter your id: ";
	const int creatorId = enterInt();
	statement.bind(2, &creatorId);
	statement.bind(3, &creatorId);

	execute(statement);
}

void editTeamById(nanodbc::connection conn, const int& id)
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



	cout << "Enter the team's new name: ";
	const string name = enterText(false);
	statement.bind(0, name.c_str());

	cout << "Enter your id: ";
	const int modifierId = enterInt();
	statement.bind(1, &modifierId);

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
