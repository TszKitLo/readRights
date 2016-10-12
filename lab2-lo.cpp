#include <iostream>
#include <cstring>


void group(){
	std::cout << "in group" << std::endl;;
}

void user(){
	std::cout << "in user" << std::endl;;
}

int main(int argc, char** argv)
{	
	if(argc < 3){
		std::cout << "Invalid input" << std::endl;
		return 1;
	}

	(strcmp( argv[1], "-g") == 0) ? group() : user();
    
    return 0;
}

