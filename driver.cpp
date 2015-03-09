#include <iostream>
#include <vector>

#include "volImage.h"

int main(int argc, char* argv[]){
    using namespace ptlmuh006;
    
    //TODO: here be old codes
    VolImage vi;
    
    std::string base = "MRI";//argv[1];
    vi.readImages(base);
    
    //vi.extract(4, "extracted");
    //vi.diffmap(2, 3, "diffed");
    vi.extractRow(150, "rEXtr");
    
    
    //new code
    if(argc < 2){
        //invalid usage
        std::cout << "invalid usage" << std::endl;
    }else if(argc == 2){
        //just load data and exit
        std::cout << "load data and exit" << std::endl;
    }else{
        std::cout << "handle flags" << std::endl;
        
        std::string flag = std::string(argv[2]);
        if(flag == "-d"){
            std::cout << "OPT diffmap" << std::endl;
        }else if(flag == "-x"){
            std::cout << "OPT extract" << std::endl;
        }else{
            //invalid usage
            std::cout << "nvalid usage" << std::endl;
        }
    }
    
    return 0;
}
