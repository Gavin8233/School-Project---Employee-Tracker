#include "employee.h"

static void ignoreInput(const std::string displayedText) {

	std::cout << displayedText;

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

int employee::getIdx_AndValidateInput(const std::string displayedText) {

	int userId = 0;

	while (true) {

		std::cout << displayedText;
		std::cin >> userId;

		if (std::cin.fail()) {

			ignoreInput("\nInvalid input, only integers allowed\n");

			continue;

		}

		if (std::cin.get() == '\n') { return userId; }

		ignoreInput("\nNo extra characters allowed, type a valid integer\n");

	}

	return 0;

}

static const std::string returnTasks_TrueOrFalse(const employeeFile& userFile) {

	return userFile.tasks_OnTrack == true ? "true" : "false";

}

void employee::viewEmployeeFile(user& activeUser) {

	std::cout << "NAME: " << activeUser.userFile.name << "; ID: " << activeUser.userFile.userId;
	std::cout << "\nTASKS ON TRACK: " << returnTasks_TrueOrFalse(activeUser.userFile) << "\n\n";

	for (const std::string& task : activeUser.userFile.employeeTasks) {

		std::cout << "- " << task << "\n";

	}

}

int employee::options(user& activeUser) {

	int userChoice = getIdx_AndValidateInput("\n--TYPE -1 TO LOGOUT--\n\n1.) View info\n\nChoose option: ");

	switch (userChoice) {

	case -1:

		return -1;

	case 1:
		
		viewEmployeeFile(activeUser);

		break;

	default:

		std::cout << "\nNot valid choice\n";

		break;

	}

	return 0;

}

void employee::employeeAccess_loggedIn(user& activeUser) {

	std::cout << "\nWelcome, " << activeUser.userFile.name << ".\n\n";

	while(options(activeUser) != -1) {  }

}