#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "VolImage.h"

#define PRINT(x) std::cout << x;

CHNJAR003::VolImage::VolImage() : width(0), height(0){};

CHNJAR003::VolImage::~VolImage()
{

    for (int i = 0; i < slices.size(); i++) //Loop through all the individual 2D slices
    {
        for (int j = 0; j < height; j++) //Loop through the rows of each 2D slice
        {
            delete[] slices[i][j]; //Destroy each row
        }
        delete[] slices[i]; //Destroy the slice itself
    }
}

bool CHNJAR003::VolImage::readImages(std::string baseName)
{

    std::ifstream baseNameFile;
    //try to open the image base header file
    baseNameFile.open((baseName + ".data").c_str());

    if (!baseNameFile)
    {
        std::cerr << "File with base name: " << baseName << " could not be opened for reading.";
        return false;
    }
    else //was able to open the image base header file
    {
        CHNJAR003::VolImage::slices.clear();

        std::string line;
        getline(baseNameFile, line);

        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (getline(iss, token, ' '))
        {
            tokens.push_back(token);
        }

        /*
        for (std::string temp : tokens)
        {
            PRINT(temp + '\n');
        }*/

        baseNameFile.close();

        width = std::stoi(tokens[0]);
        height = std::stoi(tokens[1]);
        int numSlices = std::stoi(tokens[2]);

        //Loop through all the image slices - essentially the number of images
        for (int i = 0; i < numSlices; i++)
        {
            std::ifstream ifs;
            //open the image slice for binary reading
            ifs.open((baseName + std::to_string(i) + ".raw").c_str(), std::ios::in | std::ios::binary);

            //if was able to open the image for binary processing
            if (ifs.is_open())
            {
                //Create new slice element to add to the slices vector
                //Array of unsigned char pointers for the columns
                unsigned char **tempSliceCols = new unsigned char *[height];

                /*
                //temporary array to read in the binary data from the .raw file
                char *temp = new char[width];
                */
                //Process the rows of pixels of the .raw image
                for (int row = 0; row < height; row++)
                {

                    unsigned char *tempSliceRow = new unsigned char[width];
                    ifs.read((char *)tempSliceRow, width);
                    tempSliceCols[row] = tempSliceRow;
                }

                slices.push_back(tempSliceCols);
                ifs.close();

                /*PRINT("Slices size: ");
                PRINT(slices.size());
                PRINT("\n");*/
            }
            else
            {
                PRINT("Unable to process file: " + baseName + std::to_string(i));
            }
        }

        return true;
    }
}

void CHNJAR003::VolImage::extract(int sliceId, std::string output_prefix)
{
    PRINT("VolImage extract() method called. Extracting requested image slice.\n");

    int numSlices = slices.size();

    //If the sliceId is valid
    if ((sliceId >= 0) && (sliceId < numSlices))
    {
        //Pointer to temporarily store the reference to the slice
        unsigned char **tempSliceHolder = slices[sliceId];

        std::ofstream headerFile;
        headerFile.open((output_prefix + ".dat").c_str());
        headerFile << width << " " << height << " 1" << std::endl;
        headerFile.close();

        std::ofstream outputFile;
        outputFile.open((output_prefix + ".raw").c_str(), std::ios::binary | std::ios::out);
        PRINT("Writing extracted image slice to file: " + output_prefix + ".raw\n");
        for (int i = 0; i < height; i++)
        {
            outputFile.write((char *)tempSliceHolder[i], width);
        }

        outputFile.close();
        PRINT("Extract method finished extracting requested slice.\n");
    }
}

void CHNJAR003::VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix)
{
    PRINT("VolImage diffmap() method called. Computing difference map between requested image slices.\n");
    int numSlices = slices.size();
    //If the slice indices are valid
    if ((sliceI >= 0) && (sliceI < numSlices) && (sliceJ >= 0) && (sliceJ < numSlices))
    {
        unsigned char *tempDiffRow = new unsigned char[width];

        std::ofstream outputSliceRaw;
        outputSliceRaw.open((output_prefix + ".raw").c_str(), std::ios::binary | std::ios::out);
        PRINT("Writing computed difference map to file: " + output_prefix + ".raw\n");
        for (int r = 0; r < height; r++)
        {

            for (int c = 0; c < width; c++)
            {
                tempDiffRow[c] = (unsigned char)(abs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c]) / 2);
            }

            outputSliceRaw.write((char *)tempDiffRow, width);
        }
        outputSliceRaw.close();
        delete[] tempDiffRow;

        PRINT("Difference Map method finished computing difference map.\n");
    }
}

int CHNJAR003::VolImage::volImageSize(void)
{
    //Store the number of images in the slices vector
    int numImages = slices.size();
    PRINT("Number of images: " + std::to_string(numImages) + "\n");

    //Store the number of bytes required for a char pointer
    int byteSizeUnsignedCharPointer = sizeof(unsigned char *);

    //Calculate the total number of bytes required to store all the image data
    int numBytesRequired = numImages * height * width * byteSizeUnsignedCharPointer;

    return numBytesRequired;
}