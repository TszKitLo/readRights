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

unsigned int charToUnsInt(char* name){
	std::stringstream tempStr;
	tempStr << name;
	unsigned int id;
	tempStr >> id;
	return id;
}

void findGroup(char* groupName, char* file){
	group* grp;
	grp = getgrnam(groupName);

	if(grp != NULL){
		std::cout << "group name not null" << std::endl;
	} else {
		// convert char* to unsigned int
		unsigned int gid = charToUnsInt(groupName);

		grp = getgrgid(((gid_t)gid));
		if(grp == NULL){
			std::cout << "gid null" << std::endl;
			return;
		}
			
		std::cout << "gid not null" << std::endl;
	}

	

	std::cout << "in group" << std::endl;
}

void findUser(char* username, char* file){
	passwd* pwd;
	pwd = getpwnam(username);

	if(pwd != NULL){
		std::cout << "username not null" << std::endl;
	} else {
		// convert char* to unsigned int
		unsigned int uid = charToUnsInt(username);

		pwd = getpwuid(((uid_t)uid));
		if(pwd == NULL){
			std::cout << "uid null" << std::endl;
			return;
		}
			
		std::cout << "uid not null" << std::endl;
	}

	

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

