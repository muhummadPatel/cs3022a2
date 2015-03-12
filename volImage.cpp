/*
 * Implementation of the volimage class.
 * Muhummad Patel       PTLMUH006
 * 16 - March - 2015
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "volImage.h"

namespace ptlmuh006{

    using namespace std;
    
    //Constructor for volimage class. Initialises width and height to 0.
    VolImage::VolImage(){
        width = 0;
        height = 0;
    }
    
    //Destructor for volimage class. Cleans up all dynamically allocated memory
    //created by this class, and prints out the size (in bytes) that was used to
    //store the volumetric image data.
    VolImage::~VolImage(){
        //compute size used to store the image data
        int size = sizeof(slices);
        for(int i = 0; i < slices.size(); i++){
            size += sizeof(u_char **);
            for(int row = 0; row < height; row++){
                size += sizeof(u_char *);
                size += (sizeof(u_char) * width);
            }
        }
        
        std::cout << "Number of images: " << slices.size() << std::endl;
        std::cout << "Number of bytes required: " << size << std::endl;
        
        //Cleaning up dynamically allocated memory
        for(int i = 0; i < slices.size(); i++){
            u_char ** rowsArr = slices[i];
            for(int row = 0; row < height; row++){
                delete [] rowsArr[row];
            }
            delete [] rowsArr;
        }
        
        slices.clear();
    }
    
    //Loads image data from specified files into slices vector. Returns true if
    //the data was successfully loaded and false otherwise.
    bool VolImage::readImages(std::string baseName){
        //Read in header file
        int numslices;
        ifstream hdr(baseName + ".dat");
        hdr >> width >> height >> numslices;
        cout << "w " << width << endl;
        cout << "h " << height << endl;
        cout << "s " << numslices << endl;
        hdr.close();
        
        //Read in slices
        for(int slice = 0; slice < numslices; slice++){
            //generating filename for next image in the sequence
            ostringstream oss;
            oss << baseName << slice << ".raw";
            
            //open file as binary file and read in each row
            ifstream slcfile(oss.str(), ios::binary);
            if(slcfile){
                u_char ** rowsArr = new u_char * [height];
                
                for(int row = 0; row < height; row++){
                    rowsArr[row] = new u_char [width];
                    slcfile.read((char*)rowsArr[row], (sizeof(u_char) * width));
                }
                slcfile.close();
                slices.push_back(rowsArr); 
            }else{
                //File could not be opened successfully.
                return false;
            }
        }
        
        //All image data successfully loaded.
        return true;
    }
    
    //Extracts the specified slice of data and writes it to a .dat and a .raw
    //file with prefixes as specified by output_prefix
    void VolImage::extract(int sliceId, std::string output_prefix){
        //Write header file
        ofstream hdr(output_prefix + ".dat");
        hdr << width << " " << height << " " << 1 << endl;
        hdr.close();
        
        //Write extracted slice to raw output file one row at a time
        ofstream out(output_prefix + ".raw", ios::binary);
        for(int row = 0; row < height; row++){
            out.write((char *)slices[sliceId][row], (sizeof(u_char) * width));
        }
        out.close();
    }
    
    //Produces a .dat and a .raw file that illustrate the difference between
    //sliceI and sliceJ. Ouputs the diffmap to the file.
    void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
        //Write header file
        ofstream hdr(output_prefix + ".dat");
        hdr << width << " " << height << " " << 1 << endl;
        hdr.close();
        
        //Compute the diffmap of the two slices
        u_char ** diffmapArr = new u_char * [height];
        for(int row = 0; row < height; row++){
            diffmapArr[row] = new u_char [width];
            for(int col = 0; col < width; col++){
                diffmapArr[row][col] = (u_char)(abs((float)slices[sliceI][row][col] - (float)slices[sliceJ][row][col])/2);
            }
        }
        
        //Write the diffmap data to the output .raw file one row at a time
        ofstream out(output_prefix + ".raw", ios::binary);
        for(int row = 0; row < height; row++){
            out.write((char *)diffmapArr[row], (sizeof(u_char) * width));
        }
        out.close();
        
        //Clean up memory allocated in this method
        for(int row = 0; row < height; row++){
            delete [] diffmapArr[row];
        }
        delete [] diffmapArr;
    }
    
    //Extracts the specified row from across all slices and generates a .dat and
    //a .raw file with this information.
    void VolImage::extractRow(int row, std::string output_prefix){
        //Write header file
        ofstream hdr(output_prefix + ".dat");
        hdr << width << " " << slices.size() << " " << 1 << endl;
        hdr.close();
        
        //Extract the specified row from all the slices
        u_char ** extracted = new u_char * [slices.size()];
        int currRow = 0;
        for(int slice = 0; slice < slices.size(); slice++){
            u_char ** rowsArr = slices[slice];
            extracted[currRow] = rowsArr[row];
            currRow++;
        }
        
        //Write extracted rows to output .raw file
        ofstream out(output_prefix + ".raw", ios::binary);
        for(int row = 0; row < slices.size(); row++){
            out.write((char *)extracted[row], (sizeof(u_char) * width));
        }
        out.close();
        
        //Clean up memory allocated in this method
        delete [] extracted;
    }
    
    //Helper method used for testing. My computer won't let me install numpy
    //and so cannot run the given test script (viewer.py). This method converts
    //a slice to an ascii art representation and writes it to cout. If you 
    //redirect this to a text file and open it in a text editor (eg. Gedit) and 
    //scale the font waaay down, you will see the image that was stored in the 
    //slice.
    void printSlice(u_char** slice, int width, int height){
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

}
