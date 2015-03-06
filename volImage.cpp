#include <iostream>

#include "volImage.h"

namespace ptlmuh006{

    VolImage::VolImage(){
        std::cout << "volimage constructor" << std::endl;
        width = 0;
        height = 0;
    }
    
    VolImage::~VolImage(){}

}
