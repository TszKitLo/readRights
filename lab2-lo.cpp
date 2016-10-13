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
#include <cctype>
#include <algorithm> 

bool allDigits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); 
}

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

void findGroup(char* groupName){
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

long int findUser(char* username){

	struct passwd *pwd;

	if(allDigits(username)){
		uid_t uid;
		uid = (uid_t)(std::stol(username));

		pwd = getpwuid(uid);

		if(pwd != NULL){
			std::cout << "username: " << std::string(pwd->pw_name) << std::endl;
			std::cout << "uid:" << pwd->pw_uid << std::endl;
			return pwd->pw_uid;
		} else {
			std::cout << username << ": no such user" << std::endl;
			return -1;
		}

	} else {

		pwd = getpwnam(username);

		if(pwd != NULL){
			std::cout << "user name: " << std::string(pwd->pw_name) << std::endl;
			std::cout << "user id:" << pwd->pw_uid << std::endl;
			return pwd->pw_uid;
		} else {
			std::cout << username << ": no such user" << std::endl;
			return -1;
		}

	}

	
}

int main(int argc, char** argv)
{	
	long int id = 0;

	// check whether user provide enoguh arguments
	if(argc < 2){
		std::cout << "usage: ./access [ -g ] name file1 ..." << std::endl;
		return 1;
	}

	if((strcmp( argv[1], "-g") == 0 && argc < 4) || (strcmp( argv[1], "-g") != 0 && argc < 3)){
		std::cout << ": need at least one file or directory!" << std::endl;

	} else if(strcmp( argv[1], "-g") == 0){
		findGroup(argv[2]);
		if(id != -1){
			for(int i = 3; i <argc; i++){
				std::cout << argv[i] << std::endl;
				//access rights for each files
			}
		}
		
	} else {
		id = findUser(argv[1]);
		if(id != -1){
			for(int i = 2; i <argc; i++){
				std::cout << "file " << argv[i] << std::endl;
				//std::cout << "uid: " << (uid_t)id << std::endl; 
				//access rights for each files
			}
		}

	}
    
    return 0;
}

