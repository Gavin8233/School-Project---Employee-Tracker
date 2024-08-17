#include "humanResources.h"


struct employeeBasicInfo {

	std::string name;
	int userID;

};


const std::string humanResources::getLine(const std::string displayedText) {

	std::cout << displayedText;

	std::string userInput;
	std::getline(std::cin >> std::ws, userInput);

	return userInput;

}


// code below is for new user creation

static userNamePass getNewUsernamePass() {

	const std::string username = humanResources::getLine("Employee username: ");
	const std::string password = humanResources::getLine("Employee password: ");

	return { username, password };

}

static int getNewId(const std::map<int, user>& users, int& userId) {

	userId = employee::getIdx_AndValidateInput("\nNew ID: ");

	if (users.count(userId)) { std::cout << "\nId already taken\n"; return -1; }

	return userId;

}

static employeeBasicInfo getNewEmployeeInfo(const std::map<int, user>& users) {

	const std::string employeeName = humanResources::getLine("\nNew user; Government name: ");
	int userId = 0;

	while (getNewId(users, userId) == -1) {} // gets user id until a valid option is chosen

	return { employeeName, userId };

}


// add employees

template<typename position> static void addT(position& currPos, std::map<int, user>& users, const int accessLevel) {

	employeeBasicInfo newEmployeeInfo = getNewEmployeeInfo(users);
	const std::string& name = newEmployeeInfo.name;
	const int& id = newEmployeeInfo.userID;

	currPos = { getNewUsernamePass(), name, id, accessLevel };

	users[id] = currPos;

}

static void addEmployee(std::map<int, user>& users) {

	employee newEmployee;

	addT(newEmployee, users, 0);

}

static void addManager(std::map<int, user>& users) {

	management newManager;

	addT(newManager, users, 1);

}

static void addHumanResources(std::map<int, user>& users) {

	humanResources newHr;

	addT(newHr, users, 2);

}


// view and search functions

static void view(const int& userID, const std::map<int, user>& users) {

	management::view(userID, users);

}

static void updateTasks(user* selectedUser, std::map<int, user>& users) {

	if (selectedUser->userAccessLevel > 0) {

		std::cout << "\nSelected user is not an employee, only employees have tasks\n";

		return;

	}

	const std::string newTask = humanResources::getLine("\nType task: ");

	selectedUser->userFile.employeeTasks.push_back(newTask);

}

static void updateInformation(user* selectedUser, std::map<int, user>& users) {

	const employeeBasicInfo newInfo = getNewEmployeeInfo(users);

	if (users.find(selectedUser->userFile.userId) != users.end()) {

		user updatedUser = *selectedUser;

		users.erase(selectedUser->userFile.userId);

		updatedUser.userFile.name = newInfo.name;
		updatedUser.userFile.userId = newInfo.userID;

		users[newInfo.userID] = updatedUser;

	}

}

static void modifyUserInfo(user* selectedUser, std::map<int, user>& users) {

	int userChoice = employee::getIdx_AndValidateInput(
		"\n--TYPE -1 TO EXIT--\n1.) Change name and id\n2.) Update tasks\n\nChoose option: ");

	switch (userChoice) {

	case 1:

		updateInformation(selectedUser, users);

		break;

	case 2:

		updateTasks(selectedUser, users);

		break;

	default:

		std::cout << "\nNot valid choice\n";

		break;

	}

}

static user* getUser(std::map<int, user>& users) {

	return management::getUser(users);

}

static void searchAndModify(const user& activeUser, std::map<int, user>& users) {

	user* selectedUser = getUser(users);

	if (selectedUser == nullptr || selectedUser->userFile.userId == activeUser.userFile.userId) { std::cout << "\nInvalid ID\n"; return; }

	int userChoice = employee::getIdx_AndValidateInput(
		"\n--TYPE -1 TO EXIT--\n1.) Delete user\n2.) Modify user info\n3.) View tasks\nChoose option: ");

	switch (userChoice) {

	case 1:

		users.erase(selectedUser->userFile.userId);

		return;

	case 2:

		modifyUserInfo(selectedUser, users);

		break;

	case 3:

		management::viewTasks(selectedUser);

		break;

	default:

		std::cout << "\nNot valid choice\n";

	}

}

static int options(user& activeUser, std::map<int, user>& users) {

	int userChoice = employee::getIdx_AndValidateInput(
		"\n--TYPE -1 TO LOGOUT--\n1.) View employees\n2.) Add employee\n3.) Add manager\n4.) Add Human Resources\n5.) Search for and modify employee(by id)\n\nChoose option : ");

	switch (userChoice) {

	case -1:  // exit case

		return -1; 

	case 1:

		view(activeUser.userFile.userId, users);

		break;

	case 2:

		addEmployee(users);

		break;

	case 3:

		addManager(users);

		break;

	case 4:

		addHumanResources(users);

		break;

	case 5:

		searchAndModify(activeUser, users);

		break;

	default:

		std::cout << "\nNot valid choice\n";

		break;

	}

	return 0;

}

void humanResources::hr_AccessLoggedIn(user& activeUser, std::map<int, user>& users) {

	std::cout << "\nWelcome, " << activeUser.userFile.name << ".\n\n";

	while (options(activeUser, users) != -1) {  } // user does what they want until exit command is typed

}