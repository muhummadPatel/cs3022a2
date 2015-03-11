#include <iostream>
#include <sstream>

#include "volImage.h"

void handleInvalidArgs(){
    using namespace std;
    
    ostringstream oss;
    oss << "Usage: ";
    oss << "./volimage <imageBase> ";
    oss << "[-d sliceI sliceJ output_file_name] ";
    oss << "[-x slice output_file_name] ";
    oss << "[-g row output_file_name]";
    
    cout << oss.str() << endl;
}

int main(int argc, char* argv[]){
    using namespace ptlmuh006;
    
    VolImage vi;
    if(argc < 2){
        handleInvalidArgs();
        
    }else if(argc == 2){
        //just load data and exit
        std::cout << "load data and exit" << std::endl;
        bool success = vi.readImages(argv[1]);
        if(!success){
            std::cout << "Error reading in data." << std::endl;
            return 1;
        }
        
    }else{
        bool success = vi.readImages(argv[1]);
        if(!success){
            std::cout << "Error reading in data." << std::endl;
            return 1;
        }
        
        //handle flags        
        std::string flag = std::string(argv[2]);
        
        if(flag == "-d" && argc == 6){
            int sliceI = std::stoi(argv[3]);
            int sliceJ = std::stoi(argv[4]);
            std::string output_prefix = argv[5];
            
            vi.diffmap(sliceI, sliceJ, output_prefix);
            
            std::cout << "Difference-map between slice ";
            std::cout << sliceI << " and " << sliceJ;
            std::cout << " computed and written to ";
            std::cout << output_prefix << ".dat and ";
            std::cout << output_prefix << ".raw." << std::endl;
            
        }else if(flag == "-x" && argc == 5){
            int slice = std::stoi(argv[3]);
            std::string output_prefix = argv[4];
            
            vi.extract(slice, output_prefix);
            
            std::cout << "Extracted slice " << slice;
            std::cout << " and wrote it to ";
            std::cout << output_prefix << ".dat and ";
            std::cout << output_prefix << ".raw." << std::endl;
            
        }else if(flag == "-g" && argc == 5){
            int row = std::stoi(argv[3]);
            std::string output_prefix = argv[4];
            
            vi.extractRow(row, output_prefix);
            
            std::cout << "Extracted row " << row;
            std::cout << " across all slices and wrote it to ";
            std::cout << output_prefix << ".dat and ";
            std::cout << output_prefix << ".raw." << std::endl;
            
        }else{
            handleInvalidArgs();
        }
    }
    
    return 0;
}
