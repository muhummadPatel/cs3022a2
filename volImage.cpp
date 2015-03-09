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
        //cout << "VolImage()" << endl;
        width = 0;
        height = 0;
    }
    
    VolImage::~VolImage(){
        //cout << "~VolImage() "<< slices.size() << endl;
        for(int i = 0; i < slices.size(); i++){
            //cout << "destruct slice " << i << endl;
            unsigned char ** rowsArr = slices[i]; 
            for(int row = 0; row < height; row++){
                //cout << "del ";
                delete [] rowsArr[row];
            }
            
            //cout << "del ";
            delete [] rowsArr;
        }
       // cout << endl;
        slices.clear();
        //cout << slices.size() << endl;
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
            
            //cout << oss.str() << endl;
            
            //cout << "new ";
            unsigned char ** rowsArr = new unsigned char * [height];
            for(int row = 0; row < height; row++){
            
                //cout << "new ";
                rowsArr[row] = new unsigned char [width];
                slcfile.read((char*)rowsArr[row], (sizeof(unsigned char) * width));
                
            }
            //cout << endl;
            slcfile.close();
            slices.push_back(rowsArr);
            
            //for(int row = 0; row < height; row++){
            //    delete[] rowsArr[row];
            //}
            //delete [] rowsArr;
        }
        
        //cout << "loaded: " << slices.size() << endl;
        //printSlice(slices[3], width, height);
        //cout << sizeof(unsigned char) << endl;
        
        return true;
    }
    
    void VolImage::extract(int sliceId, std::string output_prefix){
        //write header file for extracted slice
        ofstream hdr(output_prefix + ".dat");//, ios::trunc);
        hdr << width << " " << height << " " << 1 << endl;
        hdr.close();
        
        //write extracted slice to output file
        ofstream out(output_prefix + ".raw", ios::binary); //| ios::trunc);
        for(int row = 0; row < height; row++){
            out.write((char *)slices[sliceId][row], (sizeof(unsigned char) * width));
        }
        out.close();
        
        cout << "written" << endl;
    }
    
    void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
        ostringstream prefix;
        prefix << output_prefix << "_diff_" << sliceI << "_" << sliceJ;
        
        ofstream hdr(prefix.str() + ".dat");//, ios::trunc);
        hdr << width << " " << height << " " << 1 << endl;
        hdr.close();
        
        unsigned char ** diffmapArr = new unsigned char * [height];
        for(int row = 0; row < height; row++){
            diffmapArr[row] = new unsigned char [width];
            for(int col = 0; col < width; col++){
                diffmapArr[row][col] = (unsigned char)(abs((float)slices[sliceI][row][col] - (float)slices[sliceJ][row][col])/2);
            }
        }
        
        ofstream out(prefix.str() + ".raw", ios::binary); //| ios::trunc);
        for(int row = 0; row < height; row++){
            out.write((char *)diffmapArr[row], (sizeof(unsigned char) * width));
        }
        out.close();
        
        for(int row = 0; row < height; row++){
            delete [] diffmapArr[row];
        }
        delete [] diffmapArr;
        
        cout << "diffmapped" << endl;
    }
    
    void VolImage::
    extractRow(int row, std::string output_prefix){
        ostringstream prefix;
        prefix << output_prefix << "_extractRow_" << row;
        
        ofstream hdr(prefix.str() + ".dat");//, ios::trunc);
        //TODO: check that the height really is slices.size()
        hdr << width << " " << slices.size() << " " << 1 << endl;
        hdr.close();
        
        unsigned char ** extracted;
        for(int slice = 0; slice < slices.size(); slice++){
             extracted[slice] = slices[slice][row];
        }
        
        //write extracted data to output file
        ofstream out(prefix.str() + ".raw", ios::binary); //| ios::trunc);
        for(int slice = 0; slice < slices.size(); slice++){
            for(int row = 0; row < height; row++){
                out.write((char *)extracted[slice]
                , (sizeof(unsigned char) * width));
            }
        }
        out.close();
        
        cout << "written" << endl;
    }

}
