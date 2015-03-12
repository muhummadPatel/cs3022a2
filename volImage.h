/*
 * Definition of the volimage class.
 * Muhummad Patel       PTLMUH006
 * 16 - March - 2015
 */

#ifndef VOLIMAGE_H
#define VOLIMAGE_H

#include <string>
#include <vector>

namespace ptlmuh006{

typedef unsigned char u_char;

/*
 The VolImage class loads and manipulates volumetric image data(eg. MRI scan 
 data). A vector of slices stores the data for each image in the sequence as
 a 2d unsigned char array.
*/
class VolImage{
    
    private:
        int width, height; //width and height of image stack
        std::vector<u_char **> slices; //data for each slice in order
        
    public:
        VolImage(); //default constructor
        ~VolImage(); //destructor
        
        //populate the object with images in stack and set member variables
        bool readImages(std::string baseName);
        
        //compute difference map and write out
        void diffmap(int sliceI, int sliceJ, std::string output_prefix);
        
        //extract slice sliceId and write to output
        void extract(int sliceId, std::string output_prefix);
        
        //extract an image along row i of the volume, across all slices
        void extractRow(int row, std::string output_prefix);
        
        //number of bytes used to store image data bytes and pointers
        //(ignore vector,. container, dims, etc.)
        int volImageSize(void);
};

}

#endif
