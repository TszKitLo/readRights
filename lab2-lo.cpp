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
#include <string>

unsigned int charToUnsInt(char* name){
	//std::stringstream tempStr;
	//tempStr << name;
	unsigned int id;
	//tempStr >> id;
	try{
		id = std::stol(name);
	}
	catch(...){
		std::cout << name << ": no such user" << std::endl;
	}
	
	
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
	struct passwd *pwd;
	pwd = getpwnam(username);

	if(pwd != NULL){
		std::cout << "username not null" << std::endl;
		std::cout << pwd->pw_uid << std::endl;
	} else {
		
		uid_t id;
		
		try{
			// convert char* to uid_t
			id = (uid_t)(std::stol(username));
			std::cout << id << std::endl;
			pwd = getpwuid(id);
		}
		catch(...){
			std::cout << username << ": no such user" << std::endl;
			return;
		}
		
		if(pwd == NULL){
			std::cout << "uid null" << std::endl;
			
			return;
		}
			
		std::cout << std::string(pwd->pw_name) << std::endl;
	}

	

	std::cout << "in user" << std::endl;
}

int main(int argc, char** argv)
{	
	// check whether user provide enoguh arguments
	if(argc < 2){
		std::cout << "usage: ./access [ -g ] name file1 ..." << std::endl;
		return 1;
	}

	if((strcmp( argv[1], "-g") == 0 && argc < 4) || (strcmp( argv[1], "-g") != 0 && argc < 3)){
		std::cout << ": need at least one file or directory!" << std::endl;
	} else {
		findUser(argv[1],argv[2]);
	}
    
    return 0;
}

