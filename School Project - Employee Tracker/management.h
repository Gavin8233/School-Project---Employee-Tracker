#pragma once

#include "employee.h"


class management : public user {

public:

	management() {}

	management(const userNamePass& loginInfo, const std::string& name_, const int& ID, const int& accessLevel) {

		userLoginInfo = loginInfo;

		userFile.name = name_;

		userFile.userId = ID;

		userAccessLevel = accessLevel;

	}

	static user* getUser(std::map<int, user>& users);

	static void view(const int& activeUserId, const std::map<int, user>& users);
	static void viewTasks(user* selectedUser);
	static void management_loggedIn(user& activeUser, std::map<int, user>& users);

};

