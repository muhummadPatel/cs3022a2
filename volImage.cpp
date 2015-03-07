#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "volImage.h"

namespace ptlmuh006{

    using namespace std;
    
    void printSlice(unsigned char** slice, int width, int height){
        for(int row = 0; row < height; row++){
            for(int col = 0; col < width; col++){        
                int val = (int)slice[row][col];
                char intensity;
                if (val < 28) {
			        intensity = '.';
		        } else if (val < 56) {
			        intensity = ':';
		        } else if (val < 85) {
			        intensity = '-';
		        } else if (val < 113) {
			        intensity = '=';
		        } else if (val < 141) {
			        intensity = '+';
		        } else if (val < 170) {
			        intensity = '*';
		        } else if (val < 198) {
			        intensity = '#';
		        } else if (val < 226) {
			        intensity = '%';
		        } else if (val < 255) {
			        intensity = '@';
		        }
		        
		        cout << intensity << " ";
            }
            cout << endl;
        }
    }

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
        hdr >> width >> height >> numslices;
        cout << "w " << width << endl;
        cout << "h " << height << endl;
        cout << "s " << numslices << endl;
        
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
                slcfile.read((char*)rowsArr[row], (sizeof(unsigned char) * width));
                /*
                for(int col = 0; col < width; col++){
                    slcfile >> rowsArr[row][col];
                }
                */
            }
            slcfile.close();            
            slices.push_back(rowsArr);
        }
        
        cout << "loaded: " << slices.size() << endl;
        printSlice(slices[4], width, height);
        cout << sizeof(unsigned char) << endl;
        
        return true;
    }

}
