
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char* argv[]){

    if (argc !=4){
        std::cout << "Error" <<std::endl;
    }

    std::string infile_name = argv[1];
    std::string outfile_name = argv[2];
    std::string option = argv[3];

    std::ifstream infile(infile_name);

    std::string content;
    if (infile.good()){
        infile >> content;
    }

    infile.close();

    return 0;
}