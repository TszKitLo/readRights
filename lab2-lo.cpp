/*
	Tsz Kit Lo (912404574)
	ECS 153
	Lab 2
*/


#include <iostream>
#include <cstring>
#include <pwd.h>
#include <grp.h>
#include <sstream>

void findGroup(char* groupName, char* file){
	group* grp;
	

	grp = getgrnam(groupName);

	if(grp != NULL){
		std::cout << "not null" << std::endl;
	} else {
		// convert char* to unsigned int
		std::stringstream tempStr;
		tempStr << groupName;
		unsigned int gid;
		tempStr >> gid;
		std::cout << "in null" << std::endl;
		grp = getgrgid(((gid_t)gid));
	}

	

	std::cout << "in group" << std::endl;
}

void findUser(char* user, char* file){
	passwd* pwd;
	pwd = getpwnam(user);
	if(pwd == NULL)
		std::cout << "null" << std::endl;
	std::cout << "in user" << std::endl;
}

int main(int argc, char** argv)
{	
	// check whether user provide enoguh arguments
	if(argc < 3){
		std::cout << "Invalid input" << std::endl;
		return 1;
	}

	(strcmp( argv[1], "-g") == 0) ? findGroup(argv[2],argv[3]) : findUser(argv[1],argv[2]);
    
    return 0;
}

