#include "management.h"


static const std::string getPosition(const int& accessLevel) {

	switch (accessLevel) {

	case 0:

		return "Employee";

	case 1:

		return "Manager";

	case 2:

		return "Human Resources";

	default:

		return "";

	}

	return "";

}

user* management::getUser(std::map<int, user>& users) {

	int desiredId = employee::getIdx_AndValidateInput("\nType desired user ID: ");

	if (users.count(desiredId)) { return &users.at(desiredId); }

	return nullptr;

}

void management::view(const int& activeUserId, const std::map<int, user>& users) {

	for (auto i = users.begin(); i != users.end(); i++) {

		if (i->first == activeUserId) { continue; }

		std::cout << "\nNAME: " << i->second.userFile.name << "; ID: " << i->second.userFile.userId <<
			"\nPOSITION: " << getPosition(i->second.userAccessLevel) << "\n";

	}

}

void management::viewTasks(user* selectedUser) {

	std::cout << "\n--" << selectedUser->userFile.name << "'s Tasks--\n";

	for (std::string& task : selectedUser->userFile.employeeTasks) {

		std::cout << "- " << task << "\n";

	}

}

static void viewDesiredTasks(std::map<int, user>& users) {

	user* selectedUser = management::getUser(users);

	management::viewTasks(selectedUser);

}

static int options(user& activeUser, std::map<int, user>& users) {

	int userChoice = employee::getIdx_AndValidateInput(
		"\n--TYPE -1 TO LOGOUT\n\n1.) View employees\n2.) View desired user tasks(by id)\n\nChoose option: ");

	switch (userChoice) {

	case -1:

		return -1;

	case 1:

		management::view(activeUser.userAccessLevel, users);

		break;

	case 2:

		viewDesiredTasks(users);

		break;

	default:

		std::cout << "\nNot valid choice\n";

		break;

	}

	return 0;

}

void management::management_loggedIn(user& activeUser, std::map<int, user>& users) {

	std::cout << "\nWelcome, " << activeUser.userFile.name << ".\n\n";

	while(options(activeUser, users) != -1) {  }

}
