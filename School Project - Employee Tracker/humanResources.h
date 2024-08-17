#pragma once

#include "management.h"


class humanResources : public user {

public:

	humanResources() {}

	humanResources(const userNamePass& loginInfo, const std::string& name_, const int& ID, const int& accessLevel) {

		userLoginInfo = loginInfo;
		userFile.name = name_;
		userFile.userId = ID;
		userAccessLevel = accessLevel;

	}

	static void hr_AccessLoggedIn(user& activeUser, std::map<int, user>& users);
	static const std::string getLine(const std::string displayedText);

};