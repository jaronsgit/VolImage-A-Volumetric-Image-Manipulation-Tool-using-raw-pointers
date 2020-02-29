# C++ Assignment 2: VolImage: A Volumetric Image Manipulation Tool using raw pointers

The project includes VolImage.h, VolImage.cpp, driver.cpp, as well as a Makefile.

VolImage.h is the header file for function declarations.
VolImage.cpp contains all the definitions for the functions that operate the processing of the raw images.
driver.cpp is the source file that parses the command line arguments and calls the necessary methods.

## How to use the program

In order to use the program/run the executable, the MRI ".raw" files must be placed in the brain_mri_raws directory along with their corresponding ".data" header file.

The processed images that are output by the program are placed into the brain_mri_raws_output directory.

### The structure of the command line execution is as follows:

```bash
 volimage <imageBase> [-d i j output_file_name] [-x i output_file_name]
```

For example, and imageBase named "scan" would have a file “scan.dat” (the header file)
and a sequence of images numbered as follows: “scan0.raw”, “scan1.raw”, “scan2.raw” etc.

1. -d i j output_file_name: compute a difference map between images i and j, and write
   this out to file (note: we index files from 0, see below).
2. -x i output_file_name: extract and write the slice with number i and write this out
   to file.
3. -g i output_file_name: extracts an image along row i of the volume, across all slices, and write this out as above.

Navigate to the folder in Terminal and utilise the provided Makefile to compile the source code using:

```bash
make
```

The following command can be used to run the executable with the imageBase of "MRI" and no optional flags.

```bash
make run
```

Use the following command to remove the binary files from the project folder as well as any previously processed and outputted .raw and .dat files in the brain_mri_raws_output folder.

```bash
make clean
```

## Authors

**CHNJAR003**
