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

group* findGroup(char* groupName){
	
	struct group* grp;

	if(allDigits(groupName)){
		gid_t gid;
		gid = (gid_t)(std::stol(groupName));

		grp = getgrgid(gid);

		if(grp != NULL){
			std::cout << "groupName: " << std::string(grp->gr_name) << std::endl;
			std::cout << "gid:" << grp->gr_gid << std::endl;
			
		} else {
			std::cout << groupName << ": no such group" << std::endl;
			
		}

	} else {

		grp = getgrnam(groupName);

		if(grp != NULL){
			std::cout << "group name: " << std::string(grp->gr_name) << std::endl;
			std::cout << "group id:" << grp->gr_gid << std::endl;
			
		} else {
			std::cout << groupName << ": no such group" << std::endl;
			
		}

	}
	
	return grp;
}

passwd* findUser(char* username){

	struct passwd *pwd;

	if(allDigits(username)){
		uid_t uid;
		uid = (uid_t)(std::stol(username));

		pwd = getpwuid(uid);

		if(pwd != NULL){
			std::cout << "username: " << std::string(pwd->pw_name) << std::endl;
			std::cout << "uid:" << pwd->pw_uid << std::endl;
			
		} else {
			std::cout << username << ": no such user" << std::endl;
			
		}

	} else {

		pwd = getpwnam(username);

		if(pwd != NULL){
			std::cout << "user name: " << std::string(pwd->pw_name) << std::endl;
			std::cout << "user id:" << pwd->pw_uid << std::endl;
			
		} else {
			std::cout << username << ": no such user" << std::endl;
			
		}

	}

	return pwd;
	
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

	} else if(strcmp( argv[1], "-g") == 0){
		struct group* grp = findGroup(argv[2]);
		if(grp != NULL){
			for(int i = 3; i <argc; i++){
				std::cout << "file " << argv[i] << std::endl;
				//std::cout << "gid: " << (gid_t)id << std::endl; 
				//access rights for each files
			}
		}
		
	} else {
		struct passwd *pwd = findUser(argv[1]);
		if(pwd != NULL){
			for(int i = 2; i <argc; i++){
				std::cout << "file " << argv[i] << std::endl;
				//std::cout << "uid: " << (uid_t)id << std::endl; 
				//access rights for each files
			}
		}

	}
    
    return 0;
}

