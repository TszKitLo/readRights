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

// check the string is allDigits or not
bool allDigits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); 
}

// find group name and id
group* findGroup(char* groupName){
	
	struct group* grp;


    grp = getgrnam(groupName);
    
    if(grp == NULL){
		bool isAllDigits = allDigits(groupName);
		
		if(isAllDigits){
			gid_t gid;
			gid = (gid_t)(std::stol(groupName));
			
			grp = getgrgid(gid);
		}
        
        if(grp == NULL || !isAllDigits){
            std::cout << groupName << ": no such group" << std::endl;
        }
        
        
    }
	
	return grp;
}

// find username and id
passwd* findUser(char* username){

	struct passwd *pwd;


	pwd = getpwnam(username);

	if(pwd == NULL) {
		bool isAllDigits = allDigits(username);
		
		if(isAllDigits){
			uid_t uid;
			uid = (uid_t)(std::stol(username));
			
			pwd = getpwuid(uid);
		}
		
		if(pwd == NULL || !isAllDigits){
			std::cout << username << ": no such user" << std::endl;
		}
		
		
	}
    
    

	return pwd;
	
}

void groupRights(group *grp, char* fileName){
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
    if (sb.st_mode & S_IFMT & S_IFDIR){
        isDir = true;
        
    }
    
    // check ownership
    if(sb.st_gid == grp->gr_gid){

        if (sb.st_mode & S_IRGRP){
            read = true;

        }
        
        if (sb.st_mode & S_IWGRP){
            write = true;

        }
        
        if (sb.st_mode & S_IXGRP){
            execute = true;

        }
    } else {

        if (sb.st_mode & S_IROTH){
            read = true;

        }
        
        if (sb.st_mode & S_IWOTH){
            write = true;

        }
        
        if (sb.st_mode & S_IXOTH){
            execute = true;

        }
    }
    
    // print result
    std::cout << "Members of the group " << grp->gr_name << " (GID " << grp->gr_gid << ")" << " can ";
    if(read && !write && !execute){
        std::cout << "list the content of the ";
    } else if (!read && write && !execute){
        std::cout << "modify the ";
    } else if (!read && !write && execute){
        std::cout << "search the ";
    } else if (read && write && !execute){
        std::cout << "list the content of and modify the ";
    } else if (read && !write && execute){
        std::cout << "list the content of and search the ";
    } else if (!read && write && execute){
        std::cout << "modify and search the ";
    } else if (read && write && execute){
        std::cout << "list the content of, modify, and search the ";
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
    if (sb.st_mode & S_IFMT & S_IFDIR){
        isDir = true;
        
    }
    
    // check ownership
    if(sb.st_uid == pwd->pw_uid){

        if (sb.st_mode & S_IRUSR){
            read = true;

        }
        
        if (sb.st_mode & S_IRUSR){
            write = true;

        }
        
        if (sb.st_mode & S_IXUSR){
            execute = true;

        }
    } else {

        if (sb.st_mode & S_IROTH){
            read = true;

        }
        
        if (sb.st_mode & S_IWOTH){
            write = true;

        }
        
        if (sb.st_mode & S_IXOTH){
            execute = true;

        }
    }
    
    // print result
    std::cout << "The user " << pwd->pw_name << " (UID " << pwd->pw_uid << ")" << " can ";
    if(read && !write && !execute){
        std::cout << "read the ";
    } else if (!read && write && !execute){
        std::cout << "write the ";
    } else if (!read && !write && execute){
        std::cout << "execute the ";
    } else if (read && write && !execute){
        std::cout << "read and write the ";
    } else if (read && !write && execute){
        std::cout << "read and execute the ";
    } else if (!read && write && execute){
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
				//access rights for each files
                groupRights(grp, argv[i]);
			}
		}
		
	} else {
		struct passwd *pwd = findUser(argv[1]);
		if(pwd != NULL){
			for(int i = 2; i <argc; i++){
				//access rights for each files
				userRights(pwd, argv[i]);
			}
		}
		

	}
    
    return 0;
}

