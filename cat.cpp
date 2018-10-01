#include <iostream>
#include <fstream>
#include <string>
/*function to concatenate files and print out their contents on the screen*/

//this function opens the file and reads, prints out contents and closes files
void linereader(char *filename){
	std::ifstream infile(filename);

	//conditionals to safe check the file
		if (!infile.fail()){
				char character;
				//loop to read and write contents of file
				while(infile.get(character)){
					std::cout << character;
				}
				
				infile.close( );
		}//conditional to display if the file is not in the directory to ask input again
 		else{
			std::cerr << "cat: "<< filename << ": no such file or directory" << std::endl;
		}



}

//main funct to echo commmand line arguments and send them to the line reader funct
int main(int argc, char *argv[]) {
//conditional to set up if the command line is equal to 1 argument return 0
	if (argc == 1) {
		return 0;
	}
	//conditonal if anything else
	else{
		int i = 1;
		//loop iterating that if argc is < conter to send to argv and line reader funct
		while (i < argc) {
			//char * filename = argv[i];
			linereader(argv[i]);
		  i++;
		}
		return 0;
	}
}
