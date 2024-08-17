/*HOW TO USE - When you first run the program, you'll see a login screen. Just type admin for the username, admin1
for the password, and 0 for the id. When you log in, you'll see many options and I won't go into detail as they 
are to be played with and see if the features work. All errors with user input will be handled. For input, type the 
number next to the option you desire. No bugs that I can find.*/

#include "systemManagement.h"


int main() {

	// putting admin in main file for readability and so my systemManagement constructor doesn't require extra code

	userNamePass defaultInfo = { "admin", "admin1" };
	std::string defaultName = "administrator";
	int defaultId = 0;
	const int accessLevel = 2;

	humanResources admin = { defaultInfo, defaultName, defaultId, accessLevel };

	systemManagement sm(admin);

	sm.access();

}