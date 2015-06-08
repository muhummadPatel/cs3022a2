**Author**	: Muhummad Yunus Patel
**Student#**	: PTLMUH006
**Date**		: 16-March-2015

##Assignment 2 - _Volimage_

###Description	: 
A description of what each file does and how it fits into the program follows:
1. volimage.h volimage.cpp:  
 These files follow the mandated structure set out in
 the assignment brief. They handle the reading, storage and manipulation of the
  volumetric image data. The image data is stored in a vector of 2d unsigned 
  char arrays. Note, that when the destructor is called, the number of bytes 
  used to store the images \(including pointers\) will be output to the console.

2. driver.cpp:  
 This file contains the main method and uses volimage.h and volimage.cpp to read
  in the volumetric image data specified by the command line arguments and 
  execute the option requested in the command line arguments. NOTE that the
   extra credit functionality has also been included. The command line argument 
   parsing happens here.

##Usage:
Note, only one operation can be performed at a time.
Please have the volumetric image data \(MRI.dat and MRI\<i\>.raw\) files in the same directory when running.
./volimage \<imageBase\> \[-d sliceI sliceJ output_file_name\] \[-x slice output_file_name\] \[-g row output_file_name\]

* To compile, simply type _make_.
* To run, _./volimage \<imageBase\> \[-d sliceI sliceJ output_file_name\] \[-x slice output_file_name\] \[-g row output_file_name\]_
* To clean up, type _make clean_.
