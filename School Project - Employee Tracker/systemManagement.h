#pragma once

#include "humanResources.h"


class systemManagement {

public:

	user& activeUser;

	systemManagement(humanResources& admin) :

		activeUser{ admin }

	{ users[0] = admin; }

	void access();

private:

	// mapping id to user for fast checks

	std::map<int, user> users;

	int login() const;
	bool ifLogin() const;
	bool validateUserLogin(const std::string& username, const std::string& password, const userNamePass* storedLogin) const;

};