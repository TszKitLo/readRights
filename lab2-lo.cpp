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
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool allDigits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); 
}

// find group name and id
group* findGroup(char* groupName){
	
	struct group* grp;

//	if(allDigits(groupName)){
//		gid_t gid;
//		gid = (gid_t)(std::stol(groupName));
//
//		grp = getgrgid(gid);
//
//		if(grp != NULL){
//			std::cout << "groupName: " << std::string(grp->gr_name) << std::endl;
//			std::cout << "gid:" << grp->gr_gid << std::endl;
//			
//		} else {
//			std::cout << groupName << ": no grp" << std::endl;
//			
//		}
//
//	} else {
//
//		grp = getgrnam(groupName);
//
//		if(grp != NULL){
//			std::cout << "group name: " << std::string(grp->gr_name) << std::endl;
//			std::cout << "group id:" << grp->gr_gid << std::endl;
//			
//		} else {
//			std::cout << groupName << ": no grp" << std::endl;
//			
//		}
//
//	}
    grp = getgrnam(groupName);
    
    if(grp != NULL){
        
        std::cout << "group name: " << std::string(grp->gr_name) << std::endl;
        std::cout << "group id:" << grp->gr_gid << std::endl;
        
    } else {
        gid_t gid;
        gid = (gid_t)(std::stol(groupName));
        std::cout << "gid: " << gid << std::endl;
        grp = getgrgid(gid);
        if(grp != NULL){
            std::cout << "group name: " << std::string(grp->gr_name) << std::endl;
            std::cout << "group id:" << grp->gr_gid << std::endl;
            
        } else {
            std::cout << groupName << ": no GRP (no such group)" << std::endl;
        }
        
        
    }
	
	return grp;
}

// find username and id
passwd* findUser(char* username){

	struct passwd *pwd;

//	if(allDigits(username)){
//		uid_t uid;
//		uid = (uid_t)(std::stol(username));
//
//		pwd = getpwuid(uid);
//		
//
//		if(pwd != NULL){
//			std::cout << "username: " << std::string(pwd->pw_name) << std::endl;
//			std::cout << "uid:" << pwd->pw_uid << std::endl;
//			
//		} else {
//
//			std::cout << username << ": no pwd" << std::endl;
//			
//		}
//
//	} else {
//        
//		pwd = getpwnam(username);
//		
//		if(pwd != NULL){
//
//			std::cout << "user name: " << std::string(pwd->pw_name) << std::endl;
//			std::cout << "user id:" << pwd->pw_uid << std::endl;
//			
//		} else {
//            
//			std::cout << username << ": no PWD" << std::endl;
//			
//		}
//
//	}
    
            pwd = getpwnam(username);
    
    		if(pwd != NULL){
    
    			std::cout << "user name: " << std::string(pwd->pw_name) << std::endl;
    			std::cout << "user id:" << pwd->pw_uid << std::endl;
    
    		} else {
                uid_t uid;
                uid = (uid_t)(std::stol(username));
                std::cout << "uid: " << uid << std::endl;
                pwd = getpwuid(uid);
                if(pwd != NULL){
                    std::cout << "user name: " << std::string(pwd->pw_name) << std::endl;
                    std::cout << "user id:" << pwd->pw_uid << std::endl;
                
                } else {
                    std::cout << username << ": no PWD (no such user)" << std::endl;
                }
    			
    			
    		}
    
    

	return pwd;
	
}

void groupRights(group *grp, char* fileName){
    struct stat sb;
    
    if(stat(fileName, &sb) != 0){
        std::cout << fileName << ": no such file or directory" << std::endl;
        return;
    }
}

void userRights(passwd *pwd, char* fileName){
    bool isDir = false;
    bool read = false;
    bool write = false;
    bool execute = false;
    
	struct stat sb;
	
    // check file existence
	if(stat(fileName, &sb) != 0){
		std::cout << fileName << ": no such file or directory" << std::endl;
		return;
	}
    
    // check whether it is a file or directory
    mode_t test = (sb.st_mode & S_IFMT);
    
    if (test & S_IFDIR){
        isDir = true;
        
    }
    
    // check ownership
    if(sb.st_uid == pwd->pw_uid){
        if (test & S_IRUSR){
            read = true;
        }
        
        if (test & S_IRUSR){
            write = true;
        }
        
        if (test & S_IXUSR){
            execute = true;
        }
    } else {
        if (test & S_IROTH){
            read = true;
        }
        
        if (test & S_IWOTH){
            write = true;
        }
        
        if (test & S_IXOTH){
            execute = true;
        }
    }
    
    // print result
    std::cout << "The user " << pwd->pw_name << " (UID " << pwd->pw_uid << ")" << " can ";
    if(read){
        std::cout << "read the ";
    } else if (write){
        std::cout << "write the ";
    } else if (execute){
        std::cout << "execute the ";
    } else if (read && write){
        std::cout << "read and write the ";
    } else if (read && execute){
        std::cout << "read and execute the ";
    } else if (write && execute){
        std::cout << "write and execute the ";
    } else if (read && write && execute){
        std::cout << "read, write, and execute the ";
    } else {
        std::cout << "do nothing with the ";
    }
    if(isDir){
        std::cout << "directory ";
    } else {
        std::cout << "file ";
    }
    std::cout << fileName << std::endl;
	
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
                groupRights(grp, argv[i]);
			}
		}
		
	} else {
		struct passwd *pwd = findUser(argv[1]);
		if(pwd != NULL){
			for(int i = 2; i <argc; i++){
				std::cout << "file " << argv[i] << std::endl;
				//std::cout << "uid: " << (uid_t)id << std::endl; 
				//access rights for each files
				userRights(pwd, argv[i]);
			}
		}
		

	}
    
    return 0;
}

