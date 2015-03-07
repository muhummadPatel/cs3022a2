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
        int numslices;
        ifstream hdr(baseName + ".dat");
        hdr >> width;
        hdr >> height;
        hdr >> numslices;
        /*
        cout << "w " << width << endl;
        cout << "h " << height << endl;
        cout << "s " << slices << endl;
        */
        
        //for each slice
        //read into slice
        for(int slice = 0; slice < numslices; slice++){
            ostringstream oss;
            oss << baseName << slice << ".raw";
            ifstream slcfile(oss.str(), ios::binary);
            
            cout << oss.str() << endl;
            
            unsigned char ** rowsArr = new unsigned char * [height];
            for(int row = 0; row < height; row++){
            
                rowsArr[row] = new unsigned char [width];
                for(int col = 0; col < width; col++){
                    slcfile >> rowsArr[row][col];
                }
            }
            slcfile.close();            
            slices.push_back(rowsArr);
        }
        
        cout << "loaded: " << slices.size() << endl;
        
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
