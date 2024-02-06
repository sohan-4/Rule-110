
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int on_or_off(int a, int b, int c){
    
    if (a==1 && b==1 && c==1){
        return 0;
    }else if (a==1 && b==1 && c==0){
        return 1;
    }else if (a==1 && b==0 && c==1){
        return 1;
    }else if (a==1 && b==0 && c==0){
        return 0;
    }else if (a==0 && b==1 && c==1){
        return 1;
    }else if (a==0 && b==1 && c==0){
        return 1;
    }else if (a==0 && b==0 && c==1){
        return 1;
    }else if (a==0 && b==0 && c==0){
        return 0;
    }

    return -1;
}

std::vector<std::string> gen_itr (int ticks, std::string binary_string){
    std::vector<std::string> automatons;
    const int START = 1;
    const int END = binary_string.size()-2;
    for (int i = 0; i < ticks; i++){
        std::string automaton;
        for (int j = 0; j < binary_string.size(); j++){
            automaton+="0";
        }
        for (int j = START; j <= END; j++){
            int a = binary_string[j-1] - '0';
            int b = binary_string[j] - '0';
            int c = binary_string[j+1] - '0';
            int new_val = on_or_off(a, b, c);
            if (new_val == -1){
                std::cout<<"Error with the binary string"<<std::endl;
            }
            if (new_val == 1){
                automaton[j] = '1';
            }
        }
        automatons.push_back(automaton);
        binary_string = automaton;
    }

    return automatons;
}

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
    if (option == "--simple"){
        std::ofstream outfile(outfile_name, std::ios::out);
        for (int i = 1; i < content.size(); i++){
            std::string binary_string = (content[i]);
            std::vector<std::string> results = gen_itr(ticks, binary_string);
            if (outfile.good()){
                outfile<<"String-"<<i<<"\n";
                outfile<<"Tick-0="<<binary_string<<"\n";
                for (int i = 0; i < results.size(); i++){
                    outfile<<"Tick-"<<i+1<<"="<<results[i]<<"\n";
                }
                outfile.flush();
            }else{
                std::cout<< "Error with the output file" << std::endl;
            }
        }
        outfile.close();
    }else if (option == "--fancy"){
        std::string blank = "□";
        std::string hit = "■";

        std::ofstream outfile(outfile_name, std::ios::out);
        std::vector<std::vector<std::string>> results; //a vector which contains vectors of each line and it's iterations
        for (int i = 1; i < content.size(); i++){
            results.push_back(gen_itr(ticks, content[i]));
        }

        for (int i = 0; i < ticks; i++){
            if (outfile.good()){
                outfile<<"Tick-"<<i+1<<"\n";
                for (int j = 0; j < results.size(); j++){
                    std::string binary_string = results[j][i];
                    for (int k = 0; k < binary_string.size(); k++){
                        if (binary_string[k] == '1'){
                            outfile<<hit;
                        }else{
                            outfile<<blank;
                        }
                    }
                    outfile<<"\n";
                }
            }else{
                std::cout<< "Error with the output file" << std::endl;
            }
        }
        outfile.flush();
        outfile.close();
    }

    return 0;

}
