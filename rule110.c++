
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> simple_func (int ticks, std::string binary_string);

int main(int argc, char* argv[]){

    if (argc !=4){
        std::cout << "Error with the amount of arguments" <<std::endl;
    }

    std::string infile_name = argv[1];
    std::string outfile_name = argv[2];
    std::string option = argv[3];

    std::ifstream infile(infile_name);

    std::vector<std::string> content;
    if (infile.good()){
        std::string line = "";
        while (std::getline(infile, line)){
            content.push_back(line);
        }
    }else{
        std::cout << "Error with the input file" << std::endl;
    }

    infile.close();

    int ticks = std::stoi(content[0]);
    std::string binary_string = "";
    if (argv[3] == "--simple"){
        std::string binary_string = content[1];
    }

    return 0;

}
