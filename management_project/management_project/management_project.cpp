#include <iostream>
#include <string>
#include <nanodbc.h>
#include <exception>
#include <vector>
#include "Structures.h"

using namespace std;

string enterText();
int enterInt();

vector<USER> getUsers(nanodbc::connection conn);
void getAllUsers(nanodbc::connection conn);
void insertUser(nanodbc::connection conn);
void editUserById(nanodbc::connection conn, const int& id);
bool deleteUserById(nanodbc::connection conn, const int& id);


vector<TEAM> getTeams(nanodbc::connection conn)
{
	vector<TEAM> teams;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Teams]
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		TEAM team;
		team.id = result.get<int>("Id");
		team.teamName = result.get<nanodbc::string>("TeamName", "");
		team.projectId = result.get<int>("ProjectId");
		team.dateOfCreation = result.get<nanodbc::string>("DateOfCreation", "");
		team.idOfCreator = result.get<int>("IdOfCreator");
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
	const string teamName = enterText();
	statement.bind(0, teamName.c_str());

	cout << "Enter the assigned project id: ";
	const int projectId = enterInt();
	statement.bind(1, &projectId);

	cout << "Enter your id: ";
	const int creatorId = enterInt();
	statement.bind(3, &creatorId);
	statement.bind(5, &creatorId);

	execute(statement);
}

void editTeamById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE [ProjectManagement].[dbo].[Teams]
        SET    
            Title = ?, 
			IdLastChange = ?,
			DateLastChange = GETDATE()
		WHERE	
			Id = ?
    )"));



	cout << "Enter the title: ";
	const string title = enterText();
	statement.bind(0, title.c_str());

	cout << "Enter your id: ";
	const int modifierId = enterInt();
	statement.bind(1, &modifierId);

	statement.bind(3, &id);

	execute(statement);
}

bool deleteTeamById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        DELETE 
            FROM [ProjectManagement].[dbo].[Teams]
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
		getAllUsers(conn);
		//editUserById(conn, 3);

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
