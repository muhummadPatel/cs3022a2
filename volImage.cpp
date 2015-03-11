#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
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
        width = 0;
        height = 0;
    }
    
    VolImage::~VolImage(){
        int size = sizeof(slices);
        for(int i = 0; i < slices.size(); i++){
            size += sizeof(unsigned char **);
            for(int row = 0; row < height; row++){
                size += sizeof(unsigned char *);
                size += (sizeof(unsigned char) * width);
            }
        }
        
        std::cout << "Number of images: " << slices.size() << std::endl;
        std::cout << "Number of bytes required: " << size << std::endl;
        
        for(int i = 0; i < slices.size(); i++){
            unsigned char ** rowsArr = slices[i]; 
            for(int row = 0; row < height; row++){
                delete [] rowsArr[row];
            }
            delete [] rowsArr;
        }
        
        slices.clear();
    }
    
    bool VolImage::readImages(std::string baseName){
        int numslices;
        ifstream hdr(baseName + ".dat");
        hdr >> width >> height >> numslices;
        cout << "w " << width << endl;
        cout << "h " << height << endl;
        cout << "s " << numslices << endl;
        hdr.close();
        for(int slice = 0; slice < numslices; slice++){
            ostringstream oss;
            oss << baseName << slice << ".raw";
            ifstream slcfile(oss.str(), ios::binary);
            
            if(slcfile){
                unsigned char ** rowsArr = new unsigned char * [height];
                for(int row = 0; row < height; row++){
                
                    rowsArr[row] = new unsigned char [width];
                    slcfile.read((char*)rowsArr[row], (sizeof(unsigned char) * width));
                    
                }
                slcfile.close();
                slices.push_back(rowsArr); 
            }else{
                return false;
            }
        }
        
        return true;
    }
    
    void VolImage::extract(int sliceId, std::string output_prefix){
        //write header file for extracted slice
        ofstream hdr(output_prefix + ".dat");
        hdr << width << " " << height << " " << 1 << endl;
        hdr.close();
        
        //write extracted slice to output file
        ofstream out(output_prefix + ".raw", ios::binary);
        for(int row = 0; row < height; row++){
            out.write((char *)slices[sliceId][row], (sizeof(unsigned char) * width));
        }
        out.close();
    }
    
    void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
        ofstream hdr(output_prefix + ".dat");
        hdr << width << " " << height << " " << 1 << endl;
        hdr.close();
        
        unsigned char ** diffmapArr = new unsigned char * [height];
        for(int row = 0; row < height; row++){
            diffmapArr[row] = new unsigned char [width];
            for(int col = 0; col < width; col++){
                diffmapArr[row][col] = (unsigned char)(abs((float)slices[sliceI][row][col] - (float)slices[sliceJ][row][col])/2);
            }
        }
        
        ofstream out(output_prefix + ".raw", ios::binary);
        for(int row = 0; row < height; row++){
            out.write((char *)diffmapArr[row], (sizeof(unsigned char) * width));
        }
        out.close();
        
        for(int row = 0; row < height; row++){
            delete [] diffmapArr[row];
        }
        delete [] diffmapArr;
    }
    
    void VolImage::extractRow(int row, std::string output_prefix){
        ofstream hdr(output_prefix + ".dat");
        hdr << width << " " << slices.size() << " " << 1 << endl;
        hdr.close();
        
        unsigned char ** extracted = new unsigned char * [slices.size()];
        int currRow = 0;
        for(int slice = 0; slice < slices.size(); slice++){
            unsigned char ** rowsArr = slices[slice];
            extracted[currRow] = rowsArr[row];
            currRow++;
        }
        
        //write extracted slice to output file
        ofstream out(output_prefix + ".raw", ios::binary);
        for(int row = 0; row < slices.size(); row++){
            out.write((char *)extracted[row], (sizeof(unsigned char) * width));
        }
        out.close();
        
        delete [] extracted;
    }

}
