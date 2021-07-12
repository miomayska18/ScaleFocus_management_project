#include <iostream>
#include <string>
#include <nanodbc.h>
#include <exception>
#include <vector>
#include "Structures.h"
#include "UserCRUD.h"

using namespace std;

string enterText();
int enterInt();


vector<TEAM> getTeams(nanodbc::connection conn);
void getAllTeams(nanodbc::connection conn);
void insertTeam(nanodbc::connection conn);
void editTeamById(nanodbc::connection conn, const int& id);
bool deleteTeamById(nanodbc::connection conn, const int& id);

vector<PROJECT> getProjects(nanodbc::connection conn)
{
	vector<PROJECT> projects;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Projects]
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		PROJECT project;
		project.id = result.get<int>("Id");
		project.name = result.get<nanodbc::string>("Name", "");
		project.description = result.get<nanodbc::string>("Description", "");
		project.ownerId = result.get<int>("OwnerId");
		project.dateOfCreation = result.get<nanodbc::string>("DateCreation", "");
		project.idOfCreator = result.get<int>("IdCreator");
		project.dateLastChange = result.get<nanodbc::string>("DateLastChange", "");
		project.idLastChange = result.get<int>("IdLastChange");

		projects.push_back(project);
	}

	return projects;
}

void getAllProjects(nanodbc::connection conn)
{
	vector<PROJECT> projects = getProjects(conn);

	for (size_t i = 0; i < projects.size(); i++)
	{
		projects[i].displayProject();
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
		getAllUsers(conn);
		//editUserById(conn, 3);

		//insertTeam(conn);
		//getAllTeams(conn);
		//editTeamById(conn, 1);

		//getAllProjects(conn);

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
