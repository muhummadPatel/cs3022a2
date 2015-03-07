#include <iostream>

#include "volImage.h"

int main(int argc, char* argv[]){
    using namespace ptlmuh006;
    
    VolImage vi;
    
    std::string base = argv[1];
    vi.readImages(base);
    
    return 0;
}
