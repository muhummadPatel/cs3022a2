#include <iostream>

#include "volImage.h"

int main(int argc, char* argv[]){
    using namespace ptlmuh006;
    
    {
    VolImage vi;
    
    std::string base = argv[1];
    vi.readImages(base);
    }
    
    /*
    for(int i =0; i < 100; i++){
        std::cout << "yo ";
    }
    std::cout << std::endl;
    */
    
    return 0;
}
