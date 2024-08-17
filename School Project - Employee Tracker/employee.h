#pragma once

#include "user.h"


class employee : public user {

public:

	employee() {}

	employee(const userNamePass& userLogin, const std::string& emp_name, 
		const int& id, const int& accessLevel) {

		userLoginInfo = userLogin; 
		userFile.name = emp_name;
		userFile.userId = id;
		userAccessLevel = accessLevel;

	}

	void setTasks_OnTrack() { 

		bool& onTrack = userFile.tasks_OnTrack;
		
		onTrack == false ? onTrack = true : false; // just flips the bool state, true->false, false->true
	
	}

	static int getIdx_AndValidateInput(const std::string displayedText);
	static int options(user& activeUser);
	static void employeeAccess_loggedIn(user& activeUser);
	static void viewEmployeeFile(user& activeUser);

};