#include <iostream>

#include "volImage.h"

int main(int argc, char* argv[]){
    using namespace ptlmuh006;
    
    for(int i = 1; i < argc; i++){
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
    
    VolImage vi;
    return 1;
}
