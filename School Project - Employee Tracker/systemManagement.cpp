#include "systemManagement.h"


bool systemManagement::validateUserLogin(const std::string& username, const std::string& password, const userNamePass* storedLogin) const {

	return username == storedLogin->username && password == storedLogin->userPassword;

}

int systemManagement::login() const {

	std::string username = humanResources::getLine("\n--TYPE (exit) TO CLOSE PROGRAM--\n\n - LOGIN - \n\nUSERNAME: ");
	if (username == "exit") { exit(0); }
	std::string password = humanResources::getLine("PASSWORD: ");

	int id = employee::getIdx_AndValidateInput("ID: ");

	if (!users.count(id)) {

		std::cout << "\nUser with id: " << id << " does not exist, try again!\n";
		
		return -1;
	
	} // if login fails(user id isnt in users), return -1 so other code knows it failed

	const userNamePass* storedInfo = users.at(id).getUserPass();

	if (!validateUserLogin(username, password, storedInfo)) { 
		
		std::cout << "\nUsername or Password was incorrect, try again!\n";

		return -1;
	
	};

	activeUser = users.at(id);

	return id;

}

bool systemManagement::ifLogin() const {

	int userId = login();

	return userId != -1 ? true : false; 

}


void systemManagement::access() {

	while (true) {

		while (!ifLogin()) {} // holds the user here until they correctly type information

		switch (activeUser.userAccessLevel) {

		case 0:

			employee::employeeAccess_loggedIn(activeUser);

			break;

		case 1:

			management::management_loggedIn(activeUser, users);

			break;

		case 2:

			humanResources::hr_AccessLoggedIn(activeUser, users);

			break;

		default:

			break; // accessLevel is a const int always 0-2, this should never run.

		}

	}

}