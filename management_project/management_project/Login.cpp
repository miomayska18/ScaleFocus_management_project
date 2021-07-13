#include <iostream>;
#include "Structures.h"
#include "nanodbc.h"
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