#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>


struct userNamePass {

	std::string username;
	std::string userPassword;

};

struct employeeFile {

	std::string name;
	int userId;
	std::vector<std::string> employeeTasks;
	bool tasks_OnTrack = false;

};

class user {

public:

	user() {}

	int userAccessLevel = 0;
	/*I'm defining userAccess as integers, 0 - 2. 0 being low level access, 1 being mid level, 2 being high level.
	This is for later use, I plan on using a switch statement that determines user access level and then gives
	according permissions*/

	employeeFile userFile;

	const userNamePass* getUserPass() const { return &userLoginInfo; }

protected:

	userNamePass userLoginInfo;

};