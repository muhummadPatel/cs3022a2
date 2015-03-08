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
        cout << "~VolImage() "<< slices.size() << endl;
        for(int i = 0; i < slices.size(); i++){
            cout << "destruct slice " << i << endl;
            unsigned char ** rowsArr = slices[i]; 
            for(int row = 0; row < height; row++){
                cout << "del ";
                delete [] rowsArr[row];
            }
            
            cout << "del ";
            delete [] rowsArr;
        }
        cout << endl;
        slices.clear();
        cout << slices.size() << endl;
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
        hdr.close();
        
        //for each slice
        //read into slice
        
        
        for(int slice = 0; slice < numslices; slice++){
            ostringstream oss;
            oss << baseName << slice << ".raw";
            ifstream slcfile(oss.str(), ios::binary);
            
            cout << oss.str() << endl;
            
            cout << "new ";
            unsigned char ** rowsArr = new unsigned char * [height];
            for(int row = 0; row < height; row++){
            
                cout << "new ";
                rowsArr[row] = new unsigned char [width];
                slcfile.read((char*)rowsArr[row], (sizeof(unsigned char) * width));
                
            }
            cout << endl;
            slcfile.close();
            slices.push_back(rowsArr);
            
            //for(int row = 0; row < height; row++){
            //    delete[] rowsArr[row];
            //}
            //delete [] rowsArr;
        }
        
        cout << "loaded: " << slices.size() << endl;
        //printSlice(slices[4], width, height);
        cout << sizeof(unsigned char) << endl;
        
        return true;
    }

}
