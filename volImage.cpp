#include <iostream>
#include <fstream>
#include <sstream>

#include "volImage.h"

namespace ptlmuh006{

    using namespace std;

    VolImage::VolImage(){
        //cout << "VolImage()" << endl;
        width = 0;
        height = 0;
    }
    
    VolImage::~VolImage(){
        //cout << "~VolImage()" << endl;
    }
    
    bool VolImage::readImages(std::string baseName){
        //cout << "readImages(" << baseName << ")" << endl;
        
        //read dat file and get dimensions
        int slices;
        ifstream hdr(baseName + ".dat");
        hdr >> width;
        hdr >> height;
        hdr >> slices;
        /*
        cout << "w " << width << endl;
        cout << "h " << height << endl;
        cout << "s " << slices << endl;
        */
        
        //for each slice
        //read into slice
        for(int slice = 0; slice < slices; slices++){
            ostringstream oss;
            oss << baseName << slice << ".raw";
            ifstream s(oss.str());
            for(int row = 0; row < height; row++){
                for(int col = 0; col < width; col++){
                        
                }
            }
        }
        
        /*
        ifstream in(baseName, ios::binary);
        
        unsigned char item;
        int c = 0;
        while(in >> item){
            c++;
            cout << (int)item << " ";
            if(c % 429 == 0){
                cout << endl;
            }
        }
        in.close();
        */
        return true;
    }

}
